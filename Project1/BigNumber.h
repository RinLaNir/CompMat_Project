#pragma once

#define BASE_VAL 0xffffffff+1

typedef struct BigNumber {
	static const long long BASE = BASE_VAL + 1;
	static size_t SIZE;

	int _sign;
	unsigned int _bits[];
} BigNumber;