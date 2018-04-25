// ///////////////////////////////////////////////////////////////// //
// *C++ 11 BigInteger Library                                 
// *Copyright(c) 2018  Mbadiwe Nnaemeka Ronald                 
// *Github Repository <https://github.com/ron4fun>             

// *Distributed under the MIT software license, see the accompanying file LICENSE 
// *or visit http ://www.opensource.org/licenses/mit-license.php.           

// *Acknowledgements:                                  
// ** //
// *Thanks to Ugochukwu Mmaduekwe (https://github.com/Xor-el) for his creative        
// *development of this library in Pascal/Delphi                         

// ////////////////////////////////////////////////////// ///////////////

#ifndef HLPBITS_H
#define HLPBITS_H


class Bits
{
public:
	static void ReverseByteArray(const void *Source, void * Dest, int64_t size)
	{
		uint8_t *ptr_src = (uint8_t *)Source;
		uint8_t *ptr_dest = (uint8_t *)Dest;

		ptr_dest = ptr_dest + (size - 1);
		while (size > 0)
		{
			*ptr_dest = *ptr_src;
			ptr_src += 1;
			ptr_dest -= 1;
			size -= 1;
		} // end while
	} // end function ReverseByteArray
	
	inline static int32_t ReverseBytesInt32(const int32_t value)
	{
		int32_t i1 = value & 0xFF;
		int32_t i2 = Bits::Asr32(value, 8) & 0xFF;
		int32_t i3 = Bits::Asr32(value, 16) & 0xFF;
		int32_t i4 = Bits::Asr32(value, 24) & 0xFF;

		return (i1 << 24) | (i2 << 16) | (i3 << 8) | (i4 << 0);
	} // end function ReverseBytesInt32

	inline static uint8_t ReverseBitsUInt8(const uint8_t value)
	{
		uint8_t result = ((value >> 1) & 0x55) | ((value << 1) & 0xAA);
		result = ((result >> 2) & 0x33) | ((result << 2) & 0xCC);
		return ((result >> 4) & 0x0F) | ((result << 4) & 0xF0);
	} // end function ReverseBitsUInt8

	inline static uint16_t ReverseBytesUInt16(const uint16_t value)
	{
		return ((value & uint32_t(0xFF)) << 8 | (value & uint32_t(0xFF00)) >> 8);
	} // end function ReverseBytesUInt16

	inline static uint32_t ReverseBytesUInt32(const uint32_t value)
	{
		return (value & uint32_t(0x000000FF)) << 24 | 
			(value & uint32_t(0x0000FF00)) << 8 | 
			(value & uint32_t(0x00FF0000)) >> 8 |
			(value & uint32_t(0xFF000000)) >> 24;
	} // end function ReverseBytesUInt32

	inline static uint64_t ReverseBytesUInt64(const uint64_t value)
	{
		return (value & uint64_t(0x00000000000000FF)) << 56 |
			(value & uint64_t(0x000000000000FF00)) << 40 |
			(value & uint64_t(0x0000000000FF0000)) << 24 |
			(value & uint64_t(0x00000000FF000000)) << 8 |
			(value & uint64_t(0x000000FF00000000)) >> 8 |
			(value & uint64_t(0x0000FF0000000000)) >> 24 |
			(value & uint64_t(0x00FF000000000000)) >> 40 |
			(value & uint64_t(0xFF00000000000000)) >> 56;
	} // end function ReverseBytesUInt64

	inline static int32_t Asr32(const int32_t value, const int32_t ShiftBits)
	{
		int32_t result = value >> ShiftBits;
		if ((value & 0x80000000) > 0)
		{
			// if you don't want to cast (0xFFFFFFFF) to an Int32,
			// simply replace it with (-1) to avoid range check error.
			result = result | (int32_t(0xFFFFFFFF) << (32 - ShiftBits));
		} // end if

		return result;			
	} // end function Asr32

	inline static int64_t Asr64(const int64_t value, const int32_t ShiftBits)
	{
		int64_t result = value >> ShiftBits;
		if ((value & 0x8000000000000000) > 0)
		{
			result = result | (0xFFFFFFFFFFFFFFFF << (64 - ShiftBits));
		} // end if
	
		return result;
	} // end function Asr64

	inline static uint32_t RotateLeft32(const uint32_t a_value, int32_t a_n)
	{
		a_n = a_n & 31;
		return (a_value << a_n) | (a_value >> (32 - a_n));
	} // end function RotateLeft32
	
	inline static uint64_t RotateLeft64(const uint64_t a_value, int32_t a_n)
	{
		a_n = a_n & 63;
		return (a_value << a_n) | (a_value >> (64 - a_n));
	} // end function RotateLeft64

	inline static uint32_t RotateRight32(const uint32_t a_value, int32_t a_n)
	{
		a_n = a_n & 31;
		return (a_value >> a_n) | (a_value << (32 - a_n));
	} // end function RotateRight32

	inline static uint64_t RotateRight64(const uint64_t a_value, int32_t a_n)
	{
		a_n = a_n & 63;
		return (a_value >> a_n) | (a_value << (64 - a_n));
	} // end function RotateRight64


}; // end class Bits

#endif // ! HLPBITS_H
