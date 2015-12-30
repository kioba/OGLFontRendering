#include "RunicCmapTable.hpp"
#include <iostream>

namespace RunicCore {


// #############################################################################
// ### RCmapTable ##############################################################
// #############################################################################

RCmapTable::RCmapTable(RTableEntry& entry) :
	RTableEntry(entry),
	version(0),
	num_tables(0)
{
}


RCmapTable::~RCmapTable()
{
}


void RCmapTable::decrypt()
{
	table_binary->seek(range.begin());
	version = table_binary->getUInt16();

	if (version != 0) {
		throw RunicException("Incorrect CMAP table");
	}

	num_tables = table_binary->getUInt16();
	for (int i = 0; i < num_tables; ++i) {
		FormatTable form;
		form.platform_id = table_binary->getUInt16();
		form.encoding_id = table_binary->getUInt16();
		form.offset = table_binary->getUInt32();
		formats.push_back(form);
	}
}


std::string RCmapTable::toStr() const
{
	std::stringstream ss;

	ss << "cmap.version: " << version << std::endl;
	ss << "cmap.num_tables: " << num_tables << std::endl;

	return ss.str();
}


int RCmapTable::getGlyphIndex(CharCode code) const
{
	for (unsigned int i = 0; i < formats.size(); ++i) {
		if(code.platform == formats[i].platform_id && code.encode == formats[i].encoding_id) {
			return formats[i].getGlyphIndex(table_binary, range.begin(), code);
		}
	}

	return 0;
}



// #############################################################################
// ### FormatTable #############################################################
// #############################################################################

FormatTable::FormatTable()
{
}


FormatTable::~FormatTable()
{
}


int FormatTable::getGlyphIndex(std::shared_ptr<RBinary> binary, RRange::Iter begin, const CharCode& code) const
{
	binary->seek(begin + offset);
	int glyph_idx = 0;
	uint16_t format = binary->getUInt16();

	switch(format) {
		case 0:
			glyph_idx = formatType0(binary, code);
			break;

		case 4:
			glyph_idx = formatType4(binary, code);
			break;

		default:
			break;
	}
	return glyph_idx;
}


int FormatTable::formatType0(std::shared_ptr<RBinary> binary, const CharCode& code) const
{
	uint16_t length = binary->getUInt16();
	(void) length; //unsuded parameter
	uint16_t language = binary->getUInt16();

	if (code.language != language) {
		return 0;
	}

	for (int i = 0; i < 256; ++i) {
		if (code.char_code == binary->getUInt16()) {
			return i;
		}
	}

	return 0;
}


int FormatTable::formatType4(std::shared_ptr<RBinary> binary, const CharCode& code) const
{
	uint16_t length = binary->getUInt16();
	(void) length; //unsuded parameter
	uint16_t language = binary->getUInt16();

	if (code.language != language) {
		return 0;
	}

	uint16_t seg_count_x2 = binary->getUInt16();
	uint16_t search_range = binary->getUInt16();
	(void) search_range;
	uint16_t entry_selector = binary->getUInt16();
	(void) entry_selector;
	uint16_t range_shift = binary->getUInt16();
	(void) range_shift;
	uint16_t seg_count = seg_count_x2 >> 1;

	RRange::Iter end_count_pos = binary->act();
	RRange::Iter start_count_pos = end_count_pos + 2 + seg_count_x2; // +2 is the reserved pad betveen the end and the start array
	RRange::Iter id_delta_pos = start_count_pos + seg_count_x2;
	RRange::Iter id_range_offset_pos = id_delta_pos + seg_count_x2;

	// std::cout << "sizeof " << sizeof(uint16_t) << std::endl;
	// we need the last element to check the array
	binary->seek(end_count_pos + (seg_count - 1) * sizeof(uint16_t));

	uint16_t last = binary->getUInt16();

	if (last != 0xffff) {
		std::cerr << "CMAP ERROR! Last item is not equal to 0xffff!" << std::endl;
	}

	uint16_t reserve_pad = binary->getUInt16();

	if (reserve_pad != 0) {
		std::cerr << "CMAP ERROR! reserve_pad is not equal to 0!" << std::endl;
	}

	unsigned int index = seg_count;
	uint16_t start = 0;
	uint16_t end = 0;

	// linear search
	for (unsigned int i = 0; i < seg_count; ++i) {
		binary->seek(end_count_pos + i * 2);
		end = binary->getUInt16();
		binary->seek(start_count_pos + i * 2);
		start = binary->getUInt16();

		if (code.char_code >= start && code.char_code <= end) {
			index = i;
			break;
		}
	}

	// if index stil lequal to seg_count than no char found return with zero aka "unknown char"
	if (index == seg_count) {
		return 0;
	}

	// calculate glyph index
	binary->seek(id_delta_pos + index * 2);
	uint16_t id_delta = binary->getUInt16();
	binary->seek(id_range_offset_pos + index * 2);
	uint16_t id_range_offset = binary->getUInt16();

	// map code to its glyph index
	uint16_t glyph_index = 0;

	if (id_range_offset == 0) {
		glyph_index = (id_delta + static_cast<uint16_t>(code.char_code & 0xffff)) & 0xffff;
	} else {
		RRange::Iter glyph_index_pos = id_range_offset_pos + index * 2 + id_range_offset + 2 * (code.char_code - start);
		binary->seek(glyph_index_pos);
		glyph_index = binary->getUInt16();
	}

	std::cout << (char)code.char_code << " index: " << glyph_index << std::endl;
	return glyph_index;
}

std::string FormatTable::formToStr() const
{
	return "TODO!!!";
}


} // RunicCore namepsace
