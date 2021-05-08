/*
TODO LIST
- �Է���
*/

#include <stdio.h>
#include <stdlib.h>

typedef int bool;

#define true 1
#define false 0

// ��ƿ�� �Լ� ����
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
// ��ƿ�� �Լ� ��

// RBT ���� ����
typedef int RBT__ElementType;

typedef struct _RBT__Node
{
	struct _RBT__Node* parent;
	struct _RBT__Node* left;
	struct _RBT__Node* right;
	enum { RED, BLACK } color;
	RBT__ElementType data;
} RBT__Node;

// ��Ʈ���
RBT__Node* rootNode = NULL;
RBT__Node* nilNode = NULL;

// �����带 ��� �����ؾ� �ϴ���
// ��, �Էµ� ��带 �������� ���� ��, �� �뷱���� �۾��� �ؾ��ϴ��� ����
bool RBT__isNeedToContinueRebuild(RBT__Node* node) {
	return node != rootNode && node->parent->color == RED;
}

// �Էµ� ����� �θ� ���� �߿��� �������� ����
bool RBT__isMyParentNodeLeft(RBT__Node* node) {
	if (node->parent == NULL) {
		return false;
	}

	if (node->parent->parent == NULL) {
		return false;
	}

	return node->parent == node->parent->parent->left;
}

// �Էµ� ����� �θ� ���� �߿��� �������� ����
bool RBT__isMyParentNodeRight(RBT__Node* node) {
	return !RBT__isMyParentNodeLeft(node);
}

// �Էµ� ��尡 ���� �߿��� �������� ����
bool RBT__isNodeLeft(RBT__Node* node) {
	if (node->parent == NULL) {
		return false;
	}

	return node == node->parent->left;
}

// �Էµȳ�尡 ���� �߿��� �������� ����
bool RBT__isNodeRight(RBT__Node* node) {
	return !RBT__isNodeLeft(node);
}

// �θ��� �������
RBT__Node* RBT__getUncleNode(RBT__Node* node) {
	if (node->parent == NULL) {
		return NULL;
	}

	if (node->parent->parent == NULL) {
		return NULL;
	}

	return RBT__isMyParentNodeLeft(node) ? node->parent->parent->right : node->parent->parent->left;
}

// ������ ���̽��� ��ȯ�Ѵ�.
int RBT__getRebuildCase(RBT__Node* node) {
	RBT__Node* uncleNode = RBT__getUncleNode(node);

	// ������ ���
	if (uncleNode->color == RED) {
		return 1;
	}

	// ȸ���ؾ� �ϴ� ���
	return 2;
}

void RBT__rotateRight(RBT__Node* parentNode) {
	// ȸ���� ������ �Ǵ� ���
	RBT__Node* leftChild = parentNode->left;

	// ���س���� ������ �ڽ��� �θ����� �����ڽ�����
	// ���س���� ������ �ڽ��� �θ��忩�� �ϱ� ����
	parentNode->left = leftChild->right;

	// ��������� ������ �ڽ��� �ִ� ���
	if (leftChild->right != nilNode)
		// ���س���� ������ �ڽ��� �θ�� ���̻� ���س�尡 �ƴ϶� �θ���
		leftChild->right->parent = parentNode;

	// ���س���� �θ�� �θ����� �θ����̴�.
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
	// ȸ���� ������ �Ǵ� ���
	RBT__Node* rightChild = parentNode->right;

	// ���س���� ���� �ڽ��� �θ����� �������ڽ�����
	// ���س���� ���� �ڽ��� �θ��忩�� �ϱ� ����
	parentNode->right = rightChild->left;

	// ��������� ������ �ڽ��� �ִ� ���
	if (rightChild->left != nilNode)
		// ���س���� ������ �ڽ��� �θ�� ���̻� ���س�尡 �ƴ϶� �θ���
		rightChild->left->parent = parentNode;

	// ���س���� �θ�� �θ����� �θ����̴�.
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

// nilNode�� �����Ͽ� ��ȯ(left, right�� NULL �̰�, color�� BLACK)
RBT__Node* RBT__createNilNode() {
	RBT__Node* node = RBT__createNode(0);
	node->data = 0;
	node->color = BLACK;

	return node;
}

// �븻��带 ��ȯ(left, right�� nilNode�̰�, ���� RED)
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
// RBT ���� ��

// ����� ��ɾ� ó�� ����
void actionPrintNodes() {
	printf("== ������ ==\n");

	RBT__printNode(rootNode, 0, 0);
};

void actionInsertNode() {
	printf("== ����Է� ==\n");

	printf("���� : ");
	int num = inputCommand();
	printf("�Է��� ���� : %d\n", num);

	RBT__Node* newNode = RBT__createNormalNode(num);
	RBT__insertNode(newNode);
}
// ����� ��ɾ� ó�� ��

// ���� ����
int main() {
	// Nil ��Ʈ ����
	nilNode = RBT__createNilNode();

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
			printf("�������� �ʴ� ��ɾ� �Դϴ�.\n");
			break;
		}
	}

	return 0;
}
// ���� ��
