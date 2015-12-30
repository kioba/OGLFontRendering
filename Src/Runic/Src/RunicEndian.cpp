#include "RunicEndian.hpp"


namespace RunicCore {


// #############################################################################
// ### EndianConverter #########################################################
// #############################################################################

EndianConverter::EndianConverter()
{
}


EndianConverter::~EndianConverter()
{
}


int8_t EndianConverter::getInt8(RRange::Iter& iter)
{
	int8_t r = *reinterpret_cast<const int8_t*>(&*iter);
	iter += 1;
	return r;
}


uint8_t EndianConverter::getUInt8(RRange::Iter& iter)
{
	uint8_t r = *reinterpret_cast<const uint8_t*>(&*iter);
	iter += 1;
	return r;
}


// #############################################################################
// ### ShiftEndian #############################################################
// #############################################################################

ShiftEndian::ShiftEndian()
{
}


ShiftEndian::~ShiftEndian()
{
}


int16_t ShiftEndian::getInt16(RRange::Iter& iter)
{
	int16_t ret = 0;
	int8_t sig = getInt8(iter);

	if (sig & 128) {
		ret = -1;
	}

	ret <<= 8;
	ret += sig;
	ret <<= 8;
	ret += getInt8(iter);
	return ret;
}


uint16_t ShiftEndian::getUInt16(RRange::Iter& iter)
{
	uint16_t ret = getUInt8(iter);
	ret <<= 8;
	ret += getUInt8(iter);
	return ret;
}


int32_t ShiftEndian::getInt32(RRange::Iter& iter)
{
	int32_t ret = 0;
	int32_t sig = getInt8(iter);
	if (sig & 128) {
		ret = -1;
	}

	ret <<= 8;
	ret += sig;
	ret <<= 8;
	ret += getInt8(iter);
	ret <<= 8;
	ret += getInt8(iter);
	ret <<= 8;
	ret += getInt8(iter);
	return ret;
}


uint32_t ShiftEndian::getUInt32(RRange::Iter& iter)
{
	uint32_t ret = getUInt8(iter);
	ret <<= 8;
	ret += getUInt8(iter);
	ret <<= 8;
	ret += getUInt8(iter);
	ret <<= 8;
	ret += getUInt8(iter);
	return ret;
}


// #############################################################################
// ### NormalEndian ############################################################
// #############################################################################

NormalEndian::NormalEndian()
{
}


NormalEndian::~NormalEndian()
{
}


int16_t NormalEndian::getInt16(RRange::Iter& iter)
{
	int16_t ret = 0;
	int8_t sig = getInt8(iter);

	if (sig & 128) {
		ret = -1;
	}

	ret += sig;
	ret += getInt8(iter);
	return ret;
}


uint16_t NormalEndian::getUInt16(RRange::Iter& iter)
{
	uint16_t ret = getUInt8(iter);
	ret += getUInt8(iter);
	return ret;
}


int32_t NormalEndian::getInt32(RRange::Iter& iter)
{
	int32_t ret = 0;
	int32_t sig = getInt8(iter);

	if (sig & 128) {
		ret = -1;
	}

	ret += sig;
	ret += getInt8(iter);
	ret += getInt8(iter);
	ret += getInt8(iter);
	return ret;
}


uint32_t NormalEndian::getUInt32(RRange::Iter& iter)
{
	uint32_t ret = getUInt8(iter);
	ret += getUInt8(iter);
	ret += getUInt8(iter);
	ret += getUInt8(iter);
	return ret;
}

} // RunicCore namespace
