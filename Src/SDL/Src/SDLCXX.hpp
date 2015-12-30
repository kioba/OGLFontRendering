#ifndef __SDLCXX_HPP__
#define __SDLCXX_HPP__

// #############################################################################
// ### SDLCXX_API ##############################################################
// #############################################################################

#if defined(WIN32)
	#if defined (_MSC_VER)
		#pragma warning(disable: 4251)
	#endif

	#define SDLCPP_EXPORTS
	#if defined (SDLCPP_EXPORTS)
		#define SDLCXX_API __declspec(dllexport)
	#else
		#define SDLCXX_API __declspec(dllimport)
	#endif
#else
	#define SDLCXX_API
#endif

#endif // __SDLCXX_HPP__
