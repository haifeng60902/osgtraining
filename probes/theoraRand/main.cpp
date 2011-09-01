#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <time.h>



#include "ogg/ogg.h"
#include "theora/theoraenc.h"

int video_q=63;
ogg_uint32_t keyframe_frequency=2;

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
int src_c_dec_h=1;
int src_c_dec_v=1;
int dst_c_dec_h=1;
int dst_c_dec_v=1;
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

long begin_sec=-1;
long begin_usec=0;
long end_sec=-1;
long end_usec=0;

static int                 frame_state=-1;
static ogg_int64_t         frames=0;
static unsigned char      *yuvframe[3];
static th_ycbcr_buffer     ycbcr;

unsigned char    *frame;

float GetRand()
{
	//получить случайное число от 0 до 1
	return (float)rand()/(float)RAND_MAX;
}

//заполнить случайными цветаи
void FillMagicColors()
{
	for (int i=0; i< frame_w*frame_h*3;++i)
		frame[i]=GetRand()*255;
}

int fetch_and_process_video_packet(th_enc_ctx *thEncCtx,ogg_packet *op){
  int                        ret;
  int                        pic_sz;
  int                        frame_c_w;
  int                        frame_c_h;
  int                        c_w;
  int                        c_h;
  int                        c_sz;
  ogg_int64_t                beginframe;
  ogg_int64_t                endframe;
  
  beginframe=(video_fps_n*begin_sec+video_fps_n*begin_usec*.000001)/video_fps_d;
  endframe=(video_fps_n*end_sec+video_fps_n*end_usec*.000001)/video_fps_d;
  
  //выполняется только первый раз
  if(frame_state==-1){
    /* initialize the double frame buffer */

    frame_state=0;
  }
  pic_sz=pic_w*pic_h;
  frame_c_w=frame_w/dst_c_dec_h;
  frame_c_h=frame_h/dst_c_dec_v;
  c_w=(pic_w+dst_c_dec_h-1)/dst_c_dec_h;
  c_h=(pic_h+dst_c_dec_v-1)/dst_c_dec_v;
  c_sz=c_w*c_h;
 
/*
    if(fread(yuvframe[frame_state],1,y4m_dst_buf_read_sz,video)!=
     y4m_dst_buf_read_sz){
      fprintf(stderr,"Error reading YUV frame data.\n");
      exit(1);
    }
  
  if(fread(yuvframe[2],1,y4m_aux_buf_read_sz,video)!=y4m_aux_buf_read_sz){
      fprintf(stderr,"Error reading YUV frame data.\n");
      exit(1);
    }
*/
	frames++;
    if(frames>=beginframe)
    frame_state++;
  //}
  /* check to see if there are dupes to flush */

	int iLast=0;
  if(th_encode_packetout(thEncCtx,iLast,op)>0)return 1;
  if(frame_state<1){
    /* can't get here unless YUV4MPEG stream has no video */
    fprintf(stderr,"Video input contains no frames.\n");
    exit(1);
  }
  
  ycbcr[0].width=frame_w;
  ycbcr[0].height=frame_h;
  ycbcr[0].stride=pic_w;
  ycbcr[0].data=&frame[0];
  ycbcr[1].width=frame_w;
  ycbcr[1].height=frame_h;
  ycbcr[1].stride=c_w;
  ycbcr[1].data=&frame[frame_w*frame_h];
  ycbcr[2].width=frame_c_w;
  ycbcr[2].height=frame_c_h;
  ycbcr[2].stride=c_w;
  ycbcr[2].data=&frame[frame_w*frame_h*2];
  th_encode_ycbcr_in(thEncCtx,ycbcr);
  {
    unsigned char *temp=yuvframe[0];
    yuvframe[0]=yuvframe[1];
    yuvframe[1]=temp;
    frame_state--;
  }
 
  static int iF=0;
  ++iF;
  if (iF>100)
  iLast=1;
  
  std::cout <<iF <<" ";
  /* if there was only one frame, it's the last in the stream */
  ret = th_encode_packetout(thEncCtx,iLast,op);
  
  return ret;
}

int ilog(unsigned _v){
	int ret;
	for(ret=0;_v;ret++)_v>>=1;
	return ret;
}

int fetch_and_process_video(ogg_page *oggVideoPage,
			ogg_stream_state *oggStreamState,th_enc_ctx *thEncCtx){
	ogg_packet oggPacket;
	int ret;
	/* is there a video page flushed?  If not, work until there is. */
	while(1){
		if(ogg_stream_pageout(oggStreamState,oggVideoPage)>0) return 1;

		if(ogg_stream_eos(oggStreamState)) return 0;

		int ret=fetch_and_process_video_packet(thEncCtx,&oggPacket);
		if(ret<=0)return 0;
		ogg_stream_packetin(oggStreamState,&oggPacket);
	}
	return 1;
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
	y4m_dst_buf_read_sz=pic_w*pic_h*3;
	y4m_aux_buf_sz=y4m_aux_buf_read_sz=0;

	/*The size of the final frame buffers is always computed from the
         destination chroma decimation type.*/
     y4m_dst_buf_sz=pic_w*pic_h;
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

	//self->frame = malloc(frame_w * frame_h * 3);
	frame = new unsigned char[frame_w * frame_h * 3];

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

    thInfo.target_bitrate=(int)(64870*(ogg_int64_t)video_r>>16);
    thInfo.quality=video_q;
    thInfo.keyframe_granule_shift=ilog(keyframe_frequency-1);
	thInfo.pixel_fmt=TH_PF_444;

	thEncCtx=th_encode_alloc(&thInfo);

	th_info_clear(&thInfo);

    int ret=th_encode_ctl(thEncCtx,TH_ENCCTL_SET_KEYFRAME_FREQUENCY_FORCE,
     &keyframe_frequency,sizeof(keyframe_frequency-1));

    if(ret<0){
      fprintf(stderr,"Could not set keyframe interval to %d.\n",(int)keyframe_frequency);
    }

	th_comment_init(&thComment);

	if(th_encode_flushheader(thEncCtx, &thComment,&oggPacket)<=0){
		fprintf(stderr,"Internal Theora library error.\n");
		exit(1);
	}

	ogg_stream_packetin(&oggStreamState,&oggPacket);

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

		//заполнить случайными цветаи
		FillMagicColors();
		
		// is there a video page flushed?  If not, fetch one if possible
		videoflag=fetch_and_process_video(&videopage,&oggStreamState,thEncCtx);

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