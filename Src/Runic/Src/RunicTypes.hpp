#ifndef __RUNIC_TYPES__
#define __RUNIC_TYPES__

#include <cstdint>
#include <memory>
#include <iomanip>

#include "RunicRange.hpp"
#include "RunicBinary.hpp"

namespace RunicCore {

// #############################################################################
// ### TTFBase #################################################################
// #############################################################################

class TTFBase
{
protected: /* variables */
	std::shared_ptr<RBinary> table_binary;

public: /* functions */
	TTFBase();
	virtual ~TTFBase();

		void setBinary(std::shared_ptr<RBinary>& binary);
		std::shared_ptr<RBinary>& getBinary();

	virtual void decrypt() = 0;
	virtual std::string toStr() const = 0;
};


// #############################################################################
// ### RTableEntry #############################################################
// #############################################################################

class RTableEntry :
	public TTFBase
{
protected: /* variables */
	RRange range;

	std::string tag_str;	// stringified tag
	uint32_t check_sum;		// checksum for the table
	uint32_t offset;		// offset from the begining of the TrueType file
	uint32_t length;		// legth of the table
	bool checksum_verified;

private: /* functions */
	void verifyCheckSum();

public: /* functions */
	RTableEntry(std::shared_ptr<RBinary> binary);
	virtual ~RTableEntry();

	const std::string& getTagStr() const;
	bool verified() const;

	virtual void decrypt() override;
	virtual std::string toStr() const override;
};


// #############################################################################
// ### RFileHeader #############################################################
// #############################################################################

class RFileHeader :
	public TTFBase
{
public: /* variables */
	static const unsigned short TAG_LENGTH = 4;
	int32_t sfnt_version;		// sfnt version number
	uint16_t num_tables;		// number of table
	uint16_t search_range;		// used for binary searches of the table entries (not necessary)
	uint16_t entry_selector;
	uint16_t range_shift;

	std::vector<RTableEntry> entries;

private: /* functions */
	void decryptTables();

public: /* functions */
	RFileHeader();
	virtual ~RFileHeader();

	RTableEntry& GetTableEntry (const std::string& table_str);
	bool verifyTableExistance(const std::string& table_name) const;
	std::string tablesToStr() const;

	virtual void decrypt() override;
	virtual std::string toStr() const override;
};


// #############################################################################
// ### CharCode ################################################################
// #############################################################################

class CharCode
{
public:
	uint32_t char_code;
	uint16_t platform;
	uint16_t encode;
	uint16_t language;

public:
	CharCode(uint32_t character) :
		char_code{character},
		platform{3}, // TODO change!!!
		encode{1}, // TODO change!!!
		language{0} // TODO change!!!
	{ }

	virtual ~CharCode()
	{ }
};

} // RunicCore namespace

#endif // __RUNIC_TYPES__
