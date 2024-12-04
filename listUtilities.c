
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//structure representing a Student
struct Alunno{
int immatriculationYear;
char name [20];
char surname [20];
int numvoti;
int* voti ;
};

//structure representing the list of students
struct list{
struct Alunno* al;
struct list* next;
};

//add a new student on the top of the actual list of students
void listaddelem(struct list** head) {
	int voti;
	struct list * elem = (struct list *)malloc(sizeof(struct list));
	elem -> next = NULL;
	elem -> al = (struct Alunno *)malloc(sizeof(struct Alunno));
	printf("Inserire nome ,cognome, anno di immatricolazione: \n"); 
	fscanf(stdin, "%s", elem->al->name);
	fscanf(stdin , "%s", elem->al->surname);
	scanf("%d", &elem->al->immatriculationYear) ;
	printf("Quanti voti ha attualmente lo studente?: ");
	scanf("%d", &voti); 
	printf("Li si elenchi di seguito: \n");
	elem->al->voti = (int *)malloc(sizeof(int) *voti);
	elem->al->numvoti = voti;
	for(int i=0; i<voti; i++) {
		scanf("%d", &elem->al->voti[i]);
	}	
	
	
	if(*head == NULL) {
		*head = elem;
		}
	else {
		elem -> next = (*head);
		*head = elem;
	}
}

//support function for reverselist(), add on the top of the given list a students previously declared
void listAddCreatedElem(struct list **head, struct list **elem) {
	if(*head == NULL) {
		*head = (*elem);
		}
	else {
		(*elem) -> next = (*head);
		*head = (*elem);
		}		
	}

//reverse the list given
struct list * reverselist(struct list **head) {
		struct list *newHead = NULL, *temp = (*head);
		while(temp!=NULL) {
			*head = temp-> next;
			temp->next = NULL;
			listAddCreatedElem(& newHead, & temp);
			temp = (*head);
		}
		
		return newHead;
	}

//print the list given
void printlist(struct list *head) {
		struct list *temp = head;
		while(temp !=NULL) {
			printf("%s %s \nImmatriculation year: %d\nExam results:\n", temp->al->name, temp->al->surname, temp->al->immatriculationYear);
			int voti = temp->al->numvoti;
			for(int i=0; i<voti; i++) {
				printf("%d\t", temp->al->voti[i]);
			}
			printf("\n\n");	
			temp = temp->next;
		}
	}

//remove the given occurrence. return true if the operation succeded or false if the operation failed
//(for instance it can failed if the given occurrence doesn't exist)
bool removeOneOccurrence(struct list **head, char occurrence [] ) {
		struct list *prev = NULL, *temp = (*head);
		bool done = false;
		while(temp!=NULL && done == false) {
			if(strcmp(temp->al->name, occurrence) == 0) {
				if(prev == NULL) {
					*head = temp->next;
				}
				else {
					prev->next = temp->next;
				}
					free(temp->al->voti);
					free(temp->al);
					temp->next = NULL;
					done = true;
			}
			else {
				prev = temp;
				temp = temp->next;
			}
		}
		if(done == true) {
			return true;
			}
		else {
			return false;
			}
	}

// deallocate all the memroy reserved to the list of students
void destroylist( struct list** head) {
	struct list *temp = (*head), *current = NULL;
	while(temp != NULL) {
			*head = temp->next;
			current = (*head);
			free(temp->al->voti);
			free(temp->al);
			temp->next = NULL;
			temp = current;
		}
	}
		
int main() {

	int alunni;
	//Testing list implementation and printing
	struct list *head = NULL;
	printf("Quanti studenti?\n");
	scanf("%d", &alunni);
	for(int i = 0; i < alunni; i++) {
		
		listaddelem(&head);
	}
	printlist(head);
	
	//testing reverselist()
	printf("Inversione ordine lista\n");
	head = reverselist(& head);
	printlist(head);
	
	//Testing removeOneOccurrence()
	char nome [20];
	printf("Inserire nome dello studente da rimuovere dalla lista: ");
	fscanf(stdin, "%s", nome);
	if(removeOneOccurrence(& head, nome) == false) {
		printf("Nome non presente in lista\n");
	}
	printlist(head); 
	
	
	//testing destroylist()
	destroylist(&head);
	
	
	return (1);
}
