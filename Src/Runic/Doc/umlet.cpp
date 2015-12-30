// #############################################################################
// ### RBinary #################################################################
// #############################################################################
RBinary
--
- en_conv : EndianConverter*
- buff : char[]
- range : RRange
- act_pos : Iter
- cpu_endian : Endianness
- buff_endian : Endianness

--
- verifyCPUEndianness() const : Endianness
- createConverter() : void

--
+ RBinary(stream : std::ifstream&, endian : const Endianness) Constr
+ RBinary(buffer: const RBinary&) : CopyConstr
+ operator=(binary : const RBinary&) : RBinary&
+ virtual ~RBinary() : Destr

+ getContentEndianness() const : Endianness
+ getCPUEndianness() const : Endianness

+ sub(begin_pos : Iter, end_pos : Iter) : RRange
+ seek(iterator : Iter) : void

+ begin() const : Iter
+ end() const : Iter
+ act() : Iter

+ getInt8() : int8_t
+ getUInt8() : uint8_t
+ getInt16() : int16_t
+ getUInt16() : uint16_t
+ getInt32() : int32_t
+ getUInt32() : uint32_t


// #############################################################################
// ### EndianConverter #########################################################
// #############################################################################

EndianConverter
--
+ EndianConverter() : Constr
+ virtual ~EndianConverter() : Destr

+ virtual getInt8() : int8_t
+ virtual getUInt8() : uint8_t

+ virtual getInt16() = 0 : int16_t
+ virtual getUInt16() = 0 : uint16_t

+ virtual getInt32() = 0 : int32_t
+ virtual getUInt32() = 0 : uint32_t


// #############################################################################
// ### ShiftEndian #############################################################
// #############################################################################

ShiftEndian
--
+ ShiftEndian() : Constr
+ virtual ~ShiftEndian() : Destr

+ virtual getInt16(iter : Iter&) override : int16_t
+ virtual getUInt16(iter : Iter&) override : uint16_t

+ virtual getInt32(iter : Iter&) override : int32_t
+ virtual getUInt32(iter : Iter&) override : uint32_t


// #############################################################################
// ### NormalEndian ############################################################
// #############################################################################

NormalEndian
--
NormalEndian() : Constr
virtual ~NormalEndian() : Destr

virtual getInt16(iter : Iter&) override : int16_t
virtual getUInt16(iter : Iter&) override : uint16_t

virtual getInt32(iter : Iter&) override : int32_t
virtual getUInt32(iter : Iter&) override : uint32_t


// #############################################################################
// #############################################################################
// #############################################################################


// #############################################################################
// ### TTFBase #################################################################
// #############################################################################

class TTFBase
--
# table_binary : RBinary*

--
+ TTFBase() : Constr
+ virtual ~TTFBase() : Destr

+ setBinary(binary : RBinary*&) : void
+ getBinary() : RBinary*&

+ virtual decrypt() = 0 : void
+ virtual toStr() const = 0 : std::string


// #############################################################################
// ### RTableEntry #############################################################
// #############################################################################

RTableEntry
--
->public TTFBase
--
# range : RRange
# tag_str : std::string
# check_sum : uint32_t
# offset : uint32_t
# length : uint32_t
# checksum_verified : bool

--
- verifyCheckSum() : void

--
+ RTableEntry(binary : RBinary) : Constr
+ virtual ~RTableEntry() : Destr

+ getTagStr() const : const std::string&
+ verified() const : bool

+ virtual decrypt() override : void
+ virtual toStr() const override : std::string


// #############################################################################
// ### RFileHeader #############################################################
// #############################################################################

RFileHeader
--
->public TTFBase
--
+ sfnt_version : int32_t
+ num_tables : uint16_t
+ search_range : uint16_t
+ entry_selector : uint16_t
+ range_shift : uint16_t
+ entries : RTableEntry[]

--
- decryptTables() : void

--
+ RFileHeader() : Constr
+ virtual ~RFileHeader() : Destr

+ GetTableEntry (table_str : const std::string&) : RTableEntry&
+ verifyTableExistance(table_name : const std::string&) const : bool
+ tablesToStr() const : std::string

+ virtual decrypt() override : void
+ virtual toStr() const override : std::string


// #############################################################################
// ### CharCode ################################################################
// #############################################################################

CharCode
--
+ char_code : uint32_t
+ platform : uint16_t
+ encode : uint16_t
+ language : uint16_t

--
+ CharCode(character : uint32_t) : Constr
+ virtual ~CharCode() : Destr
