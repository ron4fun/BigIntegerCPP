// ///////////////////////////////////////////////////////////////// //
// *C++ 11 BigInteger Library                                 
// *Copyright(c) 2018  Mbadiwe Nnaemeka Ronald                 
// *Github Repository <https://github.com/ron4fun>             

// *Distributed under the MIT software license, see the accompanying file LICENSE 
// *or visit http ://www.opensource.org/licenses/mit-license.php.           

// *Acknowledgements:                                  
// ** //
// *Thanks to Ugochukwu Mmaduekwe (https://github.com/Xor-el) for the        
// *development of this library                          

// ////////////////////////////////////////////////////// ///////////////

#pragma once

#ifndef RANDOM_H
#define RANDOM_H

#include "../Interfaces/IRandom.h"
#include <memory>
#include <vector>
#include <cstdlib>

using namespace std;

class Random : public virtual IIRandom
{
private:
	// Resourcestring
	const char * BufferNil = "Buffer Cannot be Nil";
	const char * MaxValueNegative = "maxValue Must be Positive";
	const char * InvalidMinValue = "minValue Cannot be Greater Than maxValue";

private:
	const int32_t MBIG = int32_t(2147483647);
	const int32_t MSEED = int32_t(161803398);
	const int32_t MZ = int32_t(0);

	static vector<int32_t> SeedArray;

private:
	int32_t inext, inextp;

	inline int32_t InternalSample();
	double GetSampleForLargeRange();

protected:
	/// <summary>Returns a random floating-point number between 0.0 and 1.0.</summary>
	/// <returns>A double-precision floating point number that is greater than or equal to 0.0, and less than 1.0.</returns>
	virtual double Sample();

public:
	Random() 
	{
		SeedArray = vector<int32_t>(56);
	}

	Random(const int32_t Seed);
	~Random();

	virtual void NextBytes(vector<uint8_t> &buf);

	virtual double NextDouble();

	virtual int32_t Next();
	virtual int32_t Next(const int32_t maxValue);
	virtual int32_t Next(const int32_t minValue, const int32_t maxValue);

};

#endif // !RANDOM_H