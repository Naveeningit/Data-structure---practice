// Most used word in a file
#include<stdlib.h>
#include <stdio.h>
#include<string.h>
#include<ctype.h>
typedef struct node {
	int count;
	char * str;
	struct node*next;
} Word;
Word* Top=NULL;

Word* Createnode(char*str) {
	Word*newword=(Word*)malloc(sizeof(Word));
	newword->str=(char*)malloc(strlen(str)+1);
	strcpy(newword->str,str);
	newword->count=1;
	newword->next=NULL;
	return newword;
}
int ispresent(Word*top,char*str) {
	Word*temp=top;
	while(temp!=NULL) {
		if(!strcasecmp(temp->str,str)) {
			temp->count+=1;
			return 1;
		}
		temp=temp->next;
	}
	return 0;
}

void insert(Word**top,char *str) {
	if(!ispresent(*top,str)) {
		Word *newword=Createnode(str);
		if(*top==NULL) {
			*top=newword;
			return;
		}
		newword->next=*top;
		*top=newword;
		return;
	}
}
int getlength(Word*top) {
	Word*temp=top;
	int count=0;
	while(temp!=NULL) {
		count++;
		temp=temp->next;
	}
	return count;
}
void display(Word*top) {
	Word*temp=top;
	while(temp!=NULL) {
		printf("%s : %d\n",temp->str,temp->count);
		temp=temp->next;
	}
}
void BubbleSort(Word**top) {
	int len=getlength(*top);

	for(int i=0; i<len; i++) {
		Word* curr=*top;
		Word* prev=*top;
		int swapped=0;
		while(curr->next!=NULL) {
			Word*after=curr->next;
			if(curr->count<after->count) {
				swapped=1;
				if(curr==*top) {
					curr->next=after->next;
					after->next=curr;
					prev=after;
					*top=prev;
				}
				else {
					curr->next=after->next;
					after->next=curr;
					prev->next=after;
					prev=after;
				}
				continue;
			}
			prev=curr;
			curr=curr->next;
		}
		if(!swapped) break;
	}
}
int main()
{
	char str[20],ch,prech;
	int i=0;
	FILE*fp=fopen("text.txt","r");
	if(!fp) perror("FILE");
	while((ch=fgetc(fp))!=EOF) {
		if(ch==' '||ch=='\n') {
			str[i]='\0';
			insert(&Top,str);
			i=0;
		}
		else if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')) {
			str[i++]=ch;
		}
	}
//	printf("\nTotal Words: %d\n",getlength(Top));
	BubbleSort(&Top);
	printf("Frequently used words:\n");
	display(Top);
	return 0;
}
