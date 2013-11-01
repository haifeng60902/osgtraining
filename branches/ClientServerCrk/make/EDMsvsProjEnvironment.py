import os, platform, re, time, SCons
from SCons.Script.SConscript import SConsEnvironment, Configure
from EDEnvironment import *

class EDMsvsProjEnvironment(EDEnvironment):
	def __init__(self, arguments, mixin = None):
		EDEnvironment.__init__(self, arguments, mixin)

		self.msvsProjects = {}
		self.SConsignFile(os.path.join('Make', '.sconsign-msvsproj.dblite'))

	# Returns path to project directory relative to top dir. Override if needed
	def get_project_dir(self):
		return os.path.join('Make', 'msvs', self['MSVC_VERSION'])

	def edBuild(self, target_type, target_prefix, target_suffix, **params):
		self['TARGET_TYPE'] = target_type
		self['TARGET_NAME'] = params['target']
		self['PROJECT_NAME'], self['PROJECT_VERSION'] = (params.pop('project', params['target']) + '|').split('|')[:2]

		self.process_params(self['TARGET_TYPE'], params)
		
		modes  = [('x86', 'debug'), ('x86', 'release'), ('x86_64', 'debug'), ('x86_64', 'release')]
		
		def make_absolute(y):
			return map(lambda x: self.real_abspath(x), y)

		params['source']  = make_absolute(params['source'])
		params['srcs']    = params['source']
		params['incs']    = make_absolute(params['include'] + params['header']) 
		params['CPPPATH'] = make_absolute(params['CPPPATH'])
		
		params['auto_build_solution'] = 0
		params['target'] = os.path.join(self['PROJECT_DIR'], self['PROJECT_NAME'])
		params['variant'] = []
		params['buildtarget'] = map(lambda (arch, mode): 'tool=msvc\" \"arch=' + arch + '\" \"mode=' + mode + '\" \"' + self['TARGET_NAME'], modes)
		
		temp = {'ARCH': self['ARCH'], 'MODE': self['MODE']}
		def _lambda((arch, mode)):
			self._dict.update({'ARCH': arch, 'MODE': mode})
			return os.path.join(self['TOP_DIR'], self.get_install_bin_dir(), target_prefix + self['TARGET_NAME'] + target_suffix)
		
		params['runfile'] = map(_lambda, modes)
		self._dict.update(temp)

		# Store params for this version of this project   
		versions = self.msvsProjects.setdefault(self['PROJECT_NAME'], {})
		versions[ self['PROJECT_VERSION'] ] = params
	
	def edProgram(self, **params):
		self.edBuild('PROG', self['PROGPREFIX'], self['PROGSUFFIX'], **params)
		
	def edStaticLibrary(self, **params):
		self.edBuild('LIB', self['LIBPREFIX'], self['LIBSUFFIX'], **params)
		
	def edSharedLibrary(self, **params):
		self.edBuild('DLL', self['SHLIBPREFIX'], self['SHLIBSUFFIX'], **params)

	def edLoadableModule(self, **params):
		self.edBuild('DLL', self['LDMODULEPREFIX'], self['LDMODULESUFFIX'], **params)

	# Method to generate project files after we processed all sconscript files
	def PostActions(self):
		for project, versions in self.msvsProjects.iteritems():
			project_params = None

			# Assemble project params from all project versions
			for version, params in versions.iteritems():
				if project_params == None:
					project_params = params
				else:
					project_params['buildtarget'] += params['buildtarget']
					project_params['runfile'] += params['runfile']

				project_params['variant'] += [x[0] + version + x[1] for x in [('Debug', '|Win32'), ('Release', '|Win32'), ('Debug', '|x64'), ('Release', '|x64')]]

			# Generate project
			target = self.MSVSProject(**project_params)
			self.Alias(['install', project_params['target']], target)


