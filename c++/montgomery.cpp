/// Name: Montgomery
/// Description: Implementation of Point, Line and basic geometrical operations
/// Detail: Reference: https://cp-algorithms.com/algebra/montgomery_multiplication.html
/// Guarantee: } // Montgomery


void out(__uint128_t x)
{
	string s = "";
	while (x)
	{
		s.push_back((x%10)+'0');
		x /= 10;
	}
	reverse(s.begin(), s.end());
	cout<<s;
}

void in(__uint128_t& x)
{
    string s;
	cin>>s;
    x = 0;
	reverse(s.begin(),s.end());
	while(s.size())
	{
		x = x*10 + s.back()-'0';
		s.pop_back();
	}
}

struct u256 // struct for 256 bits integers
{
    u256() {}
    u256(__uint128_t x, __uint128_t y)
    {
        high = x;
        low = y;
    }
    __uint128_t high, low;
    u256 mult(__uint128_t x, __uint128_t y)
    {
        uint64_t a = x >> 64;
        uint64_t b = x;
        uint64_t c = y >> 64;
        uint64_t d = y;

        // perform (a+b)*(c+d) = (ac*2^128 + (ad + bc)*2^64 + bd)
        __uint128_t ac = (__uint128_t)a*c;
        __uint128_t bc = (__uint128_t)b*c;
        __uint128_t ad = (__uint128_t)a*d;
        __uint128_t bd = (__uint128_t)b*d;

        __uint128_t carry = (__uint128_t)(uint64_t)bc + (__uint128_t)(uint64_t)ad + (bd>>64);
        high = ac + (bc>>64) + (ad>>64) + (carry>>64);
        low = bd + (ad<<64) + (bc<<64);
        return u256(high, low);
    }
};

struct Montgomery // converts a number to montgomery space to perform operation mod n efficiently
{
    __uint128_t mod,inv,r256,r128;
    u256 u256_object; 
    Montgomery(__uint128_t n) // mod n
    {
        mod = n;
        
        // x*_r + n*_n = 1 (gcd(x,n))
        // precalculate the inverse and store the value of _n
        inv = 1;
        for (int i = 0; i < 7; ++i) inv *= (2 - n * inv);

        // calculate r^2 mod n
        // 2^256 % n
        r256 = -n % n;
        for (int i = 0; i < 4; ++i)
            if ((r256 <<= 1) >= mod)
                r256 -= mod;                             // 2^132
        for (int i = 0; i < 5; ++i) r256 = mult(r256, r256);  // 2^256
    }

    // performs x_bar = x.r mod n
    __uint128_t init(__uint128_t x) // (x.r mod n) = (x * r^2 mod n)
    {
        return reduce(u256_object.mult(x, r256));
    }

    __uint128_t reduce(u256 x)
    {
        __uint128_t a = x.high - u256_object.mult(x.low * inv, mod).high;
        return __int128_t(a) < 0 ? a + mod : a;
    }

    // performs a * b
    // (a*b) mod n = (a.b/r) mod n 
    __uint128_t mult(__uint128_t x, __uint128_t y) // (x.r mod n)*(y.r mod n)
    {
        return reduce(u256_object.mult(x,y));
    }

    // converts back to mod n space from montgomery space
    __uint128_t reduce(__uint128_t x)
    {
        return reduce(u256(0,x));
    }

}; // Montgomery
