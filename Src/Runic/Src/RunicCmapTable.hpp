#ifndef __RUNIC_CMAP_TABLE__
#define __RUNIC_CMAP_TABLE__

#include <string>

#include "RunicTypes.hpp"

namespace RunicCore {

class FormatTable;

// #############################################################################
// ### RCmapTable ##############################################################
// #############################################################################

class RCmapTable :
	public RTableEntry
{
public: /* variables */
	uint16_t version;
	uint16_t num_tables;
	std::vector<FormatTable> formats;

public: /* functions */
	RCmapTable(RTableEntry& entry);
	~RCmapTable();

	virtual void decrypt() override;
	virtual std::string toStr() const override;

	int	getGlyphIndex(CharCode code) const;
};


// #############################################################################
// ### FormatTable #############################################################
// #############################################################################

class FormatTable
{
public: /* variables */
	uint16_t platform_id;
	uint16_t encoding_id;
	uint32_t offset;

public: /* functions */
	FormatTable();
	virtual ~FormatTable();

	int	getGlyphIndex(std::shared_ptr<RBinary> binary, RRange::Iter begin, const CharCode& code) const;
	int formatType0(std::shared_ptr<RBinary> binary, const CharCode& code) const;
	int formatType4(std::shared_ptr<RBinary> binary, const CharCode& code) const;

	std::string formToStr() const;
};


} // RunicCore namespace

#endif // __RUNIC_CMAP_TABLE__
