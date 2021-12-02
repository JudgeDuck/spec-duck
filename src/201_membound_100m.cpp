#define N (100 * 1000 * 1000)   // 100M
#define M 10

char a[N];

int main() {
	for (int cnt = 0; cnt < M; cnt++) {
		for (int i = 0; i < N; i += 64) {
			a[i] = 1;
		}
	}
}
