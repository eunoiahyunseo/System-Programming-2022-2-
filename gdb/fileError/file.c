#include <stdio.h>

void f() {
	FILE *fp;
	int x;
	fp = fopen("aaa", "r");
	fscanf(fp, "%d", &x);
	printf("x = %d\n", x);
}

int main() {
	printf("Hello \n");
	f();
	printf("Good bye \n");
}
