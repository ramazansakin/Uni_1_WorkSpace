#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef struct text_s{
	int id;
	int length;
	char* text;
}text_t;

typedef struct node_s{
	text_t text;
	struct node_s* next;
}node_t;

text_t getText(int id, char ch);
int printText(const text_t* text);
node_t* createOrderedLL(unsigned int a, unsigned int b, unsigned int numOfElem, char ch);
int printLL(node_t* list);
node_t* mergeOrderedLists(node_t* list1, node_t* list2);
int freeList(node_t* list);

int main(){

	text_t text1;
	node_t* list1, *list2, *listMerged;
	int elemC;

	srand(time(NULL));
	
	/*PART1*/
	printf("PART1 \n");
	text1 = getText(3, '*');
	printText(&text1);
	free(text1.text);
	
	/*PART2*/
	printf("PART2 \n");
	list1 = createOrderedLL(2, 0, 20, 'a');
	list2 = createOrderedLL(10, 1, 8, 'b');
	printf("List1: \n");
	printLL(list1);
	printf("List2: \n");
	printLL(list2);

	/*PART3*/
	printf("PART3 \nMergedList: \n");
	listMerged = mergeOrderedLists(list1, list2);
	elemC = printLL(listMerged);
	printf("%d Nodes exists.\n\n", elemC);
	printf("%d elements deleted!!!\n", freeList(listMerged));

	return 0;
}

text_t getText(int id, char ch){
	text_t text;
	char* writePos;

	text.id=id;
	text.length = rand() % 26 + 5;/*get random length*/
	text.text = (char*)malloc((text.length + 1)*sizeof(char));

	/*record the text*/
	for(writePos=text.text; writePos<text.text+text.length; ++writePos)
		*writePos = ch;
	*writePos='\0';

	return text;
}

int printText(const text_t* text){
	return printf("ID: %d, length: %d, text: %s\n", text->id, text->length, text->text);
}

node_t* createOrderedLLRec(unsigned int a, unsigned int b, unsigned int elemC, unsigned int numOfElem, char ch){
	node_t* newNode;

	/*Base Case*/
	if(elemC == numOfElem)
		return NULL;

	/*create new node*/
	newNode = (node_t*)malloc(sizeof(node_t));
	newNode->text=getText(a*elemC+b, ch);
	newNode->next = createOrderedLLRec(a, b, elemC+1, numOfElem, ch);
	
	return newNode;
}

node_t* createOrderedLL(unsigned int a, unsigned int b, unsigned int numOfElem, char ch){

	return createOrderedLLRec(a, b, 0, numOfElem, ch);
}

int printLL(node_t* list){

	if(!list) /* if list == NULL */
		return 0;

	printText(&list->text);
	return (printLL(list->next) + 1);
}

node_t* mergeOrderedLists(node_t* list1, node_t* list2){
	node_t* currentNode;

	/*Base Case*/
	if(!list1)
		return list2;
	if(!list2)
		return list1;

	if(list1->text.id <list2->text.id){
		currentNode = list1;
		currentNode->next = mergeOrderedLists(list1->next, list2);
	}
	else{
		currentNode = list2;
		currentNode->next = mergeOrderedLists(list1, list2->next);
	}

	return currentNode;

}


int freeList(node_t* list){
	int count;

	/*Base Case*/
	if(!list)
		return 0;

	count = freeList(list->next);
	free(list->text.text);
	free(list);
	return count+1;
}



