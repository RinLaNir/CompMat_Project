#pragma once

/* File  BigNumber.h
Realization of BigNumber structure and list for it`s functions
Done by Avramenko Nikita  (group 2.1 comp math)
Date 20.12.2019 */

/* define for the BigNumber */
#define MAX_UItype 0x100000000
#define MAX_LEN 1024

/* changed types */
#include "common.h"

/* Base structure of BigNumber */
typedef struct BigNumber {
	S_Ttype SIZE;
	Itype base;
	Itype _sign;
	UItype _bits[1024];
} BigNumber;


/* functions for the BigNumber */
extern void input(BigNumber *x);
extern void output(BigNumber x);
extern Itype inputTextFile(Chtype* file, BigNumber* x, Itype sytema_chislennya);
extern Itype outputTextFile(Chtype* file, BigNumber* x, Itype sytema_chislennya);
extern BigNumber add(BigNumber x, BigNumber y);
extern BigNumber sub(BigNumber x, BigNumber y);
extern BigNumber mul(BigNumber x, BigNumber y);
extern void mul_num(BigNumber* x, Itype l);
extern BigNumber Div(BigNumber x, BigNumber y);
extern BigNumber Div_num(BigNumber x, Itype y);
extern BigNumber gcd(BigNumber x, BigNumber y);
extern BigNumber lcm(BigNumber x, BigNumber y);
extern BigNumber mod(BigNumber x, BigNumber y);
extern Itype unadd(BigNumber* x, const BigNumber y);
extern Itype unsub(BigNumber* x, const BigNumber y);
extern void NewBigNumber(BigNumber* x, Chtype str[MAX_LEN], Itype sytema_chislennya);
extern Itype BigNumber—ompare(BigNumber x, BigNumber y);