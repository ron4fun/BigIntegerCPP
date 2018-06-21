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

#include "BigIntegerWrapper.h"
#include "Base/BigInteger.h"

BigIntegerWrapper::BigIntegerWrapper()
{
	if (BigInteger::GetRandomSource() == nullptr)
		BigInteger::Boot();

	ptr = (void *) new BigInteger();
}

BigIntegerWrapper::BigIntegerWrapper(const string &value, const int32_t radix)
{
	if (BigInteger::GetRandomSource() == nullptr)
		BigInteger::Boot();

	ptr = (void *) new BigInteger(value, radix);
}

BigIntegerWrapper::BigIntegerWrapper(const vector<uint8_t> &bytes, const int32_t sign)
{
	if (BigInteger::GetRandomSource() == nullptr)
		BigInteger::Boot();

	ptr = (void *) new BigInteger(sign, bytes);
}

BigIntegerWrapper::~BigIntegerWrapper()
{
	if (ptr != nullptr)
	{
		delete (BigInteger *)ptr;
	}
}


BigIntegerWrapper::BigIntegerWrapper(const BigIntegerWrapper &rhs)
{
	if (ptr == nullptr)
		ptr = (void *) new BigInteger();

	*((BigInteger*)ptr) = *((BigInteger*)(rhs.ptr));
}

BigIntegerWrapper& BigIntegerWrapper::operator=(const BigIntegerWrapper &rhs)
{
	if (ptr == nullptr)
		ptr = (void *) new BigInteger();

	*((BigInteger*)ptr) = *((BigInteger*)(rhs.ptr));

	return *this;
}


BigIntegerWrapper BigIntegerWrapper::Abs() const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Abs();
	
	return result;
}

BigIntegerWrapper BigIntegerWrapper::Add(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Add(*((BigInteger *)value.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Subtract(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Subtract(*((BigInteger *)value.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::And(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->And(*((BigInteger *)value.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Not() const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Not();

	return result;
}

BigIntegerWrapper BigIntegerWrapper::AndNot(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->AndNot(*((BigInteger *)value.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Or(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Or(*((BigInteger *)value.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Xor(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Xor(*((BigInteger *)value.ptr));

	return result;
}

int32_t BigIntegerWrapper::CompareTo(const BigIntegerWrapper &value) const
{
	return ((BigInteger *)ptr)->CompareTo(*((BigInteger *)value.ptr));
}

BigIntegerWrapper BigIntegerWrapper::Divide(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Divide(*((BigInteger *)value.ptr));

	return result;
}

vector<BigIntegerWrapper> BigIntegerWrapper::DivideAndRemainder(const BigIntegerWrapper &value) const
{
	vector<BigIntegerWrapper> result(2);

	vector<BigInteger> ans = ((BigInteger *)ptr)->DivideAndRemainder(*((BigInteger *)value.ptr));

	*((BigInteger *)result[0].ptr) = ans[0];
	*((BigInteger *)result[1].ptr) = ans[1];

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Gcd(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Gcd(*((BigInteger *)value.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Inc() const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Inc();

	return result;
}

string BigIntegerWrapper::ToString(const int32_t radix) const
{
	return ((BigInteger *)ptr)->ToString(radix);
}

bool BigIntegerWrapper::RabinMillerTest(const int32_t certainty, const bool randomlySelected) const
{
	return ((BigInteger *)ptr)->RabinMillerTest(certainty, BigInteger::GetRandomSource(), randomlySelected);
}

bool BigIntegerWrapper::IsProbablePrime(const int32_t certainty, const bool randomlySelected) const
{
	return ((BigInteger *)ptr)->IsProbablePrime(certainty, randomlySelected);
}

BigIntegerWrapper BigIntegerWrapper::Max(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Max(*((BigInteger *)value.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Min(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Min(*((BigInteger *)value.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Mod(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Mod(*((BigInteger *)value.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::ModInverse(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->ModInverse(*((BigInteger *)value.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::ModPow(BigIntegerWrapper &e, const BigIntegerWrapper &m) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->ModPow(*((BigInteger *)e.ptr), *((BigInteger *)m.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Multiply(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Multiply(*((BigInteger *)value.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Square() const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Square();

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Negate() const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Negate();

	return result;
}

BigIntegerWrapper BigIntegerWrapper::NextProbablePrime() const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->NextProbablePrime();

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Pow(const int32_t exp) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Pow(exp);

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Remainder(const BigIntegerWrapper &value) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->Remainder(*((BigInteger *)value.ptr));

	return result;
}

BigIntegerWrapper BigIntegerWrapper::ShiftLeft(const int32_t n) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->ShiftLeft(n);

	return result;
}

BigIntegerWrapper BigIntegerWrapper::ShiftRight(const int32_t n) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->ShiftRight(n);

	return result;
}

vector<uint8_t> BigIntegerWrapper::ToByteArray() const
{
	return ((BigInteger *)ptr)->ToByteArray();
}

vector<uint8_t> BigIntegerWrapper::ToByteArrayUnsigned() const
{
	return ((BigInteger *)ptr)->ToByteArrayUnsigned();
}

bool BigIntegerWrapper::TestBit(const int32_t n) const
{
	return ((BigInteger *)ptr)->TestBit(n);
}

BigIntegerWrapper BigIntegerWrapper::SetBit(const int32_t n) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->SetBit(n);

	return result;
}

BigIntegerWrapper BigIntegerWrapper::ClearBit(const int32_t n) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->ClearBit(n);

	return result;
}

BigIntegerWrapper BigIntegerWrapper::FlipBit(const int32_t n) const
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = ((BigInteger *)ptr)->FlipBit(n);

	return result;
}

int32_t BigIntegerWrapper::GetLowestSetBit() const
{
	return ((BigInteger *)ptr)->GetLowestSetBit();
}

bool BigIntegerWrapper::Equals(const BigIntegerWrapper &other) const
{
	return ((BigInteger *)ptr)->Equals(*((BigInteger *)other.ptr));
}

int32_t BigIntegerWrapper::GetHashCode() const
{
	return ((BigInteger *)ptr)->GetHashCode();
}

int32_t BigIntegerWrapper::BitCnt(const int32_t i)
{
	return BigInteger::BitCnt(i);
}

int32_t BigIntegerWrapper::BitLen(const int32_t w)
{
	return BigInteger::BitLen(w);
}

BigIntegerWrapper BigIntegerWrapper::ProbablePrime(const int32_t BitLength)
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = BigInteger::ProbablePrime(BitLength, BigInteger::GetRandomSource());

	return result;
}

BigIntegerWrapper BigIntegerWrapper::ValueOf(const int64_t value)
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = BigInteger::ValueOf(value);

	return result;
}

BigIntegerWrapper BigIntegerWrapper::Arbitrary(const int32_t sizeInBits)
{
	BigIntegerWrapper result = BigIntegerWrapper();
	*((BigInteger *)result.ptr) = BigInteger::Arbitrary(sizeInBits);

	return result;
}
