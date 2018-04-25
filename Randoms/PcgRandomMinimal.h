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

#ifndef PCGRANDOMMINIMAL_H
#define PCGRANDOMMINIMAL_H

#include <memory>
#include <chrono>

using namespace std::chrono;

class Pcg
{
private:
	/// <summary>
	/// The RNG state. All values are possible.
	/// </summary>
	static uint64_t m_state;

	/// <summary>
	/// Controls which RNG sequence (stream) is selected.
	/// Must <strong>always</strong> be odd.
	/// </summary>
	static uint64_t m_inc;

	/// <summary>
	/// Internal variable used for Casting.
	/// </summary>
	static int64_t I64;

	/// <summary>
	/// Seed Pcg in two parts, a state initializer
	/// and a sequence selection constant (a.k.a.
	/// stream id).
	/// </summary>
	/// <param name="initState">Initial state.</param>
	/// <param name="initSeq">Initial sequence</param>
	static inline void Seed(const uint64_t initState, const uint64_t initSeq);

	/// <summary>
	/// Generates a uniformly distributed number, r,
	/// where 0 &lt;= r &lt; exclusiveBound.
	/// </summary>
	/// <param name="exclusiveBound">Exclusive bound.</param>
	static uint32_t Range32(const uint32_t exclusiveBound);

	/// <summary>
	/// Generates an Init State from System Time.
	/// </summary>
	/// <param name="initSeq">Calculated initSeq.</param>
	/// <returns> UInt64 </returns>
	static inline uint64_t GetInitState(uint64_t &initSeq);

	/// <summary>
	/// Generates an Init Sequence from GetInitState value * 181783497276652981.
	/// <param name="tempVal">Previous value from GetInitState.</param>
	/// </summary>
	/// <returns> UInt64 </returns>
	static inline uint64_t GetInitSeq(const uint64_t tempVal);

public:
	/// <summary>
	/// Initializes a new instance of the <see cref="TPcg"/> class
	/// <strong>FOR TESTING</strong> with a <strong>KNOWN</strong> seed.
	/// </summary>
	Pcg();

	/// <summary>
	/// Initializes a new instance of the <see cref="TPcg"/> class.
	/// </summary>
	/// <param name="initState">Initial state.</param>
	/// <param name="initSeq">Initial sequence</param>
	Pcg(const uint64_t initState, const uint64_t initSeq);

	/// <summary>
	/// Generates a uniformly-distributed 32-bit random number.
	/// </summary>
	static uint32_t NextUInt32();

	/// <summary>
	/// Generates a uniformly distributed number, r,
	/// where minimum &lt;= r &lt; exclusiveBound.
	/// </summary>
	/// <param name="minimum">The minimum inclusive value.</param>
	/// <param name="exclusiveBound">The maximum exclusive bound.</param>
	static uint32_t NextUInt32(const uint32_t minimum, const uint32_t exclusiveBound);

	/// <summary>
	/// Generates a uniformly distributed number, r,
	/// where minimum &lt;= r &lt; exclusiveBound.
	/// </summary>
	/// <param name="minimum">The minimum inclusive value.</param>
	/// <param name="exclusiveBound">The maximum exclusive bound.</param>
	static int NextInt(const int minimum, const int exclusiveBound);

};


#endif // !PCGRANDOMMINIMAL_H
