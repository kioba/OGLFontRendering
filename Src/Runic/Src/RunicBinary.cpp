#include "RunicBinary.hpp"

namespace RunicCore {

// #############################################################################
// ### RBinary #################################################################
// #############################################################################

RBinary::RBinary(std::ifstream& stream, const Endianness endian) :
	conv(nullptr),
	buff_endian(endian)
{
	stream.seekg (0, std::ios::end);
	unsigned int length = static_cast<unsigned int> (stream.tellg());
	stream.seekg (0, std::ios::beg);

	buff.resize (length, 0);
	stream.read (&buff[0], length);

	range.setBegin(&buff.front());
	range.setEnd(&buff.back());
	act_pos = range.begin();

	cpu_endian = verifyCPUEndianness();
	createConverter();
}


RBinary::~RBinary()
{
}


Endianness RBinary::verifyCPUEndianness() const
{
	int num = 1;
	return (*reinterpret_cast<char*> (&num) == 1) ? little : big;
}


void RBinary::createConverter()
{
	if (cpu_endian != buff_endian) {
		conv.reset(new ShiftEndian);
	} else {
		conv.reset(new NormalEndian);
	}
}


Endianness RBinary::getContentEndianness() const
{
	return buff_endian;
}


Endianness RBinary::getCPUEndianness() const
{
	return cpu_endian;
}


RRange RBinary::sub(RRange::Iter begin_pos, RRange::Iter end_pos)
{
	return RRange(begin_pos, end_pos);
}


void RBinary::seek(RRange::Iter iterator)
{
	if (iterator < begin() || iterator > end()) {
		return;
	}

	act_pos = iterator;
}


RRange::Iter RBinary::begin() const
{
	return range.begin();
}


RRange::Iter RBinary::end() const
{
	return range.end();
}


RRange::Iter RBinary::act()
{
	return act_pos;
}


int8_t RBinary::getInt8()
{
	return conv->getInt8(act_pos);
}


uint8_t RBinary::getUInt8()
{
	return conv->getUInt8(act_pos);
}


int16_t RBinary::getInt16()
{
	return conv->getInt16(act_pos);
}


uint16_t RBinary::getUInt16()
{
	return conv->getUInt16(act_pos);
}


int32_t RBinary::getInt32()
{
	return conv->getInt32(act_pos);
}


uint32_t RBinary::getUInt32()
{
	return conv->getUInt32(act_pos);
}

} // RunicCore namepsace
