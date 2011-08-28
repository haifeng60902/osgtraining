#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <time.h>



#include "ogg/ogg.h"
#include "theora/theoraenc.h"

int video_q=48;
ogg_uint32_t keyframe_frequency=64;

int frame_w=0;
int frame_h=0;
int pic_w=384;
int pic_h=288;
int pic_x=0;
int pic_y=0;
int video_fps_n=25;
int video_fps_d=1;
int video_par_n=0;
int video_par_d=0;
int src_c_dec_h=2;
int src_c_dec_v=2;
int dst_c_dec_h=2;
int dst_c_dec_v=2;
char chroma_type[16];

/*The size of each converted frame buffer.*/
size_t y4m_dst_buf_sz;
/*The amount to read directly into the converted frame buffer.*/
size_t y4m_dst_buf_read_sz;
/*The size of the auxilliary buffer.*/
size_t y4m_aux_buf_sz;
/*The amount to read into the auxilliary buffer.*/
size_t y4m_aux_buf_read_sz;

int video_r=-1;

int ilog(unsigned _v){
	int ret;
	for(ret=0;_v;ret++)_v>>=1;
	return ret;
}

int fetch_and_process_video(FILE *video,ogg_page *videopage,
			ogg_stream_state *to,th_enc_ctx *td,FILE *twopass_file,int passno,
			int videoflag){
	ogg_packet op;
	int ret;
	/* is there a video page flushed?  If not, work until there is. */
	while(!videoflag){
		if(ogg_stream_pageout(to,videopage)>0) return 1;
		if(ogg_stream_eos(to)) return 0;
		int ret=0;//fetch_and_process_video_packet(video,twopass_file,passno,td,&op);
		if(ret<=0)return 0;
		ogg_stream_packetin(to,&op);
	}
	return videoflag;
}

int main()
{
	strcpy(chroma_type,"420");

////////////блок переменных OGG/THEORA//////////////////////////////////////////////
	//This structure contains current encode/decode data for a logical bitstream.
	ogg_stream_state oggStreamState;

	//This structure encapsulates data into one ogg bitstream page.
	ogg_page oggPage;

	//This structure encapsulates the data and metadata for a single Ogg packet.
	ogg_packet oggPacket;

	th_enc_ctx *thEncCtx=NULL;
	th_info thInfo;
	th_comment thComment;
	int passno=0;
	int videoflag=0;
	ogg_int64_t audio_bytesout=0;
	ogg_int64_t video_bytesout=0;
	double timebase;
//////////////////////////////////////////////////////////////////////////

///////////открываем файл для записи кодированного видео////////////////////////////
	FILE *outfile = stdout;
	_setmode( _fileno( stdin ), _O_BINARY );
	_setmode( _fileno( stdout ), _O_BINARY );

	outfile=fopen( "test.avi","wb");
//////////////////////////////////////////////////////////////////////////

/////////расчет размера буферов на основании ширины-высоты////////////////////////
	y4m_dst_buf_read_sz=pic_w*pic_h+2*((pic_w+1)/2)*((pic_h+1)/2);
	y4m_aux_buf_sz=y4m_aux_buf_read_sz=0;

	/*The size of the final frame buffers is always computed from the
         destination chroma decimation type.*/
     y4m_dst_buf_sz=pic_w*pic_h+2*((pic_w+dst_c_dec_h-1)/dst_c_dec_h)*
       ((pic_h+dst_c_dec_v-1)/dst_c_dec_v);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
	 /* Set up Ogg output stream */
	 srand(time(NULL));

	//This function is used to initialize an ogg_stream_state struct 
	//and allocates appropriate memory in preparation for encoding or decoding. 
	//It also assigns the stream a given serial number.
	//Parameters
	// os 
	//	 Pointer to the ogg_stream_state struct that we will be initializing. 
	// serialno 
	//	 Serial number that we will attach to this stream. 
	ogg_stream_init(&oggStreamState,rand());


	/* Theora has a divisible-by-sixteen restriction for the encoded frame size */
	/* scale the picture size up to the nearest /16 and calculate offsets */
	frame_w=pic_w+15&~0xF;
	frame_h=pic_h+15&~0xF;

	/*Force the offsets to be even so that chroma samples line up like we
       expect.*/
    pic_x=frame_w-pic_w>>1&~1;
    pic_y=frame_h-pic_h>>1&~1;

	/*
	Initializes a th_info structure. 
	This should be called on a freshly allocated th_info structure before attempting to use it. 
	Parameters:
	_info  The th_info struct to initialize.  
	*/
	th_info_init(&thInfo);

	//заполнение данными о размере видео
	thInfo.frame_width=frame_w;
    thInfo.frame_height=frame_h;
    thInfo.pic_width=pic_w;
    thInfo.pic_height=pic_h;
    thInfo.pic_x=pic_x;
    thInfo.pic_y=pic_y;
    thInfo.fps_numerator=video_fps_n;
    thInfo.fps_denominator=video_fps_d;
    thInfo.aspect_numerator=video_par_n;
    thInfo.aspect_denominator=video_par_d;
    thInfo.colorspace=TH_CS_UNSPECIFIED;

    /*Account for the Ogg page overhead.
      This is 1 byte per 255 for lacing values, plus 26 bytes per 4096 bytes for
       the page header, plus approximately 1/2 byte per packet (not accounted for
       here).*/
    thInfo.target_bitrate=(int)(64870*(ogg_int64_t)video_r>>16);
    thInfo.quality=video_q;
    thInfo.keyframe_granule_shift=ilog(keyframe_frequency-1);
    if(dst_c_dec_h==2){
      if(dst_c_dec_v==2)thInfo.pixel_fmt=TH_PF_420;
      else thInfo.pixel_fmt=TH_PF_422;
    }
    else thInfo.pixel_fmt=TH_PF_444;

/*
Allocates an encoder instance. 

Parameters:
	_info  A th_info struct filled with the desired encoding parameters.  

Returns:
	The initialized th_enc_ctx handle. 
Return values:
	NULL  If the encoding parameters were invalid.  
*/
	thEncCtx=th_encode_alloc(&thInfo);

/*
Clears a th_info structure. 
This should be called on a th_info structure after it is no longer needed. 

Parameters:
	_info  The th_info struct to clear.  
*/
	th_info_clear(&thInfo);

	/* setting just the granule shift only allows power-of-two keyframe
       spacing.  Set the actual requested spacing. */
	/*
	Encoder control function. 

	This is used to provide advanced control the encoding process. 

	Parameters:
	_enc  A th_enc_ctx handle.  
	_req  The control code to process. See the list of available control codes for details.  
	_buf  The parameters for this control code.  
	_buf_sz  The size of the parameter buffer.  
*/
    int ret=th_encode_ctl(thEncCtx,TH_ENCCTL_SET_KEYFRAME_FREQUENCY_FORCE,
     &keyframe_frequency,sizeof(keyframe_frequency-1));

    if(ret<0){
      fprintf(stderr,"Could not set keyframe interval to %d.\n",(int)keyframe_frequency);
    }

	/* write the bitstream header packets with proper page interleave */
/*
	Initialize a th_comment structure. 

	This should be called on a freshly allocated th_comment structure before attempting to use it. 

	Parameters:
	_tc  The th_comment struct to initialize.  
*/
	th_comment_init(&thComment);



	 /* first packet will get its own page automatically */
/*
Outputs the next header packet. 

This should be called repeatedly after encoder initialization until it returns 0 
in order to get all of the header packets, in order, before encoding actual video data. 

Parameters:
_enc  A th_enc_ctx handle.  
_comments  The metadata to place in the comment header, when it is encoded.  
_op  An ogg_packet structure to fill. All of the elements of this structure will be set, 
including a pointer to the header data. The memory for the header data is owned by libtheoraenc, 
and may be invalidated when the next encoder function is called.  

Returns:
A positive value indicates that a header packet was successfully produced. 
Return values:
0  No packet was produced, and no more header packets remain.  
TH_EFAULT  _enc, _comments, or _op was NULL.  
*/
	if(th_encode_flushheader(thEncCtx, &thComment,&oggPacket)<=0){
		fprintf(stderr,"Internal Theora library error.\n");
		exit(1);
	}

/*
This function submits a packet to the bitstream for page encapsulation. 
After this is called, more packets can be submitted, or pages can be written out.

In a typical encoding situation, this should be used after filling a packet with data. 
The data in the packet is copied into the internal storage managed by the ogg_stream_state, 
so the caller is free to alter the contents of os after this call has returned. 
*/
	ogg_stream_packetin(&oggStreamState,&oggPacket);

/*
This function forms packets into pages.
In a typical encoding situation, this would be called after using ogg_stream_packetin()
to submit data packets to the bitstream. Internally, this function assembles the accumulated 
packet bodies into an Ogg page suitable for writing to a stream.

This function will only return a page when a "reasonable" amount of packet data is available. 
Normally this is appropriate since it limits the overhead of the Ogg page headers in the bitstream, 
and so calling ogg_stream_pageout() after ogg_stream_packetin() should be the common case. 
Call ogg_stream_flush() if immediate page generation is desired. This may be occasionally necessary, 
for example, to limit the temporal latency of a variable bitrate stream.
*/
	if(ogg_stream_pageout(&oggStreamState, &oggPage)!=1){
		fprintf(stderr,"Internal Ogg library error.\n");
		exit(1);
	}
	fwrite(oggPage.header,1, oggPage.header_len,outfile);
	fwrite(oggPage.body,1 ,oggPage.body_len,outfile);




	/* create the remaining theora headers */
	for(;;){
		int ret=th_encode_flushheader( thEncCtx, &thComment, &oggPacket);
		if(ret<0){
			fprintf(stderr,"Internal Theora library error.\n");
			exit(1);
		}
		else if(!ret)break;
		if(passno!=1)ogg_stream_packetin(&oggStreamState,&oggPacket);
	}

	for(;;){
		int result = ogg_stream_flush(&oggStreamState, &oggPage);
		if(result<0){
			/* can't get here */
			fprintf(stderr,"Internal Ogg library error.\n");
			exit(1);
		}
		if(result==0)break;
		fwrite(oggPage.header,1, oggPage.header_len,outfile);
		fwrite(oggPage.body,1, oggPage.body_len,outfile);
	}

	for(;;){
		double videotime;
		ogg_page videopage;
		
		// is there a video page flushed?  If not, fetch one if possible
		videoflag=fetch_and_process_video(NULL,&videopage,&oggStreamState,thEncCtx,
			NULL,passno,videoflag);

		if(!videoflag)break;

		videotime=
			videoflag?th_granule_time(thEncCtx,ogg_page_granulepos(&videopage)):-1;

		/* flush a video page */
		video_bytesout+=fwrite(videopage.header,1,videopage.header_len,outfile);
		video_bytesout+=fwrite(videopage.body,1,videopage.body_len,outfile);
		videoflag=0;
		timebase=videotime;
	}

	th_encode_free(thEncCtx);

	ogg_stream_clear(&oggStreamState);
	th_comment_clear(&thComment);

	if(outfile && outfile!=stdout)fclose(outfile);
}