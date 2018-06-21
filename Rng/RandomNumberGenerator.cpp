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

#include "RandomNumberGenerator.h"
#include "PCGRandomNumberGenerator.h"

const char * RandomNumberGenerator::UnknownAlgorithm = "Unknown Random Generation Algorithm Requested";

IRandomNumberGenerator RandomNumberGenerator::CreateRNG()
{
	return make_shared<PCGRandomNumberGenerator>();
}

IRandomNumberGenerator RandomNumberGenerator::CreateRNG(const string rngName)
{
	if (rngName == "PCGRandomNumberGenerator") return make_shared<PCGRandomNumberGenerator>();

	throw invalid_argument(UnknownAlgorithm);
}

