import os, platform, re, time, SCons
from SCons.Script.SConscript import *
from SCons.Script import *

if os.name == 'nt':
    import win32file
    os.link = lambda src, dst: win32file.CreateHardLink(dst, src)

# For every specified key ensures that this key will be present 
# in dictionary and value for this will be a list
def make_lists(params, keys):
	if params == None:
		return None
		
	for key in keys:
		if not params.has_key(key):
			params[key] = []
			
		if not isinstance(params[key], list):
			params[key] = [ params[key] ]
		
	return params

# Substle aliases   
def substitle_aliases(params, aliases):
	if params == None:
		return None

	for key, value in aliases.iteritems():
		# You specify only CPPDEFINES or cppdefines but not both at the same time
		if params.has_key(key) and params.has_key(value):
			raise SCons.Errors.UserError('both \"%s\" and \"%s\" keys specified for target' % (key, value))

		params[key] = params.pop(value, params.pop(key, []))

	return params
			
# For every specified key appends value of platform_params to value of params
def union(params, platform_params, keys):
	if platform_params == None:
		return params
			
	for key in keys:
		params[key] += platform_params[key]
		
	return params

# Substracts map m2 from m1
def sub_maps(m1, m2):
	if m1 == None or m2 == None:
		return None

	for key, value in m2.iteritems():
		if m1.has_key(key):
			m1[key] = filter(lambda x: not x in value, m1[key])

	return m1

# Special case of union() for defines 
def union_defines(params, platform_params):
	if platform_params == None or not platform_params.has_key('CPPDEFINES'):
		return params
		 
	for value in platform_params['CPPDEFINES']:
		contains = False

		for i in params['CPPDEFINES']:
			# To eleminate leading '"' in some defines
			i_offset = 0 if i[0] != '"' else 1
			value_offset = 0 if value[0] != '"' else 1

			# "DEFINE_NAME="\"DEFINE_VALUE\""" -> DEFINE_NAME
			i_name = i.split('=')[0][i_offset:]
			value_name = value.split('=')[0][value_offset:]

			contains |= i_name == value_name

		if not contains:
			params['CPPDEFINES'].append(value)
			
	return params

# Filter dictionary using regex applied to keys
def filter_with_regex(unfiltered, regex):
	result = {}
	for key, value in unfiltered.iteritems():
		res = regex.search(key)
		if res != None:
			if result.has_key(res.group(1)):
				result[res.group(1)] += value
			else:
				result[res.group(1)] = value
				
	return result
	
def verbose_print(*args):
	# Print each argument separately so caller doesn't need to
	# stuff everything to be printed into a single string
	for arg in args:
		print arg,
	print
	
class EDEnvironment(SConsEnvironment):

	PLATFORMS_ALIASES = {'Windows': 'win', 'Darwin': 'mac', 'Linux': 'linux'}

	def __init__(self, arguments, mixin = None):
		# Register custom console arguments
		SCons.Script.AddOption('--skip-version-check', dest = 'skip-version-check', action = 'store_true', help = 'Skip SCons version check at startup.')
		SCons.Script.AddOption('--edverbose', dest = 'edverbose', action = 'store_true', help = 'Enable verbose mode.')

		# Check that scons version is at least 2.2.0 and not an alpha release
		if not SCons.Script.GetOption('skip-version-check'):
			self.EnsureSConsVersion(2, 2)
			if SCons.__version__.find('alpha') >= 0:
				raise SCons.Errors.UserError('Alpha versions of SCons are not supported. Your SCons version is ' + SCons.__version__)
		
		# Verbose mode
		if not SCons.Script.GetOption('edverbose'):
			global verbose_print
			verbose_print = lambda *x: None

		# Default environment options
		self.options = {
			'MODE' : arguments.get('mode', 'debug'),
			'ARCH' : arguments.get('arch', 'x86_64'),
			'TOOL' : arguments.get('tool', 'msvc' if platform.system() == 'Windows' else 'gcc'),
			'USE_BATCH_BUILD'       : 0, # MSVC can compile multiple files during one compiler call. Disabled by default
			'NUMBER_OF_JOBS'        : 2, # Probably everybody has at least two cores today
			'ENABLE_IMPLICIT_CACHE' : 1, # Implicit cache for faster builds
			'USE_HARD_LINKS'		: 1, # Use hard links instead of files copying.
		}

		# Add mixin if needed
		if mixin != None:
			type(self).__bases__ = (mixin,) + type(self).__bases__
 
		# Read environment options from configs
		self.options.update(self.read_config(os.path.join('Make', 'options.py')))
		
		# Generate some derived environment options
		self.generate_derived_env_options(self.options)

		# Any left console arguments override any environment options
		self.options.update(arguments)
		
		# Validate environment options
		self.validate_env_options(self.options)
		
		# Initialize environment
		SConsEnvironment.__init__(self, **self.options)

		# Very rudimentary clang support. SCons still doesn't support it out of the box
		if self['TOOL'] == 'clang':
			self['CC']  = 'clang'
			self['CXX'] = 'clang++'

		# To avoid creation of temporary files.
		self['MAXLINELENGTH'] = 4096

		# Pretty way to override environment variables without manualy hardcodes for each of them
		self.environ = os.environ
		self.environ.update(self.options.pop('ENVIRON', {}))

		# Set some options after environment is created
		self.SetOption('num_jobs', self.options['NUMBER_OF_JOBS'])
		self.Decider('MD5-timestamp')
		self.SetOption('max_drift', 1)
		self.SetOption('diskcheck','match')
		self.SetOption('implicit_cache', self.options['ENABLE_IMPLICIT_CACHE'])

		if self.options['USE_HARD_LINKS']:
			self['INSTALL'] = self.hard_link
		
		# Print settings
		print "mode: %s" % self['MODE']
		print "arch: %s" % self['ARCH']
		print "tool: %s" % self['TOOL']
		
		# Setup all other settings
		self['TOP_DIR']         = os.getcwd() + '/' # we need this this slash because too many people ignore existing of os.path.join()
		self['BUILD_DIR']       = os.path.join(self['TOP_DIR'], self.get_build_dir())
		self['INSTALL_BIN_DIR'] = os.path.join(self['TOP_DIR'], self.get_install_bin_dir())
		self['INSTALL_LIB_DIR'] = os.path.join(self['TOP_DIR'], self.get_install_lib_dir())
		self['PROJECT_DIR']     = os.path.join(self['TOP_DIR'], self.get_project_dir())

		# Call mixin constructor
		if mixin != None:
			mixin.__init__(self, arguments)

	def hard_link(self, dest, source, env):
		os.link(source, dest)
		
	# Here all derived environment settings are placed
	def generate_derived_env_options(self, env_options):
		env_options['TARGET_ARCH'] = 'amd64' if env_options['ARCH'] == 'x86_64' else 'x86'
		env_options['MSVC_BATCH']  = env_options['USE_BATCH_BUILD']

		return env_options

	# Here all environment settings validations are placed
	def validate_env_options(self, env_options):
		if env_options['MODE'] == 'msvsproj' and env_options['TOOL'] != 'msvc':
			raise SCons.Errors.UserError("Mode 'msvsproj' could be set only for 'msvc' tool")
	
	# Returns a dictionary of config variables
	def read_config(self, config_name):
		verbose_print("reading config '%s'" % config_name)
		
		# TODO: somehow strip imported modules
		
		# Config could be overridden by local version
		result = {}
		for name in [config_name, config_name + '.local']:
			try:
				if os.path.isfile(name):
					temp = {}
					execfile(os.path.join(name), {'env': self}, temp)
					result.update(temp)
			except Exception as e:
				print "Error while reading config '" + name + "': " + str(e)

		return result
		
	def get_configuration_name(self, full_linux_name = False):
		if self['TOOL'] == 'msvc':
			return 'vc' + self['MSVC_VERSION'].replace('.', '') + '.' + self['MODE']

		# If full_linux_name is true than instead of gcc.Linux.debug we
		# will get gcc.Ubuntu-12.04.debug, gcc.openSUSE-12.1.debug, ...
		# This is need for custom precompiled binaries for each Linux distro in sdk
		platform_name = platform.system()
		if platform_name == 'Linux' and full_linux_name:
			platform_name = '-'.join(map(str, platform.linux_distribution()[0:2])).replace(' ', '')

		return self['TOOL'] + '.' + platform_name + '.' + self['MODE']

	# Returns build directory path relative to top dir. Override if needed
	def get_build_dir(self, full_linux_name = False):
		return os.path.join('.build', self['ARCH'], self.get_configuration_name(full_linux_name))
		
	# Returns path to bin directory relative to top dir. Override if needed     
	def get_install_bin_dir(self, full_linux_name = False):
		return os.path.join('bin', self['ARCH'], self.get_configuration_name(full_linux_name))
		
	# Returns path to lib directory relative to top dir. Override if needed
	def get_install_lib_dir(self, full_linux_name = False):
		return os.path.join('lib', self['ARCH'], self.get_configuration_name(full_linux_name))
	
	# Returns path to project directory relative to top dir. Override if needed
	def get_project_dir(self):
		return ''

	# Get real absolute path of file or directory ignoring any variant directories
	def real_abspath(self, path):
		node = self.Entry(os.path.abspath(str(path)))

		# We need to do it in a loop because variant dir could be nested
		while node != node.srcnode():
			node = node.srcnode()

		return node.abspath

	# Debug routine just to know that we do not ignore some unknown param
	def validate_known_params(self, params):
		if params == None:
			return None
		
		valid_keys = ['target', 'include', 'header', 'source', 'project', 'resource', 'LIBS', 'LIBPATH', 'LINKFLAGS', 'LINKCOM', 'CPPDEFINES', 'CCFLAGS', 'CXXFLAGS', 'CPPFLAGS', 'CPPPATH', 'FRAMEWORKS', 'FRAMEWORKPATH', 'not_linked_dependencies', 'external_libs', 'precompiled_header']
		
		for key in params.iterkeys():
			if not key in valid_keys:
				raise SCons.Errors.UserError('Unknow key \"' + key + '\" in target \"' + self['TARGET_NAME'] + '\"')
			
		return params

	def process_external_libs(self, external_libs):
		result = {}

		for key, value in external_libs.iteritems():
			k = re.split('_', key)
			if (len(k) == 2) or (len(k) == 3 and k[2] == self['MODE'].upper()):
				library_name = k[0].lower()
				if not result.has_key(library_name):
					result[library_name] = {}
				result[library_name][k[1]] = value

		return result
	
	def process_params(self, target_type, params):
		aliases = {'LIBS': 'libs', 'CPPDEFINES': 'cppdefines'}
		
		keys = ['include', 'source', 'LINKFLAGS', 'CCFLAGS', 'CXXFLAGS', 'CPPFLAGS', 'LIBPATH', 'CPPPATH', 'CPPDEFINES', 'LIBS', 'FRAMEWORKS', 'FRAMEWORKPATH', 'resource']
		
		prepare_all = lambda x: self.validate_known_params(make_lists(substitle_aliases(x, aliases), keys))
		union_all   = lambda x, y: union_defines(union(x, y, [x for x in keys if x != 'CPPDEFINES']), y)

		# platform specific
		platform_params = None
		platform_excludes = None
		for key, value in self.PLATFORMS_ALIASES.iteritems():
			p = params.pop(value, None)
			if p != None and platform.system() == key:
				platform_excludes = prepare_all(p.pop('exclude', None))
				platform_params = prepare_all(p)
				verbose_print('platform:     %s' % platform_params)
				verbose_print('platform_excludes:    %s' % platform_excludes)
		
		# common parameters
		excludes = prepare_all(params.pop('exclude', None))
		params = prepare_all(params)
		verbose_print('common:  %s' % params)
		verbose_print('common_excludes:  %s' % excludes)

		# union parameters
		excludes = union_all(excludes, platform_excludes)
		params = union_all(params, platform_params)
		
		config_prefix = os.path.join(self['TOP_DIR'], 'Make', self['ARCH'] + "-" + self['TOOL'])
		
		# read XXX-options.py config
		unfiltered_options = self.read_config(config_prefix + '-options.py')
		options = filter_with_regex(unfiltered_options, re.compile('(\w*)_(COMMON|' + self['MODE'].upper() + ')(|_' + target_type + ')$'))
		options = make_lists(options, keys)

		# add common defines to options
		common_defines = self.read_config(os.path.join(self['TOP_DIR'], 'Make','common-defines.py'))
		union_defines(options, common_defines)
		
		# read XXX-external_libs.py config
		external_libs = self.read_config(config_prefix + '-external_libs.py')
		external_libs = self.process_external_libs(external_libs)
		
		verbose_print('options: %s' % options)
		verbose_print('extlibs: %s' % external_libs)
		
		# add config params
		params = union_all(params, options)

		# Add external_libs params
		if params.has_key('external_libs'):
			for lib in params['external_libs']:
				# First try external lib alias
				l = lib.lower()
				if external_libs.has_key(l):
					params = union_all(params, make_lists(external_libs[l], keys))
				else:
					raise SCons.Errors.UserError('No such extrnal lib \"%s\" in target \"%s\"' % (lib, self['TARGET_NAME']))
		
		verbose_print('common: %s' % params)

		# apply excludes
		params = sub_maps(params, excludes)

	def PostActions(self):
		pass
		
	# Recursive analog of Glob() function
	def RGlob(self, pattern):
		(directory, pattern) = os.path.split(pattern)
		
		node = self.Dir(directory)
		build_dir = node.abspath
		
		while node != node.srcnode():
			node = node.srcnode()
		
		result = []
		for root, dirs, files in os.walk(node.abspath):
			result += self.Glob(os.path.join(root.replace(node.abspath, build_dir), pattern))
			
		return result

	# Useful helper function
	def edSubdirs(self, subdirs):
		for subdir in subdirs:
			self.SConscript(os.path.join(subdir, 'SConscript'))

	def getUserVariable(self, name):
		if self.has_key('USER_VARIABLES') and self['USER_VARIABLES'].has_key(name):
			return self['USER_VARIABLES'][name]

		return None

	def isProjGenMode(self):
		return self['MODE'] == 'msvsproj'

# Helper function for environment creation
def CreateEnvironment(arguments, supported_modes, mixin = None):
	mode = arguments.get('mode', 'debug')

	# Create appropriate environment for selected mode
	for key, value in supported_modes.iteritems():
		if mode in key.split(' '):
			return value(arguments, mixin)

	# Report about unknown mode
	all_modes = sum(map(lambda x: x.split(), supported_modes.keys()), [])
	raise SCons.Errors.UserError('Unknown mode "' + mode + '". Can be "' + '", "'.join(all_modes) + '"')




