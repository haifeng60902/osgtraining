import os, platform, re, time, SCons
from SCons.Script.SConscript import SConsEnvironment, Configure
from EDEnvironment import *

class EDBuildEnvironment(EDEnvironment):
	def __init__(self, arguments, mixin = None):
		EDEnvironment.__init__(self, arguments, mixin)

		self.not_linked_dependencies_memo = []

		# TODO: check for C++ on Windows
		# Check for C++ compiler on non-Windows platforms
		if platform.system() != 'Windows':
			conf = Configure(self)
			if not conf.CheckCXX():
				raise SCons.Errors.UserError('No C++ compiler found. You should install g++ first')

		self.force_cmd_absolute_path()
		self.SConsignFile(os.path.join('Make', '.sconsign-' + self['ARCH'] + '-' + self.get_configuration_name() + '.dblite'))

	# Hack to force scons pass to compiler absolute path instead of relative so
	# Visual Studio error navigation will working
	def force_cmd_absolute_path(self):
		# TODO: Maybe we need a bit more elegant solution instead of this hack
		def use_sources_abspath(x):
			return x.replace('$CHANGED_SOURCES', '$CHANGED_SOURCES_ABSPATH')

		self['CCCOM']    = use_sources_abspath(self['CCCOM'])
		self['SHCCCOM']  = use_sources_abspath(self['SHCCCOM'])
		self['CXXCOM']   = use_sources_abspath(self['CXXCOM'])
		self['SHCXXCOM'] = use_sources_abspath(self['SHCXXCOM'])

		self['CHANGED_SOURCES_ABSPATH'] = '${SOURCES.abspath}'

	def setup_precompiled_header(self, params):
		if not params.has_key('precompiled_header'):
			return

		if self['TOOL'] == 'msvc':
			# In Visual Studio for precompiled header there should be corresponding source file - "header.cpp" for "header.h" 
			precompiled_header = params['precompiled_header']
			precompiled_source = [x for x in params['source'] if str(x).endswith(precompiled_header.replace('.h', '.cpp'))][0]

			# Compile precompiled header
			pch_params = params.copy()
			pch_params.pop('target')
			pch_params.pop('source')

			pch = self.PCH(precompiled_source, **pch_params)

			# Add precompiled header to compilation params of other files
			params['source']  = [x for x in params['source'] if x != precompiled_source] + [pch[1]]
			params['PCH']     = pch[0]
			params['PCHSTOP'] = precompiled_header

		if self['TOOL'] == 'gcc':
			pass # Precompiled headers for gcc are not currently implemented
	
	# Generic builder. Do not call directly
	def edBuild(self, target_type, builder, **params):
		self['TARGET_TYPE'] = target_type
		self['TARGET_NAME'] = params['target']
		
		self.process_params(self['TARGET_TYPE'], params)
		self.setup_precompiled_header(params)
		
		# Compile resource files on Windows platform
		if platform.system() == 'Windows':
			params['LIBS'] += [ self.RES(x) for x in params.pop('resource', []) ]

		result = builder(**params)

		# Not linked dependencies. See PostActions() for comments
		if params.has_key('not_linked_dependencies'):
			self.not_linked_dependencies_memo.append((result, params['not_linked_dependencies']))

		return result
	
	# Build executable program
	def edProgram(self, **params):
		target = self.edBuild('PROG', self.Program, **params)

		install = self.Install(self['INSTALL_BIN_DIR'], target)
		
		# Short alias so we can write 'scons main' instead of 'scons bin/x86_64/msvc_10.0/debug/main.exe'
		self.Alias(['install', params['target']], install)

		return target
		
	# Build static library
	def edStaticLibrary(self, **params):
		target = self.edBuild('LIB', self.StaticLibrary, **params)

		install = self.Install(self['INSTALL_LIB_DIR'], target) # .lib on windows, .a on mac and linux
		
		# Short alias so we can write 'scons shared_lib' instead of 'scons bin/x86_64/msvc_10.0/debug/shared_lib.dll'
		self.Alias(['install', params['target']], install)

		return target

	# Build static library
	def edStaticLibraryStaticRuntime(self, **params):
		target = self.edBuild('LIB_STATIC_RUNTIME', self.StaticLibrary, **params)

		install = self.Install(self['INSTALL_LIB_DIR'], target) # .lib on windows, .a on mac and linux
		
		# Short alias so we can write 'scons shared_lib' instead of 'scons bin/x86_64/msvc_10.0/debug/shared_lib.dll'
		self.Alias(['install', params['target']], install)

		return target
		
	# Build shared library
	def edSharedLibrary(self, **params):
		target = self.edBuild('DLL', self.SharedLibrary, **params)

		install_bin = self.Install(self['INSTALL_BIN_DIR'], target[0])   # .dll on windows, .dylib on mac, .so on linux
		install_lib = self.Install(self['INSTALL_LIB_DIR'], target[1:2]) # .lib on windows, nothing on mac and linux
		self.Depends(install_lib, install_bin)
		
		# Short alias so we can write 'scons shared_lib' instead of 'scons lib/x86_64/msvc_10.0/debug/static_lib.lib'
		self.Alias(['install', params['target']], [install_bin, install_lib])

		return target

	# Build loadable module - same as shared library for Win and Linux. .bundle for mac
	def edLoadableModule(self, **params):
		target = self.edBuild('DLL', self.LoadableModule, **params)

		install_bin = self.Install(self['INSTALL_BIN_DIR'], target[0])   # .dll on windows, .bundle on mac, .so on linux
		install_lib = self.Install(self['INSTALL_LIB_DIR'], target[1:2]) # .lib on windows, nothing on mac and linux
		self.Depends(install_lib, install_bin)
		
		# Short alias so we can write 'scons shared_lib' instead of 'scons lib/x86_64/msvc_10.0/debug/static_lib.lib'
		self.Alias(['install', params['target']], [install_bin, install_lib])

		return target

	def PostActions(self):
		# We can not just do self.Depends(target, map(self.Alias, not_linked_dependencies)) in edBuild()
		# due to a scons bug in self.Alias incorrectly working on UNIX systems because of no extension for executables
		# while it would work on Windows because of '.exe' extension
		for (target, not_linked_dependencies) in self.not_linked_dependencies_memo:
			self.Depends(target, map(self.Alias, not_linked_dependencies))
