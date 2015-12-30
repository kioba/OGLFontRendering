#include "RunicMaxpTable.hpp"

namespace RunicCore {

// #############################################################################
// ### RMaxpTable ##############################################################
// #############################################################################

RMaxpTable::RMaxpTable(RTableEntry entry) :
	RTableEntry(entry)
{
}


void RMaxpTable::decrypt()
{
	table_binary->seek(range.begin());
	table_version = table_binary->getUInt32 ();

	if (table_version != 0x00010000) {
		throw RunicException("MAXP Table version error!");
	}

	num_glyphs = table_binary->getUInt16 ();
	max_points = table_binary->getUInt16 ();
	max_contours = table_binary->getUInt16 ();
	max_composite_points = table_binary->getUInt16 ();
	max_composite_contours = table_binary->getUInt16 ();
	max_zones = table_binary->getUInt16 ();
	max_twilight_points = table_binary->getUInt16 ();
	max_storage = table_binary->getUInt16 ();
	max_function_defs = table_binary->getUInt16 ();
	max_instruction_defs = table_binary->getUInt16 ();
	max_stack_elements = table_binary->getUInt16 ();
	max_size_of_instructions = table_binary->getUInt16 ();
	max_component_elements = table_binary->getUInt16 ();
	max_component_depth = table_binary->getUInt16 ();
}


std::string RMaxpTable::toStr() const
{
	std::stringstream ss;

	ss << "table_version: " << table_version << std::endl;
	ss << "num_glyphs: " << num_glyphs << std::endl;
	ss << "max_points: " << max_points << std::endl;
	ss << "max_contours: " << max_contours << std::endl;
	ss << "max_composite_points: " << max_composite_points << std::endl;
	ss << "max_composite_contours: " << max_composite_contours << std::endl;
	ss << "max_zones: " << max_zones << std::endl;
	ss << "max_twilight_points: " << max_twilight_points << std::endl;
	ss << "max_storage: " << max_storage << std::endl;
	ss << "max_function_defs: " << max_function_defs << std::endl;
	ss << "max_instruction_defs: " << max_instruction_defs << std::endl;
	ss << "max_stack_elements: " << max_stack_elements << std::endl;
	ss << "max_size_of_instructions: " << max_size_of_instructions << std::endl;
	ss << "max_component_elements: " << max_component_elements << std::endl;
	ss << "max_component_depth: " << max_component_depth << std::endl;

	return ss.str();
}


} // RunicCore namespace
