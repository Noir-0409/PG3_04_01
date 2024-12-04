#include <stdio.h>
#include "Pokemon.h"

int main() {

	Pokemon a(114);

	Pokemon b = a;

	printf("%d\n", a);

	printf("%d\n", b);

	return 0;

}