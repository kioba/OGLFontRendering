#include "RunicLoader.hpp"
#include "RunicTypes.hpp"

#include <algorithm>
#include <memory>
#include <iomanip>

namespace RunicCore {

// #############################################################################
// ### RLoader #################################################################
// #############################################################################

RLoader::RLoader(const std::string file_path) :
	path(file_path),
	header(new RFileHeader)
{
	if (path.empty()) {
		std::stringstream ss;
		ss << "Filename Empty!";
		throw RunicFileException(ss.str());
	}

	LoadTTF();
	ReadTables();
}


RLoader::~RLoader()
{
}


void RLoader::LoadTTF()
{
	std::ifstream stream(path, std::fstream::binary);

	if (!stream.is_open()) {
		std::stringstream ss;
		ss << "Could not open file: " << path;
		throw RunicFileException(ss.str());
	}

	bin = std::make_shared<RBinary>(stream, Endianness::big);

	if (stream.fail()) {
		stream.close();
		throw RunicFileException(path);
	}

	stream.close();
}


void RLoader::ReadTables()
{
	header->setBinary(bin);
	header->decrypt();

//	std::cout << header->toStr() << std::endl;
//	std::cout << header->tablesToStr() << std::endl;
}


std::unique_ptr<RFileHeader> RLoader::moveContent()
{
	return std::move(header);
}

// LocaTable	RLoader::ReadLocaTable ()
// {
// 	const TTFTableEntry* head_entry = GetTableEntry (TTF_table_str[TTFTableStr::id_loca]);
// 	const char* iterator = head_entry->begin;

// 	LocaTable loca_table;

// 	for (int i = 0; i < maxp.num_glyphs + 1; ++i) {
// 		uint32_t offset = 0;

// 		if (head.index_to_loc_format == 1) {
// 			offset = GetShiftUInt32 (iterator);
// 		} else {
// 			offset = 2 * GetShiftUInt16 (iterator);
// 		}

// 		loca_table.push_back (offset);
// 	}

// 	// std::cout << "--------------------------------------------------------------------------" << std::endl;

// 	// for (int i = 0; i < loca_table.size(); ++i) {
// 	// 	std::cout << "#" << i << ": " << loca_table[i] << std::endl;
// 	// }

// 	return loca_table;
// }

} // namespace Runic
