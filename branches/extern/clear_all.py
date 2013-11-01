#!/usr/bin/python
# encoding: utf-8

import shutil
import glob
import os

targets = [
	'.build',
	'bin/x86',
	'bin/x86_64',
	'lib/x86',
	'lib/x86_64',
	'Make/.sconsign*',
	'.sconsign*'
]

if __name__ == "__main__":
	# remove files

	for i in targets:
		for j in glob.glob(i):
			if os.path.isdir(j):
				shutil.rmtree(path = j, ignore_errors = True)
			else:
				os.remove(j)
			print 'Removed ', j
