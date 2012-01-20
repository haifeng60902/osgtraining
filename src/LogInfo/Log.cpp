#include "Log.h"

#include "LogInfo.h"

void d_vlogf(const char *module, int level, const char *fmt, va_list args)
{
	LogInfo::Instance().Print(module, level, fmt, args);
}