#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {

	printf("変数str(VisualStudio)の文字列の長さを取得する\n");

	char str[30] = "VisualStudio";

	int len;

	len = strlen(str);

	printf("長さ=%d\n", len);

	int islower;

	int c;

	printf("変数str(VisualStudio)の文字列の先頭を小文字に変更する\n");

	c = getchar();

	printf("返還後=%d\n", c);

	return 0;

}