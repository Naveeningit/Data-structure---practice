// treasure hunt....
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
typedef struct clue {
	char* statement;
	char letter;
	struct clue* prev;
	struct clue*next;
} Clue;

Clue*head=NULL;
Clue*tail=NULL;

Clue*Createclue(char *statement,char letter) {
	Clue *newclue=malloc(sizeof(Clue));
	newclue->statement=strdup(statement);
	newclue->letter=letter;
	newclue->next=NULL;
	newclue->prev=NULL;
	return newclue;
}
void addClue(char* statement,char letter) {

	Clue*newclue=Createclue(statement,letter);
	if(tail!=NULL) {
		tail->next=newclue;
		newclue->prev=tail;
		tail=newclue;
	}
	else {
		head=newclue;
		tail=newclue;
	}
}
void removeClue() {
	if (tail == NULL) return;

	Clue* toDelete = tail;
	tail = tail->prev;

	if (tail != NULL)
		tail->next = NULL;
	else
		head = NULL;

	free(toDelete->statement);
	free(toDelete);
}

void display() {
	struct clue*temp=head;
	while(temp!=NULL) {
		printf("%s \n",temp->statement);
		temp=temp->next;
	}
}
void play() {
	struct clue*temp=head;
	int j=1;
	char letter;
	char str[50];
	while(temp!=NULL) {
		printf("clue %d:%s\n\n",j++,temp->statement);
		while (1) {
			scanf(" %c", &letter);
			if (temp->letter == toupper(letter)) {
				printf("\tClick!!! You've unlocked it\t\n\n");
				strncat(str, &temp->letter, 1);
				break;
			} else {
				printf("\tFind the right key!\t\n");
			}
		}
		temp=temp->next;

	}
	printf("Congratualations You found the treasure! \"%s\"",str);
}
int main()
{
	addClue(" What developers write?",'C');
	addClue(" First letter of 'Open'",'O');
	addClue(" I come 23rd in alphabets reverse train",'D');
	addClue(" Last letter in 'Love'",'E');
	addClue(" I am the First and Last of 'Racer'",'R');
	play();
	return 0;
}
