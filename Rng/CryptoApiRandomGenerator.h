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

#ifndef CRYPTOAPIRANDOMGENERATOR_H
#define CRYPTOAPIRANDOMGENERATOR_H

#include "../Interfaces/ICryptoApiRandomGenerator.h"
#include "../Interfaces/IRandomGenerator.h"
#include "../Interfaces/IRandomNumberGenerator.h"
#include "../Rng/RandomNumberGenerator.h"

class CryptoApiRandomGenerator: public virtual IICryptoApiRandomGenerator, public virtual IIRandomGenerator
{
private:
	// Resource string
	const char * NegativeOffset = "Start Offset Cannot be Negative, \"Start\"";
	const char * ArrayTooSmall = "Byte Array Too Small For Requested Offset and Length";

	IRandomNumberGenerator FrndProv = nullptr;

public:
	/// <summary>
	/// Uses TRandomNumberGenerator.CreateRNG() to Get randomness generator
	/// </summary>
	CryptoApiRandomGenerator()
	{
		FrndProv = RandomNumberGenerator::CreateRNG();
	}

	CryptoApiRandomGenerator(IRandomNumberGenerator rng)
	{
		FrndProv = rng;
	}

	/// <summary>Add more seed material to the generator.</summary>
	/// <param name="seed">A byte array to be mixed into the generator's state.</param>
	virtual void AddSeedMaterial(vector<uint8_t> &seed) {};

	/// <summary>Add more seed material to the generator.</summary>
	/// <param name="seed">A long value to be mixed into the generator's state.</param>
	virtual void AddSeedMaterial(const int64_t seed) {};

	/// <summary>Fill byte array with random values.</summary>
	/// <param name="bytes">Array to be filled.</param>
	virtual void NextBytes(vector<uint8_t> &bytes)
	{
		FrndProv.get()->GetBytes(bytes);
	}

	/// <summary>Fill byte array with random values.</summary>
	/// <param name="bytes">Array to receive bytes.</param>
	/// <param name="start">Index to start filling at.</param>
	/// <param name="len">Length of segment to fill.</param>
	virtual void NextBytes(vector<uint8_t> &bytes, const int32_t start, const int32_t len)
	{
		vector<uint8_t> tmpBuf;
		
		if (start < 0)
			throw invalid_argument(NegativeOffset);

		if (bytes.size() < (start + len))
			throw invalid_argument(ArrayTooSmall);

		if ((bytes.size() == len) && (start == 0))
			NextBytes(bytes);
		else
		{
			tmpBuf = vector<uint8_t>(len);
			NextBytes(tmpBuf);

			memmove(&tmpBuf[0], &bytes[start], len * sizeof(uint8_t));
		}
	}

};

#endif // !CRYPTOAPIRANDOMGENERATOR_H