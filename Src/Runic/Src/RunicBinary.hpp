#ifndef __RUNIC_BINARY__
#define __RUNIC_BINARY__

#include <cstdint>
#include <vector>
#include <memory>

#include "RunicExceptions.hpp"
#include "RunicEndian.hpp"

namespace RunicCore {

enum Endianness {
	big		= 0,
	little	= 1
};

// #############################################################################
// ### RBinary #################################################################
// #############################################################################

class RBinary
{
private: /* variables */
	std::unique_ptr<EndianConverter> conv;
	std::vector<char> buff;
	RRange range;
	RRange::Iter act_pos;
	Endianness cpu_endian;
	Endianness buff_endian;

private: /* functions */
	Endianness verifyCPUEndianness() const;
	void createConverter();

public: /* functions */
	// RBinary(const RBinary& buffer);
	// RBinary& operator=(const RBinary& binary);
	RBinary(std::ifstream& stream, const Endianness endian);
	virtual ~RBinary();

	Endianness getContentEndianness() const;
	Endianness getCPUEndianness() const;

	RRange sub(RRange::Iter begin_pos, RRange::Iter end_pos);
	void seek(RRange::Iter iterator);

	RRange::Iter begin() const;
	RRange::Iter end() const;
	RRange::Iter act();

	int8_t getInt8();
	uint8_t getUInt8();
	int16_t getInt16();
	uint16_t getUInt16();
	int32_t getInt32();
	uint32_t getUInt32();
};

} // RunicCore namespace

#endif // __RUNIC_BINARY__
