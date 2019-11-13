#include <stdio.h>
#include <string.h>
#include <BigNumber.h>

void test_1() {
	char lst[100];
	gets_s(lst, 100);
	for (int i = strlen(lst);i > 0;i -= 4) {
		printf("%s ", i > 4 ? lst + i - 4 : lst);
		lst[i-4] = '\0';
	}
}

void test_2() {
	
}

int main() {
	test_1();
}