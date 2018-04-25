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

#ifndef IRANDOMNUMBERGENERATOR_H
#define IRANDOMNUMBERGENERATOR_H

#include <vector>
#include <memory>

using namespace std;

class IIRandomNumberGenerator;

typedef shared_ptr<IIRandomNumberGenerator> IRandomNumberGenerator;

class IIRandomNumberGenerator
{
public:
	virtual void GetBytes(vector<uint8_t> &data) = 0;

	virtual void GetNonZeroBytes(vector<uint8_t> &data) = 0;

};

#endif // !IRANDOMNUMBERGENERATOR_H
