CPPDEFINES = [
    'EDGE',
    'BOOST_ALL_NO_LIB',
    '\"ED_LOG_MODULE=\\\"' + env['TARGET_NAME'].upper() + '\\\"\"',
    '\"ED_MODULE_NAME=\\\"' + env['TARGET_NAME'].upper() + '\\\"\"'
]

if env.getUserVariable('USE_NEDMALLOC'):
	CPPDEFINES.append('USE_NEDMALLOC_STL_ALLOCATOR')

