#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <assert.h>

// includes below are only needed for:
#undef WIN32_LEAN_AND_MEAN
//#undef WIN64_LEAN_AND_MEAN
#include <windows.h> // for DWORD, BITMAPINFOHEADER

#include <aviriff.h> // for RIFFLIST, RIFFCHUNK, AVIMAINHEADER, AVISTREAMHEADER

#include <MMReg.h> // for WAVEFORMATEX

// should be 1G per spec
#define MAX_RIFF_SIZE (1024*1024*1024)
// the number of super-index entries
#define MAX_RIFF_COUNT 1024

// this one is missing from MS SDK
typedef struct _avisuperindex::_avisuperindex_entry AVISUPERINDEX_ENTRY;

typedef struct _AviSuperIndex {
	//AVIMETAINDEX
	FOURCC fcc;
	UINT   cb;
	WORD   wLongsPerEntry;
	BYTE   bIndexSubType;
	BYTE   bIndexType;
	DWORD  nEntriesInUse;
	DWORD  dwChunkId;
	DWORD  dwReserved[3];
	AVISUPERINDEX_ENTRY aIndex[MAX_RIFF_COUNT];
} AviSuperIndex;

static struct AviHeader {
	RIFFLIST hdrl;
	AVIMAINHEADER avih;
	struct _odml_header {
		RIFFLIST odml;
		RIFFCHUNK chd;
		DWORD dwTotalFrames;
	} odml;
	struct _video_header {
		RIFFLIST strl;
		AVISTREAMHEADER strh;
		RIFFCHUNK chf;
		BITMAPINFOHEADER strf;
		AviSuperIndex indx;
	} video;
	struct _audio_header {
		RIFFLIST strl;
		AVISTREAMHEADER strh;
		RIFFCHUNK chf;
		// For 24-bit data MSDN even requires WAVEFORMATEXTENSIBLE here,
		// but most software does understand only WAVEFORMATEX
		WAVEFORMATEX strf;
		AviSuperIndex indx;
	} audio;
};

struct AviHeader ref_info = {
	// RIFFLIST
	{
		FCC('LIST'),
			sizeof(ref_info) - 8,
			FCC('hdrl')
	},
	//AVIMAINHEADER
	{
		FCC('avih'),
			sizeof(ref_info.avih)-8,
			0, // ms per frame
			0, // max bytes per sec
			0, // padding
			AVIF_ISINTERLEAVED, // flags
			0, // total frames (in 1st 'movi' list)
			0, // initalframes
			2, // streams
			0, // suggested buffer size
			0, // width
			0, // height
			// reserved
		},
		// OpenDML
		{
			{
				FCC('LIST'),
					sizeof(ref_info.odml) - 8,
					FCC('odml')
			},
			{
				FCC('dmlh'),
					4,
				},
				0, // dwTotalFrames
		},
		// Video
		{
			//RIFFLIST
			{
				FCC('LIST'),
					sizeof(ref_info.video) - 8,
					FCC('strl')
			},
			// AVISTREAMHEADER
			{
				FCC('strh'), // fcc
					sizeof(ref_info.video.strh) - 8, // cb
					FCC('vids'), // fccType
					FCC('DIB '), // fccHandler (VirtualDub writes 'DIB ', ffmpeg writes 0)
					0, // dwFlags
					0, // wPriority
					0, // wLanguage
					0, // dwInitialFrames
					1, // dwScale
					0, // dwRate (!)
					0, // dwStart
					0, // dwLength (!)
					0, // dwSuggestedBufferSize (!)
					-1, // dwQuality
					0, // dwSampleSize
					// rcFrame
				},
				// RIFFCHUNK
				{
					FCC('strf'),
						sizeof(ref_info.video.strf)
				},
				//BITMAPINFOHEADER
				{
					sizeof(BITMAPINFOHEADER),
						0, // biWidth
						0, // biHeight
						1, // biPlanes
						32, // biBitCount
						BI_RGB, // biCompression
						0, // biSizeImage
						0, // biXPelsPerMeter
						0, // biYPelsPerMeter
						0, // biClrUsed
						0, // biClrImportant
						// reserved
					},
					//AviSuperIndex
					{
						FCC('indx'),
							sizeof(ref_info.video.indx) - 8,
							4,
							AVI_INDEX_SUB_DEFAULT,
							AVI_INDEX_OF_INDEXES,
							0,
							FCC('00dc'),
							// reserved
					},
				},
				// Audio
				{
					// RIFFLIST
					{
						FCC('LIST'),
							sizeof(ref_info.audio) - 8,
							FCC('strl')
					},
					// AVISTREAMHEADER
					{
						FCC('strh'), // fcc
							sizeof(ref_info.audio.strh) - 8, // cb
							FCC('auds'), // fccType
							WAVE_FORMAT_PCM, // fccHandler
							0, // dwFlags
							0, // wPriority
							0, // wLanguage
							0, // dwInitialFrames
							1, // dwScale
							0, // dwRate (!)
							0, // dwStart
							0, // dwLength (!)
							0, // dwSuggestedBufferSize
							-1, // dwQuality
							3*2,//sizeof(float)*2, // dwSampleSize
							// rcFrame
						},
						// RIFFCHUNK
						{
							FCC('strf'),
								sizeof(ref_info.audio.strf)
						},
						// WAVEFORMATEX
						{
							WAVE_FORMAT_PCM, //WAVE_FORMAT_IEEE_FLOAT, // wFormatTag
								2, // nChannels
								0, // nSamplesPerSec
								0, // nAvgBytesPerSec
								3*2,//sizeof(float) * 2, // nBlockAlign
								24,//32, // wBitsPerSample
								0, // cbSize
							},
							//AviSuperIndex
							{
								FCC('indx'),
									sizeof(ref_info.audio.indx) - 8,
									4,
									AVI_INDEX_SUB_DEFAULT,
									AVI_INDEX_OF_INDEXES,
									0,
									FCC('01wb'),
									// reserved
							},
						},
};

static RIFFLIST riff = {
	FCC('RIFF'),
	0, // size
	FCC('AVI ')
};

static RIFFLIST movi = {
	FCC('LIST'),
	0,
	FCC('movi')
};

typedef struct StreamInfo {
	RIFFCHUNK hdr;
	AVISTDINDEX *index; // allocated
	AviSuperIndex *super;
	UINT32 ticks;
} StreamInfo;

typedef
struct ed_avcapture_private {
	//VFS_File *avi;
	FILE *avi;

	UINT64 riff_start;
	UINT64 movi_start;
	UINT64 info_start;
	RIFFLIST riff;
	RIFFLIST movi;
	StreamInfo video;
	StreamInfo audio;
	struct AviHeader info;
	UINT32 index_limit;
	UINT32 index_size;
	int writeok;
} rawavi_t;

#define WIDTH 1280
#define HEIGHT 1024
#define FPS 30

void stream_init(rawavi_t *self, StreamInfo *str, AviSuperIndex *super)
{
	str->hdr.fcc = super->dwChunkId;

	str->super = super;
	str->ticks = 0;

	str->index = (AVISTDINDEX*) calloc(1, self->index_size);
	if (str->index)
	{
		AVISTDINDEX* idx = str->index;
		char str_id = ((char*)&super->dwChunkId)[1];
		idx->fcc = MAKEFOURCC('0', str_id, 'i', 'x');
		idx->cb = self->index_size - 8;
		idx->wLongsPerEntry = sizeof(AVISTDINDEX_ENTRY) / sizeof(DWORD);
		idx->bIndexSubType = AVI_INDEX_SUB_DEFAULT;
		idx->bIndexType = AVI_INDEX_OF_CHUNKS;
		idx->dwChunkId = super->dwChunkId;
	}
}

void init_streams(rawavi_t *self)
{
	UINT32 min_frame_size = self->info.avih.dwMaxBytesPerSec / self->info.video.strh.dwRate;
	self->index_limit = MAX_RIFF_SIZE / min_frame_size;
	self->index_size = (UINT32)(sizeof(AVIMETAINDEX) + sizeof(AVISTDINDEX_ENTRY) * self->index_limit);

	stream_init(self, &self->video, &self->info.video.indx);
	stream_init(self, &self->audio, &self->info.audio.indx);
}

UINT64 write_riff(rawavi_t *self, const void *buf, int len)
{
	UINT64 res;

	// do not write after errors
	if (!self->writeok)
		return 0;

	//res = VFS_write(self->avi, buf, len);
	res=fwrite(buf,1, len, self->avi);
	
	// check for errors (no space on device)
	if (res != len)
	{
		self->writeok = 0;
		return 0;
	}
	self->riff.cb += len;
	return res;
}

void stream_start(rawavi_t *self, StreamInfo *stream)
{
	if (stream->index)
	{
		stream->index->nEntriesInUse = 0;
		stream->index->qwBaseOffset = self->riff_start;
	}
	stream->ticks = 0;
}

UINT64 file_pos(rawavi_t *self)
{
	UINT64 pos = self->riff_start + self->riff.cb + 8;
	assert (ftell(self->avi) == pos);
	return pos;
}

UINT64 write_movi(rawavi_t *self, const void *buf, int len)
{
	UINT64 res = write_riff(self, buf, len);
	self->movi.cb += len;
	return res;
}

void stream_write_index(rawavi_t *self, StreamInfo *stream)
{
	AviSuperIndex *super = stream->super;
	if (super->nEntriesInUse < MAX_RIFF_COUNT)
	{
		AVISUPERINDEX_ENTRY *entry = &super->aIndex[super->nEntriesInUse++];
		entry->qwOffset = file_pos(self);
		entry->dwSize = stream->index->cb + 8;
		entry->dwDuration = stream->ticks;
	}

	write_movi(self, stream->index, self->index_size);
}

void patch_header(rawavi_t *self)
{
	UINT64 pos = ftell(self->avi);
	//VFS_seek(self->avi, self->info_start);
	fseek(self->avi, self->info_start, SEEK_SET);
	//VFS_write(self->avi, &self->info, sizeof(self->info));
	fwrite(&self->info,1,sizeof(self->info),self->avi);
	//VFS_seek(self->avi, pos);
	fseek(self->avi, pos,SEEK_SET);
}

void close_riff(rawavi_t *self)
{
	// write chunk index
	stream_write_index(self, &self->video);
	stream_write_index(self, &self->audio);

	// close movi chunk
	//VFS_seek(self->avi, self->movi_start);
	fseek(self->avi, self->movi_start, SEEK_SET);
	//VFS_write(self->avi, &self->movi, sizeof(self->movi));
	fwrite(&self->movi, 1, sizeof(self->movi), self->avi);

	// close previous riff
	//VFS_seek(self->avi, self->riff_start);
	fseek(self->avi, self->riff_start, SEEK_SET);
	//VFS_write(self->avi, &self->riff, sizeof(self->riff));
	fwrite(&self->riff, 1, sizeof(self->riff), self->avi);

	// if we successfully written a RIFF, patch main header,
	// so in case of running out of disk space
	// we will preserve already completed RIFFs.
	patch_header(self);
}


void start_avix(rawavi_t *self)
{
	close_riff(self);

	// start new riff
	self->riff_start += self->riff.cb + 8;
	//VFS_seek(self->avi, self->riff_start);
	fseek(self->avi,self->riff_start,SEEK_SET);

	stream_start(self, &self->video);
	stream_start(self, &self->audio);

	self->riff.cb = 4;
	self->riff.fccListType = FCC('AVIX');
	//VFS_write(self->avi, &self->riff, sizeof(self->riff));
	fwrite(&self->riff, 1, sizeof(self->riff),self->avi);

	self->movi_start = self->riff_start + sizeof(self->riff);
	assert (ftell(self->avi) == self->movi_start);
	self->movi.cb = 4;
	write_riff(self, &self->movi, sizeof(self->movi));
}


void stream_add_chunk(rawavi_t *self, StreamInfo* stream, UINT32 ticks)
{
	if (stream->index && stream->index->nEntriesInUse < self->index_limit)
	{
		AVISTDINDEX *index = stream->index;
		AVISTDINDEX_ENTRY *entry = &index->aIndex[index->nEntriesInUse++];
		UINT64 pos = file_pos(self) + sizeof(stream->hdr);

		entry->dwOffset = (DWORD)(pos - index->qwBaseOffset);
		entry->dwSize = stream->hdr.cb;
	}
	stream->ticks += ticks;
}

void write_chunk(rawavi_t *self, StreamInfo *stream, UINT32 ticks, const void *data)
{
	if (stream->index->nEntriesInUse == self->index_limit)
		start_avix(self);
	else if (self->riff.cb + 8 + sizeof(stream->hdr) + stream->hdr.cb + self->index_size*2 >= MAX_RIFF_SIZE)
		start_avix(self);

	stream_add_chunk(self, stream, ticks);

	//stream->hdr.cb = bytes;
	write_movi(self, &stream->hdr, sizeof(stream->hdr));
	write_movi(self, data, stream->hdr.cb);
}

int rawavi_video(rawavi_t *self, const unsigned char *data, unsigned stride)
{
	if (self)
	{
		assert ((stride * self->info.video.strf.biHeight) == self->video.hdr.cb);
		write_chunk(self, &self->video, 1, data);

		self->info.avih.dwTotalFrames++;
		self->info.video.strh.dwLength++;
		self->info.odml.dwTotalFrames++;
		return self->writeok;
	}
	return 0;
}

float GetRand()
{
	//получить случайное число от 0 до 1
	return (float)rand()/(float)RAND_MAX;
}

void EmulateScreen(unsigned char *bgra_dib)
{
	//эмул€ци€ работы заполнени€ экранного буфера
	static int iPixel=0;

	for (int y=0;y<HEIGHT;++y)
	{
		for (int x=0;x<WIDTH;++x)
		{
			bgra_dib[y*4*WIDTH+x*4]=GetRand()*255;
			bgra_dib[y*4*WIDTH+x*4+1]=GetRand()*255;
			bgra_dib[y*4*WIDTH+x*4+2]=GetRand()*255;
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


//указатель на область пам€ти эмулирующую экран
unsigned char *pScreen;

int main()
{
	//выделить пам€ть под виртуальный экранный буффер
	pScreen = new unsigned char[WIDTH*HEIGHT*4];
	memset(pScreen,0,WIDTH*HEIGHT*4);

	int abs_height;
	rawavi_t* self = (rawavi_t*)calloc(1, sizeof(*self));

	self->writeok = 1;

	abs_height = HEIGHT;

	self->riff = riff;
	self->movi = movi;

	self->info = ref_info;

	self->info.avih.dwMicroSecPerFrame = 1000000/FPS;
	self->info.avih.dwMaxBytesPerSec = 0;
	
	self->info.avih.dwWidth = WIDTH;
	self->info.avih.dwHeight = abs_height;

	self->info.video.strh.dwRate = FPS;
	self->info.video.strh.rcFrame.right = WIDTH;
	self->info.video.strh.rcFrame.bottom = abs_height;

	self->info.video.strf.biWidth = WIDTH;
	// Note: MPlayer does not understand top-to-bottom DIBs
	self->info.video.strf.biHeight = HEIGHT;
	self->info.video.strf.biSizeImage = WIDTH * abs_height * 4;

	self->info.avih.dwMaxBytesPerSec += self->info.video.strf.biSizeImage * FPS;

	self->info.audio.strh.dwRate = 44100;
	//self->info.audio.strh.dwLength = 0;//LENGTH * SAMPLERATE;

	self->info.audio.strf.nSamplesPerSec =44100;
	self->info.audio.strf.nAvgBytesPerSec = self->info.audio.strf.nSamplesPerSec * self->info.audio.strf.nBlockAlign;

	self->info.avih.dwMaxBytesPerSec += self->info.audio.strf.nAvgBytesPerSec;

	init_streams(self);
	self->video.hdr.cb = self->info.video.strf.biSizeImage;

	self->riff_start = 0;
	self->riff.cb = 4;

	FILE *outfile = stdout;
	_setmode( _fileno( stdin ), _O_BINARY );
	_setmode( _fileno( stdout ), _O_BINARY );

	outfile=fopen( "test.avi", "wb");

	self->avi=outfile;

	//VFS_write(self->avi, &self->riff, sizeof(self->riff));
	fwrite(&self->riff,1, sizeof(self->riff),outfile);

	self->info_start = sizeof(self->riff);
	write_riff(self, &self->info, sizeof(self->info));

	self->movi_start = sizeof(self->riff) + sizeof(self->info);
	self->movi.cb = 4;
	write_riff(self, &self->movi, sizeof(self->movi));

	stream_start(self, &self->video);
	stream_start(self, &self->audio);
//////////////////////////////////////////////////////////////////////////

	for (int i=0;i<50;++i)
	{
		//эмул€ци€ работы заполнени€ экранного буфера
		EmulateScreen(pScreen);
		std::cout << i << " ";

		rawavi_video(self,pScreen,WIDTH*4);
	}

//////////////////////////////////////////////////////////////////////////
	if (self)
	{
		// patches the header as well
		close_riff(self);

		if(outfile && outfile!=stdout)fclose(outfile);

		free(self->audio.index);
		free(self->video.index);
		delete self;
	}
}