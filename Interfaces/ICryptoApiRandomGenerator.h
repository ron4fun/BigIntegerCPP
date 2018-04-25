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

#ifndef ICRYPTOAPIRANDOMGENERATOR_H
#define ICRYPTOAPIRANDOMGENERATOR_H

#include "IRandomGenerator.h"

class IICryptoApiRandomGenerator;

typedef shared_ptr<IICryptoApiRandomGenerator> ICryptoApiRandomGenerator;

class IICryptoApiRandomGenerator: public virtual IIRandomGenerator
{};

#endif // !ICRYPTOAPIRANDOMGENERATOR_H