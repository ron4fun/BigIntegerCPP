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

#ifndef BIGINTEGERWRAPPER_H
#define BIGINTEGERWRAPPER_H

#include <memory>
#include <string>
#include <vector>

using namespace std;

class BigIntegerWrapper
{
public:
	BigIntegerWrapper();
	BigIntegerWrapper(const string &value, const int32_t radix = 10);
	BigIntegerWrapper(const vector<uint8_t> &bytes, const int32_t sign = 1);
	~BigIntegerWrapper();

	BigIntegerWrapper(const BigIntegerWrapper &rhs);
	BigIntegerWrapper& operator=(const BigIntegerWrapper &rhs);

	BigIntegerWrapper Abs() const;
	BigIntegerWrapper Add(const BigIntegerWrapper &value) const;
	BigIntegerWrapper Subtract(const BigIntegerWrapper &value) const;
	BigIntegerWrapper And(const BigIntegerWrapper &value) const;
	BigIntegerWrapper Not() const;
	BigIntegerWrapper AndNot(const BigIntegerWrapper &val) const;
	BigIntegerWrapper Or(const BigIntegerWrapper &value) const;
	BigIntegerWrapper Xor(const BigIntegerWrapper &value) const;

	int32_t CompareTo(const BigIntegerWrapper &value) const;
	BigIntegerWrapper Divide(const BigIntegerWrapper &value) const;
	vector<BigIntegerWrapper> DivideAndRemainder(const BigIntegerWrapper &value) const;
	BigIntegerWrapper Gcd(const BigIntegerWrapper &value) const;
	BigIntegerWrapper Inc() const;

	bool RabinMillerTest(const int32_t certainty, const bool randomlySelected = false) const;

	bool IsProbablePrime(const int32_t certainty, const bool randomlySelected = false) const;

	BigIntegerWrapper Max(const BigIntegerWrapper &value) const;
	BigIntegerWrapper Min(const BigIntegerWrapper &value) const;
	BigIntegerWrapper Mod(const BigIntegerWrapper &value) const;
	BigIntegerWrapper ModInverse(const BigIntegerWrapper &value) const;
	BigIntegerWrapper ModPow(BigIntegerWrapper &e, const BigIntegerWrapper &m) const;

	BigIntegerWrapper Multiply(const BigIntegerWrapper &value) const;
	BigIntegerWrapper Square() const;
	BigIntegerWrapper Negate() const;

	BigIntegerWrapper NextProbablePrime() const;

	BigIntegerWrapper Pow(const int32_t exp) const;

	BigIntegerWrapper Remainder(const BigIntegerWrapper &n) const;

	BigIntegerWrapper ShiftLeft(const int32_t n) const;
	BigIntegerWrapper ShiftRight(const int32_t n) const;

	vector<uint8_t> ToByteArray() const;
	vector<uint8_t> ToByteArrayUnsigned() const;

	bool TestBit(const int32_t n) const;
	BigIntegerWrapper SetBit(const int32_t n) const;
	BigIntegerWrapper ClearBit(const int32_t n) const;
	BigIntegerWrapper FlipBit(const int32_t n) const;

	int32_t GetLowestSetBit() const;
	
	bool Equals(const BigIntegerWrapper &other) const;
	
	int32_t GetHashCode() const;
	
	static int32_t BitCnt(const int32_t i);

	static int32_t BitLen(const int32_t w);
	static BigIntegerWrapper ProbablePrime(const int32_t BitLength);

	static BigIntegerWrapper ValueOf(const int64_t value);

	static BigIntegerWrapper Arbitrary(const int32_t sizeInBits);

	string ToString(const int32_t radix = 10) const;

private:		
	void * ptr = nullptr;

};

#endif //BIGINTEGERWRAPPER_H