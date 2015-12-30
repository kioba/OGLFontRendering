#include "RunicHeadTable.hpp"

namespace RunicCore {

// #############################################################################
// ### RHeadTable ##############################################################
// #############################################################################

RHeadTable::RHeadTable(RTableEntry& entry) :
	RTableEntry(entry)
{
}

RHeadTable::~RHeadTable()
{
}

void RHeadTable::decrypt()
{
	table_binary->seek(range.begin());
	table_version = table_binary->getInt32();
	font_revision = table_binary->getInt32();
	check_sum_adjustment = table_binary->getUInt32();
	magic_number = table_binary->getUInt32();
	flags = table_binary->getUInt16();
	units_per_em = table_binary->getUInt16();

	created_date = table_binary->getInt32();
	created_date <<= 32;
	created_date += table_binary->getInt32();

	modified_date = table_binary->getInt32();
	modified_date <<= 32;
	modified_date += table_binary->getInt32();

	xmin = table_binary->getInt16();
	ymin = table_binary->getInt16();
	xmax = table_binary->getInt16();
	ymax = table_binary->getInt16();

	mac_style = table_binary->getUInt16();
	lowest_rec_PPEM = table_binary->getUInt16();
	font_direction_hint = table_binary->getInt16();
	index_to_loc_format = table_binary->getInt16();
	glyph_data_format = table_binary->getInt16();
}


std::string RHeadTable::toStr() const
{
	std::stringstream ss;

	ss << "table_version: " << table_version << std::endl;
	ss << "font_revision: " << font_revision << std::endl;
	ss << "check_sum_adjustment: " << check_sum_adjustment << std::endl;
	ss << "magic_number: " << magic_number << std::endl;
	ss << "flags: " << flags << std::endl;
	ss << "units_per_em: " << units_per_em << std::endl;
	ss << "created_date: " << created_date << std::endl;
	ss << "modified_date: " << modified_date << std::endl;
	ss << "xmin: " << xmin << std::endl;
	ss << "ymin: " << ymin << std::endl;
	ss << "xmax: " << xmax << std::endl;
	ss << "ymax: " << ymax << std::endl;
	ss << "mac_style: " << mac_style << std::endl;
	ss << "lowest_rec_PPEM: " << lowest_rec_PPEM << std::endl;
	ss << "font_direction_hint: " << font_direction_hint << std::endl;
	ss << "index_to_loc_format: " << index_to_loc_format << std::endl;
	ss << "glyph_data_format: " << glyph_data_format << std::endl;

	return ss.str();
}


} // RunicCore
