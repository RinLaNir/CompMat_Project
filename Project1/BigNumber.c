#include <stdio.h>
#include <string.h>
#include "BigNumber.h"

#define MAX_LEN 1024

BigNumber input() {
	BigNumber *BN;
	char str[MAX_LEN];
	int sytema_chislennya;

	printf("sytema_chislennya: ");
	scanf("%d", &sytema_chislennya);

	BN->SIZE = strlen(str)/4;
	unsigned int lst[MAX_LEN];
	BN->_bits = *lst;
	printf("Number: ");
	gets_s(str, 1024);
	return *BN;
}