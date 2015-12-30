#ifndef __RAGNA__
#define __RAGNA__

#if defined (WIN32)
	#if defined (_MSC_VER)
		#pragma warning(disable: 4251)
	#endif

	#define RAGNA_EXPORTS
	#if defined(RAGNA_EXPORTS)
		#define RAGNA_API __declspec(dllexport)
	#else
		#define RAGNA_API __declspec(dllimport)
	#endif
#else
	#define RAGNA_API
#endif

#endif // __RAGNA__
