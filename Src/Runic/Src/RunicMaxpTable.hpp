#ifndef __RUNIC_MAXP_TABLE__
#define __RUNIC_MAXP_TABLE__

#include "RunicTypes.hpp"

namespace RunicCore {

// #############################################################################
// ### RMaxpTable ##############################################################
// #############################################################################

class RMaxpTable :
	public RTableEntry
{
public: /* variables */
	int32_t table_version;
	uint16_t num_glyphs;
	uint16_t max_points;
	uint16_t max_contours;
	uint16_t max_composite_points;
	uint16_t max_composite_contours;
	uint16_t max_zones;
	uint16_t max_twilight_points;
	uint16_t max_storage;
	uint16_t max_function_defs;
	uint16_t max_instruction_defs;
	uint16_t max_stack_elements;
	uint16_t max_size_of_instructions;
	uint16_t max_component_elements;
	uint16_t max_component_depth;

public: /* functions */
	RMaxpTable(RTableEntry entry);

	virtual void decrypt() override;
	virtual std::string toStr() const override;
};

} // RunicCore namespace

#endif // __RUNIC_MAXP_TABLE__
