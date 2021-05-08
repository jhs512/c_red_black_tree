/*
TODO LIST
- 입력폼
*/

#include <stdio.h>
#define true 1
#define false 0

int main() {
	char command[21];

	while (true) {
		printf("명령어) ");
		scanf_s("%s", command, sizeof(command));

		printf("%s\n", command);
	}
	return 0;
}

