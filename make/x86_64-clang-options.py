import os, platform
from Make.gcc_warnings_as_errors import WARNINGS_AS_ERRORS

CPPPATH_COMMON = [
    os.path.join(env.environ['SDK_DIR'], 'inc'),

    # to simplify code transfer between lockon and edge
    os.path.join(env['TOP_DIR'], 'inc'),
    os.path.join(env['TOP_DIR'], 'inc', 'Core'),
    os.path.join(env['TOP_DIR'], 'src', 'render', 'inc'),
]

LIBPATH_COMMON = [
    env['INSTALL_LIB_DIR'],
    env['INSTALL_BIN_DIR'],
    env['SDK_BIN_DIR'],
    env['SDK_LIB_DIR'],
]

CPPDEFINES_COMMON = [
    'TBB_IMPLEMENT_CPP0X=1'
]

# Have to expand -Wall to exclude -Wunknown-pragmas.
# No '-Wsign-compare' as people ignore it.
WALL_SHIT = [
	'-Waddress',
	'-Warray-bounds',
	'-Wc++0x-compat',
	'-Wchar-subscripts',
	'-Wformat',
	'-Wmissing-braces',
#	'-Wparentheses',
#	'-Wreorder',
	'-Wreturn-type',
	'-Wsequence-point',
	'-Wstrict-aliasing',
	'-Wstrict-overflow=1',
	'-Wswitch',
	'-Wtrigraphs',
	'-Wuninitialized',
	'-Wunused-function',
	'-Wunused-label',
	'-Wunused-value',
#	'-Wunused-variable',
	'-Wvolatile-register-var']

CXXFLAGS_COMMON = ['-std=c++0x', '-stdlib=libc++', '-Wunused', '-Wpointer-arith']
CXXFLAGS_COMMON += WALL_SHIT
CXXFLAGS_COMMON += WARNINGS_AS_ERRORS

#-----------------------------------#

CXXFLAGS_RELEASE = ['-O3']
#' -O3 -ffast-math -funroll-all-loops -ftree-vectorize'

CPPDEFINES_RELEASE = ['NDEBUG']

#-----------------------------------#

CXXFLAGS_DEBUG = ['-O0', '-g3']

CPPDEFINES_DEBUG = ['_DEBUG']

#-----------------------------------#
LIBS_COMMON = []
if env.getUserVariable('USE_NEDMALLOC'):
    LIBS_COMMON += ['nedmalloc']
    
#-----------------------------------#

# Link flag for executables that forces them to search for dynamic libraries in executable folder first on Linux
if platform.system() == 'Linux':
    LINKFLAGS_COMMON_PROG = ['-Wl,-rpath,\$$ORIGIN', '-Wl,-rpath-link,' + env['INSTALL_BIN_DIR']]
    CCFLAGS_COMMON_LIB = ['-fPIC']

# Same for Mac OS X
if platform.system() == 'Darwin':
    LINKFLAGS_COMMON_DLL = ['-install_name', '@executable_path/' + env.subst('$SHLIBPREFIX') + env['TARGET_NAME'] + env.subst('$SHLIBSUFFIX')]
    CPPPATH_COMMON += ['/Users/stopiccot/code/other/SDL2']
