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

#ifndef SECURERANDOM_H
#define SECURERANDOM_H

#include "../Interfaces/ISecureRandom.h"
#include "../Interfaces/IRandomGenerator.h"
#include "../Interfaces/IRandomNumberGenerator.h"
#include "Random.h"

class SecureRandom: public Random, public virtual IISecureRandom
{
private:
	// Resource string
	const char * UnrecognisedPRNGAlgorithm = "Unrecognised PRNG Algorithm: %s \"algorithm\"";
	const char * CannotBeNegative = "Cannot be Negative \"maxValue\"";
	const char * InvalidMaxValue = "maxValue Cannot be Less Than minValue";

private:
	static int64_t Counter;
	static ISecureRandom master;
	static double DoubleScale;

	static int64_t NextCounterValue();
	
protected:
	static IRandomGenerator generator;

public:
	SecureRandom()
	{
		Boot();
	}

	SecureRandom(IRandomGenerator _generator)
		: Random(0)
	{
		generator = _generator;
	}
	
	static ISecureRandom GetMaster()
	{
		return master;
	}

	virtual vector<uint8_t> GenerateSeed(const int32_t length);
	virtual void SetSeed(vector<uint8_t> &seed);
	virtual void SetSeed(const int64_t seed);

	virtual void NextBytes(vector<uint8_t> &buf);
	virtual void NextBytes(vector<uint8_t> &buf, const int32_t off, const int32_t len);
	virtual int32_t NextInt32();
	virtual int64_t NextInt64();
	
	virtual double NextDouble();

	virtual int32_t Next();
	virtual int32_t Next(const int32_t maxValue);
	virtual int32_t Next(const int32_t minValue, const int32_t maxValue);

	static vector<uint8_t> GetNextBytes(ISecureRandom secureRandom, const int32_t length);

	static void Boot();

};

#endif // !SECURERANDOM_H
