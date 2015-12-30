#include "RunicGlyphTable.hpp"

#include <iostream>
#include <algorithm>

#include "RunicGlyph.hpp"
namespace RunicCore {

// #############################################################################
// ### RGlyfTable ##############################################################
// #############################################################################

RGlyfTable::RGlyfTable(RTableEntry& entry) :
	RTableEntry(entry)
{
}


RGlyfTable::~RGlyfTable()
{
}


void RGlyfTable::decrypt()
{
}


Runic::RawGlyph RGlyfTable::decryptGlyph(const int glyph_offset_begin, const int glyph_offset_end)
{
	table_binary->seek(range.begin() + glyph_offset_begin);
	Runic::RawGlyph glyph;
	glyph.number_of_contours = table_binary->getInt16();
	glyph.x_min = table_binary->getInt16();
	glyph.y_min = table_binary->getInt16();
	glyph.x_max = table_binary->getInt16();
	glyph.y_max = table_binary->getInt16();

	std::cout << "number_of_contours " << glyph.number_of_contours << std::endl;
	std::cout << "x_min " << glyph.x_min << std::endl;
	std::cout << "y_min " << glyph.y_min << std::endl;
	std::cout << "x_max " << glyph.x_max << std::endl;
	std::cout << "y_max " << glyph.y_max << std::endl;

	if (glyph.number_of_contours >= 0) { // simple

		auto& points = glyph.points;

		// contour
		for (int i = 0; i < glyph.number_of_contours; ++i) {
			uint16_t end_pt = table_binary->getUInt16();

			if (end_pt >= points.size()) {
				points.resize(end_pt + 1);
			}
			points[end_pt].setToEndPoint();
		}

		// points
		unsigned int pts = points.size();
		glyph.instruction_length = table_binary->getUInt16();

		//instructions
		auto& inst = glyph.instructions;

		for (unsigned int i = 0; i < glyph.instruction_length; ++i) {
			inst.push_back(table_binary->getUInt8());
		}

		unsigned int flag_count = 0;

		// flags
		while (flag_count < pts) {
			uint8_t flag = table_binary->getUInt8();
			uint8_t recurse = 1;

			if ((flag & Runic::GlyphPoint::repeate) != 0) {
				recurse += table_binary->getUInt8();
			}

			for (int j = 0; j < recurse; ++j) {
				points[flag_count].setFlag(flag);
				++flag_count;
			}
		}

		// decrypting X
		int16_t x_from_base = 0;
		for (unsigned int i = 0; i < pts; ++i) {
			Runic::GlyphPoint& glyph_point = points[i];
			int16_t x_offset = 0;

			if (glyph_point.xShortVector()) {
				x_offset = table_binary->getUInt8();

				if (!glyph_point.xIsPositive()) {
					x_offset *= -1;
				}
			} else {
				x_offset = 0;

				if (!glyph_point.xIsSame()) {
					x_offset = table_binary->getUInt16();
				}
			}
			x_from_base += x_offset;
			glyph_point.pos.first = x_from_base;
		}

		// decrypting Y
		int16_t y_from_base = 0;
		for (unsigned int i = 0; i < pts; ++i) {
			Runic::GlyphPoint& glyph_point = points[i];
			int16_t y_offset = 0;

			if (glyph_point.yShortVector()) {
				y_offset = table_binary->getUInt8();

				if (!glyph_point.yIsPositive()) {
					y_offset *= -1;
				}
			} else {
				y_offset = 0;

				if (!glyph_point.yIsSame()) {
					y_offset = table_binary->getUInt16();
				}
			}
			y_from_base += y_offset;
			glyph_point.pos.second = y_from_base;
		}
	} else {
		// TODO!!!
		std::cout << "error!!! Composite Glyph! Not supported yet" << std::endl;
	}

	if (table_binary->act() < range.begin() + glyph_offset_end) {
		int left_size = (range.begin() + glyph_offset_end) - table_binary->act();
		std::cout << "not the end! Still Left: " << left_size << std::endl;
	}
	else if (table_binary->act() == range.begin() + glyph_offset_end) {
		std::cout << "equal!" << std::endl;
	}

	return glyph;
}


std::string RGlyfTable::toStr() const
{
	return std::string("GlyfTable");
}

} // RunicCore namespace
