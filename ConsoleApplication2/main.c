/*
TODO LIST
- 입력폼
*/

#include <stdio.h>
#include<ctype.h>
#include<string.h>

#define true 1
#define false 0

char command[21];

void inputCommand() {
	printf("명령어) ");
	fgets(command, sizeof command, stdin);

	for (int i = 0; true; i++) {
		if (command[i] == NULL && i > 0) {
			command[i - 1] = NULL;
			break;
		}
	}
}

int main() {
	while (true) {
		printf("== 명령어 리스트 ==\n");
		printf("1 : 노드출력\n");
		printf("2 : 노드추가\n");
		printf("3 : 노드삭제\n");
		printf("4 : 노드검색\n");

		inputCommand();

		printf("%s\n", command);
	}
	return 0;
}

