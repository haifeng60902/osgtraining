import os

def get_home_dir():
	if os.environ.has_key('HOME'):
		return os.environ['HOME']

	if os.name == 'nt':
		return os.environ['HOMEDRIVE'] + os.environ['HOMEPATH']

	return ''

def install_win(dest, source, env):
	if os.system(''.join( ['fsutil.exe hardlink create "', dest, '" "', source, '"'] )) != 0:
		os.system(''.join( ['copy "', source, '" "', dest, '"'] ))

def install_linux_sl(dest, source, env):
	os.system(''.join(['ln -f --symbolic \'', os.path.abspath(source), "' '", dest, "'"]))

def install_linux_hl(dest, source, env):
	try:
		os.unlink(dest)
	except:
		pass
	os.link(source, dest)
	
def read_config(cfgPaths, cfgFileName, dictionary, export_dict):
	res = False
	for i in cfgPaths:
		f = i + '/' + cfgFileName
		if (os.access(f, os.R_OK)):
			execfile(f, export_dict, dictionary)
			res = True
	if not res:
		raise Exception("Can't open %s config file!" % cfgFileName)

def append_to_dict(dict, key, value):
	if not dict.has_key(key):
		dict[key] = value
	else:
		dict[key] = dict[key] + value
