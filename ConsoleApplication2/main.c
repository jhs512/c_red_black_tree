/*
TODO LIST
- 입력폼
*/

#include <stdio.h>
#include <stdlib.h>

typedef int bool;

#define true 1
#define false 0

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
RBT__Node* nilNode = NULL;

// 리빌드를 계속 진행해야 하는지
// 즉, 입력된 노드를 기준으로 봤을 때, 더 밸런스를 작업을 해야하는지 여부
bool RBT__isNeedToContinueRebuild(RBT__Node* node) {
	return node != rootNode && node->parent->color == RED;
}

// 입력된 노드의 부모가 형제 중에서 왼쪽인지 여부
bool RBT__isMyParentNodeLeft(RBT__Node* node) {
	if (node->parent == NULL) {
		return false;
	}

	if (node->parent->parent == NULL) {
		return false;
	}

	return node->parent == node->parent->parent->left;
}

// 입력된 노드의 부모가 형제 중에서 오른인지 여부
bool RBT__isMyParentNodeRight(RBT__Node* node) {
	return !RBT__isMyParentNodeLeft(node);
}

// 입력된 노드가 형제 중에서 왼쪽인지 여부
bool RBT__isNodeLeft(RBT__Node* node) {
	if (node->parent == NULL) {
		return false;
	}

	return node == node->parent->left;
}

// 입력된노드가 형제 중에서 오른인지 여부
bool RBT__isNodeRight(RBT__Node* node) {
	return !RBT__isNodeLeft(node);
}

// 부모의 형제노드
RBT__Node* RBT__getUncleNode(RBT__Node* node) {
	if (node->parent == NULL) {
		return NULL;
	}

	if (node->parent->parent == NULL) {
		return NULL;
	}

	return RBT__isMyParentNodeLeft(node) ? node->parent->parent->right : node->parent->parent->left;
}

// 리빌드 케이스를 반환한다.
int RBT__getRebuildCase(RBT__Node* node) {
	RBT__Node* uncleNode = RBT__getUncleNode(node);

	// 간단한 경우
	if (uncleNode->color == RED) {
		return 1;
	}

	// 회전해야 하는 경우
	return 2;
}

void RBT__rotateRight(RBT__Node* parentNode) {
	// 회전의 기준이 되는 노드
	RBT__Node* leftChild = parentNode->left;

	// 기준노드의 오른쪽 자식을 부모노드의 왼쪽자식으로
	// 기준노드의 오른쪽 자식은 부모노드여야 하기 때문
	parentNode->left = leftChild->right;

	// 기존노드의 오른쪽 자식이 있는 경우
	if (leftChild->right != nilNode)
		// 기준노드의 오른쪽 자식의 부모는 더이상 기준노드가 아니라 부모노드
		leftChild->right->parent = parentNode;

	// 기준노드의 부모는 부모노드의 부모노드이다.
	leftChild->parent = parentNode->parent;

	if (parentNode->parent == NULL)
		rootNode = leftChild;
	else
	{
		if (parentNode == parentNode->parent->left)
			parentNode->parent->left = leftChild;
		else
			parentNode->parent->right = leftChild;
	}

	leftChild->right = parentNode;
	parentNode->parent = leftChild;
}

void RBT__rotateLeft(RBT__Node* parentNode) {
	// 회전의 기준이 되는 노드
	RBT__Node* rightChild = parentNode->right;

	// 기준노드의 왼쪽 자식을 부모노드의 오른쪽자식으로
	// 기준노드의 왼쪽 자식은 부모노드여야 하기 때문
	parentNode->right = rightChild->left;

	// 기존노드의 오른쪽 자식이 있는 경우
	if (rightChild->left != nilNode)
		// 기준노드의 오른쪽 자식의 부모는 더이상 기준노드가 아니라 부모노드
		rightChild->left->parent = parentNode;

	// 기준노드의 부모는 부모노드의 부모노드이다.
	rightChild->parent = parentNode->parent;

	if (parentNode->parent == NULL)
		rootNode = rightChild;
	else
	{
		if (parentNode == parentNode->parent->right)
			parentNode->parent->right = rightChild;
		else
			parentNode->parent->left = rightChild;
	}

	rightChild->left = parentNode;
	parentNode->parent = rightChild;
}

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

// nilNode를 생성하여 반환(left, right가 NULL 이고, color가 BLACK)
RBT__Node* RBT__createNilNode() {
	RBT__Node* node = RBT__createNode(0);
	node->data = 0;
	node->color = BLACK;

	return node;
}

// 노말노드를 반환(left, right가 nilNode이고, 색이 RED)
RBT__Node* RBT__createNormalNode(RBT__ElementType data) {
	RBT__Node* node = RBT__createNode(0);
	node->data = data;
	node->left = nilNode;
	node->right = nilNode;

	return node;
}

void RBT__addChildNode(RBT__Node* parentNode, RBT__Node* node) {
	if (parentNode->data > node->data) {
		if (parentNode->left == nilNode) {
			node->parent = parentNode;
			parentNode->left = node;
		}
		else {
			RBT__addChildNode(parentNode->left, node);
		}
	}
	else {
		if (parentNode->right == nilNode) {
			node->parent = parentNode;
			parentNode->right = node;
		}
		else {
			RBT__addChildNode(parentNode->right, node);
		}
	}
}

void RBT__rotateForBalance(RBT__Node* childNode) {
	if (RBT__isMyParentNodeLeft(childNode)) {
		if (RBT__isNodeRight(childNode)) {
			childNode = childNode->parent;
			RBT__rotateLeft(childNode);
		}

		childNode->parent->color = BLACK;
		childNode->parent->parent->color = RED;

		RBT__rotateRight(childNode->parent->parent);
	}
	else {
		if (RBT__isNodeLeft(childNode)) {
			childNode = childNode->parent;
			RBT__rotateRight(childNode);
		}

		childNode->parent->color = BLACK;
		childNode->parent->parent->color = RED;

		RBT__rotateLeft(childNode->parent->parent);
	}
}

void RBT__rebuildNode(RBT__Node* node) {
	while (RBT__isNeedToContinueRebuild(node))
	{
		int caseNo = RBT__getRebuildCase(node);

		if (caseNo == 1) {
			RBT__Node* uncleNode = node->parent->parent->right;

			node->parent->color = BLACK;
			uncleNode->color = BLACK;
			node->parent->parent->color = RED;

			node = node->parent->parent;
		}
		else if (caseNo == 2) {
			RBT__rotateForBalance(node);
		}
	}

	rootNode->color = BLACK;
}

void RBT__insertNode(RBT__Node* node) {
	if (rootNode == NULL) {
		rootNode = node;
	}
	else {
		RBT__addChildNode(rootNode, node);
	}

	RBT__rebuildNode(node);
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

	if ( node->left != nilNode) {
		RBT__printNode(node->left, depth + 1, blackNodeDepth);
	}

	if (node->right != nilNode) {
		RBT__printNode(node->right, depth + 1, blackNodeDepth);
	}
}
// RBT 관련 끝

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

	RBT__Node* newNode = RBT__createNormalNode(num);
	RBT__insertNode(newNode);
}
// 사용자 명령어 처리 끝

// 메인 시작
int main() {
	// Nil 노트 생성
	nilNode = RBT__createNilNode();

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
