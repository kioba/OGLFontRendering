#ifndef __RUNIC_GLYPH_TABLE__
#define __RUNIC_GLYPH_TABLE__

#include <string>

#include "RunicTypes.hpp"
#include "RunicGlyph.hpp"

namespace RunicCore {

// #############################################################################
// ### RGlyfTable ##############################################################
// #############################################################################

class RGlyfTable :
	public RTableEntry
{
public:
	RGlyfTable(RTableEntry& entry);
	virtual ~RGlyfTable();
	virtual void decrypt() override;

	Runic::RawGlyph decryptGlyph(const int glyph_offset_begin, const int glyph_offset_end);

	virtual std::string toStr() const override;
};

} // RunicCore namespace

#endif // __RUNIC_GLYPH_TABLE__
