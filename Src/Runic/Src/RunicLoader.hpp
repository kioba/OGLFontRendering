#ifndef __RUNIC_LOADER__
#define __RUNIC_LOADER__

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>

#include <assert.h>

#include "Runic.hpp"
#include "RunicExceptions.hpp"
#include "RunicTypes.hpp"

namespace RunicCore {

// #############################################################################
// ### RLoader #################################################################
// #############################################################################

class RLoader
{
private: /* variables */
	std::string path;
	std::shared_ptr<RBinary> bin;
	std::unique_ptr<RFileHeader> header;

	enum TTFTableStr {
		id_cmap	= 0,
		id_head	= 1,
		id_hhea	= 2,
		id_hmtx	= 3,
		id_maxp	= 4,
		id_name	= 5,
		id_OS2	= 6,
		id_post	= 7,
		id_cvt	= 8,
		id_fpgm	= 9,
		id_glyf	= 10,
		id_loca	= 11,
		id_prep	= 12
	};

private: /* functions */
	void LoadTTF();
	void ReadTables();

public: /* functions */
	RLoader(const std::string file_path);
	~RLoader();

	std::unique_ptr<RFileHeader> moveContent();
};

} // Runic namespace

#endif // __RUNIC_LOADER__
