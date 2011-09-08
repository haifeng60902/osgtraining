#External variables: 
#	_MODE_','- holds build mode (RELEASE, DEBUG, etc.)
#	_TOPDIR_','- hold root dir of EdSim
#Template [CPPPATH|LIBPATH|CXXFLAGS|CPPDEFINES|LINKFLAGS]_[_MODE_={COMMON,RELEASE,DEBUG,...}]_[TARGET={PROG,LIB,DLL}]
#UNBREAKABLE suffix means that value will replace any old value. For example: CXX_UNBREAKABLE='g++4'. UNBREAKABLE doesn't work with any target suffix.

CXXFLAGS_COMMON = ['-nologo','-EHsc','-GR','/Zc:forScope',
		'/W3',
		'/wd4511',
		'/wd4512',
		'/wd4996',
		'/wd4251',
		'/wd4800',
		'/wd4995', # name was marked as #pragma deprecated
		'/wd4244', # 'variable' : conversion from 'type' to 'type', possible loss of data
		'/wd4018', # 'expression' : signed/unsigned mismatch
		'/wd4503', # 'identifier' : decorated name length exceeded, name was truncated
		'/wd4200', # a structure or union contains an array with zero size.
		'/wd4275',
		'/wd4284',		
'/FIpragmas22.h']

CPPDEFINES_COMMON = ['WIN32','_WINDOWS','WIN32_LEAN_AND_MEAN','WIN64_LEAN_AND_MEAN','_USE_MATH_DEFINES','NOMINMAX', 'EDGE', '_CRT_SECURE_NO_DEPRECATE']

#-----------------------------------#

CXXFLAGS_RELEASE = ['-MD','-O2','-Zi']

CPPDEFINES_RELEASE = ['NDEBUG']

#-----------------------------------#

CXXFLAGS_DEBUG = ['-MDd','-Od','-ZI']

CPPDEFINES_DEBUG = ['_DEBUG', '_HAS_ITERATOR_DEBUGGING=0', '_SECURE_SCL=0']

if 0: CPPDEFINES_DEBUG.append('D3D_DEBUG_INFO')

#-----------------------------------#

CPPDEFINES_COMMON_DLL = ['_USRDLL']

#-----------------------------------#

LINKFLAGS_COMMON = ['-STACK:16777216', '/MACHINE:X86', '/MANIFEST']

LINKFLAGS_DEBUG = ['/NODEFAULTLIB:libc','/NODEFAULTLIB:libcmt', '-DEBUG']

LINKFLAGS_RELEASE = ['/NODEFAULTLIB:libc','/NODEFAULTLIB:libcmt','/DEBUG']

#-----------------------------------#
