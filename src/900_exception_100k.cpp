static int f() {
	try {
		__asm__ volatile ("");
		throw "test";
	} catch (const char *s) {
		return 1;
	}
	return 0;
}

const int N = 100000;

int main() {
	for (int i = 0; i < N; i++) {
		f();
	}
}
