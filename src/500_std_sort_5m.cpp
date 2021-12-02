#include <stdio.h>
#include <string.h>
#include <algorithm>

inline unsigned next_int(unsigned x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return x;
}

const int N = 5000000;

unsigned a[N];

int main() {
	unsigned x = 233;
	for (int i = 0; i < N; i++) {
		x = next_int(x);
		a[i] = x;
	}
	
	std::sort(a, a + N);
	
	printf("%u\n", a[0]);
}
