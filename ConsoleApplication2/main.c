/*
TODO LIST
- �Է���
*/

#include <stdio.h>
#include<ctype.h>
#include<string.h>

#define true 1
#define false 0

char command[21];

void inputCommand() {
	printf("��ɾ�) ");
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
		printf("== ��ɾ� ����Ʈ ==\n");
		printf("1 : ������\n");
		printf("2 : ����߰�\n");
		printf("3 : ������\n");
		printf("4 : ���˻�\n");

		inputCommand();

		printf("%s\n", command);
	}
	return 0;
}

