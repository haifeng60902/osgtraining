# encoding: utf-8

WARNINGS_AS_ERRORS = [
	'/we4715',
	'/we4258',
	'/we4482',
	'/we4805',
	'/we4172',
	'/we4723',
	'/we4554',
	'/we4150', # deletion of pointer to incomplete type
	'/we4700', # uninitialized local variable used
	'/we4552', # operator has no effect; expected operator with side-effect
	'/we4293', # 'operator' : shift count negative or too big, undefined behavior
	'/we4005', # macro redefinition
	'/we4930', # prototyped function not called (was a variable definition intended?)
	'/we4789', # destination of memory copy is too small
	'/we4013', #  'memcpy' undefined; assuming extern returning int
	'/we4661', # 'identifier' : no suitable definition provided for explicit template instantiation request
	'/we4231', # 'extern' before template explicit instantiation
	'/we4311', # 'variable' : pointer truncation from 'type' to 'type'
	'/we4259', # 'identifier' : pure virtual function was not defined
	'/we4291', # 'declaration' : no matching operator delete found; memory will not be freed if initialization throws an exception
	'/we4290', # C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
	'/we4731', # 'pointer' : frame pointer register 'register' modified by inline assembly code
	'/we4804', # 'operation' : unsafe use of type 'bool' in operation
	'/we4002', # too many actual parameters for macro
	'/we4099', # type name first seen using 'struct' now seen using 'class'
	'/we4808', # case 'value' is not a valid value for switch condition of type 'bool'
	'/we4065', # switch statement contains 'default' but no 'case' labels
	'/we4717', # 'function' : recursive on all control paths, function will cause runtime stack overflow
	'/we4390', # ';' : empty controlled statement found; is this the intent?
	'/we4007', # 'function' : must be 'attribute'
	'/we4183', # 'identifier': missing return type; assumed to be a member function returning 'int'
	'/we4060', # switch statement contains no 'case' or 'default' labels
	'/we4309', # 'conversion' : truncation of constant value
	'/we4067', # unexpected tokens following preprocessor directive - expected a newline

	# We need C4238 and C4239 to be an always error cause they are always error in GCC
	'/we4238', # nonstandard extension used : class rvalue used as lvalue
    '/we4239', # nonstandard extension used : 'token' : conversion from 'type' to 'type'

#	'\we4251', # 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#	'\we4250', # 'class1' : inherits 'class2::member' via dominance
#	'\we4275', # non – DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
]
