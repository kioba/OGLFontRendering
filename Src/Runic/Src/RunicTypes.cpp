#include "RunicTypes.hpp"

#include <sstream>
#include <algorithm>
#include <iostream>

namespace RunicCore {

// #############################################################################
// ### TTFBase #################################################################
// #############################################################################

TTFBase::TTFBase()
{
}


TTFBase::~TTFBase()
{
}


void TTFBase::setBinary(std::shared_ptr<RBinary>& binary)
{
	table_binary.reset();
	table_binary = binary;
}


std::shared_ptr<RBinary>& TTFBase::getBinary()
{
	return table_binary;
}


// #############################################################################
// ### RFileHeader #############################################################
// #############################################################################

RFileHeader::RFileHeader() :
	sfnt_version {0},
	num_tables {0},
	search_range {0},
	entry_selector {0},
	range_shift {0}
{
}


RFileHeader::~RFileHeader()
{
}


void RFileHeader::decrypt()
{
	sfnt_version = table_binary->getInt32 ();
	num_tables = table_binary->getUInt16 ();
	search_range = table_binary->getUInt16 ();
	entry_selector = table_binary->getUInt16 ();
	range_shift = table_binary->getUInt16 ();

	decryptTables();
}


void RFileHeader::decryptTables()
{
	for (int i = 0; i < num_tables; ++i) {
		RTableEntry entry {table_binary};
		entry.decrypt();
		entries.push_back(entry);
	}
}


std::string RFileHeader::toStr() const
{
	std::stringstream ss;

	ss << "=== File header ===" << std::endl;
	ss << "sfnt_version: " << "0x"<< std::hex << std::setw(8)
		<< std::setfill('0') << sfnt_version << std::dec << std::endl;
	ss << "num_tables: " <<  num_tables << std::endl;
	ss << "search_range: " <<  search_range << std::endl;
	ss << "entry_selector: " <<  entry_selector << std::endl;
	ss << "range_shift: " <<  range_shift << std::endl;

	return ss.str();
}


std::string RFileHeader::tablesToStr() const
{
	std::stringstream ss;

	for (unsigned int i = 0; i < entries.size(); ++i) {
		ss << "=== Entry table #" << i + 1 << " ===" << std::endl;
		ss << entries[i].toStr();
		ss << "verify: " << (entries[i].verified() ? "Succeeded" : "Failed")
			<< "!" << std::endl << std::endl;
	}

	return ss.str();
}


RTableEntry& RFileHeader::GetTableEntry (const std::string& table_str)
{
	std::vector<RTableEntry>::iterator entry = std::find_if(entries.begin(),
									entries.end(),
									[&table_str] (const RTableEntry& entry) {
										return entry.getTagStr() == table_str;
									});

	if (entry == entries.end()) {
		std::cout << "GetTableEntry failed to find table: "
					<< table_str << std::endl;
	}

	return *entry;
}


bool RFileHeader::verifyTableExistance(const std::string& table_name) const
{
	if (table_name.length() != TAG_LENGTH) {
		return false;
	}

	std::vector<RTableEntry>::const_iterator IT;
	for (IT = entries.begin(); IT != entries.end(); ++IT) {
		if (IT->getTagStr() == table_name) {
			return true;
		}
	}

	return false;
}


// #############################################################################
// ### RTableEntry #############################################################
// #############################################################################

RTableEntry::RTableEntry(std::shared_ptr<RBinary> binary) :
	check_sum {0},
	offset {0},
	length {0},
	checksum_verified {false}
{
	setBinary(binary);
}


RTableEntry::~RTableEntry()
{
}


void RTableEntry::verifyCheckSum()
{
	unsigned int ch_sum = 0;
	RRange::Iter act_pos = table_binary->act();

	table_binary->seek(range.begin());

	if (tag_str == "head") { // special event with the head table
		ch_sum += table_binary->getUInt32();
		ch_sum += table_binary->getUInt32();
		// check_suadjustment member of head table, must be skipped
		// or set to 0 for correct checksum
		table_binary->seek(table_binary->act() + 4);
	}

	while (table_binary->act() < range.end()) {
		ch_sum += table_binary->getUInt32();
	}

	table_binary->seek(act_pos);

	checksum_verified = ch_sum == this->check_sum;
}


const std::string& RTableEntry::getTagStr() const
{
	return tag_str;
}


bool RTableEntry::verified() const
{
	return checksum_verified;
}


void RTableEntry::decrypt()
{
	tag_str.clear();

	for (int i = 0; i < 4; ++i) {
		tag_str += table_binary->getInt8();
	}

	check_sum = table_binary->getUInt32();
	offset = table_binary->getUInt32();
	length = table_binary->getUInt32();

	RRange::Iter table_begin = table_binary->begin() + offset;
	RRange::Iter table_end = table_begin + length;

	range = table_binary->sub(table_begin, table_end);
	verifyCheckSum();
}


std::string RTableEntry::toStr() const
{
	std::stringstream ss;

	ss << "tag_str: " <<  tag_str << std::endl;
	ss << "check_sum: " <<  check_sum << std::endl;
	ss << "offset: " <<  offset << std::endl;
	ss << "length: " <<  length << std::endl;

	return ss.str();
}


} // namespace RunicCore
