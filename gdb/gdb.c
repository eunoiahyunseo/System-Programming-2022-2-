#include <stdio.h>

int add(int a, int b) {
	int result;
	result = a + b;
	return result;
}

int main() {
	int x;
	int value1, value2;
	scanf("%d %d", &value1, &value2);
	x = add(value1, value2);
	printf("x = %d\n", x);
}


