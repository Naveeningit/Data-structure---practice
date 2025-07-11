// AudioPlaylist

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct song{
    char*str;
    struct song*next;
}Song;
Song*Head=NULL;
Song*CreateNode(char*str){
    Song*newsong=malloc(sizeof(Song));
    newsong->str=strdup(str);
    newsong->next=NULL;
    return newsong;
}
void Addsong(char*str){
    Song*newsong=CreateNode(str);
    if(Head==NULL){
        Head=newsong;
    }
    else{
    newsong->next=Head;
    Head=newsong;
    }
    printf("\"%s\" added to playlist\n",Head->str);
    return;
}
void display(){
    if(Head==NULL) printf("No song Added\n");
    Song*temp=Head;int i=1;
    while(temp!=NULL){
        printf("%d %s\n",i++,temp->str);
        temp=temp->next;
    }
    return;
}
int main() {
    int choice;
    char str[100];  // Safe buffer on stack

    while (1) {
        printf("\n1: Add a song\n2: Display songs\n3: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume leftover newline from scanf

        switch (choice) {
            case 1:
                printf("Enter the Song: ");
                scanf("%[^\n]",str);
                //fgets(str, sizeof(str), stdin);
                //str[strcspn(str, "\n")] = 0; // Remove trailing newline
                Addsong(str);
                break;
            case 2:
                display();
                break;
            case 3:
                printf("Exited\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
