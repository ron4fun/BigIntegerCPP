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

#include "PcgRandomMinimal.h"


uint64_t Pcg::m_state = 0;
uint64_t Pcg::m_inc = 0;
int64_t Pcg::I64 = 0;

Pcg::Pcg()
{
	uint64_t LinitState, LinitSeq;
	
	LinitState = GetInitState(LinitSeq);

	// ==> initializes using system time as initState and calculated value as
	// initSeq
	Seed(LinitState, LinitSeq);
}

Pcg::Pcg(const uint64_t initState, const uint64_t initSeq)
{
	Seed(initState, initSeq);
}

uint32_t Pcg::NextUInt32()
{
	uint64_t oldState;
	uint32_t xorShifted;
	int rot;
	
	oldState = m_state;
	m_state = oldState * uint64_t(6364136223846793005) + m_inc;
	xorShifted = uint32_t(((oldState >> 18) ^ oldState) >> 27);
	rot = int(oldState >> 59);
	
	return (xorShifted >> rot) | (xorShifted << ((-rot) & 31));
}

uint32_t Pcg::NextUInt32(const uint32_t minimum, const uint32_t exclusiveBound)
{
	uint32_t boundRange, rangeResult;
	
	boundRange = exclusiveBound - minimum;
	rangeResult = Range32(boundRange);

	return rangeResult + minimum;
}

int Pcg::NextInt(const int minimum, const int exclusiveBound)
{
	uint32_t boundRange, rangeResult;

	boundRange = uint32_t(exclusiveBound - minimum);
	rangeResult = Range32(boundRange);
	
	return int(rangeResult) + int(minimum);
}

void Pcg::Seed(const uint64_t initState, const uint64_t initSeq)
{
	m_state = uint32_t(0);
	m_inc = (initSeq << 1) | uint64_t(1);
	NextUInt32();
	m_state = m_state + initState;
	NextUInt32();
}

uint32_t Pcg::Range32(const uint32_t exclusiveBound)
{
	uint32_t r, threshold;

	// To avoid bias, we need to make the range of the RNG
	// a multiple of bound, which we do by dropping output
	// less than a threshold. A naive scheme to calculate the
	// threshold would be to do
	//
	// threshold = UInt64($100000000) mod exclusiveBound;
	//
	// but 64-bit div/mod is slower than 32-bit div/mod
	// (especially on 32-bit platforms). In essence, we do
	//
	// threshold := UInt32((UInt64($100000000) - exclusiveBound) mod exclusiveBound);
	//
	// because this version will calculate the same modulus,
	// but the LHS value is less than 2^32.
	threshold = uint32_t((uint64_t(0x100000000) - exclusiveBound) % exclusiveBound);

	// Uniformity guarantees that this loop will terminate.
	// In practice, it should terminate quickly; on average
	// (assuming all bounds are equally likely), 82.25% of
	// the time, we can expect it to require just one
	// iteration. In the worst case, someone passes a bound
	// of 2^31 + 1 (i.e., 2147483649), which invalidates
	// almost 50% of the range. In practice bounds are
	// typically small and only a tiny amount of the range
	// is eliminated.
	while (true)
	{
		r = NextUInt32();
		if (r >= threshold)
		{
			return r % exclusiveBound;
		}
	}

	return  0; // to make FixInsight Happy :)
}

uint64_t Pcg::GetInitState(uint64_t &initSeq)
{
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	uint64_t result = ms.count();
	initSeq = GetInitSeq(result) * uint64_t(int64_t(1000000));

	return result;
}

uint64_t Pcg::GetInitSeq(const uint64_t tempVal)
{
	return tempVal * uint64_t(181783497276652981);
}