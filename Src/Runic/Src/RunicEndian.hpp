#ifndef __RUNIC_ENDIAN__
#define __RUNIC_ENDIAN__

#include <cstdint>

#include "RunicRange.hpp"

namespace RunicCore {


// #############################################################################
// ### EndianConverter #########################################################
// #############################################################################

class EndianConverter
{
public: /* functions */
	EndianConverter();
	virtual ~EndianConverter();

	virtual int8_t getInt8(RRange::Iter& iter);
	virtual uint8_t getUInt8(RRange::Iter& iter);

	virtual int16_t getInt16(RRange::Iter& iter) = 0;
	virtual uint16_t getUInt16(RRange::Iter& iter) = 0;

	virtual int32_t getInt32(RRange::Iter& iter) = 0;
	virtual uint32_t getUInt32(RRange::Iter& iter) = 0;
};


// #############################################################################
// ### ShiftEndian #############################################################
// #############################################################################

class ShiftEndian :
	public EndianConverter
{
public: /* functions */
	ShiftEndian();
	virtual ~ShiftEndian();

	virtual int16_t getInt16(RRange::Iter& iter) override;
	virtual uint16_t getUInt16(RRange::Iter& iter) override;

	virtual int32_t getInt32(RRange::Iter& iter) override;
	virtual uint32_t getUInt32(RRange::Iter& iter) override;
};


// #############################################################################
// ### NormalEndian ############################################################
// #############################################################################

class NormalEndian :
	public EndianConverter
{
public: /* functions */
	NormalEndian();
	virtual ~NormalEndian();

	virtual int16_t getInt16(RRange::Iter& iter) override;
	virtual uint16_t getUInt16(RRange::Iter& iter) override;

	virtual int32_t getInt32(RRange::Iter& iter) override;
	virtual uint32_t getUInt32(RRange::Iter& iter) override;

};


} // RunicCore namespace

#endif // __RUNIC_ENDIAN__
