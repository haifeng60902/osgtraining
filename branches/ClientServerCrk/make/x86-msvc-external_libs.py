#-----------------------------------#

DX_CPPPATH = [env.environ['DXSDK_DIR'] + '/Include']
DX_LIBPATH = [env.environ['DXSDK_DIR'] + '/Lib/x86']
DX_LIBS = ['d3d9','d3dx9', 'dxerr']

#-----------------------------------#

DX11WIN8_CPPPATH = [
    env.environ['WIN8_SDK'] + '/Include/um',
    env.environ['WIN8_SDK'] + '/Include/shared'
]
DX11WIN8_LIBPATH = [env.environ['WIN8_SDK'] + '/Lib/win8/um/x86']
DX11WIN8_LIBS = ['d3d11.lib', 'dxgi.lib', 'd3dcompiler.lib', 'dxguid.lib', 'd3d9']

DX11_CPPPATH = [env.environ['DXSDK_DIR'] + '/Include']
DX11_LIBPATH = [env.environ['DXSDK_DIR'] + '/Lib/x86']
DX11_LIBS = ['d3d11.lib', 'd3dx11.lib', 'dxgi.lib', 'd3dcompiler.lib', 'dxerr', 'dxguid.lib', 'd3d9']

#-----------------------------------#

GL_LIBS = ['opengl32.lib']

#-----------------------------------#

OSGMATH_LIBS = ['OsgMath']

#-----------------------------------#

PGF_LIBS = ['pgf.lib']

#-----------------------------------#

TBB_LIBS = ['tbb.lib']

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

NEDMALLOC_LIBS = ['nedmalloc.lib']

#-----------------------------------#

LUASTATIC_LIBS = ['lua_static.lib']

#-----------------------------------#

SDL_LINKFLAGS = ['-SUBSYSTEM:CONSOLE']

SDL_LIBS = ['SDL.lib','SDLmain.lib']

#-----------------------------------#

PTHREAD_LIBS = ['pthread.lib']

#-----------------------------------#

WX_LIBS_RELEASE = ['wx.lib']
WX_LIBS_DEBUG = ['wx.lib']

#-----------------------------------#

TRE_LIBS = ['tre.lib']

#-----------------------------------#

MD5_LIBS = ['md5.lib']

#-----------------------------------#

BULLET_LIBS = ['bullet.lib']

#-----------------------------------#

PREDICATES_LIBS = ['predicates.lib']

#-----------------------------------#

NVTT_LIBS = ['nvtt.lib']
ZLIB_LIBS = ['zlib.lib']

#-----------------------------------#

MAXSDK_LIBPATH = []
MAXSDK_CPPPATH = []
MAXSDK_LIBS = []

if env.environ.has_key('MAX_SDK'):
    MAXSDK_LIBPATH = [env.environ['MAX_SDK'] + '/lib']
    MAXSDK_CPPPATH = [env.environ['MAX_SDK'] + '/include']
    MAXSDK_LIBS    = ['comctl32.lib', 'geom.lib', 'core.lib', 'gfx.lib', 'mesh.lib', 'maxutil.lib', 'maxscrpt.lib', 'paramblk2.lib', 'bmm.lib', 'gup.lib', 'mnmath.lib', 'igame.lib']

#-----------------------------------#

MAYASDK_LIBPATH = []
MAYASDK_CPPPATH = []
MAYASDK_LIBS = []

if env.environ.has_key('MAYA_SDK'):
    MAYASDK_LIBPATH = [env.environ['MAYA_SDK'] + '/x86/lib']
    MAYASDK_CPPPATH = [env.environ['MAYA_SDK'] + '/x86/include']
    MAYASDK_LIBS    = ['Foundation.lib', 'OpenMaya.lib', 'OpenMayaUI.lib',
                       'OpenMayaRender.lib', 'OpenMayaFX.lib',
                       'OpenMayaAnim.lib', 'OpenGL32.lib']

#-----------------------------------#



#-----------------------------------#

BOOST_LIBS = [
    'boost_date_time',
    'boost_filesystem',
#    'boost_iostreams',
#    'boost_python',
    'boost_system',
    'boost_thread',
    'boost_wave',
]

#-----------------------------------#

SYS_LIBS = ['Kernel32.lib','User32.lib','gdi32.lib','winspool.lib','comdlg32.lib','advapi32.lib','shell32.lib','ole32.lib','oleaut32.lib','uuid.lib','odbc32.lib','odbccp32.lib','winmm.lib','comctl32.lib','rpcrt4.lib','wsock32.lib', 'Shlwapi.lib', 'Version.lib']
