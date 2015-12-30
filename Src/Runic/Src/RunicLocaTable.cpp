#include "RunicLocaTable.hpp"

namespace RunicCore {

// #############################################################################
// ### RLocaTable ##############################################################
// #############################################################################

RLocaTable::RLocaTable(RTableEntry& entry) :
	RTableEntry(entry),
	loc_format(-1)
{
}


RLocaTable::~RLocaTable()
{
}

int RLocaTable::getGlyphLocation(const int index) const
{
	if (index >= num_glyphs) {
		return 0;
	}

	int jump_size = (loc_format == 0) ? sizeof(uint16_t) : sizeof(uint32_t);
	RRange::Iter loca_pos = range.begin() + index * jump_size;

	int glyph_offset = 0;
	table_binary->seek(loca_pos);

	if (loc_format == 0) {
		glyph_offset = table_binary->getUInt16();
		// offset is half of the unit, make it double
		glyph_offset *= sizeof(uint32_t) / sizeof(uint16_t);
	} else {
		glyph_offset = table_binary->getUInt32();
	}

	return glyph_offset;
}


void RLocaTable::setLocFormat(int index_to_loc_format)
{
	loc_format = index_to_loc_format;
}


void RLocaTable::setNumGlyphs(int numGlyphs)
{
	num_glyphs = numGlyphs;
}


void RLocaTable::decrypt()
{
}


std::string RLocaTable::toStr() const
{
	return std::string("LocaTable");
}

} // RunicCore namespace
