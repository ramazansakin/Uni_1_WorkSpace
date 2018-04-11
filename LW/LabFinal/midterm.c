#include<stdio.h>
#include<stdlib.h>


typedef struct
{
    int s1,s2,s3;
    int perimeter;

}triangle_t;

typedef struct
{
    int s1,s2;
    int perimeter;

}rectangle_t;

typedef struct
{
    int s1,s2,s3,s4,s5,s6;
    int perimeter;

}hexagon_t;

typedef enum {TRIANGLE,RECTANGLE,HEXAGON} shape_enum;

typedef union
{
    triangle_t tShape;
    rectangle_t rShape;
    hexagon_t hShape;

}shape_t;

typedef struct
{
    shape_enum type; /*0-triangle, 1-rectangle, 2-hexagon*/
    shape_t shape;

}tShape_t;

typedef struct node_s
{
	tShape_t shape;
	struct node_s* next;
}node_t;


char* getLastOcc(char* str, char letter);
int printArr(const tShape_t shapes[], int size);
int printLinkedList(node_t* list);
int freeList(node_t* list);

int main(){

	char str[] = "This is a sample string";
	tShape_t* shapes;
	int size;
	node_t* list1, *list2, *list3* list4;

	/*PART 1*/
	printf("After the character: %s\n", getLastOcc(str, 's')); 

	/*PART 2*/
	printf("\n\nPART2\n");
	
	/*PART 3*/
	printf("\n\nPART3\n");

}


/*prints a tShape_t type variable, returns the number of characters printed*/
int printShape(const tShape_t* shape){
	const triangle_t* t;
	const rectangle_t* r;
	const hexagon_t* h;
	
	if(shape->type == TRIANGLE){
			t=&shape->shape.tShape;
			return printf("Triangle with edges: %d, %d, %d and perimeter %d\n",
			 t->s1, t->s2, t->s3, t->perimeter);
		}
		if(shape->type == RECTANGLE){
			r=&shape->shape.rShape;
			return printf("Rectangle with edges: %d, %d and perimeter %d\n", r->s1, 
				r->s2, r->perimeter);
		}
		else{
			h=&shape->shape.hShape;
			return printf("Hexagon with edges: %d, %d, %d, %d, %d, %d and perimeter %d\n", h->s1, h->s2, h->s3, h->s4, h->s5, h->s6, h->perimeter);
		}

}

/*prints the content of a tShape_t array, returns the number of characters printed*/
int printArr(const tShape_t shapes[], int size){
	int i, total=0;
	
	for(i=0; i<size; ++i)
		total += printShape(&shapes[i]);
	
	return total;
}

/*prints the content of a linked list, returns the number of characters printed*/
int printLinkedList(node_t* list){
	int characterCount;
	
	/*Base Case*/
	if(!list)
		return 0;
		
	return printShape(&list->shape) + printLinkedList(list->next); 
}

/*Deallocates dynamically allocated memory for the linked list, 
returns number  of nodes deallocated*/
int freeList(node_t* list){
	int nodesDeleted;
	
	/*Base Case*/
	if(!list)
		return 0;
	
	nodesDeleted=freeList(list->next);
	free(list);
	return nodesDeleted + 1;
}



	
		


