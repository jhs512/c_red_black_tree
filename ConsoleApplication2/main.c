/*
TODO LIST
- �Է���
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
	printf("== ����Է� ==\n");

	printf("���� : ");
	int num = inputCommand();
	printf("�Է��� ���� : %d\n", num);
}

int main() {
	while (true) {
		printf("== ��ɾ� ����Ʈ ==\n");
		printf("1 : ������\n");
		printf("2 : ����߰�\n");
		printf("3 : ������\n");
		printf("4 : ���˻�\n");

		printf("��ɾ�) ");
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
			printf("�������� �ʴ� ��ɾ� �Դϴ�.\n");
			break;
		}
	}

	return 0;
}

