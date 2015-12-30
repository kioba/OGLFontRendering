#ifndef __RUNIC_HEAD_TABLE__
#define __RUNIC_HEAD_TABLE__

#include <cstdint>

#include "RunicTypes.hpp"

namespace RunicCore {

// #############################################################################
// ### RHeadTable ##############################################################
// #############################################################################

class RHeadTable :
	public RTableEntry
{
public: /* variables */
	int32_t table_version;
	int32_t font_revision;
	uint32_t check_sum_adjustment;
	uint32_t magic_number;
	uint16_t flags;
	uint16_t units_per_em;
	int64_t created_date;
	int64_t modified_date;
	uint16_t xmin;
	uint16_t ymin;
	uint16_t xmax;
	uint16_t ymax;
	uint16_t mac_style;
	uint16_t lowest_rec_PPEM;
	int16_t font_direction_hint;
	int16_t index_to_loc_format;
	int16_t glyph_data_format;

public: /* functions */
	RHeadTable(RTableEntry& entry);
	virtual ~RHeadTable();
	virtual void decrypt() override;
	virtual std::string toStr() const override;
};

} // RunicCore namespace

#endif // __RUNIC_HEAD_TABLE__
