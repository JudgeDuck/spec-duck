#include <stdio.h>
#include <string.h>

inline unsigned next_int(unsigned x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return x;
}

const int N = 50000000;

unsigned a[N], b[N];

void sort(unsigned *a, int n, unsigned *b){
	unsigned cnt1[256], cnt2[256], cnt3[256], cnt4[256];
	memset(cnt1, 0, sizeof(cnt1));
	memset(cnt2, 0, sizeof(cnt2));
	memset(cnt3, 0, sizeof(cnt3));
	memset(cnt4, 0, sizeof(cnt4));
	
	for (int i = 0; i < n; i++) {
		cnt1[a[i] & 255]++;
		cnt2[(a[i] >> 8) & 255]++;
		cnt3[(a[i] >> 16) & 255]++;
		cnt4[a[i] >> 24]++;
	}
	
	for (int i = 1; i < 256; i++) {
		cnt1[i] += cnt1[i - 1];
		cnt2[i] += cnt2[i - 1];
		cnt3[i] += cnt3[i - 1];
		cnt4[i] += cnt4[i - 1];
	}
	
	for (int i = n - 1; i >= 0; i--) b[--cnt1[a[i] & 255]] = a[i];
	for (int i = n - 1; i >= 0; i--) a[--cnt2[(b[i] >> 8) & 255]] = b[i];
	for (int i = n - 1; i >= 0; i--) b[--cnt3[(a[i] >> 16) & 255]] = a[i];
	for (int i = n - 1; i >= 0; i--) a[--cnt4[b[i] >> 24]] = b[i];
}

int main() {
	unsigned x = 233;
	for (int i = 0; i < N; i++) {
		x = next_int(x);
		a[i] = x;
	}
	
	sort(a, N, b);
	
	printf("%u\n", a[0]);
}
