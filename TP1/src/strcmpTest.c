#include <stdio.h>

int strcmp(char* a, char* b);

int main(int argc, char* argv[]) {
	char a1[10] = "aaa";
	char b1[10] = "bbb";
	printf("strcmp(%s, %s) = %d\n", a1, b1, strcmp(a1, b1));
	
	char a2[10] = "bbb";
	char b2[10] = "aaa";
	printf("strcmp(%s, %s) = %d\n", a2, b2, strcmp(a2, b2));
	
	char a3[10] = "aaa";
	char b3[10] = "aaa";
	printf("strcmp(%s, %s) = %d\n", a3, b3, strcmp(a3, b3));
	
	char a4[10] = "aaaaa";
	char b4[10] = "aaaab";
	printf("strcmp(%s, %s) = %d\n", a4, b4, strcmp(a4, b4));
	
	char a5[10] = "a";
	char b5[10] = "b";
	printf("strcmp(%s, %s) = %d\n", a5, b5, strcmp(a5, b5));
	
	char a6[10] = "";
	char b6[10] = "";
	printf("strcmp(%s, %s) = %d\n", a6, b6, strcmp(a6, b6));
	
	char a7[10] = "";
	char b7[10] = "b";
	printf("strcmp(%s, %s) = %d\n", a7, b7, strcmp(a7, b7));
	
	char a8[10] = "a";
	char b8[10] = "";
	printf("strcmp(%s, %s) = %d\n", a8, b8, strcmp(a8, b8));
	
	return 0;
}
