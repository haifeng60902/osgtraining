import platform

Import('env')

subdirs = [
    'lua'
]

not_ported = [
    
]

# On Windows we should build ports of some UNIX libs
if platform.system() == 'Windows':
    subdirs += not_ported

    subdirs += ['dl', 'pthreads.2']

    if env['ARCH'] == 'x86':
        subdirs += ['detours']

env.edSubdirs(subdirs)
