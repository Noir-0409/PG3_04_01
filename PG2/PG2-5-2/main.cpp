#include <stdio.h>

int main(void) {

	FILE* fp;

	char fname[] = "test.txt";

	int err;

	err = fopen_s(&fp, fname, "r");

	char str[32] = {};

	if (err != 0) {

		printf("%s file not open!\n", fname);

		return err;

	} else {

		printf("%s file opend!\n", fname);

		fscanf_s(fp, "%s", &str, sizeof(str));

		printf("“Ç‚İ‚ñ‚¾•¶š‚Í%s‚Å‚·\n", str);

	}

	fclose(fp);

	return 0;

}