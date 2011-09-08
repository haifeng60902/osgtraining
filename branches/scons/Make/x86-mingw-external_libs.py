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

SDK_DIR = 'd:/projects/extern/sdk/'

CPPPATH = ['d:/projects/extern/sdk/inc']

LIBPATH = ['d:/projects/extern/sdk/lib/x86/mingw.'+_MODE_]

#-----------------------------------#

import os

DX_CPPPATH = [os.environ['DXSDK_DIR']+'/Include']

DX_LIBPATH = [os.environ['DXSDK_DIR']+'/Lib/x86']

DX_LIBS = ['d3d9','d3dx9']

#-----------------------------------#

PHYSFS_LIBS = ['physfs']

#-----------------------------------#

SPEEDTREE_LIBS = ['speedtree']

#-----------------------------------#

PNG_LIBS = ['png']

#-----------------------------------#

JPEG_LIBS = ['jpeg']

#-----------------------------------#

TIFF_LIBS = ['tiff']

#-----------------------------------#

LUA_LIBS = ['lua']

#-----------------------------------#

SDL_LIBS = ['SDLmain','SDL']

#-----------------------------------#

PTHREAD_LIBS = ['pthread']

#-----------------------------------#

MAXSDK_LIBS = []

#-----------------------------------#

OBJECTARX_LIBS = []

#-----------------------------------#

WX_MERGEFLAGS = '!wx-config --cppflags --libs'

WX_LIBS = ['wx_gtk2u_gl-2.8']

WX_CPPDEFINES = ['_UNICODE']

#-----------------------------------#

GL_LIBS = ['opengl32','glu32']

#-----------------------------------#

SYS_LIBS = ['winmm','mingw32']
