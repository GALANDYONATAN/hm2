#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	union
	{
		double Vec[4];
		struct Coordinates
		{
			double xCor;
			double yCor;
			double zCor;
			double tCor;
		};
	}Vector4D;
	struct node* next;
}Node;

int isCyclic(Node* head);
int repairCyclic(Node* head);
Node* findCartesianDist(Node* head, double distance, double epsilon);

int main()
{
	Node N;
	Node F, E, D, C, B, A;
	A.next = &B;
	B.next = &C;
	C.next = &D;
	D.next = &E;
	E.next = &B;
	printf("%d\n", isCyclic(&A));
	printf("%d\n", repairCyclic(&A));
}

int isCyclic(Node* head)
{
	Node* t = head;
	while (head != NULL && t != NULL && t->next != NULL)
	{
		head = head->next;
		t = t->next->next;
		if (head == t)
			return 1;
	}
	return 0;
}

int repairCyclic(Node* head)
{
	// check if need to make sure the linked list is really cyclic
	if (isCyclic(head))
	{
		Node* t = head, * p = head;
		// find the meeting for finding the cyclic linked list
		while (p != NULL && t != NULL && t->next != NULL)
		{
			p = p->next;
			t = t->next->next;
			if (p == t)
				break;
		}
		p = p->next;
		t->next = NULL;
		int cnt = 1;
		while (head != p)
		{
			head = head->next;
			cnt++;
		}
		return cnt;
	}
	return 0;
}

Node* findCartesianDist(Node* head, double distance, double epsilon)
{
	Node* t = head;
	while (t != NULL)
	{
		double dis = sqrt(pow(t->Vector4D.xCor, 2) + pow(t->Vector4D.yCor, 2) + pow(t->Vector4D.zCor, 2) + pow(t->Vector4D.tCor, 2));
		if (abs(dis - distance) < epsilon) // abs --> absolute
			return t;
		t = t->next;
	}
	return NULL;
}