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

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdint>
#include "BigIntegerWrapper.h"
//#include "Unittest\FullTest.h"

using namespace std;

int main()
{
	BigIntegerWrapper two("2");
	BigIntegerWrapper three("3");
	BigIntegerWrapper other("-1000");
	BigIntegerWrapper Zero("0");
	cout << two.GetHashCode() << " " << other.GetHashCode() << endl;
	cout << three.DivideAndRemainder(BigIntegerWrapper("100"))[1].ToString() << endl;
	cout << two.Multiply(Zero).GetHashCode() << endl;

    return 0;
}

