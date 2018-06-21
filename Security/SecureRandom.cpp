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

#include "SecureRandom.h"
#include "../Utils/HlpBits.h"
#include "../Rng/CryptoApiRandomGenerator.h"
#include <chrono>

using namespace std::chrono;

int64_t SecureRandom::Counter = 0;
double SecureRandom::DoubleScale = 0;
IRandomGenerator SecureRandom::generator = nullptr;
ISecureRandom SecureRandom::master = nullptr;


vector<uint8_t> SecureRandom::GenerateSeed(const int32_t length)
{
	return GetNextBytes(master, length);
}

void SecureRandom::SetSeed(vector<uint8_t> &seed)
{
	generator.get()->AddSeedMaterial(seed);
}

void SecureRandom::SetSeed(const int64_t seed)
{
	generator.get()->AddSeedMaterial(seed);
}

void SecureRandom::NextBytes(vector<uint8_t> &buf)
{
	generator.get()->NextBytes(buf);
}

void SecureRandom::NextBytes(vector<uint8_t> &buf, const int32_t off, const int32_t len)
{
	generator.get()->NextBytes(buf, off, len);
}

int32_t SecureRandom::NextInt32()
{
	uint32_t tempRes;
	vector<uint8_t> bytes(4);

	NextBytes(bytes);

	tempRes = bytes[0];
	tempRes = tempRes << 8;
	tempRes = tempRes | bytes[1];
	tempRes = tempRes << 8;
	tempRes = tempRes | bytes[2];
	tempRes = tempRes << 8;
	tempRes = tempRes | bytes[3];

	return int32_t(tempRes);
}

int64_t SecureRandom::NextInt64()
{
	return (int64_t(uint32_t(NextInt32())) << 32) | (int64_t(uint32_t(NextInt32())));
}

double SecureRandom::NextDouble()
{
	return uint64_t(NextInt64()) / DoubleScale;
}

int64_t SecureRandom::NextCounterValue()
{
	uint32_t LCounter;

	LCounter = uint32_t(Counter);
	int64_t result = LCounter; // InterLockedIncrement(LCounter);
	Counter = int64_t(LCounter);

	return result;
}

int32_t SecureRandom::Next()
{
	return NextInt32() & INT32_MAX;
}

int32_t SecureRandom::Next(const int32_t maxValue)
{
	int32_t bits;
	
	if (maxValue < 2)
	{
		if (maxValue < 0)
			throw out_of_range(CannotBeNegative);
		
		return 0;
	}
			

	// Test whether maxValue is a power of 2
	if ((maxValue & (maxValue - 1)) == 0)
	{
		bits = NextInt32() & INT32_MAX;
		return int32_t(Bits::Asr64((int64_t(bits) * maxValue), 31));
	}
	
	int32_t result;

	do
	{
		bits = NextInt32() & INT32_MAX;
		result = bits % maxValue;
		// Ignore results near overflow
	} while (((bits - (result + (maxValue - 1))) < 0));

	return result;
}

int32_t SecureRandom::Next(const int32_t minValue, const int32_t maxValue)
{
	int32_t diff, i;
	
	if (maxValue <= minValue)
	{
		if (maxValue == minValue) return minValue;
		
		throw invalid_argument(InvalidMaxValue);
	}
		

	diff = maxValue - minValue;
	if (diff > 0) return  minValue + Next(diff);
	
	while (true)
	{
		i = NextInt32();

		if ((i >= minValue) && (i < maxValue)) return i;
	}

	return 0; // to make FixInsight Happy :)
}

vector<uint8_t> SecureRandom::GetNextBytes(ISecureRandom secureRandom, const int32_t length)
{
	vector<uint8_t> result(length);
	secureRandom.get()->NextBytes(result);

	return result;
}

void SecureRandom::Boot()
{
	auto now = high_resolution_clock::now();
	nanoseconds nn = duration_cast<nanoseconds>(now.time_since_epoch());
	
	Counter = nn.count();
	if (master == nullptr)
	{
		master = make_shared<SecureRandom>(make_shared<CryptoApiRandomGenerator>());
	}
	DoubleScale = pow(2.0, 64.0);
}