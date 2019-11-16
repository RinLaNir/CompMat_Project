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
	BigNumber bn;
	bn = input();
	printf("%x", bn._bits[1]);
	output(bn);
}

int main() {
	test_2();
	char str[20] = "FFFF";
	printf("%x", atoi(str));
}