#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* next;
};

struct Node* insertAtBeginning(struct Node* head, int newData){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = newData;
	newNode->next = head;
	head = newNode;
	return head;
}

void printList(struct Node* head){
	while(head != NULL){
		printf("%d ->",head->data);
		head = head->next;
	}
	printf(" NULL\n");
}


int main(){
	struct Node* head = NULL;
	head = insertAtBeginning(head, 8);
	printList(head);
	head = insertAtBeginning(head, 9);
	printList(head);
	head = insertAtBeginning(head, 10);
	printList(head);
	return 0;

}
