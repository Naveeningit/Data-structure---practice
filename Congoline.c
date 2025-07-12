#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{             // structure declaration
    char *name;
    struct node* prev;
    struct node*next;
};

struct node*head=NULL;  // head declaration
struct node*tail=NULL;  // tail declaration

void joinLine(char *name){        // insert at end function
    struct node *newnode=(struct node*)malloc(sizeof(struct node*)); // creates new node
    newnode->name=(char*)malloc(strlen(name)+1);  // memory allocation for name
    strcpy(newnode->name,name);     // copy name from argument to newnode
    if(tail!=NULL){        // add as newnode to the tail
        tail->next=newnode;
        newnode->prev=tail;
        tail=newnode;
        newnode->next=NULL;
    }
    else{                 // initial node
        head=newnode;
        tail=newnode;
        newnode->next=NULL;
        newnode->prev=NULL;
    }
}

void leaveLine(){         // delete at begining
    struct node* temp=head;
    head=temp->next;
    free(temp); 
    head->prev=NULL;
}

void viewLine(){         // display
    struct node*temp=head;
    while(temp!=NULL){
        printf("\n%s\n || ",temp->name);
        temp=temp->next;
    }
    printf("\nNULL\n");
}

int main()
{
  joinLine("Naveen");
  joinLine("praveen");
  joinLine("Sudharshan");
  viewLine();
  leaveLine();
  viewLine();
  joinLine("Sasi");
}
