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

#ifndef IRANDOM_H
#define IRANDOM_H

#include <vector>
#include <memory>

using namespace std;

class IIRandom;

typedef shared_ptr<IIRandom> IRandom;

class IIRandom
{
public:
	virtual void NextBytes(vector<uint8_t> &buf) = 0;

	virtual double NextDouble() = 0;

	virtual int32_t Next() = 0;
	virtual int32_t Next(const int32_t maxValue) = 0;
	virtual int32_t Next(const int32_t minValue, const int32_t maxValue) = 0;

};

#endif // !IRANDOM_H
