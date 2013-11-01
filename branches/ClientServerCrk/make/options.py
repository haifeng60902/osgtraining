import multiprocessing
import os

# Version on Visual Studio compiler
MSVC_VERSION = '10.0'

# Sets the number of parallel building processes
NUMBER_OF_JOBS = multiprocessing.cpu_count()

# Use batch builds in Visual Studio
USE_BATCH_BUILD = 1

# Implicit cache for faster builds. Disable if you like it slooow
ENABLE_IMPLICIT_CACHE = 1

# Use hard links instead of files copying.
USE_HARD_LINKS = 0

# Holds variables set by user.
USER_VARIABLES = {
    'FORCE_LC_MESSAGES': 'EN',
    'USE_NEDMALLOC': 0,
    'SECRET_CORRECTOR': 0,
#	'DX11_BACKEND': 'FROM_WIN8_SDK', # to use new dx11backend
    'COMPILE_DX11BACKEND_WIN8': 1,
    'EDTERRAIN4': 1,
    'NONPATCHED_3DSMAX_SDK': 0,
    'MAX_PLUGIN_VERSIONS': ['2010', '2011', '2012'],
    'MAYA_PLUGIN_VERSIONS': [], 
}

# Pretty way for overriding environment vars
ENVIRON = {
    #'WIN8_SDK': os.path.join(os.environ['ProgramFiles'], 'Windows Kits/8.0/'),
    #'SDK_DIR': 'd:/d/ED-SDK/sdk/', 
    # for each max sdk path specify
    #'ADSK_3DSMAX_SDK_XXXX': 'path-to-sdk-XXXX',
    #'ADSK_MAYA_SDK_XXXX': 'd:/dev/.SDKs/MayaXXXX/', #MayaXXXX must contain x86 or x86_64 dir
}
