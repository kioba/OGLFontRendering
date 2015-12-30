#include "RunicNameTable.hpp"

namespace RunicCore {

// #############################################################################
// ### RNameTable ##############################################################
// #############################################################################

RNameTable::RNameTable(RTableEntry& entry) :
	RTableEntry(entry)
{
}


RNameTable::~RNameTable()
{
}


void RNameTable::decrypt()
{
	table_binary->seek(range.begin());
	format_selector = table_binary->getUInt16();
	num_records = table_binary->getUInt16();
	offset = table_binary->getUInt16();

	name_records.clear ();
	for (int i = 0; i < num_records; ++i) {
		RNameTable::NameRecord record;
		record.platform_id = table_binary->getUInt16();
		record.encoding_id = table_binary->getUInt16();
		record.language_id = table_binary->getUInt16();
		record.name_id = table_binary->getUInt16();
		record.length = table_binary->getUInt16();
		record.offset = table_binary->getUInt16();

		for (int j = 0; j < record.length; ++j) {
			record.str.push_back(*(range.begin() + offset + record.offset + j));
		}

		name_records.push_back(record);
	}
}

std::string RNameTable::toStr() const
{
	std::stringstream ss;

	// ss << "format_selector: " << format_selector << std::endl;
	// ss << "num_records: " << num_records << std::endl;
	// ss << "offset: " << offset << std::endl;

	for (unsigned int i = 0; i < name_records.size(); ++i) {
		// ss << "--------------------------------------------------------------------------" << std::endl;
		//
		// ss << "#" << i << " platform_id: " << name_records[i].platform_id << std::endl;
		// ss << "#" << i << " encoding_id: " << name_records[i].encoding_id << std::endl;
		// ss << "#" << i << " language_id: 0x" << std::hex << std::setw(4) << std::setfill('0') << name_records[i].language_id << std::dec <<  std::endl;
		// ss << "#" << i << " name_id: " << name_records[i].name_id << std::endl;
		// ss << "#" << i << " length: " << name_records[i].length << std::endl;
		// ss << "#" << i << " offset: " << name_records[i].offset << std::endl;
		// ss << "#" << i << " str: " << name_records[i].str << std::endl;
	}

	return ss.str();
}

} // RunicCore namespace
