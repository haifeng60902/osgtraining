#External variables: 
#	_MODE_ - holds build mode (RELEASE, DEBUG, PROFILE.)
#	_TOPDIR_ - hold root dir of EdSim
#Template [CPPPATH|LIBPATH|CXXFLAGS|CPPDEFINES|LINKFLAGS]_[_MODE_={COMMON,RELEASE,DEBUG,...}]_[TARGET={PROG,LIB,DLL}]
#UNBREAKABLE suffix means that value will replace any old value. For example: CXX_UNBREAKABLE='g++4'. UNBREAKABLE doesn't work with any target.

CPPDEFINES_COMMON = ['_WINDOWS','WIN32','_WIN32_WINNT=0x0500','GCC_COMPILED', 'EDGE']
CPPPATH_COMMON = [_TOPDIR_+'/inc']

LIBPATH_COMMON = [_TOPDIR_+'/lib/'+_MODE_]

#-----------------------------------#

CXXFLAGS_RELEASE = ' -O3 -ffast-math -funroll-all-loops -ftree-vectorize -Wall -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wparentheses -Wpointer-arith -Wuninitialized'

CPPDEFINES_RELEASE = ['NDEBUG']

#-----------------------------------#

CXXFLAGS_DEBUG = ' -g3 -O0 -ggdb -Wall -Wimplicit -Wreturn-type -Wunused -Wswitch -Wcomment -Wparentheses -Wpointer-arith'

CPPDEFINES_DEBUG = ['_DEBUG']

#-----------------------------------#

CXXFLAGS_PROFILE = CXXFLAGS_DEBUG+' -pg'

CPPDEFINES_PROFILE = CPPDEFINES_DEBUG

#-----------------------------------#

CPPDEFINES_COMMON_DLL = ['_USRDLL']

#-----------------------------------#

import os.path

LINKFLAGS_COMMON = '-Wl,--rpath -Wl,'+os.path.abspath(_TOPDIR_+'/bin/'+_MODE_)

#-----------------------------------#

LINKFLAGS_COMMON_DLL = '--shared --fpic'

#-----------------------------------#

LINKFLAGS_PROFILE = ' -pg'
