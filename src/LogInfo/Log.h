#ifndef _LOG_H_ 
#define _LOG_H_

// taken from POSIX syslog interface
enum {
	//ED_LOG_EMERG  = 1<<0, /**< system is unusable */
	ED_LOG_ALERT    = 1<<1, /**< action must be taken immediately */
	//ED_LOG_CRIT   = 1<<2, /**< critical conditions */
	ED_LOG_ERROR    = 1<<3, /**< error conditions */
	ED_LOG_WARNING  = 1<<4, /**< warning conditions */
	//ED_LOG_NOTICE = 1<<5, /**< normal, but significant, condition */
	ED_LOG_INFO     = 1<<6, /**< informational message */
	ED_LOG_DEBUG    = 1<<7, /**< debug-level message */

	/* special log level for debug dumps/traces */
	ED_LOG_TRACE    = 1<<8, /**< trace message */

	/* Never lose messages: ed_log() becomes blocking. Implied for ED_LOG_TRACE */
	ED_LOG_RELIABLE = 1<<15,
};

static inline
void ed_logf(const char *module, int level, const char *fmt, ...)
{

}

#define _ED_LOG(level, ...) ed_logf(ED_LOG_MODULE, level, __VA_ARGS__)

#define ED_ALERT(...)    _ED_LOG(ED_LOG_ALERT,   __VA_ARGS__)
#define ED_ERROR(...)    _ED_LOG(ED_LOG_ERROR,   __VA_ARGS__)
#define ED_WARNING(...)  _ED_LOG(ED_LOG_WARNING, __VA_ARGS__)
#define ED_INFO(...)     _ED_LOG(ED_LOG_INFO,    __VA_ARGS__)

#endif	//_LOG_H_