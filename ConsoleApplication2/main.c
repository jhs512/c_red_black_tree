/*
TODO LIST
- 입력폼
*/

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

int inputCommand() {
	char command[21];
	fgets(command, sizeof command, stdin);

	for (int i = 0; true; i++) {
		if (command[i] == NULL && i > 0) {
			command[i - 1] = NULL;
			break;
		}
	}

	return atoi(command);
}

void actionInsertNode() {
	printf("== 노드입력 ==\n");

	printf("숫자 : ");
	int num = inputCommand();
	printf("입력할 숫자 : %d\n", num);
}

int main() {
	while (true) {
		printf("== 명령어 리스트 ==\n");
		printf("1 : 노드출력\n");
		printf("2 : 노드추가\n");
		printf("3 : 노드삭제\n");
		printf("4 : 노드검색\n");

		printf("명령어) ");
		int commandNum = inputCommand();

		switch (commandNum) {
		case 1:
			
			break;
		case 2:
			actionInsertNode();
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			printf("존재하지 않는 명령어 입니다.\n");
			break;
		}
	}

	return 0;
}

