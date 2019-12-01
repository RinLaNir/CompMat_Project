#pragma once

#define MAX_UINT 0x100000000

#include "common.h"

typedef struct BigNumber {
	S_Ttype SIZE;
	Itype base;
	Itype _sign;
	UItype _bits[1024];
} BigNumber;

extern void input(BigNumber *x);
extern void output(BigNumber x);
extern BigNumber add(BigNumber x, BigNumber y);
extern BigNumber sub(BigNumber x, BigNumber y);
/*extern BigNumber mul(BigNumber x, BigNumber y);
extern BigNumber div(BigNumber x, BigNumber y);
extern BigNumber mod(BigNumber x, BigNumber y);
extern BigNumber unadd(BigNumber x, BigNumber y);
extern BigNumber unsub(BigNumber x, BigNumber y);*/