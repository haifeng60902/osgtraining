import os

CPPPATH_COMMON = [
	env['INSTALL_INC_DIR'],
	os.path.join(env['INSTALL_INC_DIR'], 'win32'),
]

LIBPATH_COMMON = [
	env['INSTALL_LIB_DIR'],
	env['INSTALL_BIN_DIR'],
	os.path.join(env.environ['SDK_DIR'], 'lib', env['ARCH']), # TODO: Fix this. We should not use SDK_DIR var in extern
]

if env.environ.has_key('DXSDK_DIR'):
	CPPPATH_COMMON.append(os.path.join(env.environ['DXSDK_DIR'], 'Include'))
	LIBPATH_COMMON.append(os.path.join(env.environ['DXSDK_DIR'], 'Lib', 'x64'))

CCFLAGS_COMMON = [
	'/nologo', '/Zc:forScope', '/W3',
	'/wd4511', '/wd4512', '/wd4996', '/wd4251', '/wd4800',
]

CXXFLAGS_COMMON = ['/EHsc', '/GR']

CPPDEFINES_COMMON = ['WIN64', '_WIN64', '_WINDOWS', '_USE_MATH_DEFINES', 'NOMINMAX', '_CRT_SECURE_NO_DEPRECATE']

# XP support on 2012
if env['MSVC_VERSION'] == "11.0":
	CPPDEFINES_COMMON += ['_USING_V110_SDK71_', '__WIN32_WINNT=0x0502', 'WINVER=0x0502']
	CPPPATH_COMMON = ['C:/Program Files/Microsoft SDKs/Windows/v7.1/Include'] + CPPPATH_COMMON
	LIBPATH_COMMON = ['C:/Program Files/Microsoft SDKs/Windows/v7.1/Lib/x64'] + LIBPATH_COMMON

#-----------------------------------#

if env['TARGET_TYPE'] == 'LIB_STATIC_RUNTIME':
	CCFLAGS_RELEASE = ['/MT',  '/O2']
	CCFLAGS_DEBUG   = ['/MTd', '/Od']
else:
	CCFLAGS_RELEASE = ['/MD',  '/O2']
	CCFLAGS_DEBUG   = ['/MDd', '/Od']

#-----------------------------------#

CPPDEFINES_RELEASE = ['NDEBUG']
CPPDEFINES_DEBUG   = ['_DEBUG', 'DEBUG', '_ITERATOR_DEBUG_LEVEL=0']

#-----------------------------------#
 
LINKFLAGS_COMMON = [
	'/nologo', '/INCREMENTAL:NO',
	'/STACK:16777216', '/MACHINE:X64', '/MANIFEST', '/LARGEADDRESSAWARE',
]

LINKFLAGS_DEBUG = ['/DEBUG']#, '/NODEFAULTLIB:libc', '/NODEFAULTLIB:libcmt']

LINKFLAGS_RELEASE = ['/DEBUG']#'/NODEFAULTLIB:libc', '/NODEFAULTLIB:libcmt']
