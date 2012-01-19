from SCons.Script.SConscript import SConsEnvironment
import SCons.Tool
import SCons.Script

import os
import re

import utils

class BuildEnvironment(SConsEnvironment):
	TARGET_LIB=0
	TARGET_DLL=1
	TARGET_PROG=2

	def __init__(self, mode, arch, **args):
		os.environ["USERPROFILE"]="" # avoid scons's bug
		os.environ["VISUALSTUDIODIR"]="" # avoid scons's bug

		if arch == "x86" or arch == "i386":
			TARGET_ARCH = "x86"
			arch = "x86"
		elif arch == "x86_64":
			TARGET_ARCH = "amd64"

		SConsEnvironment.__init__(self, ENV = os.environ, ARCHITECTURE = arch, TARGET_ARCH = TARGET_ARCH, MODE = mode, **args)

		# Initialization by zero
		self.__ex_libs={}
			
		self.globals={}

		# Open config files

		self['TOP_DIR']=os.getcwd()+'/../'
		self['ROOT_DIR']=os.getcwd()+'/'

		# Read global defines
		utils.read_config(self['CONFIG_PATHS'], 'globals.py', self.globals, {'_MODE_': self['MODE'], '_ARCHITECTURE_': self['ARCHITECTURE']})
		self['CPPDEFINES'] = self.globals['CPPDEFINES']

		el_flags = {}
		export_vars = {'_MODE_' : self['MODE'], '_ARCHITECTURE_' : self['ARCHITECTURE']}
		if self['TOOL'] == 'msvc':
			export_vars['_MSVS_VERSION_'] = self['MSVS_VERSION']

		utils.read_config(self['CONFIG_PATHS'], self['ARCHITECTURE'] + '-' + self['TOOL'] + '-external_libs.py', el_flags, export_vars)

		# Apply config files
		# Make external libraries dictonary
		for key in el_flags.keys():
			if key == 'SDK_DIR':
				self['SDK_DIR']=el_flags[key]
				continue

			k=re.split('_',key)
			if len(k) == 1:
				utils.append_to_dict(self._dict,key,el_flags[key])
			elif (len(k) == 2) or (len(k) == 3 and k[2] == self['MODE'].upper()):
				if not self.__ex_libs.has_key(k[0].lower()):
					self.__ex_libs[k[0].lower()]=[]
				self.__ex_libs[k[0].lower()].append((k[1],el_flags[key]))

		# Setting of install functions
		if self._dict.has_key('INSTALL_LINKS') and self['INSTALL_LINKS']!=0:
			if os.name=='nt':
				self['INSTALL']=utils.install_win
			elif self._dict.has_key('USE_SYMBOLIC_LINKS') and self['USE_SYMBOLIC_LINKS']:
				self['INSTALL']=utils.install_linux_sl
			else:
				self['INSTALL']=utils.install_linux_hl

		# Regexps compilation
		self.__unbreakable_re=re.compile('(\w*)_UNBREAKABLE$')
		self.__mode_target_re=(	re.compile('(\w*)_(COMMON|'+self['MODE'].upper()+')(|_LIB)$'),
								re.compile('(\w*)_(COMMON|'+self['MODE'].upper()+')(|_DLL)$'),
								re.compile('(\w*)_(COMMON|'+self['MODE'].upper()+')(|_PROG)$'))

		# Generate one solution for both x86 and x64 platforms
		if self['MODE'] == 'msvsproj' and os.name == 'nt':
			self.EdSimStaticLibrary = self.__MSVSProj_EdSimStaticLibrary
			self.EdSimSharedLibrary = self.__MSVSProj_EdSimSharedLibrary
			self.EdSimProgram = self.__MSVSProj_EdSimProgram
			self.buildMSVSProj = self.buildMSVSProj

			self._dict['MSVS_PROJECT_TARGETS'] = [('debug', 'x86', 'Win32'), ('release', 'x86', 'Win32'), ('debug', 'x86_64', 'x64'), ('release', 'x86_64', 'x64')]

			self.SConsignFile('./.sconsign-msvsproj.dblite')
		else:
			self.SConsignFile('./.sconsign-'+self['ARCHITECTURE']+'-'+os.name+'-'+self['TOOL']+'.dblite')

		print 'Architecture:\t', self['ARCHITECTURE']
		print 'Tool:\t\t', self['TOOL']
		print 'Mode:\t\t', self['MODE'],'\n'

	def __setupFlags(self,dict,target,target_index):
		if self['TOOL']=='msvc':
			utils.append_to_dict(dict,'CCFLAGS',['/Fd' + self.File(target+'.pdb').abspath])

		flags={}
		utils.read_config(self['CONFIG_PATHS'],self['ARCHITECTURE']+'-'+self['TOOL']+'-options.py',flags,{'_MODE_':self['MODE'],'_TOPDIR_':self['TOP_DIR'],'_ARCHITECTURE_':self['ARCHITECTURE']})

		ub={}
		for (k,v) in flags.iteritems():
			res=self.__mode_target_re[target_index].search(k)
			
			if res!=None:
				utils.append_to_dict(dict,res.group(1),v)
			else:
				res=self.__unbreakable_re.search(k)
				if res!=None:
					ub[res.group(1)]=v

		for (k,v) in ub.iteritems():
			dict[k]=v

	def __setupLibs(self,dict,libs,resource,ex_libs):
		if libs!=None:
			utils.append_to_dict(dict,'LIBS',libs)

		if resource!=None:
			res = map(lambda x: self.RES(x),resource)
			utils.append_to_dict(dict,'LIBS',res)

		if ex_libs==None: return

		for lib in ex_libs:
			for t in self.__ex_libs[lib]:
				if t[0] == 'MERGEFLAGS':
					tmp=self.ParseFlags(t[1]);
					for (k,v) in tmp.iteritems():
						utils.append_to_dict(dict,k,v)
					continue

				utils.append_to_dict(dict,t[0],t[1])

	def find_cppdefine(self, cppdefs, dfn):
		sz = len(dfn)
		for i in cppdefs:
			if i[0] == '"': part = i[1:sz+1]
			else: part = i[:sz]
			if part == dfn: return i
		return None

	def __build(self, func, target, target_index, source, header, resource, libs, external_libs, not_linked_dependencies, params):
		parameters = self._dict.copy()

		for (k,v) in params.iteritems():
			utils.append_to_dict(parameters, k, v)

		self.__setupFlags(parameters, target, target_index)
		self.__setupLibs(parameters, libs, resource, external_libs)

		if not parameters.has_key('CPPDEFINES'):
			parameters['CPPDEFINES'] = ['"ED_LOG_MODULE=""%s"""' % target.upper(), '"ED_MODULE_NAME=""%s"""' % target.upper()]
		else:
			if not self.find_cppdefine(parameters['CPPDEFINES'], 'ED_LOG_MODULE'):
				parameters['CPPDEFINES'].append('"ED_LOG_MODULE=""%s"""' % target.upper())
			if not self.find_cppdefine(parameters['CPPDEFINES'], 'ED_MODULE_NAME'):
				parameters['CPPDEFINES'].append('"ED_MODULE_NAME=""%s"""' % target.upper())	

		obj = func(target = target, source = source, **parameters)
		self.Precious(obj)

		if not_linked_dependencies:
			self.Depends(obj, not_linked_dependencies)
	
		self.Depends(obj,'copy_sdk_libs')

		return obj

	def __getInstallBinPath(self,params):
		if params.has_key('INSTALL_BIN_PATH'):
			return params['INSTALL_BIN_PATH']
		return self['INSTALL_BIN_PATH']
	
	def __getInstallLibPath(self,params):
		if params.has_key('INSTALL_LIB_PATH'):
			return params['INSTALL_LIB_PATH']
		return self['INSTALL_LIB_PATH']

	# Generate one solution for both x86 and x64 platforms
	def buildMSVSProj(self, target, target_index, file, srcs, incs, resource, libs, external_libs, not_linked_dependencies, params):
		runfile = map(lambda x: self['TOP_DIR'] + '/bin/' + x[1] + '/msvc_' + self['MSVS_VERSION'] + '/' + x[0] + '/' + file, self['MSVS_PROJECT_TARGETS'])

		res = []
		if resource != None:
			res = map(lambda x: os.path.abspath(x), resource)

		parameters = self._dict.copy()
		self.__setupFlags(parameters, target, target_index)
		self.__setupLibs(parameters, libs, resource, external_libs)

		return self.MSVSProject(
					target = self['TOP_DIR'] + 'Make/msvs/' + self['MSVS_VERSION'] + '/' + target + self['MSVSPROJECTSUFFIX'],
					srcs = map(lambda x: os.path.abspath(str(x)), srcs),
					incs = map(lambda x: os.path.abspath(str(x)), incs),
					resources = res,
					misc = os.path.abspath('./SConscript'),
					variant = map(lambda x: x[0] + '|' + x[2], self['MSVS_PROJECT_TARGETS']),
					buildtarget = map(lambda x: 'mode=' + x[0] + '\" \"arch=' + x[1] +'\" \"' + target, self['MSVS_PROJECT_TARGETS']),
					runfile = runfile,
					auto_build_solution = 0,
					CPPPATH = map(lambda x : os.path.abspath(str(x)), parameters['CPPPATH'] + (params['CPPPATH'] if 'CPPPATH' in params else [])),
					CPPDEFINES = parameters['CPPDEFINES'] + (params['CPPDEFINES'] if 'CPPDEFINES' in params else [])
				)
	
	def EdSimStaticLibrary(self, target, source, header, resource = None, external_libs = None, not_linked_dependencies = None, **params):
		if self['DONT_BUILD_DEPENDENCIES']:
			if not target in SCons.Script.BUILD_TARGETS: return

		lib = self.__build(self.StaticLibrary, target, self.TARGET_LIB, source, header, resource, None, external_libs, not_linked_dependencies, params)
		
		inst = self.Install(self.__getInstallLibPath(params),lib)
	
		self.Alias(['install',target], inst)

		return lib

	def EdSimSharedLibrary(self, target, source, header, resource = None, external_libs = None, libs = None, not_linked_dependencies = None, **params):
		if self['DONT_BUILD_DEPENDENCIES']:
			if not target in SCons.Script.BUILD_TARGETS: return

		lib = self.__build(self.SharedLibrary, target, self.TARGET_DLL, source, header, resource, libs, external_libs, not_linked_dependencies, params)

		if os.name != 'nt':
			inst = self.Install(self.__getInstallLibPath(params), lib)
			self.Alias(['install', target], inst)
		else:
			inst_bin = self.Install(self.__getInstallBinPath(params), lib[0])
			inst_lib = self.Install(self.__getInstallLibPath(params), lib[1:])
			
			self.Depends(inst_lib,inst_bin)
			self.Alias(['install', target], [inst_bin, inst_lib])

		return lib

	def EdSimProgram(self, target, source, header, resource = None, external_libs = None, libs = None, not_linked_dependencies = None, **params):
		if self['DONT_BUILD_DEPENDENCIES']:
			if not target in SCons.Script.BUILD_TARGETS: return

		prog = self.__build(self.Program, target, self.TARGET_PROG, source, header, resource, libs, external_libs, not_linked_dependencies, params)

		inst = self.Install(self.__getInstallBinPath(params), prog)
			
		self.Alias(['install',target], inst)

		return prog
	
	def __MSVSProj_EdSimStaticLibrary(self, target, source, header, resource = None, external_libs = None, libs = None, not_linked_dependencies = None, **params):
		fileName = self['LIBPREFIX'] + target + self['LIBSUFFIX']
		proj = self.buildMSVSProj(target, self.TARGET_LIB, fileName, source, header, resource, libs, external_libs, not_linked_dependencies, params)
		self.Alias(['install', target], proj)

		return proj

	def __MSVSProj_EdSimSharedLibrary(self, target, source, header, resource = None, external_libs = None, libs = None, not_linked_dependencies = None, **params):
		fileName = self['SHLIBPREFIX'] + target + self['SHLIBSUFFIX']
		proj = self.buildMSVSProj(target, self.TARGET_DLL, fileName, source, header, resource, libs, external_libs, not_linked_dependencies, params)
		self.Alias(['install', target], proj)

		return proj

	def __MSVSProj_EdSimProgram(self, target, source, header, resource = None, external_libs = None, libs = None, not_linked_dependencies = None, **params):
		fileName = self['PROGPREFIX'] + target + self['PROGSUFFIX']
		proj = self.buildMSVSProj(target, self.TARGET_PROG, fileName, source, header, resource, libs, external_libs, not_linked_dependencies, params)
		self.Alias(['install',target], proj)

		return proj

	def __rglob(self,dirName,buildDir,pattern,res):
		for i in os.listdir(dirName):
			if i[0]=='.': continue

			dn=dirName+i+'/'
			if os.path.isdir(dn):
				self.__rglob(dn,buildDir+i+'/',pattern,res)
	
		res+=self.Glob(buildDir+pattern)

	def RGlob(self, pattern):
		(dirName,pat)=os.path.split(pattern)

		node=self.Dir(dirName)

		buildDir=node.abspath+'/'

		# as variant_dir may be changed during build
		node=node.srcnode()
		while node!=node.srcnode():
			node=node.srcnode()

		realDir=node.abspath+'/'

		res=[]
		self.__rglob(realDir,buildDir,pat,res)
		return res

	def processSconscripts(self, sconscripts):
		print 'Processing dir: ', os.getcwd()
		for i in sconscripts:
			print '\t',os.path.abspath(i)
	
		self.SConscript(sconscripts)

	def isProjGenMode(self):
		return self['MODE'] == 'msvsproj'

	def getProjectName(self):
		return "EDGE"

	def getUserVariable(self, name):
		if not self._dict.has_key('USER_VARIABLES'):
			return None

		m = self._dict['USER_VARIABLES']
		
		if m.has_key(name):
			return m[name]
		else:
			return None;
