#include <stdio.h>
#include <string.h>
#include "BigNumber.h"
#include <stdlib.h>

#define MAX_LEN 1024

BigNumber input() {
	BigNumber *BN;
	char str[MAX_LEN];
	int sytema_chislennya;
	int k = 0;

	printf("sytema_chislennya: ");
	scanf("%d", &sytema_chislennya);

	BN->SIZE = strlen(str)/4;
	unsigned int lst[MAX_LEN];
	BN->_bits = *lst;
	printf("Number: ");
	gets_s(str, 1024);
	for (size_t i = strlen(str);i > 0;i -= 4)
	{
		BN->_bits[k] = atoi(i > 4 ? str + i - 4 : str);
		str[i - 4] = '\0';
		k++;
	}
	return *BN;
}

void output(BigNumber x) {
	char m_str[MAX_LEN];
	char str[MAX_LEN];
	for (int i = x.SIZE - 1;i >= 0;i--) {
		itoa(x._bits[i], str, 16);
		strcat(m_str, str);
	}
	printf("%s", m_str);
}