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

#define BOOST_TEST_MODULE FullTest

#include "../Base/BigInteger.h"
#include "../Security/SecureRandom.h"
#include <boost/test/included/unit_test.hpp>

BigInteger zero = BigInteger::GetZero();
BigInteger one = BigInteger::GetOne();
BigInteger two = BigInteger::GetTwo();
BigInteger three = BigInteger::GetThree();
BigInteger minusTwo = BigInteger::GetTwo().Negate();
BigInteger minusOne = BigInteger::GetOne().Negate();

ISecureRandom Random = nullptr;

vector<int32_t> firstPrimes = vector<int32_t>({ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 });
vector<int32_t> nonPrimes = vector<int32_t>({ 0, 1, 4, 10, 20, 21, 22, 25, 26, 27 });
vector<int32_t> mersennePrimeExponents = vector<int32_t>({ 2, 3, 5, 7, 13, 17, 19, 31, 61, 89 });
vector<int32_t> nonPrimeExponents = vector<int32_t>({ 1, 4, 6, 9, 11, 15, 23, 29, 37, 41 });

BigInteger val(int64_t n)
{
	return BigInteger::ValueOf(n);
}

void CheckEqualsBigInteger(BigInteger a, BigInteger b, const string msg = "")
{
	BOOST_CHECK(a.Equals(b), msg);
}

vector<uint8_t> GetBytes(const int32_t value)
{
	vector<uint8_t> result = vector<uint8_t>(sizeof(int32_t));
	*(int32_t *)(&(result[0])) = value;

	return result;
} // end function GetBytes

BigInteger mersenne(const int32_t e)
{
	return two.Pow(e).Subtract(one);
}

BOOST_AUTO_TEST_SUITE(FullTest)

BOOST_AUTO_TEST_CASE(TestAbs)
{
	// First test Boots all BigInteger's static variables
	BigInteger::Boot();

	zero = BigInteger::GetZero();
	one = BigInteger::GetOne();
	two = BigInteger::GetTwo();
	three = BigInteger::GetThree();
	minusTwo = BigInteger::GetTwo().Negate();
	minusOne = BigInteger::GetOne().Negate();
	
	Random = make_shared<SecureRandom>();

	BOOST_CHECK(zero.Equals(zero.Abs()));
	BOOST_CHECK(one.Equals(one.Abs()));
	BOOST_CHECK(one.Equals(minusOne.Abs()));
	BOOST_CHECK(two.Equals(two.Abs()));
	BOOST_CHECK(two.Equals(minusTwo.Abs()));
}

BOOST_AUTO_TEST_CASE(TestAdd)
{
	int32_t i, j;

	for (i = -10; i <= 10; i++)
	{
		for (j = -10; j <= 10; j++)
		{
			char char_a[5];
			char char_b[5];
			_itoa_s(i + j, char_a, 10);
			
			BigInteger a(char_a);

			_itoa_s(i, char_a, 10);
			_itoa_s(j, char_b, 10);
			BigInteger b = BigInteger(char_a).Add((BigInteger)char_b);

			BOOST_CHECK(a.Equals(b));
		}
	}
		
}

BOOST_AUTO_TEST_CASE(TestAnd)
{
	int32_t i, j;

	for (i = -10; i <= 10; i++)
	{
		for (j = -10; j <= 10; j++)
		{
			char char_a[5];
			char char_b[5];
			_itoa_s(i & j, char_a, 10);

			BigInteger a(char_a);

			_itoa_s(i, char_a, 10);
			_itoa_s(j, char_b, 10);
			BigInteger b = BigInteger(char_a).And((BigInteger)char_b);

			BOOST_CHECK(a.Equals(b));
		}
	}

}

BOOST_AUTO_TEST_CASE(TestAndNot)
{
	int32_t i, j;

	for (i = -10; i <= 10; i++)
	{
		for (j = -10; j <= 10; j++)
		{
			char char_a[5];
			char char_b[5];
			_itoa_s(i & (~j), char_a, 10);

			BigInteger a(char_a);

			_itoa_s(i, char_a, 10);
			_itoa_s(j, char_b, 10);
			BigInteger b = BigInteger(char_a).AndNot((BigInteger)char_b);

			BOOST_CHECK(a.Equals(b));
		}
	}

}

BOOST_AUTO_TEST_CASE(TestBitCount)
{
	int32_t i, bitCount, bit;
	BigInteger pow2, test;

	BOOST_CHECK(0 == zero.GetBitCount());
	BOOST_CHECK(1 == one.GetBitCount());
	BOOST_CHECK(0 == minusOne.GetBitCount());
	BOOST_CHECK(1 == two.GetBitCount());
	BOOST_CHECK(1 == minusTwo.GetBitCount());

	for (i = 0; i < 100; i++)
	{
		pow2 = one.ShiftLeft(i);

		BOOST_CHECK(1 == pow2.GetBitCount());
		BOOST_CHECK(i == pow2.Negate().GetBitCount());
	}

	i = 0;
	while (i < 10)
	{
		test = BigInteger(128, 0, Random);
		bitCount = 0;

		for (bit = 0; bit < test.GetBitLength(); bit++)
		{
			if (test.TestBit(bit)) bitCount++;
		}
		
		BOOST_CHECK(bitCount == test.GetBitCount());
		i++;
	}
	
}

BOOST_AUTO_TEST_CASE(TestBitLength)
{
	int32_t i, bitCount, bit;
	BigInteger pow2, odd;

	BOOST_CHECK(0 == zero.GetBitLength());
	BOOST_CHECK(1 == one.GetBitLength());
	BOOST_CHECK(0 == minusOne.GetBitLength());
	BOOST_CHECK(2 == two.GetBitLength());
	BOOST_CHECK(1 == minusTwo.GetBitLength());

	for (i = 0; i < 100; i++)
	{
		bit = i + Random.get()->Next(64);
		odd = BigInteger(bit, Random).SetBit(bit + 1).SetBit(0);
		pow2 = one.ShiftLeft(bit);

		BOOST_CHECK(bit + 2 == odd.GetBitLength());
		BOOST_CHECK(bit + 2 == odd.Negate().GetBitLength());
		BOOST_CHECK(bit + 1 == pow2.GetBitLength());
		BOOST_CHECK(bit == pow2.Negate().GetBitLength());
	}

}

BOOST_AUTO_TEST_CASE(TestClearBit)
{
	int32_t i, j, pos;
	BigInteger n, m, pow2, minusPow2, bigI, negI;
	string data;
	bool test;

	BOOST_CHECK(zero.Equals(zero.ClearBit(0)));
	BOOST_CHECK(zero.Equals(one.ClearBit(0)));
	BOOST_CHECK(two.Equals(two.ClearBit(0)));

	BOOST_CHECK(zero.Equals(zero.ClearBit(1)));
	BOOST_CHECK(one.Equals(one.ClearBit(1)));
	BOOST_CHECK(zero.Equals(two.ClearBit(1)));

	// TODO Tests for clearing bits in negative numbers

	// TODO Tests for clearing extended bits

	i = 0;
	while (i < 10)
	{
		n = BigInteger(128, Random);

		j = 0;
		while (j < 10)
		{
			pos = Random.get()->Next(128);
			m = n.ClearBit(pos);
			test = m.ShiftRight(pos).Remainder(two).Equals(one);

			BOOST_CHECK(test == false);
			j++;
		}
			
		i++;
	}

	for (i = 0; i < 100; i++)
	{
		pow2 = one.ShiftLeft(i);
		minusPow2 = pow2.Negate();

		BOOST_CHECK(zero.Equals(pow2.ClearBit(i)));
		BOOST_CHECK(minusPow2.ShiftLeft(1).Equals(minusPow2.ClearBit(i)));

		bigI = BigInteger::ValueOf(i);
		negI = bigI.Negate();

		for (j = 0; j < 10; j++)
		{
			BOOST_CHECK(bigI.AndNot(one.ShiftLeft(j)).Equals(bigI.ClearBit(j)));
			BOOST_CHECK(negI.AndNot(one.ShiftLeft(j)).Equals(negI.ClearBit(j)));
		}
	}

}

BOOST_AUTO_TEST_CASE(TestCompareTo)
{
	BOOST_CHECK(0 == minusTwo.CompareTo(minusTwo));
	BOOST_CHECK(-1 == minusTwo.CompareTo(minusOne));
	BOOST_CHECK(-1 == minusTwo.CompareTo(zero));
	BOOST_CHECK(-1 == minusTwo.CompareTo(one));
	BOOST_CHECK(-1 == minusTwo.CompareTo(two));

	BOOST_CHECK(1 == minusOne.CompareTo(minusTwo));
	BOOST_CHECK(0 == minusOne.CompareTo(minusOne));
	BOOST_CHECK(-1 == minusOne.CompareTo(zero));
	BOOST_CHECK(-1 == minusOne.CompareTo(one));
	BOOST_CHECK(-1 == minusOne.CompareTo(two));

	BOOST_CHECK(1 == zero.CompareTo(minusTwo));
	BOOST_CHECK(1 == zero.CompareTo(minusOne));
	BOOST_CHECK(0 == zero.CompareTo(zero));
	BOOST_CHECK(-1 == zero.CompareTo(one));
	BOOST_CHECK(-1 == zero.CompareTo(two));

	BOOST_CHECK(1 == one.CompareTo(minusTwo));
	BOOST_CHECK(1 == one.CompareTo(minusOne));
	BOOST_CHECK(1 == one.CompareTo(zero));
	BOOST_CHECK(0 == one.CompareTo(one));
	BOOST_CHECK(-1 == one.CompareTo(two));

	BOOST_CHECK(1 == two.CompareTo(minusTwo));
	BOOST_CHECK(1 == two.CompareTo(minusOne));
	BOOST_CHECK(1 == two.CompareTo(zero));
	BOOST_CHECK(1 == two.CompareTo(one));
	BOOST_CHECK(0 == two.CompareTo(two));
}

BOOST_AUTO_TEST_CASE(TestConstructors)
{
	int32_t i;
	
	BOOST_CHECK(BigInteger::GetZero().Equals(BigInteger(vector<uint8_t>({ 0 }))));
	BOOST_CHECK(BigInteger::GetZero().Equals(BigInteger(vector<uint8_t>({ 0, 0 }))));

	for (i = 0; i < 10; i++)
	{
		BOOST_CHECK(BigInteger(i + 3, 0, Random).TestBit(0));
	}

	// TODO Other constructors
}

BOOST_AUTO_TEST_CASE(TestDivide)
{
	int32_t i, product, productPlus, rep, shift, divisor;
	BigInteger bigProduct, bigProductPlus, expected, a, b, c, d, e, bShift;
	string data;

	for (i = -5; i < 5; i++)
	{
		BOOST_CHECK_THROW(val(i).Divide(zero), invalid_argument);
	}

	product = 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9;
	productPlus = product + 1;

	bigProduct = val(product);
	bigProductPlus = val(productPlus);
	for (divisor = 1; divisor < 10; divisor++)
	{
		// Exact division
		expected = val(product / divisor);

		CheckEqualsBigInteger(expected, bigProduct.Divide(val(divisor)));
		CheckEqualsBigInteger(expected.Negate(), bigProduct.Negate().Divide(val(divisor)));
		CheckEqualsBigInteger(expected.Negate(), bigProduct.Divide(val(divisor).Negate()));
		CheckEqualsBigInteger(expected, bigProduct.Negate().Divide(val(divisor).Negate()));

		expected = val((product + 1) / divisor);

		CheckEqualsBigInteger(expected, bigProductPlus.Divide(val(divisor)));
		CheckEqualsBigInteger(expected.Negate(), bigProductPlus.Negate().Divide(val(divisor)));
		CheckEqualsBigInteger(expected.Negate(), bigProductPlus.Divide(val(divisor).Negate()));
		CheckEqualsBigInteger(expected, bigProductPlus.Negate().Divide(val(divisor).Negate()));
	}

	for (rep = 0; rep < 10; rep++)
	{
		a = BigInteger(100 - rep, 0, Random);
		b = BigInteger(100 + rep, 0, Random);
		c = BigInteger(10 + rep, 0, Random);
		d = a.Multiply(b).Add(c);
		e = d.Divide(a);

		CheckEqualsBigInteger(b, e);
	}
	
	// Special tests for power of two since uses different code path internally
	i = 0;
	while (i < 100)
	{
		shift = Random.get()->Next(64);
		a = one.ShiftLeft(shift);
		b = BigInteger(64 + Random.get()->Next(64), Random);
		bShift = b.ShiftRight(shift);

		CheckEqualsBigInteger(bShift, b.Divide(a), data);
		CheckEqualsBigInteger(bShift.Negate(), b.Divide(a.Negate()), data);
		CheckEqualsBigInteger(bShift.Negate(), b.Negate().Divide(a), data);
		CheckEqualsBigInteger(bShift, b.Negate().Divide(a.Negate()), data);
		i++;
	}

	// Regression
	
	shift = 63;
	a = one.ShiftLeft(shift);
	b = BigInteger(1, GetBytes(0x2504b470dc188499));
	bShift = b.ShiftRight(shift);

	CheckEqualsBigInteger(bShift, b.Divide(a), data);
	CheckEqualsBigInteger(bShift.Negate(), b.Divide(a.Negate()), data);
	CheckEqualsBigInteger(bShift.Negate(), b.Negate().Divide(a), data);
	CheckEqualsBigInteger(bShift, b.Negate().Divide(a.Negate()), data);

}

BOOST_AUTO_TEST_CASE(TestDivideAndRemainder)
{
	vector<BigInteger> qr, es;
	int32_t rep, shift;
	BigInteger n, a, b, c, d, bShift, bMod;
	string data;

	// TODO More basic tests

	n = BigInteger(48, Random);
	qr = n.DivideAndRemainder(n);
	CheckEqualsBigInteger(one, qr[0]);
	CheckEqualsBigInteger(zero, qr[1]);

	qr = n.DivideAndRemainder(one);
	CheckEqualsBigInteger(n, qr[0]);
	CheckEqualsBigInteger(zero, qr[1]);

	for (rep = 0; rep < 10; rep++)
	{
		a = BigInteger(100 - rep, 0, Random);
		b = BigInteger(100 + rep, 0, Random);
		c = BigInteger(10 + rep, 0, Random);
		d = a.Multiply(b).Add(c);
		es = d.DivideAndRemainder(a);

		CheckEqualsBigInteger(b, es[0]);
		CheckEqualsBigInteger(c, es[1]);
	}

	// Special tests for power of two since uses different code path internally
	rep = 0;
	while (rep < 100)
	{
		shift = Random.get()->Next(64);
		a = one.ShiftLeft(shift);
		b = BigInteger(64 + Random.get()->Next(64), Random);
		bShift = b.ShiftRight(shift);
		bMod = b.And(a.Subtract(one));

		qr = b.DivideAndRemainder(a);
		CheckEqualsBigInteger(bShift, qr[0], data);
		CheckEqualsBigInteger(bMod, qr[1], data);

		qr = b.DivideAndRemainder(a.Negate());
		CheckEqualsBigInteger(bShift.Negate(), qr[0], data);
		CheckEqualsBigInteger(bMod, qr[1], data);

		qr = b.Negate().DivideAndRemainder(a);
		CheckEqualsBigInteger(bShift.Negate(), qr[0], data);
		CheckEqualsBigInteger(bMod.Negate(), qr[1], data);

		qr = b.Negate().DivideAndRemainder(a.Negate());
		CheckEqualsBigInteger(bShift, qr[0], data);
		CheckEqualsBigInteger(bMod.Negate(), qr[1], data);
		
		rep++;
	}

}

BOOST_AUTO_TEST_CASE(TestFlipBit)
{
	int32_t i, j, x, pos;
	BigInteger a, b, pow2, minusPow2, bigI, negI;
	string data;
	
	i = 0;
	while (i < 10)
	{
		a = BigInteger(128, 0, Random);
		b = a;

		x = 0;
		while (x < 100)
		{
			// Note: Intentionally greater than initial size
			pos = Random.get()->Next(256);

			a = a.FlipBit(pos);
			if (b.TestBit(pos)) b = b.ClearBit(pos);
			else
				b = b.SetBit(pos);
		
			x++;
		}

		CheckEqualsBigInteger(a, b);
		i++;
	}

	for (i = 0; i < 100; i++)
	{
		pow2 = one.ShiftLeft(i);
		minusPow2 = pow2.Negate();

		CheckEqualsBigInteger(zero, pow2.FlipBit(i));
		CheckEqualsBigInteger(minusPow2.ShiftLeft(1), minusPow2.FlipBit(i));

		bigI = BigInteger::ValueOf(i);
		negI = bigI.Negate();

		for (j = 0; j < 10; j++)
		{
			CheckEqualsBigInteger(bigI.Xor(one.ShiftLeft(j)), bigI.FlipBit(j));
			CheckEqualsBigInteger(negI.Xor(one.ShiftLeft(j)), negI.FlipBit(j));
		}
	}

}

BOOST_AUTO_TEST_CASE(TestGcd)
{
	int32_t i;
	BigInteger fac, p1, p2, gcd;
	
	i = 0;
	while (i < 10)
	{
		fac = BigInteger(32, Random).Add(two);
		p1 = BigInteger::ProbablePrime(63, Random);
		p2 = BigInteger::ProbablePrime(64, Random);

		gcd = fac.Multiply(p1).Gcd(fac.Multiply(p2));

		CheckEqualsBigInteger(fac, gcd);

		i++;
	}

}

BOOST_AUTO_TEST_CASE(TestGetLowestSetBit)
{
	int32_t i, bit1, bit2, bit3;
	BigInteger test;
	
	for (i = 1; i <= 100; i++)
	{
		test = BigInteger(i + 1, 0, Random).Add(one);
		bit1 = test.GetLowestSetBit();
		CheckEqualsBigInteger(test, test.ShiftRight(bit1).ShiftLeft(bit1));
		bit2 = test.ShiftLeft(i + 1).GetLowestSetBit();
		
		BOOST_CHECK(i + 1 == bit2 - bit1);

		bit3 = test.ShiftLeft(3 * i).GetLowestSetBit();

		BOOST_CHECK(3 * i == bit3 - bit1);
	}

}

BOOST_AUTO_TEST_CASE(TestInt32Value)
{
	vector<int32_t> tests;
	int32_t i, test;
	
	tests = vector<int32_t>({ INT32_MIN, -1234, -10, -1, 0,(~0), 1, 10, 5678, INT32_MAX });

	for (i = 0; i < tests.size(); i++)
	{
		test = tests[i];
		BOOST_CHECK(test == val(test).GetInt32Value());
	}

	// TODO Tests for large numbers
}

BOOST_AUTO_TEST_CASE(TestInt64Value)
{
	vector<int64_t> tests;
	int64_t i, test;
	

	tests = vector<int64_t>({ int64_t(INT64_MIN), int64_t(-1234), int64_t(-10), int64_t(-1), int64_t(0),
		(~int64_t(0)), int64_t(1), int64_t(10), int64_t(5678), int64_t(INT64_MAX) });

	for (i = 0; i < tests.size(); i++)
	{
		test = tests[i];
		BOOST_CHECK(test == val(test).GetInt64Value());
	}

	// TODO Tests for large numbers
}

BOOST_AUTO_TEST_CASE(TestIsProbablePrime)
{
	int32_t i, p, c, e;

	BOOST_CHECK(zero.IsProbablePrime(100) == false);
	BOOST_CHECK(zero.IsProbablePrime(0));
	BOOST_CHECK(zero.IsProbablePrime(-10));
	BOOST_CHECK(minusOne.IsProbablePrime(100) == false);
	BOOST_CHECK(minusTwo.IsProbablePrime(100));
	BOOST_CHECK(val(-17).IsProbablePrime(100));
	BOOST_CHECK(val(67).IsProbablePrime(100));
	BOOST_CHECK(val(773).IsProbablePrime(100));

	for (i = 0; i < firstPrimes.size(); i++)
	{
		p = firstPrimes[i];
		BOOST_CHECK(val(p).IsProbablePrime(100));
		BOOST_CHECK(val(-p).IsProbablePrime(100));
	}
	
	for (i = 0; i < nonPrimes.size(); i++)
	{
		c = nonPrimes[i];
		BOOST_CHECK(val(c).IsProbablePrime(100) == false);
		BOOST_CHECK(val(-c).IsProbablePrime(100) == false);
	}

	for (i = 0; i < mersennePrimeExponents.size(); i++)
	{
		e = mersennePrimeExponents[i];
		BOOST_CHECK(mersenne(e).IsProbablePrime(100));
		BOOST_CHECK(mersenne(e).Negate().IsProbablePrime(100));
	}
	
	for (i = 0; i < nonPrimeExponents.size(); i++)
	{
		e = nonPrimeExponents[i];
		BOOST_CHECK(mersenne(e).IsProbablePrime(100) == false);
		BOOST_CHECK(mersenne(e).Negate().IsProbablePrime(100) == false);
	}

	// TODO Other examples of 'tricky' values?
}

BOOST_AUTO_TEST_CASE(TestMax)
{
	int32_t i, j;
	
	for (i = -10; i <= 10; i++)
	{
		for (j = -10; j <= 10; j++)
		{
			CheckEqualsBigInteger(val(__max(i, j)), val(i).Max(val(j)));
		}
	}
}

BOOST_AUTO_TEST_CASE(TestMin)
{
	int32_t i, j;

	for (i = -10; i <= 10; i++)
	{
		for (j = -10; j <= 10; j++)
		{
			CheckEqualsBigInteger(val(__min(i, j)), val(i).Min(val(j)));
		}
	}
}

BOOST_AUTO_TEST_CASE(TestMod)
{
	int32_t rep, diff;
	BigInteger a, b, c, d, e, pow2;
	
	// TODO Basic tests

	rep = 0;
	while (rep < 100)
	{
		diff = Random.get()->Next(25);
		a = BigInteger(100 - diff, 0, Random);
		b = BigInteger(100 + diff, 0, Random);
		c = BigInteger(10 + diff, 0, Random);

		d = a.Multiply(b).Add(c);
		e = d.Mod(a);
		CheckEqualsBigInteger(c, e);

		pow2 = one.ShiftLeft(Random.get()->Next(128));
		CheckEqualsBigInteger(b.And(pow2.Subtract(one)), b.Mod(pow2));
		rep++;
	}

}

BOOST_AUTO_TEST_CASE(TestModInverse)
{
	int32_t i;
	BigInteger p, q, inv, inv2, m, d, x, check;
	
	i = 0;
	while (i < 10)
	{
		p = BigInteger::ProbablePrime(64, Random);
		q = BigInteger(63, Random).Add(one);
		inv = q.ModInverse(p);
		inv2 = inv.ModInverse(p);

		CheckEqualsBigInteger(q, inv2);
		CheckEqualsBigInteger(one, q.Multiply(inv).Mod(p));
		i++;
	}

	// ModInverse a power of 2 for a range of powers
	for (i = 1; i <= 128; i++)
	{
		m = one.ShiftLeft(i);
		d = BigInteger(i, Random).SetBit(0);
		x = d.ModInverse(m);
		check = x.Multiply(d).Mod(m);

		CheckEqualsBigInteger(one, check);
	}

}

BOOST_AUTO_TEST_CASE(TestModPow)
{
	int32_t i;
	BigInteger m, x, y, n, n3, resX, resY, res, res3, a, b;
	
	BOOST_CHECK_THROW(two.ModPow(one, zero), invalid_argument);
	
	CheckEqualsBigInteger(zero, zero.ModPow(zero, one));
	CheckEqualsBigInteger(one, zero.ModPow(zero, two));
	CheckEqualsBigInteger(zero, two.ModPow(one, one));
	CheckEqualsBigInteger(one, two.ModPow(zero, two));

	for (i = 0; i < 100; i++)
	{
		m = BigInteger::ProbablePrime(10 + i, Random);
		x = BigInteger(m.GetBitLength() - 1, Random);

		CheckEqualsBigInteger(x, x.ModPow(m, m));
		if (x.GetSignValue() != 0)
		{
			CheckEqualsBigInteger(zero, zero.ModPow(x, m));
			CheckEqualsBigInteger(one, x.ModPow(m.Subtract(one), m));
		}

		y = BigInteger(m.GetBitLength() - 1, Random);
		n = BigInteger(m.GetBitLength() - 1, Random);
		n3 = n.ModPow(three, m);

		resX = n.ModPow(x, m);
		resY = n.ModPow(y, m);
		res = resX.Multiply(resY).Mod(m);
		res3 = res.ModPow(three, m);

		CheckEqualsBigInteger(res3, n3.ModPow(x.Add(y), m));

		a = x.Add(one); // Make sure it's not zero
		b = y.Add(one); // Make sure it's not zero

		CheckEqualsBigInteger(a.ModPow(b, m).ModInverse(m),
		a.ModPow(b.Negate(), m));
	}

}

BOOST_AUTO_TEST_CASE(TestMonoBug81857)
{
	BigInteger b, exp, Mod, expected, manual;
	
	b = BigInteger("18446744073709551616");
	exp = BigInteger::GetTwo();
	Mod = BigInteger("48112959837082048697");
	expected = BigInteger("4970597831480284165");

	manual = b.Multiply(b).Mod(Mod);
	BOOST_CHECK(expected.Equals(manual));
}

BOOST_AUTO_TEST_CASE(TestMultiply)
{
	int32_t i, aLen, bLen, shift;
	BigInteger One, a, b, c, ab, bc, bShift;
	
	CheckEqualsBigInteger(one, one.Negate().Multiply(one.Negate()));

	i = 0;
	while (i < 100)
	{
		aLen = 64 + Random.get()->Next(64);
		bLen = 64 + Random.get()->Next(64);

		a = BigInteger(aLen, Random).SetBit(aLen);
		b = BigInteger(bLen, Random).SetBit(bLen);
		c = BigInteger(32, Random);

		ab = a.Multiply(b);
		bc = b.Multiply(c);

		CheckEqualsBigInteger(ab.Add(bc), a.Add(c).Multiply(b));
		CheckEqualsBigInteger(ab.Subtract(bc), a.Subtract(c).Multiply(b));
		i++;
	}
	
	// Special tests for power of two since uses different code path internally
	i = 0;
	while (i < 100)
	{
		shift = Random.get()->Next(64);
		a = one.ShiftLeft(shift);
		b = BigInteger(64 + Random.get()->Next(64), Random);
		bShift = b.ShiftLeft(shift);

		CheckEqualsBigInteger(bShift, a.Multiply(b));
		CheckEqualsBigInteger(bShift.Negate(), a.Multiply(b.Negate()));
		CheckEqualsBigInteger(bShift.Negate(), a.Negate().Multiply(b));
		CheckEqualsBigInteger(bShift, a.Negate().Multiply(b.Negate()));

		CheckEqualsBigInteger(bShift, b.Multiply(a));
		CheckEqualsBigInteger(bShift.Negate(), b.Multiply(a.Negate()));
		CheckEqualsBigInteger(bShift.Negate(), b.Negate().Multiply(a));
		CheckEqualsBigInteger(bShift, b.Negate().Multiply(a.Negate()));
		i++;
	}

}

BOOST_AUTO_TEST_CASE(TestNegate)
{
	int32_t i;
	
	for (i = -10; i < 10; i++)
	{
		CheckEqualsBigInteger(val(-i), val(i).Negate());
	}

}

BOOST_AUTO_TEST_CASE(TestNextProbablePrime)
{
	BigInteger firstPrime, nextPrime, check;
	
	firstPrime = BigInteger::ProbablePrime(32, Random);
	nextPrime = firstPrime.NextProbablePrime();

	BOOST_CHECK(firstPrime.IsProbablePrime(10));
	BOOST_CHECK(nextPrime.IsProbablePrime(10));

	check = firstPrime.Add(one);

	while (check.CompareTo(nextPrime) < 0)
	{
		BOOST_CHECK(check.IsProbablePrime(10) == false);
		check = check.Add(one);
	}

}

BOOST_AUTO_TEST_CASE(TestNot)
{
	int32_t i;
	
	for (i = -10; i <= 10; i++)
	{
		CheckEqualsBigInteger(val(~i), val(i).Not());
	}

}

BOOST_AUTO_TEST_CASE(TestOr)
{
	int32_t i, j;
	
	for (i = -10; i <= 10; i++)
	{
		for (j = -10; j <= 10; j++)
		{
			CheckEqualsBigInteger(val(i | j), val(i).Or(val(j)));
		}
	}

}

BOOST_AUTO_TEST_CASE(TestPow)
{
	int32_t i;
	BigInteger n, result;
	
	CheckEqualsBigInteger(one, zero.Pow(0));
	CheckEqualsBigInteger(zero, zero.Pow(123));
	CheckEqualsBigInteger(one, one.Pow(0));
	CheckEqualsBigInteger(one, one.Pow(123));

	CheckEqualsBigInteger(two.Pow(147), one.ShiftLeft(147));
	CheckEqualsBigInteger(one.ShiftLeft(7).Pow(11), one.ShiftLeft(77));

	n = BigInteger("1234567890987654321");
	result = one;
	for (i = 0; i < 10; i++)
	{
		BOOST_CHECK_THROW(val(i).Pow(-1), invalid_argument);

		CheckEqualsBigInteger(result, n.Pow(i));

		result = result.Multiply(n);
	}

}

BOOST_AUTO_TEST_CASE(TestRemainder)
{
	int32_t rep;
	BigInteger a, b, c, d, e;
	
	// TODO Basic tests
	for (rep = 0; rep < 10; rep++)
	{
		a = BigInteger(100 - rep, 0, Random);
		b = BigInteger(100 + rep, 0, Random);
		c = BigInteger(10 + rep, 0, Random);
		d = a.Multiply(b).Add(c);
		e = d.Remainder(a);

		CheckEqualsBigInteger(c, e);
	}

}

BOOST_AUTO_TEST_CASE(TestSetBit)
{
	int32_t i, j, pos;
	bool test;
	BigInteger m, n, pow2, minusPow2, bigI, negI;
	string data;

	CheckEqualsBigInteger(one, zero.SetBit(0));
	CheckEqualsBigInteger(one, one.SetBit(0));
	CheckEqualsBigInteger(three, two.SetBit(0));

	CheckEqualsBigInteger(two, zero.SetBit(1));
	CheckEqualsBigInteger(three, one.SetBit(1));
	CheckEqualsBigInteger(two, two.SetBit(1));

	// TODO Tests for setting bits in negative numbers

	// TODO Tests for setting extended bits

	i = 0;
	while (i < 10)
	{
		n = BigInteger(128, Random);

		j = 0;
		while (j < 10)
		{
			pos = Random.get()->Next(128);
			m = n.SetBit(pos);
			test = m.ShiftRight(pos).Remainder(two).Equals(one);

			BOOST_CHECK(test);
			j++;
		}

		i++;
	}
	
	for (i = 0; i < 100; i++)
	{
		pow2 = one.ShiftLeft(i);
		minusPow2 = pow2.Negate();

		CheckEqualsBigInteger(pow2, pow2.SetBit(i));
		CheckEqualsBigInteger(minusPow2, minusPow2.SetBit(i));

		bigI = BigInteger::ValueOf(i);
		negI = bigI.Negate();

		for (j = 0; j < 10; j++)
		{
			CheckEqualsBigInteger(bigI.Or(one.ShiftLeft(j)), bigI.SetBit(j));
			CheckEqualsBigInteger(negI.Or(one.ShiftLeft(j)), negI.SetBit(j));
		}
	}

}

BOOST_AUTO_TEST_CASE(TestShiftLeft)
{
	int32_t i, j, shift;
	BigInteger a, b, c, negA;
	vector<uint8_t> bt;
	
	for (i = 0; i < 100; i++)
	{
		shift = Random.get()->Next(128);
		bt = vector<uint8_t>(1000);
		Random.get()->NextBytes(bt);

		a = BigInteger(128 + i, Random).Add(one);

		negA = a.Negate();

		b = a.ShiftLeft(shift);
		c = negA.ShiftLeft(shift);

		BOOST_CHECK(a.GetBitCount() == b.GetBitCount());
		BOOST_CHECK(negA.GetBitCount() + shift == c.GetBitCount());
		BOOST_CHECK(a.GetBitLength() + shift == b.GetBitLength());
		BOOST_CHECK(negA.GetBitLength() + shift == c.GetBitLength());

		j = 0;
		while (j < shift)
		{
			BOOST_CHECK(b.TestBit(j) == false);
			j++;
		}

		while (j < b.GetBitLength())
		{
			BOOST_CHECK(a.TestBit(j - shift) == b.TestBit(j));
			j++;
		}

	}

}

BOOST_AUTO_TEST_CASE(TestShiftRight)
{
	int32_t i, j, shift;
	BigInteger a, b;
	
	for (i = 0; i < 10; i++)
	{
		shift = Random.get()->Next(128);
		a = BigInteger(256 + i, Random).SetBit(256 + i);
		b = a.ShiftRight(shift);

		BOOST_CHECK(a.GetBitLength() - shift == b.GetBitLength());

		for (j = 0; j < b.GetBitLength(); j++)
		{
			BOOST_CHECK(a.TestBit(j + shift) == b.TestBit(j));
		}

	}

}

BOOST_AUTO_TEST_CASE(TestSignValue)
{
	int32_t i;
	
	for (i = -10; i <= 10; i++)
	{
		if (i < 0) BOOST_CHECK(-1 == val(i).GetSignValue());
		else if (i > 0)
			BOOST_CHECK(1 == val(i).GetSignValue());
		else
			BOOST_CHECK(0 == val(i).GetSignValue());
	}

}

BOOST_AUTO_TEST_CASE(TestSubtract)
{
	int32_t i, j;
	
	for (i = -10; i <= 10; i++)
	{
		for (j = -10; j <= 10; j++)
		{
			CheckEqualsBigInteger(val(i - j), val(i).Subtract(val(j)));
		}
	}
}

BOOST_AUTO_TEST_CASE(TestTestBit)
{
	int32_t i, j, pos;
	BigInteger n;
	bool test;
	
	i = 0;
	while (i < 10)
	{
		n = BigInteger(128, Random);

		BOOST_CHECK(n.TestBit(128) == false);
		BOOST_CHECK(n.Negate().TestBit(128));

		j = 0;
		while (j < 10)
		{
			pos = Random.get()->Next(128);
			test = n.ShiftRight(pos).Remainder(two).Equals(one);

			BOOST_CHECK(test == n.TestBit(pos));
			j++;
		}
		
		i++;
	}
	
}

BOOST_AUTO_TEST_CASE(TestToByteArray)
{
	vector<uint8_t> z, temp, b;
	int32_t i;
	BigInteger x, y;
	
	z = zero.ToByteArray();
	temp = vector<uint8_t>(1);

	BOOST_CHECK(temp == z);

	for (i = 16; i <= 48; i++)
	{
		x = BigInteger::ProbablePrime(i, Random);
		b = x.ToByteArray();
		
		BOOST_CHECK(((i / 8) + 1) == b.size());
		
		y = BigInteger(b);
		CheckEqualsBigInteger(x, y);

		x = x.Negate();
		b = x.ToByteArray();
		
		BOOST_CHECK(((i / 8) + 1) == b.size());

		y = BigInteger(b);
		CheckEqualsBigInteger(x, y);
	}

}

BOOST_AUTO_TEST_CASE(TestToByteArrayUnsigned)
{
	vector<uint8_t> z, temp, b;
	int32_t i;
	BigInteger x, y;
	
	z = zero.ToByteArrayUnsigned();
	temp = vector<uint8_t>(0);
	
	BOOST_CHECK(temp == z);

	for (i = 16; i <= 48; i++)
	{
		x = BigInteger::ProbablePrime(i, Random);
		b = x.ToByteArrayUnsigned();
		
		BOOST_CHECK(((i + 7) / 8) == b.size());
		
		y = BigInteger(1, b);
		CheckEqualsBigInteger(x, y);

		x = x.Negate();
		b = x.ToByteArrayUnsigned();
		
		BOOST_CHECK(((i / 8) + 1) == b.size());

		y = BigInteger(b);
		CheckEqualsBigInteger(x, y);
	}

}

BOOST_AUTO_TEST_CASE(TestToString)
{
	string s, str;
	vector<int32_t> radices;
	vector<BigInteger>	tests;
	int32_t i, trials, len, radix;
	BigInteger n, n1, n2;
	
	s = "12345667890987654321";

	BOOST_CHECK(s == BigInteger(s).ToString());
	BOOST_CHECK(s == BigInteger(s, 10).ToString(10));
	BOOST_CHECK(s == BigInteger(s, 16).ToString(16));

	BOOST_CHECK("-e4437ed6010e88286f547fa90abfe4c3" == BigInteger("-e4437ed6010e88286f547fa90abfe4c3", 16).ToString(16));

	for (i = 0; i < 100; i++)
	{
		n = BigInteger(i, Random);

		CheckEqualsBigInteger(n, BigInteger(n.ToString(2), 2));
		CheckEqualsBigInteger(n, BigInteger(n.ToString(8), 8));
		CheckEqualsBigInteger(n, BigInteger(n.ToString(10), 10));
		CheckEqualsBigInteger(n, BigInteger(n.ToString(16), 16));
	}

	// Radix version	
	radices = vector<int32_t>({ 2, 8, 10, 16 });
	trials = 256;

	tests = vector<BigInteger>(trials);
	for (i = 0; i < trials; i++)
	{
		len = Random.get()->Next(i + 1);
		tests[i] = BigInteger(len, Random);
	}

	for (i = 0; i < radices.size(); i++)
	{
		radix = radices[i];

		for (i = 0; i < trials; i++)
		{
			n1 = tests[i];
			str = n1.ToString(radix);
			n2 = BigInteger(str, radix);

			CheckEqualsBigInteger(n1, n2);
		}
	}

}

BOOST_AUTO_TEST_CASE(TestValueOf)
{
	int32_t i;
	
	BOOST_CHECK(-1 == BigInteger::ValueOf(-1).GetSignValue());
	BOOST_CHECK(0 == BigInteger::ValueOf(0).GetSignValue());
	BOOST_CHECK(1 == BigInteger::ValueOf(1).GetSignValue());

	for (i = -5; i < 5; i++)
	{
		BOOST_CHECK(i == BigInteger::ValueOf(i).GetInt32Value());
	}

}

BOOST_AUTO_TEST_CASE(TestXor)
{
	int32_t i, j;
	
	for (i = -10; i <= 10; i++)
	{
		for (j = -10; j <= 10; j++)
		{
			CheckEqualsBigInteger(val(i ^ j), val(i).Xor(val(j)));
		}
	}
		
}

BOOST_AUTO_TEST_SUITE_END()

