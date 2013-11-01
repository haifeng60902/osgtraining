import os, platform

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

CCFLAGS_COMMON = ['-std=c++0x']

#-----------------------------------#

CCFLAGS_RELEASE = ['-O3']
#' -O3 -ffast-math -funroll-all-loops -ftree-vectorize -Wall -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wparentheses -Wpointer-arith -Wuninitialized'

CPPDEFINES_RELEASE = ['NDEBUG']

#-----------------------------------#

CCFLAGS_DEBUG = ['-O0']
#' -g3 -O0 -ggdb -Wall -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wparentheses -Wpointer-arith'

CPPDEFINES_DEBUG = ['_DEBUG']

#-----------------------------------#

# Link flag for executables that forces them to search for dynamic libraries in executable folder first on Linux
if platform.system() == 'Linux':
    LINKFLAGS_COMMON_PROG = ['-Wl,-rpath,\$$ORIGIN', '-Wl,-rpath-link,' + env['INSTALL_BIN_DIR']]
    CCFLAGS_COMMON_LIB = ['-fPIC']

# Same for Mac OS X
if platform.system() == 'Darwin':
    LINKFLAGS_COMMON_DLL = ['-install_name', '@executable_path/' + env.subst('$SHLIBPREFIX') + env['TARGET_NAME'] + env.subst('$SHLIBSUFFIX')]
