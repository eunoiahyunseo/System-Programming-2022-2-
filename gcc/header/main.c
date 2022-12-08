#include <stdio.h>
#include "add.h"


int main(void) {
	int value1, value2;

	printf("hello my name is hyunseo");
	scanf("%d %d", &value1, &value2);
	printf("\n %d + %d = %d\n", value1, value2, add(value1, value2));
	return 0;
}

