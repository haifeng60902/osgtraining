#include <iostream>

#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <time.h>

#include "ogg/ogg.h"
#include "theora/theoraenc.h"

struct enScreen
{
    /**
     * Video width in pixels.
     */
    int iWidth;

    /**
     * Video height in pixels.
     * Negative value means bottom-to-top image.
     * In DCS it is always negative.
     */
    int iHeight;

    /**
     * Video frames per second.
     */
    int iFramerate;

    /**
     * Video quality [0, 1.0], where 1.0 means best.
     */
    float fQuality;

};

//описание структуры дл€ кодировани€ видео
struct enState
{
	enScreen Screen;

	// theora state
	ogg_stream_state oggStreamState;
	
	th_enc_ctx       *thEncCtx;
	th_info          thInfo;
	th_comment       thComment;
	unsigned char    *frame;
	int frame_ready;
	th_ycbcr_buffer  ycbcr;

	// output
	ogg_page oggPage;
	ogg_packet oggPacket;

	FILE *outfile;
};

enState State;

int init_theora(enState *self);

int write_pageout(enState *self);

int write_page(enState *self);

void exit_theora(enState *self);

 /* Flush the rest of our headers. This ensures
       the actual data in each stream will start
       on a new page, as per spec. */
int write_flush(enState *self);

//работа с видео
int xiph_video(enState *self, const unsigned char *bgra_dib, unsigned int stride);

//преобразование из rgb в Y'CbCr
void bgra2yuv(enState *self, const unsigned char *bgra_dib, unsigned int stride);


//эмул€ци€ работы заполнени€ экранного буфера
void EmulateScreen(unsigned char *bgra_dib);

//получить случайное число от 0 до 1
float GetRand();

//указатель на область пам€ти эмулирующую экран
unsigned char *pScreen;

int main()
{
	//настройка выходного файла
	FILE *outfile = stdout;
	_setmode( _fileno( stdin ), _O_BINARY );
	_setmode( _fileno( stdout ), _O_BINARY );

	outfile=fopen( "test.avi","wb");
//////////////////////////////////////////////////////////////////////////
	State.Screen.fQuality=1.0;
	State.Screen.iFramerate=25;
	State.Screen.iWidth=800;//384
	State.Screen.iHeight=600;//288
	State.outfile=outfile;

	//выделить пам€ть под виртуальный экранный буффер
	pScreen = new unsigned char[State.Screen.iWidth*State.Screen.iHeight*3];
	memset(pScreen,0,State.Screen.iWidth*State.Screen.iHeight*3);

	//иницализаци€ theora
	init_theora( &State );

	/* Flush the rest of our headers. This ensures
       the actual data in each stream will start
       on a new page, as per spec. */
    if (!write_flush(&State))
        return -1;


//////////////////////////////////////////////////////////////////////////
//формирование кадров видео
	for (int i=0; i<4*25;++i)
	{
		//эмул€ци€ работы заполнени€ экранного буфера
		EmulateScreen(pScreen);
		std::cout << i << " ";

		int res=xiph_video( &State, pScreen, 0);
	}

	xiph_video( &State, NULL, 0);
//////////////////////////////////////////////////////////////////////////


	exit_theora(&State);

	delete pScreen;
	pScreen=NULL;

	if(outfile && outfile!=stdout)fclose(outfile);
}

int init_theora(enState *self)
{
int frame_w, frame_h;
    int w, h;
    int res;
    int i;

    th_info_init(&self->thInfo);

    w = self->Screen.iWidth;
    h = self->Screen.iHeight;
    if (h<0)
        h = -h;
    frame_w = (w + 0xF) & ~0xF;
    frame_h = (h + 0xF) & ~0xF;
    self->thInfo.frame_width = frame_w;
    self->thInfo.frame_height = frame_h;
    self->thInfo.pic_width = w;
    self->thInfo.pic_height = h;
    self->thInfo.pic_x = 0;
    self->thInfo.pic_y = 0;
    self->thInfo.colorspace = TH_CS_UNSPECIFIED;
    self->thInfo.pixel_fmt = TH_PF_444;
    // some players (based on example_player.c from libtheora) can't propely play 4:4:4
    // should we downsample the chroma, or let them fix their players?
    self->thInfo.target_bitrate = -1;
    self->thInfo.quality = (int)(self->Screen.fQuality * 63);
	self->thInfo.keyframe_granule_shift=1;

    self->thInfo.fps_numerator = (int)self->Screen.iFramerate;
    self->thInfo.fps_denominator = 1;
    self->thInfo.aspect_numerator = 1;
    self->thInfo.aspect_denominator = 1;

    self->thEncCtx = th_encode_alloc(&self->thInfo);
    if (!self->thEncCtx)
        return 0;

	ogg_uint32_t keyframe_frequency=2;
	int ret=th_encode_ctl( self->thEncCtx,TH_ENCCTL_SET_KEYFRAME_FREQUENCY_FORCE,
		&keyframe_frequency,sizeof(keyframe_frequency-1));

    /* set up Ogg output */
    ogg_stream_init(&self->oggStreamState, rand());

    th_comment_init(&self->thComment);

    if (th_encode_flushheader(self->thEncCtx, &self->thComment, &self->oggPacket)<=0)
        return 0;

    ogg_stream_packetin(&self->oggStreamState, &self->oggPacket);

	if (!write_pageout(self))
        return 0;

    // Packetize remaining theora headers.
    //   We will write them after first vorbis header.
    while ((res = th_encode_flushheader(self->thEncCtx, &self->thComment, &self->oggPacket)) > 0)
    {
        ogg_stream_packetin(&self->oggStreamState, &self->oggPacket);
    }
    if (res < 0)
        return 0;

    //self->frame = malloc(frame_w * frame_h * 3);
	self->frame = new unsigned char[frame_w * frame_h * 3];
    self->frame_ready = 0;

    // setup image planes
    for (i=0; i<3; ++i)
    {
        self->ycbcr[i].width = frame_w;
        self->ycbcr[i].height = frame_h;
        self->ycbcr[i].stride = frame_w;
        self->ycbcr[i].data = self->frame + i * (frame_w * frame_h);
    }

    return 1;
}

int write_pageout(enState *self)
{
	int res;

	while ((res = ogg_stream_pageout(&self->oggStreamState, &self->oggPage) > 0))
	{
		if (!write_page(self))
			return 0;
	}
	if (res < 0)
	{
		return 0;
	}
	return 1;
}

int write_page(enState *self)
{
	int res = fwrite(self->oggPage.header, 1, self->oggPage.header_len, self->outfile);

	if (res != self->oggPage.header_len || 
		fwrite(self->oggPage.body, 1, self->oggPage.body_len, self->outfile ) != self->oggPage.body_len)
	{
		return 0;
	}
	return 1;
}

void exit_theora(enState *self)
{
	if (self->frame)
	{
		delete self->frame;
		self->frame = 0;
	}
	th_info_clear(&self->thInfo);
	if (self->thEncCtx)
	{
		th_encode_free(self->thEncCtx);
		self->thEncCtx = NULL;
	}
	ogg_stream_clear(&self->oggStreamState);
	th_comment_clear(&self->thComment);
}

int write_flush(enState *self)
{
	int res;

	while ((res = ogg_stream_flush(&self->oggStreamState, &self->oggPage)) > 0)
	{
		if (!write_page(self))
			return 0;
	}
	return 1;
}

int xiph_video(enState *self, const unsigned char *bgra_dib, unsigned int stride)
{
	int res = 1;
	int last = bgra_dib == 0;
	if (self->frame_ready)
	{
		int iR=th_encode_ycbcr_in(self->thEncCtx, self->ycbcr);
		if (iR)
		{
			int a=1;
		}
		

		int iK=th_packet_iskeyframe(&self->oggPacket);

		while (th_encode_packetout(self->thEncCtx, last, &self->oggPacket)>0)
			ogg_stream_packetin(&self->oggStreamState, &self->oggPacket);

		res = write_pageout(self);

		if (last)
			res &= write_flush(self);
	}
	if (!last)
	{
		bgra2yuv(self, bgra_dib, self->Screen.iWidth);
		self->frame_ready = 1;
	}
	return res;
}

void EmulateScreen(unsigned char *bgra_dib)
{
	//эмул€ци€ работы заполнени€ экранного буфера
	static int iPixel=0;

	for (int y=0;y<State.Screen.iHeight;++y)
	{
		for (int x=0;x<State.Screen.iWidth;++x)
		{
			bgra_dib[y*3*State.Screen.iWidth+x*3]=GetRand()*255;
			bgra_dib[y*3*State.Screen.iWidth+x*3+1]=GetRand()*255;
			bgra_dib[y*3*State.Screen.iWidth+x*3+2]=GetRand()*255;
		}
	}
/*	
	int iP=GetRand()*(State.Screen.iWidth*State.Screen.iHeight-1);

	bgra_dib[iP*3]=GetRand()*255;
	bgra_dib[iP*3+1]=GetRand()*255;
	bgra_dib[iP*3+2]=GetRand()*255;

	++iPixel;
	if (iPixel==State.Screen.iWidth*State.Screen.iHeight)
		iPixel=0;
		*/
}

float GetRand()
{
	//получить случайное число от 0 до 1
	return (float)rand()/(float)RAND_MAX;
}

//преобразование из rgb в Y'CbCr
void bgra2yuv(enState *self, const unsigned char *bgra_dib, unsigned int stride)
{
	int x, maxx;
	int y, maxy;
	int rowlen;
	const unsigned char *rgb_row;
	int yuv_row = 0;

	maxx = self->Screen.iWidth;
	maxy = self->Screen.iHeight;
	if (maxy < 0)
	{
		maxy = -maxy;
		rowlen = -(int)stride;
		rgb_row = bgra_dib + stride * (maxy - 1);
	}
	else
	{
		rowlen = (int)stride;
		rgb_row = bgra_dib;
	}
	// Sloooooowpoke
	// TODO: MMX/SSE optimisation
	// better to do this on libtheora side
	for (y=0; y<maxy; ++y, yuv_row += self->thInfo.frame_width, rgb_row += rowlen)
	{
		for (x = 0; x<maxx; ++x)
		{
			// http://en.wikipedia.org/wiki/YCbCr
			int B = rgb_row[x*3 + 0];
			int G = rgb_row[x*3 + 1];
			int R = rgb_row[x*3 + 2];

			int Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16;
			int U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128;
			int V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128;

			self->ycbcr[0].data[yuv_row + x] = Y;
			self->ycbcr[1].data[yuv_row + x] = U;
			self->ycbcr[2].data[yuv_row + x] = V;
		}
	}
}