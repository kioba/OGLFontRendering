#ifndef __RUNIC__
#define __RUNIC__

#if defined (WIN32)

	// microsoft dll compiler error
	// https://msdn.microsoft.com/en-us/library/esew7y1w.aspx
	#if defined (_MSC_VER)
		#pragma warning(disable: 4251)
	#endif

	#define RUNIC_EXPORTS
	#if defined(RUNIC_EXPORTS)
		#define RUNIC_API __declspec(dllexport)
	#else
		#define RUNIC_API __declspec(dllimport)
	#endif
#else
	#define RUNIC_API
#endif

#endif // __RUNIC__
