#External variables: _MODE_ - holds build mode (RELEASE, DEBUG, etc.)
#Supported suffixes:
#	CPPPATH
#	LIBPATH
#	CXXFLAGS
#	CPPDEFINES
#	LINKFLAGS
#	LIBS
#	MERGEFLAGS - holds command string wich after execution provides string containig compilel flags, library list, etc. Work only with gcc.
#Keys without library name means that their values will be applied independently of used libraries.

import os

DX_LIBS = []

#-----------------------------------#

PHYSFS_LIBS = ['physfs']

#-----------------------------------#

FREETYPE_LIBS = ['freetype']

FREETYPE_CPPPATH = ['/usr/include/freetype2']

#-----------------------------------#

OSGMATH_LIBS = ['OsgMath']

#-----------------------------------#

PGF_LIBS = ['libpgf.lib']

#-----------------------------------#

TBB_LIBS = ['tbb.lib', 'tbbmalloc.lib']

#-----------------------------------#

CIGI_LIBS = ['ccl_lib.lib']

CIGI_CPPPATH = [os.environ['SDK_DIR'] + '/inc/cigi']

#-----------------------------------#

DL_LIBS = ['dl']

#-----------------------------------#

GEOGRAPHICLIB_LIBS = ['geographiclib.lib']

#-----------------------------------#

FTGL_LIBS = ['ftgl']

#-----------------------------------#

GLEW_LIBS = ['GLEW']

#-----------------------------------#

FFTW_LIBS = ['fftw3']

#-----------------------------------#

PNG_LIBS = ['png']

#-----------------------------------#

JPEG_LIBS = ['jpeg']

#-----------------------------------#

TIFF_LIBS = ['tiff']

#-----------------------------------#

LUA_LIBS = ['lua']

#-----------------------------------#

SDL_LIBS = ['SDL','SDLmain']

#-----------------------------------#

PTHREAD_LIBS = ['pthread']

#-----------------------------------#

SPEEDTREE_CPPPATH = ['/home/evgeny/projects/work/extern/speedtree']

SPEEDTREE_LIBPATH = ['/home/evgeny/projects/work/extern/speedtree']

SPEEDTREE_LIBS = ['SpeedTreeRT']

#-----------------------------------#

WX_MERGEFLAGS = '!wx-config --cppflags --libs'

WX_LIBS = ['wx_gtk2u_gl-2.8']

#-----------------------------------#

FOX_MERGEFLAGS = '!fox-config --cflags --libs'

FOX_CPPDEFINES = ['FOX_VERSION_1_6']

#-----------------------------------#

GL_LIBS = ['GL','GLU','Xxf86vm']

#-----------------------------------#

SYS_LIBS = ['rt']
