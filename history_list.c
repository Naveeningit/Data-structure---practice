//History list of file directories
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct directory {
	char* filename;
	struct directory* prev;
	struct directory*next;
};
struct directory*head=NULL;
struct directory*tail=NULL;
struct directory*curr=NULL;
void insertDirectory(char* filename) {
	struct directory *newdirectory=(struct directory*)malloc(sizeof(struct directory));
	newdirectory->filename=(char*)malloc(strlen(filename)+1);
	strcpy(newdirectory->filename,filename);
	if(head!=NULL) {
		head->prev=newdirectory;
		newdirectory->next=head;
		head=newdirectory;
		curr=head;
		newdirectory->prev=NULL;
	}
	else {
		head=newdirectory;
		tail=newdirectory;
		curr=head;
		newdirectory->next=NULL;
		newdirectory->prev=NULL;
	}
}
int previousDirectory() {
	if(curr->next!=NULL) {
		curr=curr->next;
		return 1;
	}
	else return 0;
}
int nextDirectory() {
	if(curr->prev!=NULL) {
		curr=curr->prev;
		return 1;
	}
	else return 0;
}
void traversal() {
	char key;
	printf("Enter P = previous directory N = next directory E = exit\n");
	while(key!='E') {
		scanf(" %c",&key);
		if(key=='P'&&previousDirectory()) {
			printf("Previous: %s\n",curr->filename);
		}
		else if(key=='N'&&nextDirectory()) {
			printf("Next: %s\n",curr->filename);
		}
		else if((curr==head&&key!='E')||(curr==tail&&key!='E')) {
			printf("curr: %s\n",curr->filename);
			continue;
		}
	}
}

int main()
{
	insertDirectory("instagram");
	insertDirectory("whatsapp");
	insertDirectory("linkedin");
	insertDirectory("youtube");
	traversal();
}
