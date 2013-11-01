import os, multiprocessing

# Version on Visual Studio compiler
MSVC_VERSION = '10.0'

# Sets the number of parallel building processes
NUMBER_OF_JOBS = multiprocessing.cpu_count()

# Use hard links instead of files copying
USE_HARD_LINKS = 0

# Use batch builds in Visual Studio
USE_BATCH_BUILD = 1

# Pretty way for overriding environment vars
ENVIRON = {
    #'SDK_DIR': some-path-here
}
