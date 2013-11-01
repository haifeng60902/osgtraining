import os
from make.msvc_warnings_as_errors import WARNINGS_AS_ERRORS

CPPPATH_COMMON = [
    os.path.join(env.environ['GSDK_DIR'], 'inc'),
    os.path.join(env.environ['GSDK_DIR'], 'inc', 'win32'),

    # to simplify code transfer between lockon and edge
    os.path.join(env['TOP_DIR'], 'inc'),
    os.path.join(env['TOP_DIR'], 'inc', 'Core'),
    os.path.join(env['TOP_DIR'], 'src', 'render', 'inc')
]

if env['MSVC_VERSION'] == "10.0":
	CPPPATH_COMMON += [env.environ['GSDK_DIR'] + '/inc/vc10compat']

LIBPATH_COMMON = [
    env['INSTALL_LIB_DIR'],
    env['SDK_LIB_DIR']
]

CCFLAGS_COMMON = ['/nologo', '/EHsc', '/GR', '/Zc:forScope', '/Zm111',
        '/Fd' + env.File(env['TARGET_NAME'] + '.pdb').abspath,
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
        '/wd4284']

CCFLAGS_COMMON += WARNINGS_AS_ERRORS

CPPDEFINES_COMMON = [
    '_WIN32', '_WINDOWS', 'WIN32_LEAN_AND_MEAN', 'WIN64_LEAN_AND_MEAN', '_USE_MATH_DEFINES', 'NOMINMAX', '_CRT_SECURE_NO_DEPRECATE'
]

#-----------------------------------#

CCFLAGS_RELEASE = ['/MD', '/O2', '/Zi']

CPPDEFINES_RELEASE = ['NDEBUG']

#-----------------------------------#

CCFLAGS_DEBUG = ['/MDd', '/Od', '/ZI']

CPPDEFINES_DEBUG = ['_DEBUG', '_HAS_ITERATOR_DEBUGGING=0', '_SECURE_SCL=0']

#-----------------------------------#

CPPDEFINES_COMMON_DLL = ['_USRDLL']

#-----------------------------------#

LINKFLAGS_COMMON = [
    '/STACK:16777216', '/MACHINE:X86', '/MANIFEST', '/NODEFAULTLIB:libc', '/NODEFAULTLIB:libcmt', '/DEBUG',
    '/PDB:' + env.File(env['TARGET_NAME'] + '.pdb').abspath
]

#-----------------------------------#
