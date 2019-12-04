#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "BigNumber.h"
#include <stdlib.h>

void test_1() {
	char lst[100];
	gets_s(lst, 100);
	for (int i = strlen(lst);i > 0;i -= 4) {
		printf("%s ", i > 4 ? lst + i - 4 : lst);
		lst[i - 4] = '\0';
	}
}

void test_2() {
	BigNumber x,y,z;
	input(&x);
	input(&y);
	z = mul(x, y);
	output(z);
}

int main() {
	/*int i = 0;
	while (i != 100)
	{
		test_2();
		printf("i = ");
		scanf("%d", &i);
	}*/
	BigNumber x;
	x = Parse();
	output(x);
}