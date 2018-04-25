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

#include "IRandom.h"

#ifndef ISECURERANDOM_H
#define ISECURERANDOM_H

class IISecureRandom;

typedef shared_ptr<IISecureRandom> ISecureRandom;

class IISecureRandom : public virtual IIRandom
{
public:
	virtual vector<uint8_t> GenerateSeed(const int32_t length) = 0;
	virtual void SetSeed(vector<uint8_t> &seed) = 0;
	virtual void SetSeed(const int64_t seed) = 0;

	virtual void NextBytes(vector<uint8_t> &buf) = 0;
	virtual void NextBytes(vector<uint8_t> &buf, const int32_t off, const int32_t len) = 0;
	virtual int32_t NextInt32() = 0;
	virtual int64_t NextInt64() = 0;

};

#endif // !ISECURERANDOM_H
