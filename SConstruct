import os, platform
from Make.EDBuildEnvironment import *
from Make.EDMsvsProjEnvironment import *

class ExternEnvironment:
    def __init__(self, arguments):
        self['INSTALL_INC_DIR'] = os.path.join(self['TOP_DIR'], 'sdk', 'inc')
    
    # SDK uses old lockon naming convention    
    def get_install_bin_dir(self):
        return os.path.join('sdk', 'bin', self['ARCH'], self.get_configuration_name())
        
    # SDK uses old lockon naming convention
    def get_install_lib_dir(self):
        return os.path.join('sdk', 'lib', self['ARCH'], self.get_configuration_name())

supported_modes = {
    'debug release': EDBuildEnvironment,
    'msvsproj':      EDMsvsProjEnvironment,
}

env = CreateEnvironment(ARGUMENTS, supported_modes, ExternEnvironment)

Export('env')
env.SConscript('SConscript', variant_dir = env['BUILD_DIR'], duplicate = 0)
env.PostActions()

env.Default('install')