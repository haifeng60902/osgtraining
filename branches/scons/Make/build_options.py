# External variables: _MODE_ - holds build mode (RELEASE, DEBUG, etc.)

# Sets tool to be used. Now supported is 'gcc', 'mingw', 'msvc'. On windows 'msvc' will be used by default, 'gcc' on other platforms
# TOOL = 'msvc'

# Sets version of Visual Studio.
MSVS_VERSION = '9.0'

# Sets directory where object files will be store. If it is not 
# an absolute path name then dir'll be created in the same directory 
# of SConstruct file.
BUILD_DIR = '.build/'

# If set to 1 the libraries which are used by target wouldn't build.
# If you don't set any target in command line then nothing will be built.
# WARNING! Use this option only if you know what you are doing!
DONT_BUILD_DEPENDENCIES = 0

# When install create links instead of copying of files.
INSTALL_LINKS = 0

# Use symbolic links instead of hardlinks. See also INSTALL_LINKS.
# Note: this option doesn't take effect on windows.
USE_SYMBOLIC_LINKS = 1

#Sets the number of parallel processes of building
NUMBER_JOBS = 4

# Turns on/off implicit cache.
ENABLE_IMPLICIT_CACHE = 0

# Enables batch build on MSVS, has no effect on other platforms.
import os
if os.environ.has_key('BUILD_BOT'):
	USE_BATCH_BUILD = 0
else:
	USE_BATCH_BUILD = 0

if not os.environ.has_key('SDK_DIR'):
	os.environ['SDK_DIR']='k:/projects/extern/sdk/'

# Holds variables set by user.
USER_VARIABLES = {}

# two variants: current, old
USER_VARIABLES['renderer'] = 'current'

FORCE_LC_MESSAGES = 'EN'
