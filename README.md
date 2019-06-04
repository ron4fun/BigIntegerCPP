BigIntegerCPP
====

 **`BigIntegerCPP`** is a C++11 port of large integer library used in [CryptoLib4Pascal](https://github.com/xor-el/CryptoLib4Pascal). It allows 
mostly parsing of numbers as strings in different bases (2, 8, 10 & 16) and converting them back to string, also in different base as stated above. The advantages of this library is its simplistic nature and cleanliness of code.
  

Code Example
------------

Here is a sample of code which uses `BigIntergerCPP` to calc 2^20.
    
```c++
#include <iostream>
#include "Base/BigInteger.h"

using namespae std;

int main()
{
    BigInteger::Boot();
    
    BigInteger two("2");
    BigInteger result = two.Pow(20);
    cout << result.ToString(2) << endl; // output string in Base 2

    return 0;
} // end main
```

Note:
**Some other functions you might like**

  	
	  RabinMillerTest
	  IsProbablePrime
	  ModInverse (Modular Inverse)
	  ModPow (Modular Exponentiation)
	  NextProbablePrime
	  Negate
	  TestBit
	  GetLowestSetBit
	  SetBit
	  ClearBit
	  FlipBit
	  GCD (Greatest Common Divisor (HCF)) 
      Square 
      AbsoluteValue (Get Absolute Value of a Negative BigInteger)
      Random (PcgRandom)



**Tested Enviroments:**
     
    Visual Studio 2015.


**Unittests:**
     
You can find all the unit tests in the Unittest folder. 
To run the unit tests, you should have [boost library](http://www.boost.org/) installed in your workstation.


**Special Note:**
     
   You may have noticed that this library needs to Boot firstly before you can begin to use it else it will crash. So, I wrote a wrapper around the BigInteger library called `BigIntegerWrapper` for those who feel they might forget to Boot the library before using it.

### License

This "Software" is Licensed Under  **`MIT License (MIT)`** .
    
#### Tip Jar
* :dollar: **Bitcoin**: `1Mcci95WffSJnV6PsYG7KD1af1gDfUvLe6`

Conclusion
--------------------------------------------------

   Special thanks to [Xor-el](https://github.com/xor-el) for making this library available in the first place.
