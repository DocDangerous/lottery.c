//Caleb Harris, ID 5439602, P2

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct person {
    int num;
    struct person* next;
} person;

int findWinner(int groupNum);
person* pInsert(person* list, int value);
person* pBack(person* list, int p);
person* elim(person* list, int p, int s, int t);
person* delete(person* list, int s);
void freeList(person* list, int t);
void printList(person* list, int p);

//Main
int main()
{
    int n, g;
    //Case loop
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        //Get number of groups
        scanf("%d", &g);
        //Array to store winners from each group
        int* winArray = calloc((g+1), sizeof(int));
        //Group loop
        for(int j = 1; j <= g; j++) {
            winArray[j] = findWinner(j);
        }
        //Go through win array to find lowest numbered person
        int realWinner = winArray[1];
        int winGroup = 1;
        for(int k = 2; k <= g; k++) {
            if(winArray[k] < realWinner) {
                realWinner = winArray[k];
                winGroup = k;
            }
        }

        printf("Lottery winner is person %d from group %d.\n", realWinner, winGroup);
    }

    return 0;
}

//Go through the data of a group and determine the winner
int findWinner(int groupNum)
{
    //Get number of people in group, skip value, and threshold
    int p, s, t;
    scanf("%d", &p);
    scanf("%d", &s);
    scanf("%d", &t);

    //Make front of linked list
    person* pList = NULL;
    pList = malloc(sizeof(person));
    pList->num = 1;
    pList->next = NULL;

    //Go through each person after the first (besides the last) and add them to the linked list
    for(int i=2; i<p; i++) {
        pList = pInsert(pList, i);
    }

    //Make final person and link them to the front of the list
    pList = pBack(pList, p);

    //printList(pList, p);
    printf("\nGroup %d:\n", groupNum);

    //Eliminate people
    pList = elim(pList, p, s ,t);


    //Set a baseline winner
    int winner = pList->num;

    //Loop through remainder of the linked list, searching for the lowest numbered person
    for(int j=1; j<=t; j++) {
        pList = pList->next;
        if(pList->num < winner) {
            winner = pList->num;
        }
    }

    freeList(pList, t);

    //Return the winner
    return winner;
}

//Add to linked list
person* pInsert(person* list, int value)
{
    //Make new person
    person* pNew = NULL;
    pNew = malloc(sizeof(person));
    pNew->num = value;
    pNew->next = NULL;

    //Make helpPtr to move through list;
    person* helpPtr = list;

    //Go through list until reaching the end
    while(helpPtr->next != NULL) {
        helpPtr = helpPtr->next;
    }
    //Place new person at end
    helpPtr->next = pNew;

    return list;
}

//Close the loop of a list
person* pBack(person* list, int p)
{
    //Make last person in list, numbered "p"
    person* pLast = NULL;
    pLast = malloc(sizeof(person));
    pLast->num = p;
    pLast->next = list;

    //Make helpPtr to move through list;
    person* helpPtr = list;

    //Go through list until reaching the end
    while(helpPtr->next != NULL) {
        helpPtr = helpPtr->next;
    }
    //Place new person at end
    helpPtr->next = pLast;

    return list;
}

//Function to eliminate people
person* elim(person* list, int p, int s, int t)
{
    int count = p;

    while(count != t) {
        for(int i = 1; i < s; i++) {
            list = list->next;
        }
        list = delete(list, s);
        list = list->next;
        count--;
    }

    return list;
}

//Function to delete a person
person* delete(person* list, int s)
{

        //Temp storage
        person* delCopy = list->next;
        person* newNext = delCopy->next;

        //Log
        printf("%d\n", delCopy->num);

        //Set next person to person after the one being deleted
        list->next = newNext;
        free(delCopy);

    return list;
}

//Free a list's memory
void freeList(person* list, int t)
{
   person* freeCopy = NULL;
   for(int i=0; i<t; i++) {
        freeCopy = list;
        list = list->next;
        free(freeCopy);
   }
}

//Debug to make sure linked lists are accurate and circular
void printList(person* list, int p)
{
    for(int i=1; i<=(p*2); i++) {
        printf("%d\n", list->num);
        list = list->next;
    }
}
