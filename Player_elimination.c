#include <stdio.h>
#include<string.h>
#include<stdlib.h>
struct player {             // player structure
	char *name;
	int number;
	struct player*next;
	struct player*prev;
};
struct player*head=NULL;   // head declaration
struct player*tail=NULL;   // tail declaration
void addPlayer(char* name, int number) {    // insert at end
	struct player *newplayer=(struct player*)malloc(sizeof(struct player));
	newplayer->name=(char*)malloc(strlen(name)+1);
	strcpy(newplayer->name,name);
	newplayer->number=number;
	if(tail!=NULL) {
		tail->next=newplayer;
		newplayer->prev=tail;
		tail=newplayer;
		newplayer->next=NULL;
	}
	else {
		head=newplayer;
		tail=newplayer;
		newplayer->next=NULL;
		newplayer->prev=NULL;
	}
}

void removePlayer(int pos) {  // getting position as input to remove particular player
	struct player* temp=head;
	int i=1;
	while(i<pos) {
		temp=temp->next;
		i++;
	}
	if(head==temp) {
		head=temp->next;
		free(temp);
	}
	else if(temp==tail) {
		tail=tail->prev;
		free(tail->next);
		tail->next=NULL;
	}
	else {
		temp->prev->next=temp->next;
		temp->next->prev=temp->prev;
		free(temp);
	}
}
int numberOfPlayers() {      // to count numberOfPlayers in the list
	struct player*temp=head;
	int i=0;
	while(temp!=NULL) {
		temp=temp->next;
		i++;
	}
	return i;
}
void play() {             // the game begins here
	int n=numberOfPlayers(),pos;
	while(n>1) {        // iterates untill only one player present in the list
		n=numberOfPlayers();
		if(n==1) break;
		printf("%d players present\n\n",n);
		printf("Enter n to eliminate the nth player: ");
		scanf("%d",&pos);
		if(pos<=n)
		removePlayer(pos);
		else{
		     printf("\tEnter valid position: ");
		     		scanf("%d",&pos);
		}
	}
	printf("\n\tTHE WINNER IS \"%s\" \"%d\" \n",head->name,head->number);
}
int main()
{
	addPlayer("Naveen",3);
	addPlayer("Siva",1);
	addPlayer("ravi",10);
	addPlayer("prem",5);
	addPlayer("Mani",9);
	addPlayer("Kumar",6);
	addPlayer("Aravind",4);
	addPlayer("Kishore",8);
	addPlayer("Kiran",2);
	addPlayer("Santhosh",7);
	play();
	return 0;
}
