#define _CRT_SECURE_NO_WARNINGS
#define MAX_UINT 0x100000000

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include <math.h>
#include "BigNumber.h"
#include "common.h"

#define MAX_LEN 1024

void input(BigNumber *BN) {
	//args
	Chtype str[MAX_LEN];                                          //âõ³äíå ÷èñëî
	Itype sytema_chislennya;
	Itype k = 0;													//âèêîðèñòîâóºòüñÿ ó for

	printf("Sytema_chislennya: ");
	scanf("%d", &sytema_chislennya);
	BN->base = sytema_chislennya;

	for (Itype i = 0; i < MAX_LEN; i++) BN->_bits[i] = 0;
	printf("Number: ");
	getchar();
	gets_s(str, 1024);
	BN->SIZE = strlen(str) / 8;
	if (str[0] == '-') {
		BN->_sign = -1;
		strcpy(str, str + 1);
	}
	else BN->_sign = 1;

	for (Itype i = strlen(str);i > 0;i -= 8)
	{
		BN->_bits[k] = Ñonvert(i > 8 ? str + i - 8 : str, BN->base);
		if (i > 8)str[i - 8] = '\0';
		k++;
	}
}

void output(BigNumber x) {
	if (x._sign == -1) printf("-");
	for (Itype i = x.SIZE;i >= 0;i--)
	{
		if (x._bits == 0) x.SIZE--;
		else break;
	}
	printf("%x", x._bits[x.SIZE]);
	for (Itype i = x.SIZE-1;i >= 0;i--) printf("%08x", x._bits[i]);
	printf("\n");
}

UItype Ñonvert(char* number, Itype base) {
	UItype num = 0;
	Itype len = strlen(number)-1;
	//printf("len %d %s\n", len, number);
	for (Itype i = len; i >= 0; i--)
	{
		if (number[i] >= '0' && number[i] <= '9') num += ((Itype)number[i] - 48)*pow(base, len - i);
		else if (tolower(number[i]) >= 'a' && tolower(number[i]) <= 'f') num += ((Itype)tolower(number[i]) - 87)*pow(base, len - i);
		else printf("Convert error %c %s\n", tolower(number[i]), number);
	}
	return num;
}

//error C2371  redefinition; different basic types
void add_BigNumber(BigNumber x, BigNumber y, BigNumber *z);
void add_BigNumber2(BigNumber x, BigNumber y, BigNumber *z);
void sub_BigNumber(BigNumber x, BigNumber y, BigNumber *z);
void sub_BigNumber2(BigNumber x, BigNumber y, BigNumber *z);


BigNumber add(const BigNumber x, const BigNumber y) {
	BigNumber z;
	z.base = x.base;
	LLtype num = 0;
	for (Itype i = 0; i < MAX_LEN; i++) z._bits[i] = 0;
	z.SIZE = BigNumberMaxSize(x, y);
	if (x._sign == y._sign) add_BigNumber(x, y, &z);
	else sub_BigNumber(x, y, &z);
	return z;
}

void add_BigNumber(BigNumber x, BigNumber y, BigNumber *z) {
	z->_sign = x._sign;
	ULLtype num = 0;
	Itype i = 0;
	while (i <= x.SIZE && i <= y.SIZE)
	{
		num = (ULLtype)x._bits[i] + (ULLtype)y._bits[i];
		if (z->_bits[i] + num > MAX_UINT) {
			z->_bits[i] += (UItype)(num - MAX_UINT);
			z->_bits[i + 1] += 1;
			i++;
		}
		else {
			z->_bits[i] += (UItype)num;
			i++;
		}
	}
	if (x.SIZE > y.SIZE) {
		add_BigNumber2(x, y, z);
	}
	else if (x.SIZE < y.SIZE) {
		add_BigNumber2(y, x, z);
	}
}

void add_BigNumber2(BigNumber x, BigNumber y, BigNumber *z) {
	ULLtype num;
	for (Itype i = y.SIZE + 1;i <= x.SIZE;i++) {
		num = z->_bits[i] + x._bits[i];
		if (num > MAX_UINT) {
			z->_bits[i] += num - MAX_UINT;
			z->_bits[i + 1] = 1;
		}
		else z->_bits[i] += num;
	}
}

BigNumber sub(BigNumber x, BigNumber y) {
	BigNumber z;
	z.base = x.base;
	LLtype num = 0;
	for (Itype i = 0; i < MAX_LEN; i++) z._bits[i] = 0;
	z.SIZE = BigNumberMaxSize(x, y);
	if (x._sign == y._sign) sub_BigNumber(x, y, &z);
	else add_BigNumber(x, y, &z);
	return z;
}

void sub_BigNumber(BigNumber x, BigNumber y, BigNumber *z) {
	z->_sign = x._sign * y._sign;
	Stype CompareResult = BigNumberÑompare(x, y);
	if (CompareResult == 2) {
		z->SIZE = 0;
		z->_bits[0] = 0;
		z->_sign = 1;
	}
	else if (CompareResult == 1) {
		z->_sign = x._sign;
		sub_BigNumber2(x, y, z);
	}
	else if (CompareResult == 0) {
		z->_sign = y._sign * -1;
		sub_BigNumber2(y, x, z);
	}
}

void sub_BigNumber2(BigNumber x, BigNumber y, BigNumber *z) {
	LLtype num = 0;
	Itype i = 0;
	while (i <= x.SIZE && i <= y.SIZE)
	{
		if (x._bits[i] < y._bits[i]) {
			z->_bits[i] += MAX_UINT + x._bits[i] - y._bits[i];
			z->_bits[i + 1] -= 1;
			i++;
		}
		else {
			z->_bits[i] += x._bits[i] - y._bits[i];
			i++;
		}
	}
	if (x.SIZE > y.SIZE) {
		for (Itype i = y.SIZE + 1;i <= x.SIZE;i++) {
			if (z->_bits[i] == MAX_UINT - 1 && x._bits[i] == 0) z->_bits[i + 1] -= 1;
			else z->_bits[i] += x._bits[i];
		}
	}
	else if (x.SIZE < y.SIZE) {
		for (Itype i = x.SIZE + 1;i <= y.SIZE;i++) {
			if (z->_bits[i] == MAX_UINT - 1 && y._bits[i] == 0) z->_bits[i + 1] -= 1;
			else z->_bits[i] += y._bits[i];
		}
	}
}

Itype BigNumberMaxSize(BigNumber x, BigNumber y) {
	if (x.SIZE > y.SIZE) return x.SIZE;
	else return y.SIZE;
}

Itype BigNumberÑompare(BigNumber x, BigNumber y) {
	if (x.SIZE > y.SIZE) return 1;
	else if (x.SIZE < y.SIZE) return 0;
	else
	{
		Itype i = x.SIZE;
		while (i>=0)
		{
			if (x._bits[i] > y._bits[i]) return 1;
			else if (x._bits[i] < y._bits[i]) return 0;
			i--;
		}
		return 2;
	}
}

void mulmns(BigNumber x, BigNumber y, BigNumber* z);

BigNumber mul(BigNumber x, BigNumber y) {
	BigNumber z;
	z.base = x.base;
	z._sign = x._sign * y._sign;
	for (Itype i = 0; i < MAX_LEN; i++) z._bits[i] = 0;
	z.SIZE = x.SIZE + y.SIZE;
	mulmns(x, y, &z);
	return z;
}

void mulmns(BigNumber x, BigNumber y, BigNumber* z) {
	Itype m = x.SIZE+1;
	Itype n = y.SIZE+1;
	ULLtype k, t, b;
	Itype i, j;
	for (j = 0; j < n; j++) {
		k = 0;
		for (i = 0; i < m; i++) {
			t = (ULLtype)x._bits[i] * (ULLtype)y._bits[j] + (ULLtype)z->_bits[i + j] + k;
			z->_bits[i + j] = (UItype)t;
			if (t > MAX_UINT) k = t >> 32;
			else k = 0;
		}
		z->_bits[j + m] = k;
	}
}