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

#ifndef NUMBERSTYLES_H
#define NUMBERSTYLES_H

class NumberStyles
{
public:
	static const auto None = 0;
	static const auto AllowLeadingWhite = 1;
	static const auto AllowTrailingWhite = 2;
	static const auto AllowLeadingSign = 4;
	static const auto AllowTrailingSign = 8;
	static const auto AllowParentheses = 16;
	static const auto AllowDecimalPoint = 32;
	static const auto AllowThousands = 64;
	static const auto AllowExponent = 128;
	static const auto AllowCurrencySymbol = 256;
	static const auto AllowHexSpecifier = 512;
	static const auto Integer = 4 | 2 | 1;

};


#endif // !NUMBERSTYLES_H
