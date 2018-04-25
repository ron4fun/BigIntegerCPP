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

#ifndef IRANDOMGENERATOR_H
#define IRANDOMGENERATOR_H

#include <vector>	

using namespace std;

class IIRandomGenerator;

typedef shared_ptr<IIRandomGenerator> IRandomGenerator;

class IIRandomGenerator
{
public:
	/// <summary>Add more seed material to the generator.</summary>
	/// <param name="seed">A byte array to be mixed into the generator's state.</param>
	virtual void AddSeedMaterial(vector<uint8_t> &seed) = 0;

	/// <summary>Add more seed material to the generator.</summary>
	/// <param name="seed">A long value to be mixed into the generator's state.</param>
	virtual void AddSeedMaterial(const int64_t seed) = 0;

	/// <summary>Fill byte array with random values.</summary>
	/// <param name="bytes">Array to be filled.</param>
	virtual void NextBytes(vector<uint8_t> &bytes) = 0;

	/// <summary>Fill byte array with random values.</summary>
	/// <param name="bytes">Array to receive bytes.</param>
	/// <param name="start">Index to start filling at.</param>
	/// <param name="len">Length of segment to fill.</param>
	virtual void NextBytes(vector<uint8_t> &bytes, const int32_t start, const int32_t len) = 0;
};

#endif // !IRANDOMGENERATOR_H
