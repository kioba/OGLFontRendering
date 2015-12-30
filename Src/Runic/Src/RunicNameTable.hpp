#ifndef __RUNIC_NAME_TABLE__
#define __RUNIC_NAME_TABLE__

#include <cstdint>
#include <string>
#include <memory>

#include "RunicTypes.hpp"

namespace RunicCore {

// #############################################################################
// ### RNameTable ##############################################################
// #############################################################################

class RNameTable :
	public RTableEntry
{
private: /* types */
	class NameRecord
	{
	public: /* variables */
		uint16_t	platform_id;
		uint16_t	encoding_id;
		uint16_t	language_id;
		uint16_t	name_id;
		uint16_t	length;
		uint16_t	offset;
		std::string	str;
	};

public: /* variables */
	uint16_t format_selector;
	uint16_t num_records;
	uint16_t offset;

	std::vector<NameRecord> name_records;

public: /* functions */
	RNameTable(RTableEntry& entry);
	virtual ~RNameTable();

	virtual void decrypt() override;
	virtual std::string toStr() const override;
};


} // RunicCore namespace

#endif // __RUNIC_NAME_TABLE__
