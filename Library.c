

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

//insert a new book
//print all book based on when inserted
//remove a book
//remove a book according to title
//print all books sorted based on year
//

struct DNode {
	char title[100], author[100];
	int year;
	float price;
	struct DNode* next;
};

struct Queue {																											//Creatting nodes and queue pointers
	DNode* head;
	DNode* runner;
};


void queueinit(Queue* lq);
void queueinitnum2(Queue* sq);
void Insertendlist(Queue* iq, char auth[100], char title[100], int year, float price);
void printlist(Queue* printq);
void linkbubble(Queue* startN);
void nodeswap(DNode* a, DNode* b);
void removelast(Queue* findlast);
void removebytitle(Queue* findtitle);
void printofile(Queue* fq, FILE* outfile);

int main()
{

	FILE* fout;
	Queue myqueue;
	int choice = 0, choice2 = 0;
	char auth[100], title[100];
	int year;
	float price;

	queueinit(&myqueue);

	fout = fopen("C:\\Users\\corti\\Documents\\Homework\\Library.txt", "w");


	while (choice != 5) {

		printf("\nWhat would you like to do?\n");
		printf("Insert (1)\n");
		printf("Print (2)\n");
		printf("Remove (3)\n");
		printf("Print Sorted (4)\n");
		printf("Exit (5)\n");																								//Asks user which action should be taken
		scanf("%d", &choice);

		switch (choice) {
		case 1:

			printf("Please type the author of the book\n");
			scanf("%s", &auth);
			printf("Please type the title of the book\n");																	//If "Insert" the following info must be given
			scanf("%s", &title);
			printf("Please type the year of the book\n");
			scanf("%d", &year);
			printf("Please type the price of the book\n");
			scanf("%f", &price);
			Insertendlist(&myqueue, auth, title, year, price);																//Then inserts into the list
			printf("The book has been archived\n\n");
			break;
		case 2:				
			printlist(&myqueue);																							//Prints my list
			break;
		case 3:
			printf("would you like to remove the last entered (1) or by title (2)\n");										//User choice to delete node by last insertion or by title
			scanf("%d", &choice2);

			switch (choice2)
			{
			case 1:
				removelast(&myqueue);
				break;

			case 2:
				removebytitle(&myqueue);
				break;

			default:
				break;
			}

			break;

		case 4:
			linkbubble(&myqueue);																								//Bubble sort to order list by publishing year
			printlist(&myqueue);
			break;

		case 5:
			printofile(&myqueue, fout);																							//Prints to my out file
			break;


		default:
			break;
		}

	}
}

void queueinit(Queue* lq) {
	lq->head = nullptr;
	lq->runner = nullptr;																								//Initialize queue pointers
}

void Insertendlist(Queue* iq, char auth[100], char title[100], int year, float price) {
	DNode* myn = (DNode*)malloc(sizeof(DNode));

	if (myn == NULL) {
		printf("No memory!");
		exit(1);
	}

	strcpy(myn->author, auth);
	strcpy(myn->title, title);

	myn->year = year;
	myn->price = price;

	if ((iq->head == NULL) || (iq->runner == NULL)) {																//This function inserts the given info into a done then places in the list
		myn->next = NULL;
		iq->head = iq->runner = myn;
	}
	else {
		myn->next = NULL;
		iq->runner->next = myn;
		iq->runner = myn;

	}
}

void linkbubble(Queue* startN) {
	int flagswap = 0;
	DNode* bubn;
	DNode* lbubn = NULL;

	if (startN == NULL) {
		return;
	}
	else {
		do {
			flagswap = 0;
			bubn = startN->head;
			while (bubn->next != NULL) {
				if (bubn->year > bubn->next->year) {
					nodeswap(bubn, bubn->next);																				//Performs a bubble sort based on earliest publishing year
					flagswap = 1;
				}
				bubn = bubn->next;
			}
			lbubn = bubn;
		} while (flagswap);
	}
}

void removelast(Queue* findlast) {
	DNode* rn;
	rn = findlast->head;
	while (rn != NULL) {
		if (rn->next->next == NULL) {																						//Function removes last element placed in the list
			rn->next = NULL;
		}
		rn = rn->next;
	}
	printf("The last booked entered was removed\n");

}


void removebytitle(Queue* findtitle) {
	DNode* rtn;
	char findstr[100];																										//Searches through the list to find title then moves the pointer around it
	printf("What is the title you wish to delete?\n");
	scanf("%s", findstr);

	rtn = findtitle->head;
	while (rtn->next != NULL) {
		if (!strcmp(rtn->next->title, findstr)) {
			rtn->next = rtn->next->next;
			printf("The title has been deleted\n");
		}
		else {
			rtn = rtn->next;
		}
	}
}

void printlist(Queue* printq) {
	DNode* pn;
	if (printq->head == nullptr) {
		printf("The are no books entered!\n");
	}
	else {
		pn = printq->head;
		while (pn != NULL)
		{																															//Prints out the given list
			printf("The title is %s\n", pn->title);
			printf("The author is %s\n", pn->author);
			printf("The year it was printed is %d\n", pn->year);
			printf("The price for the book is %f\n", pn->price);
			pn = pn->next;
		}
	}
}

void queueinitnum2(Queue* sq) {
	sq->head = nullptr;
	sq->runner = nullptr;
}

void printofile(Queue* fq, FILE* outfile) {
	DNode* current;																											//Performs another bubble sort, then prints to my out file
	DNode* lcurrent;
	int flag = 0;

	if (fq == NULL) {
		return;
	}
	else {
		do {
			flag = 0;
			current = fq->head;
			while (current->next != NULL) {
				if (current->year > current->next->year) {
					nodeswap(current, current->next);
					flag = 1;
				}
				fprintf(outfile, "The author of this book is ");
				fprintf(outfile, "%s\n", current->author);
				fprintf(outfile, "The title of this book is ");
				fprintf(outfile, "%s\n", current->title);
				fprintf(outfile, "The publishing year of this book is ");
				fprintf(outfile, "%d\n", current->year);
				fprintf(outfile, "The price of this book is ");
				fprintf(outfile, "%f\n", current->price);
				current = current->next;
			}
			lcurrent = current;
		} while (flag);
	}
}


void nodeswap(DNode* a, DNode* b) {
	DNode* temp = (DNode*)malloc(sizeof(DNode));
	char tempstr[100] = "";
	char tempstrtitle[100] = "";
	temp->price = 0;
	temp->year = 0;

	strcpy(tempstr, a->author);
	strcpy(tempstrtitle, a->title);
	temp->price = a->price;																									//Swaps the information between two nodes
	temp->year = a->year;

	strcpy(a->author, b->author);
	strcpy(a->title, b->title);
	a->price = b->price;
	a->year = b->year;

	strcpy(b->author, tempstr);
	strcpy(b->title, tempstrtitle);
	b->price = temp->price;
	b->year = temp->year;
}
