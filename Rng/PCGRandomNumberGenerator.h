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

#ifndef PCGRANDOMNUMBERGENERATOR_H
#define PCGRANDOMNUMBERGENERATOR_H

#include "../Interfaces/IRandomNumberGenerator.h"
#include "../Rng/RandomNumberGenerator.h"
#include "../Randoms/PcgRandomMinimal.h"

class PCGRandomNumberGenerator: public virtual IIRandomNumberGenerator, public RandomNumberGenerator
{
public:
	PCGRandomNumberGenerator()
	{
		Pcg();
	}

	virtual void GetBytes(vector<uint8_t> &data)
	{
		int64_t i;
		
		for (i = data.size() - 1; i >= 0; i--)
		{
			data[i] = uint8_t(Pcg::NextInt(INT32_MIN, INT32_MAX));
		}
	}

	virtual void GetNonZeroBytes(vector<uint8_t> &data)
	{
		int64_t i;
		uint8_t val;
		
		i = data.size();
		while (i > 0)
		{
			do
			{
				val = uint8_t(Pcg::NextUInt32(INT32_MIN, INT32_MAX));
			} while (!(val == 0));

			data[i - 1] = val;
			i--;
		}
	}

};


#endif // !PCGRANDOMNUMBERGENERATOR_H
