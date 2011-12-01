#ifndef DX11BACKEND_H
#define DX11BACKEND_H

#ifdef EDGE

#define DX11BACKEND_API

#else

#ifdef DX11BACKEND_EXPORTS
#define DX11BACKEND_API __declspec(dllexport)
#else
#define DX11BACKEND_API __declspec(dllimport)
#endif

#endif

#endif //
