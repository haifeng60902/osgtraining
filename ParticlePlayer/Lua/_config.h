/**
 * Lua Wrapper library
 * (C)opyright 2004 by Dmitry S. Baikov
 *
 * Eagle Dynamics has non-exclusive rights to use, sell and sublicense this code.
 *
 */
#ifndef _Lua_config_h_
#define _Lua_config_h_


#ifndef ED_LUA_EXTERN
#if defined(ED_LUA_INTERNALS) || defined(_USRDLL)
#define ED_LUA_EXTERN __declspec(dllexport)
#else
#define ED_LUA_EXTERN __declspec(dllimport)
#endif
#endif


#ifndef ED_LUA_API
#define ED_LUA_API __stdcall
#endif


/**
 * @brief Lua bindings library.
 */
namespace Lua {}


#endif /* _Lua_config_h_ */
