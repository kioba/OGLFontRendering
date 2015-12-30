#ifndef __RUNIC_EXCEPTIONS__
#define __RUNIC_EXCEPTIONS__

// #include <exception>
#include <string>
#include <sstream>
#include "Runic.hpp"

namespace RunicCore {

// #############################################################################
// ### RunicException ##########################################################
// #############################################################################

class RUNIC_API RunicException
	// public std::exception
{
protected: /* variables */
	std::string m_msg;

public: /* functions */
	RunicException ();
	RunicException (std::string exception_msg);
	virtual ~RunicException () throw ();

	virtual const char* what() const throw ();
};


// #############################################################################
// ### RunicFileException ######################################################
// #############################################################################

class RUNIC_API RunicFileException :
	public RunicException
{
public: /* functions */
	RunicFileException (std::string exception_msg);
	virtual ~RunicFileException () throw ();
};


} //Runic namespace

#endif // __RUNIC_EXCEPTIONS__
