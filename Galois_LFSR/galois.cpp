#include <stdint.h>
#include <stdio.h>
#include <cstring>

template<int len, unsigned long long mask>
class Galois
{
	unsigned long long lfsr;

public:
	Galois(unsigned long long seed = 1) : lfsr(seed)
	{
	}
	
	unsigned long long next()
	{
        unsigned long long lsb = lfsr & 1;   /* Get MSB (i.e., the output bit). */
        lfsr >>= 1;                          /* Shift register */
        if (lsb)                             /* If the output bit is 1, */
            lfsr ^= mask;                    /* apply toggle mask. */

        return lfsr;
	}
	
	unsigned long long prev()
	{
        unsigned long long msb = lfsr & (1 << (len - 1));   /* Get MSB (i.e., the output bit). */
        lfsr <<= 1;                                         /* Shift register */
        if (msb)                                            /* If the output bit is 1, */
            lfsr ^= (mask << 1) | 1;                        /* apply toggle mask. */		

        return lfsr;
	}
};

int main(int argc, char* argv[])
{
	Galois<8, 0xB8ull> e; // pseudo-random sequence of 2^8-1 (255) unique numbers with vulues between 1 and 255
	Galois<16, 0xD008ull> f; // pseudo-random sequence of 2^16-1 (65535) unique numbers with values between 1 and 65535
	Galois<32, 0x80200003u> g; // pseudo-random sequence of 2^32-1 (4.29 billion) unique numbers with values between 1 and 4,294,967,296
	Galois<64, 0xD800000000000000ull> h; // pseudo-random sequence of 2^64-1 (18.4 billion billion) unique numbers with values between 1 and 18,446,744,073,709,551,616

	for(int i = 0; i < 8; i++)
	{
		printf("%02llX ", e.next());
	}
	printf("# ");
	for(int i = 0; i < 8; i++)
	{
		printf("%02llX ", e.prev());
	}
	printf("\n");

	unsigned long long xxx = 1;
	while(1 != f.next())
	{
		xxx++;
	}
	printf("%16llX\n", xxx);

	return 0;
}
