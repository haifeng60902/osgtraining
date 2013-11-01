import os, platform
from make.EDBuildEnvironment import *
from make.EDMsvsProjEnvironment import *
from make.EDXcodeProjEnvironment import *

# Custom EDGE settings for all environments
class EDGEEnvironment:
	def __init__(self, arguments):
	 	self['SDK_BIN_DIR'] = os.path.join(self.environ['GSDK_DIR'], self.get_install_bin_dir())
	 	self['SDK_LIB_DIR'] = os.path.join(self.environ['GSDK_DIR'], self.get_install_lib_dir())
	 	self['EDGE_SDK_DIR'] = os.path.join(os.getcwd(), '3rdparty')
	 	self['EDGE_SDK_BIN_DIR'] = os.path.join(self['EDGE_SDK_DIR'], self.get_install_bin_dir())
	 	self['EDGE_SDK_LIB_DIR'] = os.path.join(self['EDGE_SDK_DIR'], self.get_install_lib_dir())
		if not self.environ.has_key('WIN8_SDK'):
			if os.environ.has_key('ProgramFiles6432'):
				self.environ['WIN8_SDK'] = os.path.join(os.environ['ProgramFiles'], 'Windows Kits/8.0/')
			else:
				self.environ['WIN8_SDK'] = 'c:/Program Files (x86)/Windows Kits/8.0/'

# Custom build environment for EDGE
class EDGEBuildEnvironment(EDBuildEnvironment):
	def __init__(self, arguments, mixin = None):
		EDBuildEnvironment.__init__(self, arguments, mixin)

		print 'Configuration: %s' % self.get_configuration_name(full_linux_name = True)

		# Install sdk libs target
		sdk_libs = []
		
		sdk_libs += self.Glob(self['SDK_BIN_DIR'] + '/*' + self['SHLIBSUFFIX'])
		sdk_libs += self.Glob(self['SDK_BIN_DIR'] + '/*' + self['SHLIBSUFFIX'] + '.*') # For libXXX.so.Y libs on Linux
		sdk_libs += self.Glob(self['SDK_BIN_DIR'] + '/*.exe')
		sdk_libs += self.Glob(self['EDGE_SDK_BIN_DIR'] + '/*' + self['SHLIBSUFFIX'])
		sdk_libs += self.Glob(self['EDGE_SDK_BIN_DIR'] + '/*' + self['SHLIBSUFFIX'] + '.*') # For libXXX.so.Y libs on Linux

		install_sdk_libs = self.Install(self['INSTALL_BIN_DIR'], sdk_libs)

		self.Alias('install_sdk_libs', install_sdk_libs)
	
	# Make all targets depend on 'install_sdk_libs' target
	def edBuild(self, target_type, builder, **params):
		target = EDBuildEnvironment.edBuild(self, target_type, builder, **params)
		self.Depends(target, 'install_sdk_libs')

		return target


#========================================================================================

supported_modes = {
	'debug release': EDGEBuildEnvironment,
	'msvsproj':      EDMsvsProjEnvironment,
	'xcodeproj':     EDXcodeProjEnvironment,
}

env = CreateEnvironment(ARGUMENTS, supported_modes, EDGEEnvironment)

Export('env')
env.SConscript('SConscript', variant_dir = env['BUILD_DIR'], duplicate = 0)
env.PostActions()

if platform.system() == 'Windows':
	env.Default([''])
else:
	env.Default(['edCore', 'edModelDesc', 'edModelGraph', 'edterrainUtils4', 'renderer', 'Graphics', 'Space', 'Ephemeris', 'GraphicsUtils', 'glbackend', 'Viewer'])
