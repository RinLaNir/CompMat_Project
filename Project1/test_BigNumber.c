/* File  test_BigNumber.c
Realization of tests for BigNumber structure functions
Done by Avramenko Nikita(group 2.1 comp math)
Date 20.12.2019 */


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "BigNumber.h"
#include <stdlib.h>

void test_1() {
	printf("Test function add:\n");
	Itype CompareNumber;
	BigNumber x, y, z, res;
	NewBigNumber(&x, "1", 10);
	NewBigNumber(&y, "1", 10);
	NewBigNumber(&res, "2", 10);
	z = add(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("1 test passed\n");
	else printf("1 test failed\n");
	NewBigNumber(&x, "FFFFFFFF", 16);
	NewBigNumber(&y, "F", 16);
	NewBigNumber(&res, "10000000E", 16);
	z = add(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("2 test passed\n");
	else printf("2 test failed\n");
	NewBigNumber(&x, "1243423534523345364535345", 10);
	NewBigNumber(&y, "3423543636342322113543", 10);
	NewBigNumber(&res, "1246847078159687686648888", 10);
	z = add(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("3 test passed\n");
	else printf("3 test failed\n");
	NewBigNumber(&x, "-14", 10);
	NewBigNumber(&y, "20", 10);
	NewBigNumber(&res, "6", 10);
	z = add(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("4 test passed\n");
	else printf("4 test failed\n");
	printf("\n");
}

void test_2() {
	printf("Test function sub:\n");
	Itype CompareNumber;
	BigNumber x, y, z, res;
	NewBigNumber(&x, "1", 10);
	NewBigNumber(&y, "1", 10);
	NewBigNumber(&res, "0", 10);
	z = sub(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("1 test passed\n");
	else printf("1 test failed\n");
	NewBigNumber(&x, "FFFFFFFF", 16);
	NewBigNumber(&y, "F", 16);
	NewBigNumber(&res, "FFFFFFF0", 16);
	z = sub(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("2 test passed\n");
	else printf("2 test failed\n");
	NewBigNumber(&x, "1243423534523345364535345", 10);
	NewBigNumber(&y, "3423543636342322113543", 10);
	NewBigNumber(&res, "1239999990887003042421802", 10);
	z = sub(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("3 test passed\n");
	else printf("3 test failed\n");
	NewBigNumber(&x, "-14", 10);
	NewBigNumber(&y, "20", 10);
	NewBigNumber(&res, "-34", 10);
	z = sub(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("4 test passed\n");
	else printf("4 test failed\n");
	printf("\n");
}

void test_3() {
	printf("Test function mul:\n");
	Itype CompareNumber;
	BigNumber x, y, z, res;
	NewBigNumber(&x, "1", 10);
	NewBigNumber(&y, "1", 10);
	NewBigNumber(&res, "1", 10);
	z = mul(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("1 test passed\n");
	else printf("1 test failed\n");
	NewBigNumber(&x, "FFFFFFFF", 16);
	NewBigNumber(&y, "F", 16);
	NewBigNumber(&res, "EFFFFFFF1", 16);
	z = mul(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("2 test passed\n");
	else printf("2 test failed\n");
	NewBigNumber(&x, "1243423534523345364535345", 10);
	NewBigNumber(&y, "3423543636342322113543", 10);
	NewBigNumber(&res, "4256914728895676688552219484077091096526677335", 10);
	z = mul(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("3 test passed\n");
	else printf("3 test failed\n");
	NewBigNumber(&x, "-14", 10);
	NewBigNumber(&y, "20", 10);
	NewBigNumber(&res, "-280", 10);
	z = mul(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("4 test passed\n");
	else printf("4 test failed\n");
	printf("\n");
}

void test_4() {
	printf("Test function div:\n");
	Itype CompareNumber;
	BigNumber x, y, z, res;
	NewBigNumber(&x, "1", 10);
	NewBigNumber(&y, "1", 10);
	NewBigNumber(&res, "1", 10);
	z = Div(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("1 test passed\n");
	else printf("1 test failed\n");
	NewBigNumber(&x, "FFFFFFFF", 16);
	NewBigNumber(&y, "F", 16);
	NewBigNumber(&res, "11111111", 16);
	z = Div(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("2 test passed\n");
	else printf("2 test failed\n");
	NewBigNumber(&x, "1243423534523345364535345", 10);
	NewBigNumber(&y, "3423543636342322113543", 10);
	NewBigNumber(&res, "363", 10);
	z = Div(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("3 test passed\n");
	else printf("3 test failed\n");
	NewBigNumber(&x, "-14", 10);
	NewBigNumber(&y, "20", 10);
	NewBigNumber(&res, "0", 10);
	z = Div(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("4 test passed\n");
	else printf("4 test failed\n");
	printf("\n");
}

void test_5() {
	printf("Test function mod:\n");
	Itype CompareNumber;
	BigNumber x, y, z, res;
	NewBigNumber(&x, "1", 10);
	NewBigNumber(&y, "1", 10);
	NewBigNumber(&res, "0", 10);
	z = mod(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("1 test passed\n");
	else printf("1 test failed\n");
	NewBigNumber(&x, "FFFFFFFF", 16);
	NewBigNumber(&y, "F", 16);
	NewBigNumber(&res, "0", 16);
	z = mod(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("2 test passed\n");
	else printf("2 test failed\n");
	NewBigNumber(&x, "1243423534523345364535345", 10);
	NewBigNumber(&y, "3423543636342322113543", 10);
	NewBigNumber(&res, "677194531082437319236", 10);
	z = mod(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("3 test passed\n");
	else printf("3 test failed\n");
	NewBigNumber(&x, "-14", 10);
	NewBigNumber(&y, "20", 10);
	NewBigNumber(&res, "14", 10);
	z = mod(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("4 test passed\n");
	else printf("4 test failed\n");
	printf("\n");
}

void test_6() {
	printf("Test function input and output file:\n");
	BigNumber x,y;
	NewBigNumber(&x, "1111111", 10);
	inputTextFile("test_file.txt", &x, 10);
	outputTextFile("test_file.txt", &y, 10);
	Itype CompareNumber = BigNumber—ompare(x, y);
	if (CompareNumber == 2) printf("1 test passed\n");
	else printf("1 test failed\n");
	printf("\n");
}

void test_7() {
	printf("Test function gcd:\n");
	Itype CompareNumber;
	BigNumber x, y, z, res;
	NewBigNumber(&x, "4", 10);
	NewBigNumber(&y, "3", 10);
	NewBigNumber(&res, "1", 10);
	z = gcd(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("1 test passed\n");
	else printf("1 test failed\n");
	NewBigNumber(&x, "FFFFFFFF", 16);
	NewBigNumber(&y, "F", 16);
	NewBigNumber(&res, "F", 16);
	z = gcd(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("2 test passed\n");
	else printf("2 test failed\n");
	NewBigNumber(&x, "23436124565465534", 10);
	NewBigNumber(&y, "32432", 10);
	NewBigNumber(&res, "2", 10);
	z = gcd(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("3 test passed\n");
	else printf("3 test failed\n");
	printf("\n");
}

void test_8() {
	printf("Test function lcm:\n");
	Itype CompareNumber;
	BigNumber x, y, z, res;
	NewBigNumber(&x, "4", 10);
	NewBigNumber(&y, "3", 10);
	NewBigNumber(&res, "12", 10);
	z = lcm(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("1 test passed\n");
	else printf("1 test failed\n");
	NewBigNumber(&x, "FFFFFFFF", 16);
	NewBigNumber(&y, "F", 16);
	NewBigNumber(&res, "FFFFFFFF", 16);
	z = lcm(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("2 test passed\n");
	else printf("2 test failed\n");
	NewBigNumber(&x, "23436124565465534", 10);
	NewBigNumber(&y, "32432", 10);
	NewBigNumber(&res, "380040195953589099344", 10);
	z = lcm(x, y);
	CompareNumber = BigNumber—ompare(z, res);
	if (CompareNumber == 2) printf("3 test passed\n");
	else printf("3 test failed\n");
	printf("\n");
}

int main() {
	BigNumber x;
	input(&x);
	output(x);
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();
	test_6();
	test_7();
	test_8();
}