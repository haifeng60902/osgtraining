# External variables: 
#	_MODE_ - holds build mode (RELEASE, DEBUG, etc.)
#	_ARCHITECTURE_ - holds build mode (RELEASE, DEBUG, etc.)
#	_MSVS_VERSION_ - holds version of visual studio
# Supported suffixes:
#	CPPPATH
#	LIBPATH
#	CXXFLAGS
#	CPPDEFINES
#	LINKFLAGS
#	LIBS
#	MERGEFLAGS - holds command string wich after execution provides string containig compilel flags, library list, etc. Work only with gcc.
# Keys without library name means that their values will be applied independently of used libraries.
# On windows if you want to install sdk's libraris to bin directory you have to set SDK_DIR.

import os

CPPPATH = [os.environ['GSDK_DIR']+'/inc',os.environ['GSDK_DIR']+'/inc/win32']

LIBPATH = [os.environ['GSDK_DIR']+'/lib/'+_ARCHITECTURE_+'/vc'+_MSVS_VERSION_.replace('.','')+'.'+_MODE_]

#-----------------------------------#

DX_CPPPATH = [os.environ['DXSDK_DIR']+'/Include']

DX_LIBPATH = [os.environ['DXSDK_DIR']+'/Lib/x86']

DX_LIBS = ['d3d9','d3dx9', 'dxerr']

#-----------------------------------#

DX11_CPPPATH = [os.environ['DXSDK_DIR'] + '/Include']

DX11_LIBPATH = [os.environ['DXSDK_DIR'] + '/Lib/x86']

DX11_LIBS = ['d3d11.lib', 'd3dx11.lib', 'dxgi.lib', 'd3dcompiler.lib', 'dxguid.lib', 'dxerr', 'd3d9']

#-----------------------------------#

GL_LIBS = ['opengl32.lib']

#-----------------------------------#

OSGMATH_LIBS = ['OsgMath']

#-----------------------------------#

PGF_LIBS = ['libpgf.lib']

#-----------------------------------#

TBB_LIBS = ['tbb.lib', 'tbbmalloc.lib']

#-----------------------------------#

CIGI_LIBS = ['ccl_lib.lib']

CIGI_CPPPATH = [os.environ['SDK_DIR']+'/inc/cigi']

#-----------------------------------#

DL_LIBS = ['dl']

#-----------------------------------#

GEOGRAPHICLIB_LIBS = ['geographiclib.lib']

#-----------------------------------#

PARTICLE_LIBS = ['particlelib.lib']

#-----------------------------------#

PHYSFS_LIBS = ['physfs']

#-----------------------------------#

SPEEDTREE_LIBS = ['speedtree']

#-----------------------------------#

GDAL_LIBS = ['gdal_i.lib']

#-----------------------------------#

FREETYPE_LIBS = ['freetype']

#-----------------------------------#

PNG_LIBS = ['png.lib']

#-----------------------------------#

GDAL_LIBS = ['gdal_i.lib']

#-----------------------------------#

JPEG_LIBS = ['jpeg.lib']

#-----------------------------------#

TIFF_LIBS = ['libtiff.lib', 'zlib']

#-----------------------------------#

FFTW_LIBS = ['libfftw3-3.lib']

#-----------------------------------#

LUA_LIBS = ['lua.lib']

#-----------------------------------#

SDL_LINKFLAGS = ['-SUBSYSTEM:CONSOLE']

SDL_LIBS = ['SDL.lib','SDLmain.lib']

#-----------------------------------#

PTHREAD_LIBS = ['pthread.lib']

#-----------------------------------#

WX_LIBS_RELEASE =	[
						'wx.lib'
					]

WX_LIBS_DEBUG = [
					'wx.lib'
				]


#-----------------------------------#

TRE_LIBS = ['tre.lib']

#-----------------------------------#

MD5_LIBS = ['md5.lib']

#-----------------------------------#

BULLET_LIBS = ['bullet.lib']

#-----------------------------------#

MAXSDK_LIBPATH = []

MAXSDK_CPPPATH = []

MAXSDK_LIBS = []

if os.environ.has_key('MAX_SDK'):

	MAXSDK_LIBPATH = [os.environ['MAX_SDK']+'\lib']

	MAXSDK_CPPPATH = [os.environ['MAX_SDK']+'\include']

	MAXSDK_LIBS = [
					'geom',
					'core',
					'expr',
					'gfx',
					'mesh',
					'maxutil',
					'maxscrpt',
					'paramblk2',
					'bmm',
					'gup',
					'mnmath.lib',
					'igame.lib'
				  ]

#-----------------------------------#

OBJECTARX_CPPPATH = [os.environ['SDK_DIR']+'/inc/ObjectARX']

#-----------------------------------#

SYS_LIBS = ['Kernel32.lib','User32.lib','gdi32.lib','winspool.lib','comdlg32.lib','advapi32.lib','shell32.lib','ole32.lib','oleaut32.lib','uuid.lib','odbc32.lib','odbccp32.lib','winmm.lib','comctl32.lib','rpcrt4.lib','wsock32.lib']
