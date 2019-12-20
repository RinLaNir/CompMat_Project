/* File  BigNumber.c
Realization of BigNumber structure functions
Done by Avramenko Nikita  (group 2.1 comp math)
Date 20.12.2019 */


#define _CRT_SECURE_NO_WARNINGS
//max value of unsigned int
#define MAX_UINT 0x100000000
//max len of our lists
#define MAX_LEN 1024

//libraries and imported files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include <math.h>
#include <malloc.h>
#include "BigNumber.h"
#include "common.h"

//specify existing functions in advance to avoid error C2071
UItype Ñonvert(char* number, Itype base);
BigNumber add_num(BigNumber* x, LLtype l);
void mul_num(BigNumber* x, Itype l);
void change_size_plus(BigNumber* x);
void change_size_minus(BigNumber* x);
void NewBigNumber(BigNumber* x, Chtype str[MAX_LEN], Itype sytema_chislennya);
void CreateBigNumber(BigNumber* x, Itype num);
void mul_num_output(BigNumber* x, LLtype l);
BigNumber add_num_output(BigNumber* x, LLtype l);
void add_BigNumber(BigNumber x, BigNumber y, BigNumber *z);
void add_BigNumber2(BigNumber x, BigNumber y, BigNumber *z);
void sub_BigNumber(BigNumber x, BigNumber y, BigNumber *z);
void sub_BigNumber2(BigNumber x, BigNumber y, BigNumber *z);
int divmnu(BigNumber* q, BigNumber* r, const BigNumber x, const BigNumber y);
int nlz(unsigned x);
void mulmns(BigNumber x, BigNumber y, BigNumber* z);
void unadd_BigNumber(BigNumber *x, BigNumber y);
void unsub_BigNumber(BigNumber* x, BigNumber y);

//input BigNumber
void input(BigNumber *BN) {
	Chtype str[MAX_LEN];                                         
	Itype sytema_chislennya;
	Itype k = 0;												

	//input BigNumber base
	printf("Sytema chislennya: ");
	scanf("%d", &sytema_chislennya);
	if (sytema_chislennya != 2 && sytema_chislennya != 10 && sytema_chislennya != 16) {
		printf("Error input\n");
		exit(0);
	}
	BN->base = sytema_chislennya;

	//set BigNumber size
	for (Itype i = 0; i < MAX_LEN; i++) BN->_bits[i] = 0;
	printf("Number: ");
	getchar();
	gets_s(str, 1024);
	if (strlen(str) % 8 == 0) BN->SIZE = strlen(str) / 8 - 1;
	else BN->SIZE = strlen(str) / 8;
	//set BigNumber sign
	if (str[0] == '-') {
		BN->_sign = -1;
		strcpy(str, str + 1);
	}
	else BN->_sign = 1;
	
	//each time we take 8 characters because 16 is 2 ** 4 (32/4 = 8)
	if (sytema_chislennya == 16) {
		for (Itype i = strlen(str);i > 0;i -= 8)
		{
			BN->_bits[k] = Ñonvert(i > 8 ? str + i - 8 : str, BN->base);
			if (i > 8)str[i - 8] = '\0';
			k++;
		}
	}
	//for 2 we take 32 characters
	else if (sytema_chislennya == 2) {
		for (Itype i = strlen(str);i > 0;i -= 32)
		{
			BN->_bits[k] = Ñonvert(i > 32 ? str + i - 32 : str, BN->base);
			if (i > 32)str[i - 32] = '\0';
			k++;
		}
	}
	//we can give the decimal number system in the form a = b + 10*(b + 10*(b + 10*(....)))
	else if(sytema_chislennya == 10){
		Itype n;
		BN->SIZE = 0;
		for (Itype i = 0;i < strlen(str);i++) {
			change_size_plus(BN);
			n = (int)str[i] - (int)'0';
			mul_num(BN, 10);
			add_num(BN, n);
		}
		change_size_plus(BN);
	}
}

//input to the file same as output
Itype inputTextFile(Chtype* file, BigNumber* x, Itype sytema_chislennya) {
	Chtype bal;
	FILE *fl;
	fl = fopen(file, "w");
	//check the file exist
	if (fl == NULL)
	{
		printf("FILE ERROR");
		exit(0);
	}
	if (x->_sign == -1) fputs("-",fl);
	change_size_minus(x);
	if (x->base == 16) {
		fprintf(fl,"%x", x->_bits[x->SIZE]);
		for (Itype i = x->SIZE - 1;i >= 0;i--) fprintf(fl,"%08x", x->_bits[i]);
	}
	else if (x->base == 2) {
		Chtype st[MAX_LEN];
		fprintf(fl, "%s", ultoa(x->_bits[x->SIZE],st,2));
		for (Itype i = x->SIZE - 1;i >= 0;i--) fprintf(fl, "%08s", ultoa(x->_bits[i], st, 2));
	}
	else if (x->base == 10) {
		BigNumber BN;
		CreateBigNumber(&BN, 0);
		Itype n;
		BN.SIZE = 0;
		for (Itype i = x->SIZE;i >= 0;i--) {
			change_size_plus(&BN);
			mul_num_output(&BN, 4294967296);
			add_num_output(&BN, x->_bits[i]);
		}
		change_size_plus(&BN);
		fprintf(fl,"%u", BN._bits[x->SIZE]);
		for (Itype i = BN.SIZE - 1;i >= 0;i--) fprintf(fl,"%0*u", 8, BN._bits[i]);
	}
	printf("\n");
	fclose(fl);
}

//the same as input but to file
Itype outputTextFile(Chtype* file, BigNumber* x, Itype sytema_chislennya) {
	FILEtype *fl;
	fl = fopen(file, "r");
	if (fl == NULL)
	{
		printf("FILE ERROR");
		exit(0);
	}
	Itype i = 0;
	Itype cnt = 1;
	Chtype s[MAX_LEN];
	//looking for the end of a word or line
	do
	{
		s[i] = fgetc(fl);
		if (s[i] == ' ')    --cnt;
		++i;
	} while (cnt && s[i - 1] != EOF && i != BUFSIZ);
	s[i-1] = '\0';
	fclose(fl);
	NewBigNumber(x, s, sytema_chislennya);
}

//create new BigNumber by integer
void CreateBigNumber(BigNumber* x, Itype num) {
	for (Itype i = 0; i < MAX_LEN; i++) x->_bits[i] = 0;
	x->SIZE = 0;
	if (num >=0) x->_sign = 1;
	else x->_sign = -1;
	x->base = 0;
	x->_bits[0] = (UItype)num;
}

//create any BigNumber same as input
void NewBigNumber(BigNumber* x, Chtype m_str[MAX_LEN], Itype sytema_chislennya) {
	Itype k = 0;
	Chtype str[MAX_LEN];
	for (Itype i = 0; i < MAX_LEN; i++) str[i] = m_str[i];
	x->base = sytema_chislennya;
	for (Itype i = 0; i < MAX_LEN; i++) x->_bits[i] = 0;
	if (strlen(str) % 8 == 0) x->SIZE = strlen(str) / 8 - 1;
	else x->SIZE = strlen(str) / 8;
	if (str[0] == '-') {
		x->_sign = -1;
		strcpy(str, str + 1);
	}
	else x->_sign = 1;
	if (sytema_chislennya == 2 || sytema_chislennya == 16) {
		for (Itype i = strlen(str);i > 0;i -= 8) {
			x->_bits[k] = Ñonvert(i > 8 ? str + i - 8 : str, x->base);
			if (i > 8) str[i - 8] = '\0';
			k++;
		}
	}
	else if (sytema_chislennya == 10) {
		Itype n;
		x->SIZE = 0;
		for (Itype i = 0;i < strlen(str);i++) {
			change_size_plus(x);
			n = (int)str[i] - (int)'0';
			mul_num(x, 10);
			add_num(x, n);
		}
		change_size_plus(x);
	}
}

//output of BigNumber
void output(BigNumber x) {
	if (x._sign == -1) printf("-");
	change_size_minus(&x);
	if (x.base == 16) {
		printf("%x", x._bits[x.SIZE]);
		for (Itype i = x.SIZE - 1;i >= 0;i--) printf("%08x", x._bits[i]);
	}
	else if (x.base == 2) {
		Chtype st[MAX_LEN];
		printf("%s", ultoa(x._bits[x.SIZE], st, 2));
		for (Itype i = x.SIZE - 1;i >= 0;i--) printf("%08s", ultoa(x._bits[i], st, 2));
	}
	else if (x.base == 10) {
		BigNumber BN;
		CreateBigNumber(&BN, 0);
		Itype n;
		BN.SIZE = 0;
		for (Itype i = x.SIZE;i >= 0;i--) {
			change_size_plus(&BN);
			mul_num_output(&BN, 4294967296);
			add_num_output(&BN, x._bits[i]);
		}
		change_size_plus(&BN);
		printf("%u", BN._bits[BN.SIZE]);
		for (Itype i = BN.SIZE - 1;i >= 0;i--) printf("%0*u",8, BN._bits[i]);
	}
	printf("\n");
}

//special multiplication for output. We translate from the number 
//system 2 ** 32 to 10. The principle is the same as when entering a decimal number
void mul_num_output(BigNumber* x, LLtype l) {
	UItype MAX = 1000000000;
	Itype m = x->SIZE + 1;
	ULLtype k, t, b;
	Itype i;
	k = 0;
	for (i = 0; i < m; i++) {
		t = (ULLtype)x->_bits[i] * (ULLtype)l + k;
		x->_bits[i] = t%1000000000;
		if (t > MAX) k = t/1000000000;
		else k = 0;
	}
	x->_bits[m] = k;
}

//special add for output. differs only in the limit of the number in the cell
BigNumber add_num_output(BigNumber* x, LLtype l) {
	LLtype num = 0;
	UItype MAX = 1000000000;
	for (Itype i = 0;i <= x->SIZE;i++) {
		num = x->_bits[i] + l;
		if (num >= MAX) {
			x->_bits[i] = num%MAX;
			l = num/MAX;
		}
		else { x->_bits[i] = num; l = 0; }
	}
	if (l != 0) {
		int i = x->SIZE + 1;
		while (l != 0)
		{
			num = x->_bits[i] + l;
			if (num >= MAX) {
				x->_bits[i] = num%MAX;
				l = num/MAX;
			}
			else { x->_bits[i] = num; l = 0; }
			i++;
			x->SIZE++;
		}
	}
}

//increase size
void change_size_plus(BigNumber* x) {
	Itype i = x->SIZE+1;
	while (i<=1024)
	{
		if (x->_bits[i] != 0) {
			x->SIZE++; 
			i++;
		}
		else break;
	}
}

//remove unnecessary cells
void change_size_minus(BigNumber* x) {
	Itype i = x->SIZE;
	while (i > 0)
	{
		if (x->_bits[i] == 0) {
			x->SIZE--;
			i--;
		}
		else break;
	}
}

//convert decimal to base 16 or 2
UItype Ñonvert(char* number, Itype base) {
	UItype num = 0;
	Itype len = strlen(number)-1;
	//printf("len %d %s\n", len, number);
	if (base == 16) {
		for (Itype i = len; i >= 0; i--)
		{
			if (number[i] >= '0' && number[i] <= '9') num += ((Itype)number[i] - 48)*pow(base, len - i);
			else if (tolower(number[i]) >= 'a' && tolower(number[i]) <= 'f') num += ((Itype)tolower(number[i]) - 87)*pow(base, len - i);
			else {
				printf("Convert error %c %s\n", tolower(number[i]), number); 
				exit(0);
			}
		}
	}
	else if (base == 2) {
		for (Itype i = len; i >= 0; i--)
		{
			if (number[i] >= '0' && number[i] <= '1') num += ((Itype)number[i] - 48)*pow(base, len - i);
			else {
				printf("Convert error %c %s\n", tolower(number[i]), number);
				exit(0);
			}
		}
	}
	return num;
}

//product of two BigNumbers
BigNumber add(const BigNumber x, const BigNumber y) {
	BigNumber z;
	z.base = x.base;
	for (Itype i = 0; i < MAX_LEN; i++) z._bits[i] = 0;
	z.SIZE = BigNumberMaxSize(x, y);
	//check sign of two numbers
	if (x._sign == y._sign) add_BigNumber(x, y, &z);
	else sub_BigNumber(x, y, &z);
	change_size_plus(&z);
	return z;
}

//add BigNum to iteger
BigNumber add_num(BigNumber* x, LLtype l) {
	LLtype num = 0;
	//the same as in the column
	for (Itype i = 0;i <= x->SIZE;i++) {
		num = x->_bits[i] + l;
		if (num >= MAX_UINT) {
			x->_bits[i] = num - MAX_UINT;
			l = 1;
		}
		else { x->_bits[i] = num; l = 0; }
	}
	if (l != 0) {
		int i = x->SIZE+1;
		while (l!=0)
		{
			num = x->_bits[i] + l;
			if (num >= MAX_UINT) {
				x->_bits[i] = num - MAX_UINT;
				l = 1;
			}
			else { x->_bits[i] = num; l = 0; }
			i++;
			x->SIZE++;
		}
	}
}


//main function of additional
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

//helper function
//if the size of one number is bigger after another
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

//difference of two Bignumbers
BigNumber sub(BigNumber x, BigNumber y) {
	BigNumber z;
	z.base = x.base;
	LLtype num = 0;
	for (Itype i = 0; i < MAX_LEN; i++) z._bits[i] = 0;
	z.SIZE = BigNumberMaxSize(x, y);
	//check sign of two numbers
	if (x._sign == y._sign) sub_BigNumber(x, y, &z);
	else add_BigNumber(x, y, &z);
	return z;
}


//check size of two numbers
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

//main function of sub
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
}

//BigNumber size
Itype BigNumberMaxSize(BigNumber x, BigNumber y) {
	if (x.SIZE > y.SIZE) return x.SIZE;
	else return y.SIZE;
}

//compare two BigNumbers
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

//multiplication of two BigNumbers
BigNumber mul(BigNumber x, BigNumber y) {
	BigNumber z;
	z.base = x.base;
	z._sign = x._sign * y._sign;
	for (Itype i = 0; i < MAX_LEN; i++) z._bits[i] = 0;
	z.SIZE = x.SIZE + y.SIZE;
	mulmns(x, y, &z);
	//chage size after act
	change_size_plus(&z);
	return z;
}

//multiplication of BigNumbers and integer
void mul_num(BigNumber* x, Itype l) {
	Itype m = x->SIZE + 1;
	ULLtype k, t, b;
	Itype i;
	k = 0;
	for (i = 0; i < m; i++) {
		t = (ULLtype)x->_bits[i] * (ULLtype)l + k;
		x->_bits[i] = (UItype)t;
		if (t > MAX_UINT) k = t >> 32;
		else k = 0;
	}
	x->_bits[m] = k;
}

//main function of multiplication
//the same as collumn
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

BigNumber Div_num(BigNumber x, Itype num) {
	BigNumber y, q, r;
	CreateBigNumber(&y, num);
	q.base = x.base;
	q._sign = x._sign * y._sign;
	for (Itype i = 0; i < MAX_LEN; i++) q._bits[i] = 0;
	q.SIZE = BigNumberMaxSize(x, y);
	r.base = x.base;
	r._sign = x._sign * y._sign;
	for (Itype i = 0; i < MAX_LEN; i++) r._bits[i] = 0;
	r.SIZE = BigNumberMaxSize(x, y);
	divmnu(&q, &r, x, y);
	return q;
}

//division of two BigNumbers
BigNumber Div(BigNumber x, BigNumber y) {
	BigNumber q;
	q.base = x.base;
	q._sign = x._sign * y._sign;
	for (Itype i = 0; i < MAX_LEN; i++) q._bits[i] = 0;
	q.SIZE = BigNumberMaxSize(x, y);
	BigNumber r;
	r.base = x.base;
	r._sign = x._sign * y._sign;
	for (Itype i = 0; i < MAX_LEN; i++) r._bits[i] = 0;
	r.SIZE = BigNumberMaxSize(x, y);
	divmnu(&q, &r, x, y);
	change_size_minus(&q);
	return q;
}

//modulus of two BigNumbers
BigNumber mod(BigNumber x, BigNumber y) {
	BigNumber q;
	q.base = x.base;
	q._sign = x._sign * y._sign;
	for (Itype i = 0; i < MAX_LEN; i++) q._bits[i] = 0;
	q.SIZE = BigNumberMaxSize(x, y);
	BigNumber r;
	r.base = x.base;
	r._sign = x._sign * y._sign;
	for (Itype i = 0; i < MAX_LEN; i++) r._bits[i] = 0;
	r.SIZE = BigNumberMaxSize(x, y);
	divmnu(&q, &r, x, y);
	return r;
}

// Normalized form of x
//Number of rigth zero
int nlz(unsigned x) {
	int n;

	if (x == 0) return(32);
	n = 0;
	if (x <= 0x0000FFFF) { n = n + 16; x = x << 16; }
	if (x <= 0x00FFFFFF) { n = n + 8; x = x << 8; }
	if (x <= 0x0FFFFFFF) { n = n + 4; x = x << 4; }
	if (x <= 0x3FFFFFFF) { n = n + 2; x = x << 2; }
	if (x <= 0x7FFFFFFF) { n = n + 1; }
	return n;
}

int divmnu(BigNumber* q, BigNumber* r, const BigNumber x, const BigNumber y) {

	Itype m = x.SIZE + 1;
	Itype n = y.SIZE + 1;
	const ULLtype b = 4294967296LL; // Number base (2**32).
	UItype *un, *vn;                         // Normalized form of u, v.
	ULLtype qhat;                   // Estimated quotient digit.
	ULLtype rhat;                   // A remainder.
	ULLtype p;                      // Product of two digits.
	LLtype t, k;
	Itype s, i, j;

	if (m < n || n <= 0 || y._bits[n - 1] == 0)
		return 1;                         // Return if invalid param.

	if (n == 1) {                        // Take care of
		k = 0;                            // the case of a
		for (j = m - 1; j >= 0; j--) {    // single-digit
			q->_bits[j] = (k*b + x._bits[j]) / y._bits[0];      // divisor here.
			k = (k*b + x._bits[j]) - q->_bits[j] * y._bits[0];
		}
		if (r != NULL) r->_bits[0] = k;
		return 0;
	}

	/* Normalize by shifting v left just enough so that its high-order
	bit is on, and shift u left the same amount. We may have to append a
	high-order digit on the dividend; we do that unconditionally. */

	s = nlz(y._bits[n - 1]);             // 0 <= s <= 31.
	vn = (UItype *)alloca(4 * n);
	for (i = n - 1; i > 0; i--)
		vn[i] = (y._bits[i] << s) | ((ULLtype)y._bits[i - 1] >> (32 - s));
	vn[0] = y._bits[0] << s;

	un = (UItype *)alloca(4 * (m + 1));
	un[m] = (ULLtype)x._bits[m - 1] >> (32 - s);
	for (i = m - 1; i > 0; i--)
		un[i] = (x._bits[i] << s) | ((ULLtype)x._bits[i - 1] >> (32 - s));
	un[0] = x._bits[0] << s;

	for (j = m - n; j >= 0; j--) {       // Main loop.
										 // Compute estimate qhat of q[j].
		qhat = (un[j + n] * b + un[j + n - 1]) / vn[n - 1];
		rhat = (un[j + n] * b + un[j + n - 1]) - qhat*vn[n - 1];
	again:
		if (qhat >= b || qhat*vn[n - 2] > b*rhat + un[j + n - 2])
		{
			qhat = qhat - 1;
			rhat = rhat + vn[n - 1];
			if (rhat < b) goto again;
		}

		// Multiply and subtract.
		k = 0;
		for (i = 0; i < n; i++) {
			p = qhat*vn[i];
			t = un[i + j] - k - (p & 0xFFFFFFFFLL);
			un[i + j] = t;
			k = (p >> 32) - (t >> 32);
		}
		t = un[j + n] - k;
		un[j + n] = t;

		q->_bits[j] = qhat;              // Store quotient digit.
		if (t < 0) {              // If we subtracted too
			q->_bits[j] = q->_bits[j] - 1;       // much, add back.
			k = 0;
			for (i = 0; i < n; i++) {
				t = (ULLtype)un[i + j] + vn[i] + k;
				un[i + j] = t;
				k = t >> 32;
			}
			un[j + n] = un[j + n] + k;
		}
	} // End j.
	  // If the caller wants the remainder, unnormalize
	  // it and pass it back.
	if (r != NULL) {
		for (i = 0; i < n - 1; i++)
			r->_bits[i] = (un[i] >> s) | ((unsigned long long)un[i + 1] << (32 - s));
		r->_bits[n - 1] = un[n - 1] >> s;
	}
	return 0;
}


//gcs of two BigNumbers
BigNumber gcd(BigNumber a, BigNumber b) {
	BigNumber t;
	CreateBigNumber(&t, 0);
	//euclidean algorithm
	while (b.SIZE != 0 || b._bits[0]!=0) {
		t.SIZE = b.SIZE;
		t._sign = b._sign;
		for (Itype i = 0; i <= t.SIZE; i++) t._bits[i] = b._bits[i];
		b = mod(a,b);
		a.SIZE = t.SIZE;
		a._sign = t._sign;
		for (Itype i = 0; i <= a.SIZE; i++) a._bits[i] = t._bits[i];
		a = t;
		change_size_minus(&b);
	}
	return a;
}

//lcm of two BigNumbers
BigNumber lcm(BigNumber x, BigNumber y) {
	//lcm(a,b) = (a*b) / gcd(a,b)
	BigNumber MUL, GCD, BN;
	CreateBigNumber(&MUL, 0);
	CreateBigNumber(&GCD, 0);
	CreateBigNumber(&BN, 0);
	MUL = mul(x, y);
	change_size_plus(&MUL);
	if (BigNumberÑompare(x,y) == 0) GCD = gcd(y, x);
	else GCD = gcd(x, y);
	change_size_plus(&GCD);
	BN = Div(MUL, GCD);
	change_size_plus(&GCD);
	return BN;
}

//unary add
Itype unadd(BigNumber* x, const BigNumber y) {
	//check sign
	if (x->_sign == y._sign) unadd_BigNumber(x, y);
	else unsub_BigNumber(x, y);
	change_size_plus(x);
}

//main unary add
void unadd_BigNumber(BigNumber *x, BigNumber y) {
	ULLtype num = 0;
	Itype i = 0;
	while (i <= x->SIZE && i <= y.SIZE)
	{
		num = (ULLtype)x->_bits[i] + (ULLtype)y._bits[i];
		if (num > MAX_UINT) {
			x->_bits[i] = (UItype)(num - MAX_UINT);
			x->_bits[i + 1] += 1;
			i++;
		}
		else {
			x->_bits[i] += y._bits[i];
			i++;
		}
	}
	if (x->SIZE < y.SIZE) {
		ULLtype num;
		for (Itype i = x->SIZE + 1;i <= y.SIZE;i++) {
			num = x->_bits[i] + y._bits[i];
			if (num > MAX_UINT) {
				x->_bits[i] = num - MAX_UINT;
				x->_bits[i + 1] = 1;
			}
			else x->_bits[i] += y._bits[i];
		}
	}
}

//unary sub
Itype unsub(BigNumber* x, const BigNumber y) {
	if (x->_sign == y._sign) unsub_BigNumber(x, y);
	else unadd_BigNumber(x, y);
}

//main unary add
void unsub_BigNumber(BigNumber* x, BigNumber y) {
	Stype CompareResult = BigNumberÑompare(*x, y);
	LLtype num = 0;
	Itype i = 0;
	if (CompareResult == 2) {
		x->SIZE = 0;
		x->_bits[0] = 0;
		x->_sign = 1;
	}
	else if (CompareResult == 1) {
		while (i <= x->SIZE && i <= y.SIZE)
		{
			if (x->_bits[i] < y._bits[i]) {
				x->_bits[i] = MAX_UINT + x->_bits[i] - y._bits[i];
				x->_bits[i + 1] -= 1;
				i++;
			}
			else {
				x->_bits[i] -= y._bits[i];
				i++;
			}
		}
		if (x->SIZE > y.SIZE) {
			for (Itype i = y.SIZE + 1;i <= x->SIZE;i++) {
				if (x->_bits[i] == MAX_UINT - 1) { x->_bits[i + 1] -= 1; x->_bits[i] = 0; }
			}
		}
	}
	else if (CompareResult == 0) {
		x->_sign = x->_sign * -1;
		while (i <= x->SIZE && i <= y.SIZE)
		{
			if (x->_bits[i] > y._bits[i]) {
				x->_bits[i] = MAX_UINT + y._bits[i] - x->_bits[i];
				x->_bits[i + 1] -= 1;
				i++;
			}
			else {
				x->_bits[i] = y._bits[i] - x->_bits[i];
				i++;
			}
		}
		if (y.SIZE > x->SIZE) {
			for (Itype i = x->SIZE + 1;i <= y.SIZE;i++) {
				x->_bits[i] += y._bits[i];
			}
		}
	}
}
