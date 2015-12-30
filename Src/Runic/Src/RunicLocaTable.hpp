#ifndef __RUNIC_LOCA_TABLE__
#define __RUNIC_LOCA_TABLE__

#include <string>

#include "RunicTypes.hpp"

namespace RunicCore {

// #############################################################################
// ### RLocaTable ##############################################################
// #############################################################################

class RLocaTable :
	public RTableEntry
{
private: /* variables */
	int loc_format;	// 0 for short offsets, 1 for long.
	int num_glyphs;

public: /* functions */
	RLocaTable(RTableEntry& entry);
	virtual ~RLocaTable();

	int getGlyphLocation(const int index) const;

	void setLocFormat(int index_to_loc_format);
	void setNumGlyphs(int numGlyphs);

	virtual void decrypt() override;
	virtual std::string toStr() const override;
};

} // RunicCore Namespace

#endif // __RUNIC_LOCA_TABLE__
