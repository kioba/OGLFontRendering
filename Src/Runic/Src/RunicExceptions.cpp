#include "RunicExceptions.hpp"

namespace RunicCore {

// #############################################################################
// ### RunicException ##########################################################
// #############################################################################

RunicException::RunicException() :
	m_msg("Unspecified Runic exception")
{
}


RunicException::RunicException(std::string exception_msg) :
	m_msg(exception_msg)
{
}


RunicException::~RunicException() throw()
{
}


const char* RunicException::what() const throw()
{
	return m_msg.c_str();
}


// #############################################################################
// ### RunicFileException ######################################################
// #############################################################################

RunicFileException::RunicFileException(std::string file_path)
{
	std::stringstream ss;
	ss << "Unknown error reading file: " << file_path << std::endl;
	m_msg = ss.str();
}


RunicFileException::~RunicFileException() throw()
{
}

} // Runic namespace
