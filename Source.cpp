/*********************
Assignment 1			
Kevin Hartwig
October 4, 2015
**********************/

/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Constants*/
#define FALSE 0
#define TRUE 1
#define MAX 140
#define MIN

/*Prototypes*/

struct message {
	char mssgText[140];
	int senderID;
	int receiverID;
	char mssgPriority;
	int mssgSequence;
};

typedef message Message;
struct node {node *pNext; Message data;};
typedef struct node Node;
Node *pHead;
Node *pTail;
Node *pNode;
Node *Nodes[10];


int RandRange(int Min, int Max);
int GetMessageFromFile(char *szBuf, int iLen);
int clearBuffer(char *bufArr);
 
int checkQueue(void);
void addToQueue(char *newMssg);
void deQueue(void);
void initQueue(void);

int numberNodes;
int messages[1140];  // I want to check if any duplicate messages are retreived from the text file.  I am aware this takes up extra computing time.
int messageTracker;  //This is used to track number of messages in messages[]

/*Main Function*/
int main()
{
	char bufferArray[MAX+10] = "";  //+10 is a buffer safety net
	int mssgLen = MAX;
	int check = FALSE;
	int check1 = FALSE;
	char cont;
	int i, loopCounter, j, h;
	int number = 0;
	int numberDuplicates = 0;
	messageTracker = 0;
	numberNodes = 0;
	(*pHead).pNext == NULL;

	char userInput[10] = "";
	int userI;

	srand(time(NULL));

	while (check1 == FALSE)
	{
		initQueue;
		puts("Assignment 1 - FORTUNE COOKIES!\n\nHow many messages would you like to queue?\n");
		
		userI = -1;

		while (userI == -1) {
			flushall();
			gets(userInput);
			userI = atoi(userInput);
			if (userI == 0) {
				printf("If you don't want to queue, press 'enter'.  Otherwise please enter a valid \nnumber:  ", numberNodes);
					gets(userInput);
					if (userInput[0] == '\0' || userInput[0] == '0'){
						userI=0;
						break;
					}
				userI = atoi(userInput);
			}
		}

		loopCounter = 0;

		puts("Message(s) chosen: ");

		for (i=0;i<userI;i++) {

			if (loopCounter % 8 == 0)				//Formatting
				printf("\n     ");

			check = GetMessageFromFile(bufferArray, mssgLen);
			if (check == 1) {
				printf("Error reading file: program will close");
				system("PAUSE");
				return 0; 
			} else {
					addToQueue(bufferArray);
				
				clearBuffer(bufferArray);
				
			}
				loopCounter++; messageTracker++;
			}

	for (i = 0 ; i < messageTracker ; i++)
		for (j = 0 ; j < messageTracker ; j++)
			if (messages[i] == messages[j] && i != j)
				numberDuplicates++;

			
	printf("\n\nThere are now %d messages in the queue, with %d duplicates. \n\nHow many would you like to dequeue?\n\n", numberNodes, numberDuplicates);

	userI = -1;

	while (userI == -1) {
		flushall();
		gets(userInput);
		userI = atoi(userInput);
		if (userI == 0 || userI > numberNodes) {
			printf("If you don't want to dequeue, press 'enter'.  Otherwise please enter a \nnumber between 0 and %d:  ", numberNodes);
				gets(userInput);
				if (userInput[0] == '\0' || userInput[0] == '0') {
					userI=0;
					break;
				}
			userI = atoi(userInput);
		}
	}

	for (i = 0 ; i < userI ; i++)
		deQueue();

	//Clear buffer

		clearBuffer(bufferArray);	

		puts("\nEnter y to do more with the Queue.  Any other key will quit.");

		flushall();
		cont = _fgetchar();
		if (cont == 'y')   
			system("cls");
		else 
			return 0;		

	}


}

int GetMessageFromFile(char *szBuf, int iLen)
{
	char fileloc[MAX+1] = "c:\\Text Files\\FortuneCookies.txt";
	int check = FALSE; 
	FILE *fptr;
	int random, counter, max = 0, b, a, find = 0;
	char i = NULL;	

	fptr = fopen(fileloc, "r");	

	if (fptr == NULL)
	{
		printf("\n\nError in file address.");
		return FALSE;
	}	

//Determine number of messages in file	(I know this shouldn't be counted every time.  But what if we were reading from different text files every time?)
		
	while (i != EOF){
		i = getc(fptr);

		if (i == '%') {
			i = getc(fptr);
				if (i == '%')
					max++;
		}
	}

	max = max + 1;					//max + 1 because first message does not start with '%%'

//Generate random number between 0 and the number of messages in the text file	

		for (a=0;a<100;a++)
			for (b=0;b<100;b++)
				random = RandRange(1, max);

	printf("%8d", random);
	messages[messageTracker] = random;

//Reset file pointer

	fclose(fptr);
	fptr = fopen(fileloc, "r");

	i = NULL;

//Find associated message in file (associated with random number just generated)
//'find' (variable below) used to track number of %%'s passed so far

	if (random != 1)         //If random == 1, leave fptr pointing to first character in text file
	{
		while (i != EOF && find < random)
		{
			i = getc(fptr);

			if (i == '%')
				i = getc(fptr); 
				if (i == '%') {
					find++;
					i = getc(fptr);
				}
			
		}
	} 

//Read message into buffer
	
	for (a=0;a<iLen;a++) {
		if (i != '%') {			
			szBuf[a]=i;	
			i = getc(fptr);
		}
		else {
			i = getc(fptr);
			if (i == '%')
				a=iLen;
			else
				szBuf[a] = '%';
		}
	} 

//Close file and terminate string
	fclose(fptr);

	szBuf[a+1]='\0';

	if (szBuf == "")
		return 1;

	return 0;
}

int checkQueue() {
	if (numberNodes == 0)
		return 0;
	else if (numberNodes == 3)
		return 1;
	else if (numberNodes < 3)
		return 2;
}

void initQueue(void) {
	pTail = pHead = NULL;
}

void deQueue(void) {

	puts((*pHead).data.mssgText);

	Node *pTemp = pHead;
	if ((*pHead).pNext != NULL)
		pHead = (*pHead).pNext;
	else
		pHead == NULL;

	free(pTemp);

	numberNodes--;

}	

void addToQueue(char *newMssg) {

	if (numberNodes > 1) {
			(*pTail).pNext = (Node *)malloc(sizeof(Node));
			pTail = (*pTail).pNext;
			strcpy((*pTail).data.mssgText, newMssg);
		} else if (numberNodes == 1) {
			(*pHead).pNext = (Node *)malloc(sizeof(Node));
			strcpy((*(*pHead).pNext).data.mssgText, newMssg);
			pTail = (*pHead).pNext;			
		} else if (numberNodes == 0){
			pHead = (Node *)malloc(sizeof(Node)); 		
			strcpy((*pHead).data.mssgText, newMssg);
			(*pHead).pNext = pTail;
	}
	numberNodes++;
}

int RandRange(int Min, int Max)
{
    int diff = Max-Min;
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + Min);
}

int clearBuffer(char *clrBuf)
{
	clrBuf = "";
	return 1;
}

