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

#include "Random.h"

vector<int32_t> Random::SeedArray = vector<int32_t>();

Random::Random(const int32_t Seed)
{
	Random();

	int32_t num1, num2, index1, index2;
	
	num1 = MSEED - abs(Seed);
	SeedArray[55] = num1;
	num2 = 1;
	for (index1 = 1; index1 < 55; index1++)
	{
		index2 = 21 * index1 % 55;
		SeedArray[index2] = num2;
		num2 = num1 - num2;
		if (num2 < 0)
			num2 = num2 + INT32_MAX;
		num1 = SeedArray[index2];
	}
		
	index1 = 1;
	while (index1 < 5)
	{
		for (index2 = 1; index2 < 56; index2++)
		{
			SeedArray[index2] = SeedArray[index2] - SeedArray[1 + (index2 + 30) % 55];
			if (SeedArray[index2] < 0) 
				SeedArray[index2] = SeedArray[index2] + INT32_MAX;
		}
				
		index1++;
	}
		
	inext = 0;
	inextp = 21;
}

Random::~Random()
{
}

double Random::Sample()
{
	return InternalSample() * 4.6566128752458E-10;
}

void Random::NextBytes(vector<uint8_t> &buf)
{
	int32_t i;
	
	if (buf.empty())
		throw invalid_argument(BufferNil);

	for (i = 0; i < buf.size(); i++)
		buf[i] = uint8_t(InternalSample() % (255 + 1));
}

double Random::NextDouble()
{
	return Sample();
}

int32_t Random::InternalSample()
{
	int32_t _inext, _inextp, index1, index2, num;
	
	_inext = inext;
	_inextp = inextp;
	index1 = _inext + 1;
	if ((index1) >= 56) 
		index1 = 1;

	index2 = _inextp + 1;
	if ((index2) >= 56) 
		index2 = 1;

	num = SeedArray[index1] - SeedArray[index2];
	if (num < 0) 
		num = num + INT32_MAX;

	SeedArray[index1] = num;
	inext = index1;
	inextp = index2;
	
	return num;
}

double Random::GetSampleForLargeRange()
{
	int32_t num;
	
	num = InternalSample();
	if (InternalSample() % 2 == 0) 
		num = -num;

	return (num + 2147483646.0) / 4294967293.0;
}

int32_t Random::Next()
{
	return InternalSample();
}

int32_t Random::Next(const int32_t maxValue)
{
	if (maxValue < 0)
		throw out_of_range(MaxValueNegative);

	return int32_t(trunc(Sample() * maxValue));
}

int32_t Random::Next(const int32_t minValue, const int32_t maxValue)
{
	int64_t num;
	
	if (minValue > maxValue)
		throw out_of_range(InvalidMinValue);
	
	num = int64_t(maxValue) - int64_t(minValue);
	if (num <= int64_t(INT32_MAX)) 
		return int32_t(trunc(Sample()) * num) + minValue;

	return int32_t(int64_t(trunc(GetSampleForLargeRange()) * num) + int64_t(minValue));
}