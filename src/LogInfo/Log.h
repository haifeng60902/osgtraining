#ifndef _LOG_H_ 
#define _LOG_H_

#include <stdarg.h>

// taken from POSIX syslog interface
enum {
	//ED_LOG_EMERG  = 1<<0, /**< system is unusable */
	E_ALERT    = 1<<1, /**< action must be taken immediately */
	//ED_LOG_CRIT   = 1<<2, /**< critical conditions */
	E_ERROR    = 1<<3, /**< error conditions */
	E_WARNING  = 1<<4, /**< warning conditions */
	//ED_LOG_NOTICE = 1<<5, /**< normal, but significant, condition */
	E_INFO     = 1<<6, /**< informational message */
	E_DEBUG    = 1<<7, /**< debug-level message */

	/* special log level for debug dumps/traces */
	E_TRACE    = 1<<8, /**< trace message */

	/* Never lose messages: ed_log() becomes blocking. Implied for ED_LOG_TRACE */
	E_RELIABLE = 1<<15,
};

void d_vlogf(const char *module, int level, const char *fmt, va_list args);

static inline
void d_logf(const char *module, int level, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	d_vlogf(module, level, fmt, args);
	va_end(args);
}

#define _D_LOG(level, ...) d_logf(LOG_MODULE, level, __VA_ARGS__)

#define LOG_ALERT(...)    _D_LOG(E_ALERT,   __VA_ARGS__)
#define LOG_ERROR(...)    _D_LOG(E_ERROR,   __VA_ARGS__)
#define LOG_WARNING(...)  _D_LOG(E_WARNING, __VA_ARGS__)
#define LOG_INFO(...)     _D_LOG(E_INFO,    __VA_ARGS__)

#endif	//_LOG_H_