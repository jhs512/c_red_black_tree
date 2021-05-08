/*
TODO LIST
- 입력폼
*/

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

// RBT 관련 시작
typedef int RBT__ElementType;

typedef struct _RBT__Node
{
	struct _RBT__Node* parent;
	struct _RBT__Node* left;
	struct _RBT__Node* right;
	enum { RED, BLACK } color;
	RBT__ElementType data;
} RBT__Node;

// 루트노드
RBT__Node* rootNode = NULL;

RBT__Node* RBT__createNode(RBT__ElementType data) {
	RBT__Node* node = malloc(sizeof(RBT__Node));

	if (node == NULL) {
		return NULL;
	}

	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->color = RED;
	node->data = data;

	return node;
}

void RBT__addChildNode(RBT__Node* parentNode, RBT__Node* node) {
	if (parentNode->data > node->data) {
		if (parentNode->left == NULL) {
			node->parent = parentNode;
			parentNode->left = node;
		}
		else {
			RBT__addChildNode(parentNode->left, node);
		}
	}
	else {
		if (parentNode->right == NULL) {
			node->parent = parentNode;
			parentNode->right = node;
		}
		else {
			RBT__addChildNode(parentNode->right, node);
		}
	}
}

RBT__Node* RBT__insertNode(RBT__Node* node) {
	if (rootNode == NULL) {
		rootNode = node;
		return node;
	}

	RBT__addChildNode(rootNode, node);

	return node;
}

void RBT__printNode(RBT__Node* node, int depth, int blackNodeDepth) {
	if (node == NULL) return;

	for (int i = 0; i < depth; i++) {
		printf("\t");
	}

	if (node->color == BLACK) {
		blackNodeDepth++;
	}

	RBT__ElementType parentData = -1;
	char* parentOf = "X";

	if (node->parent != NULL) {
		parentData = node->parent->data;
		parentOf = node == node->parent->left ? "Left" : "Right";
	}

	printf("[data : %04d, color : %4s, parent : %04d, parentOf : %5s, depth : %02d, blackNodeDepth:%02d]\n", node->data, node->color == BLACK ? "BLACK" : "RED", parentData, parentOf, depth, blackNodeDepth);

	if ( node->left != NULL ) {
		RBT__printNode(node->left, depth + 1, blackNodeDepth);
	}

	if (node->right != NULL) {
		RBT__printNode(node->right, depth + 1, blackNodeDepth);
	}
}
// RBT 관련 끝

// 유틸성 함수 시작
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
// 유틸성 함수 끝

// 사용자 명령어 처리 시작
void actionPrintNodes() {
	printf("== 노드출력 ==\n");

	RBT__printNode(rootNode, 0, 0);
};

void actionInsertNode() {
	printf("== 노드입력 ==\n");

	printf("숫자 : ");
	int num = inputCommand();
	printf("입력할 숫자 : %d\n", num);

	RBT__Node* newNode = RBT__createNode(num);
	RBT__insertNode(newNode);
}
// 사용자 명령어 처리 끝

// 메인 시작
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
			actionPrintNodes();
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
// 메인 끝
