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
		
#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include "../Interfaces/IRandomNumberGenerator.h"
#include <string>

class RandomNumberGenerator: public IRandomNumberGenerator
{
private:
	// Resource string
	static const char * UnknownAlgorithm;

public:
	static IRandomNumberGenerator CreateRNG();

	static IRandomNumberGenerator CreateRNG(const string rngName);

	virtual void GetBytes(vector<uint8_t> &data) = 0;

	virtual void GetNonZeroBytes(vector<uint8_t> &data) = 0;

};

#endif // !RANDOMNUMBERGENERATOR_H