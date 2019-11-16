#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "BigNumber.h"
#include <stdlib.h>
#include <ctype.h> 
#include <math.h>

#define MAX_LEN 1024

BigNumber input() {
	//args
	BigNumber BN;
	char str[MAX_LEN];                                          //вхідне число
	int sytema_chislennya;
	int k = 0;													//використовується у for
	unsigned int lst[MAX_LEN];                                  //массив чисел, який передаеться у _bits головної структури

	printf("Sytema_chislennya: ");
	scanf("%d", &sytema_chislennya);
	BN.base = sytema_chislennya;

	BN._bits = lst;
	printf("Number: ");
	getchar();
	gets_s(str, 1024);
	BN.SIZE = strlen(str) / 4;
	if (str[0] == '-') {
		BN._sign = -1;
		strcpy(str, str + 1);
	}
	else BN._sign = 1;

	for (int i = strlen(str);i > 0;i -= 4)
	{
		BN._bits[k] = convert(i > 4 ? str + i - 4 : str, BN.base);
		if (i > 4)str[i - 4] = '\0';
		k++;
	}
	//printf(" k = %d size = %d ", k, BN.SIZE);
	return BN;
}

void output(BigNumber x) {
	if (x._sign == -1) printf("-");
	for (int i = x.SIZE;i >= 0;i--) {
		printf("%x", x._bits[i]);
	}
	printf("\n");
}

unsigned int convert(char* number, int base) {
	unsigned int num = 0;
	int len = strlen(number)-1;
	//printf("len %d %s\n", len, number);
	for (int i = len; i >= 0; i--)
	{
		if (number[i] >= '0' && number[i] <= '9') num += ((int)number[i] - 48)*pow(base, len - i);
		else if (tolower(number[i]) >= 'a' && tolower(number[i]) <= 'f') num += ((int)tolower(number[i]) - 87)*pow(base, len - i);
		else printf("Convert error %c %s\n", tolower(number[i]), number);
	}
	return num;
}