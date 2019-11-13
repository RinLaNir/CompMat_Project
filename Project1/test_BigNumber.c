#include <stdio.h>
#include <string.h>

int main() {
	char *lst;
	gets_s(lst, 100);
	printf("%d", sizeof(lst));
}