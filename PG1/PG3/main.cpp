#include <stdio.h>
int main() {
	int number = 0;

	scanf_s("%d", &number);

	if (number > 50) {
		printf("“ü—Í‚µ‚½’l‚Í50‚æ‚è‘å‚«‚¢", number);
	}

	else if (number < 50) {
		printf("“ü—Í‚µ‚½’l‚Í50‚æ‚è¬‚³‚¢",number);

	}

	else  {
		printf("“ü—Í‚µ‚½’l‚Í50", number);
	}
	return 0;
}