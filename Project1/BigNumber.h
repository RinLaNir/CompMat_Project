#pragma once

#define MAX_UINT 0xffffffff

typedef struct BigNumber {
	size_t SIZE;
	int base;
	int _sign;
	unsigned int *_bits;
} BigNumber;

extern BigNumber input();
extern void output(BigNumber x);
/*extern BigNumber add(BigNumber x, BigNumber y);
extern BigNumber sub(BigNumber x, BigNumber y);
extern BigNumber mul(BigNumber x, BigNumber y);
extern BigNumber div(BigNumber x, BigNumber y);
extern BigNumber mod(BigNumber x, BigNumber y);
extern BigNumber unadd(BigNumber x, BigNumber y);
extern BigNumber unsub(BigNumber x, BigNumber y);*/