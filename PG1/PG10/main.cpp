#include <stdio.h>

int main(){

	char str[7] = { 's','t','r','i','n','g','\0' };



	for (int i = 0; i < 6; i++) {
		printf("%c\n", str[i]);
	}

	return 0;

}