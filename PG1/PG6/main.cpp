#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main() {
	unsigned int currenTime = time(nullptr);
	srand(currenTime);

	int num = 0;
	
	while(num<10) {

		int dice = rand();

		printf("%d回目に振ったサイコロの値：%d\n",num+1, dice%6+1);
		
		num++;
	}

	return 0;
}