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

#pragma once

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include "../Interfaces/ISecureRandom.h"

using namespace std;


class BigInteger
{
private:
	// Resource string
	static const char * DivisionByZero;
	static const char * ModulusPositive;
	static const char * NotRelativelyPrime;
	static const char * NegativeValue;
	static const char * NegativeExponent;
	static const char * ResultTooLarge;
	static const char * NegativeBitPosition;
	static const char * InvalidBitAddress;
	static const char * ZeroLengthBigInteger;
	static const char * InvalidSign;
	static const char * NegativeSizeInBits;
	static const char * InvalidBitLength;
	static const char * InvalidBase;
	static const char * BadCharacterRadix8;
	static const char * BadCharacterRadix2;
	static const char * UnSupportedBase;

private:
	static const int64_t IMASK = 0xFFFFFFFF;
	static const uint64_t UIMASK = 0xFFFFFFFF;
	static vector<uint8_t> BitLengthTable;

	/// <summary>
	/// These are the threshold bit-lengths (of an exponent) where we
	/// increase the window size. <br />They are calculated according to the
	/// expected savings in multiplications. <br />Some squares will also be
	/// saved on average, but we offset these against the extra storage
	/// costs. <br />
	/// </summary>

	static vector<int32_t> ExpWindowThresholds;

	// TODO Parse radix-2 64 bits at a time and radix-8 63 bits at a time
	static const int32_t chunk2 = 1;
	static const int32_t chunk8 = 1;
	static const int32_t chunk10 = 19;
	static const int32_t chunk16 = 16;

	static const int32_t BitsPerByte = 8;
	static const int32_t BitsPerInt = 32;
	static const int32_t BytesPerInt = 4;

private:
	// array of ints with [0] being the most significant
	vector<int32_t> magnitude;
	int32_t sign; // -1 means -ve; +1 means +ve; 0 means 0;
	int32_t nBits; // cache BitCount() value
	int32_t nBitLength; // cache BitLength() value
	// -m^(-1) mod b, b = 2^32 (see Montgomery mult.), 0 when uninitialised
	int32_t mQuote;
	bool IsInitialized = false;

private:
	static BigInteger Zero, One, Two, Three, Ten;
	// Each list has a product < 2^31
	static vector<vector<int32_t>> primeLists;
	static vector<int32_t> primeProducts, ZeroMagnitude;
	static vector<uint8_t> ZeroEncoding;
	static vector<BigInteger> SMALL_CONSTANTS;
	static BigInteger radix2, radix2E, radix8, radix8E, radix10, radix10E, radix16, radix16E;
	static ISecureRandom RandomSource;


private:
	BigInteger AddToMagnitude(const vector<int32_t> &magToAdd) const;
	inline bool QuickPow2Check() const;

	/// <summary>
	/// return z = x / y - done in place (z value preserved, x contains the *
	/// remainder)
	/// </summary>
	vector<int32_t> Divide(vector<int32_t> &x, vector<int32_t> &y) const;
	bool IsEqualMagnitude(const BigInteger &x) const;

	bool CheckProbablePrime(const int32_t certainty, IRandom random, const bool randomlySelected);

	BigInteger ModInversePow2(const BigInteger &value) const;

	/// <summary>
	/// Calculate mQuote = -m^(-1) mod b with b = 2^32 (32 = word size)
	/// </summary>
	inline int32_t GetMQuote();

	inline int32_t Remainder(const int32_t m) const;

	/// <summary>
	/// return x = x mod y - done in place (y value preserved)
	/// </summary>
	vector<int32_t> Remainder(vector<int32_t> &x, const vector<int32_t> &y) const;

	inline vector<int32_t> LastNBits(const int32_t n) const;

	inline BigInteger DivideWords(const int32_t w) const;

	inline BigInteger RemainderWords(const int32_t w) const;

	vector<uint8_t> ToByteArray(const bool _unsigned) const;

	inline BigInteger FlipExistingBit(const int32_t n) const;

	int32_t GetLowestSetBitMaskFirst(const int32_t firstWordMask) const;

	void ParseString(const string &str, const int32_t radix);
	void ParseBytes(const vector<uint8_t> &bytes, const int32_t offset, const int32_t length);
	void ParseBytesWithSign(const int32_t sign, const vector<uint8_t> &bytes, const int32_t offset, const int32_t length);
	
	inline static int32_t GetByteLength(const int32_t nBits);

	static vector<int32_t> MakeMagnitude(const vector<uint8_t> &bytes, const int32_t offset, const int32_t length);

	/// <summary>
	/// a = a + b - b preserved.
	/// </summary>
	inline static vector<int32_t> AddMagnitudes(vector<int32_t> &a, const vector<int32_t> &b);

	static int32_t CalcBitLength(const int32_t sign, const int32_t indx, const vector<int32_t> &mag);

	/// <summary>
	/// unsigned comparison on two arrays - note the arrays may start with
	/// leading zeros.
	/// </summary>
	static int32_t CompareTo(const int32_t xIndx, const vector<int32_t> &x, const int32_t yIndx, const vector<int32_t> &y);

	static int32_t CompareNoLeadingZeroes(const int32_t xIndx, const vector<int32_t> &x, const int32_t yIndx, const vector<int32_t> &y);

	inline static int32_t ModInverse32(const int32_t d);

	inline static int64_t ModInverse64(const int64_t d);

	/// <summary>
	/// Calculate the numbers u1, u2, and u3 such that: <br />u1 * a + u2 * b
	/// = u3 <br />where u3 is the greatest common divider of a and b. <br />
	/// a and b using the extended Euclid algorithm (refer p. 323 of The Art
	/// of Computer Programming vol 2, 2nd ed). <br />This also seems to have
	/// the side effect of calculating some form of multiplicative inverse.
	/// </summary>
	/// <param name="a">
	/// First number to calculate gcd for
	/// </param>
	/// <param name="b">
	/// Second number to calculate gcd for
	/// </param>
	/// <param name="u1Out">
	/// the return object for the u1 value
	/// </param>
	/// <returns>
	/// The greatest common divisor of a and b
	/// </returns>
	inline static BigInteger ExtEuclid(const BigInteger &a, const BigInteger &b, BigInteger &u1Out);

	static BigInteger ModPowBarrett(const BigInteger &b, const BigInteger &e, const BigInteger &m);

	static BigInteger ReduceBarrett(BigInteger &x, BigInteger &m, const BigInteger &mr, const BigInteger &yu);

	static BigInteger ModPowMonty(BigInteger &b, const BigInteger &e, const BigInteger &m, const bool convert);

	static vector<int32_t> GetWindowList(const vector<int32_t> &mag, const int32_t extraBits);

	inline static int32_t CreateWindowEntry(int32_t mult, int32_t zeroes);

	/// <returns>
	/// w with w = x * x - w is assumed to have enough space.
	/// </returns>
	static vector<int32_t> Square(vector<int32_t> &w, const vector<int32_t> &x);

	/// <returns>
	/// x with x = y * z - x is assumed to have enough space.
	/// </returns>
	static vector<int32_t> Multiply(vector<int32_t> &x, const vector<int32_t> &y, const vector<int32_t> &z);

	// mDash = -m^(-1) mod b
	static void MontgomeryReduce(vector<int32_t> &x, const vector<int32_t> &m, const uint32_t mDash);

	// mDash = -m^(-1) mod b

	/// <summary>
	/// Montgomery multiplication: a = x * y * R^(-1) mod m <br />Based
	/// algorithm 14.36 of Handbook of Applied Cryptography. <br />&lt;li&gt;
	/// m, x, y should have length n &lt;/li&gt; <br />&lt;li&gt; a should
	/// have length (n + 1) &lt;/li&gt; <br />&lt;li&gt; b = 2^32, R = b^n
	/// &lt;/li&gt; <br />&lt;br/&gt; <br />The result is put in x <br />
	/// &lt;br/&gt; <br />NOTE: the indices of x, y, m, a different in HAC
	/// and in Java <br />
	/// </summary>
	static void MultiplyMonty(vector<int32_t> &a, vector<int32_t> &x, const vector<int32_t> &y,
		const vector<int32_t> &m, const uint32_t mDash, const bool smallMontyModulus);

	// mDash = -m^(-1) mod b
	static void SquareMonty(vector<int32_t> &a, vector<int32_t> &x, const vector<int32_t> &m,
		const uint32_t mDash, const bool smallMontyModulus);

	inline static uint32_t MultiplyMontyNIsOne(const uint32_t x, const uint32_t y, const uint32_t m, const uint32_t mDash);

	/// <summary>
	/// do a left shift - this returns a new array.
	/// </summary>
	static vector<int32_t> ShiftLeft(const vector<int32_t> &mag, const int32_t n);

	/// <summary>
	/// do a right shift - this does it in place.
	/// </summary>
	static void ShiftRightInPlace(const int32_t start, vector<int32_t> &mag, const int32_t n);

	/// <summary>
	/// do a right shift by one - this does it in place.
	/// </summary>
	static void ShiftRightOneInPlace(const int32_t start, vector<int32_t> &mag);

	/// <summary>
	/// returns x = x - y - we assume x is &gt;= y
	/// </summary>
	static vector<int32_t> Subtract(const int32_t xStart, vector<int32_t> &x, const int32_t yStart, const vector<int32_t> &y);

	inline static vector<int32_t> doSubBigLil(const vector<int32_t> &bigMag, const vector<int32_t> &lilMag);

	inline static void AppendZeroExtendedString(ostringstream &sl,	const string s, const int32_t minLength);

	static void ToString(ostringstream &sl, int32_t radix, vector<BigInteger> &moduli, int32_t scale, BigInteger &pos);

	static BigInteger CreateUValueOf(const uint64_t value);
	static BigInteger CreateValueOf(const int64_t value);

	static string IntToBin(const int32_t input);

	static string IntToOctal(const int32_t input);

private:
	BigInteger(const int32_t signum, const vector<int32_t> &mag, const bool checkMag);

public:
	BigInteger();
	BigInteger(const string &value);
	BigInteger(const string &value, const int32_t radix);
	BigInteger(const vector<uint8_t> &bytes);
	BigInteger(const vector<uint8_t> &bytes, const int32_t offset, const int32_t length);
	BigInteger(const int32_t sign, const vector<uint8_t> &bytes);
	BigInteger(const int32_t sign, const vector<uint8_t> &bytes, const int32_t offset, const int32_t length);
	BigInteger(const int32_t sizeInBits, IRandom random);
	BigInteger(const int32_t BitLength, const int32_t certainty, IRandom random);

	BigInteger Abs() const;
	BigInteger Add(const BigInteger &value) const;
	BigInteger Subtract(const BigInteger &n) const;
	BigInteger And(const BigInteger &value) const;
	BigInteger Not() const;
	BigInteger AndNot(const BigInteger &val) const;
	BigInteger Or(const BigInteger &value) const;
	BigInteger Xor(const BigInteger &value) const;

	int32_t CompareTo(const BigInteger &value) const;
	BigInteger Divide(const BigInteger &val) const;
	vector<BigInteger> DivideAndRemainder(const BigInteger &val) const;
	BigInteger Gcd(const BigInteger &value) const;
	BigInteger Inc() const;

	bool RabinMillerTest(const int32_t certainty, IRandom random) const;

	bool RabinMillerTest(const int32_t certainty, IRandom random, const bool randomlySelected) const;

	/// <summary>
	/// return whether or not a BigInteger is probably prime with a
	/// probability of 1 - (1/2)**certainty. <br />&lt;p&gt;From Knuth Vol 2,
	/// pg 395.&lt;/p&gt;
	/// </summary>
	bool IsProbablePrime(const int32_t certainty) const;
	bool IsProbablePrime(const int32_t certainty, const bool randomlySelected) const;

	BigInteger Max(const BigInteger &value) const ;
	BigInteger Min(const BigInteger &value) const;
	BigInteger Mod(const BigInteger &m) const;
	BigInteger ModInverse(const BigInteger &m) const;
	BigInteger ModPow(BigInteger &e, const BigInteger &m) const;

	BigInteger Multiply(const BigInteger &val) const;
	BigInteger Square() const;
	BigInteger Negate() const;

	BigInteger NextProbablePrime() const;

	BigInteger Pow(const int32_t exp) const;

	BigInteger Remainder(const BigInteger &n) const;

	BigInteger ShiftLeft(const int32_t n) const;
	BigInteger ShiftRight(const int32_t n) const;

	vector<uint8_t> ToByteArray() const;
	vector<uint8_t> ToByteArrayUnsigned() const;

	bool TestBit(const int32_t n) const;
	BigInteger SetBit(const int32_t n) const;
	BigInteger ClearBit(const int32_t n) const;
	BigInteger FlipBit(const int32_t n) const;

	int32_t GetLowestSetBit() const;

	string ToString() const;
	string ToString(const int32_t radix) const;

	inline bool Equals(const BigInteger &other) const;
	int32_t GetHashCode() const;
	static int32_t BitCnt(const int32_t i);

	static int32_t BitLen(const int32_t w);
	static BigInteger ProbablePrime(const int32_t BitLength, IRandom random);

	static BigInteger ValueOf(const int64_t value);

	static BigInteger Arbitrary(const int32_t sizeInBits);

	static void Boot();
	
public:
	inline int32_t GetBitLength();
	inline int32_t GetBitCount();
	inline int32_t GetInt32Value() const;
	inline int64_t GetInt64Value() const;

	inline bool GetIsInitialized() const
	{
		return IsInitialized;
	}

	inline int32_t GetSignValue() const
	{
		return sign;
	}

	inline static BigInteger GetZero()
	{
		return Zero;
	}

	inline static BigInteger GetOne()
	{
		return One;
	}

	inline static BigInteger GetTwo()
	{
		return Two;
	}

	inline static BigInteger GetThree()
	{
		return Three;
	}

	inline static BigInteger GetTen()
	{
		return Ten;
	}

	inline static vector<vector<int32_t>> GetprimeLists()
	{
		return primeLists;
	}

	inline static vector<int32_t> GetprimeProducts()
	{
		return primeProducts;
	}

	inline static IRandom GetRandomSource()
	{
		return RandomSource;
	}

};


#endif // !BIGINTEGER_H

