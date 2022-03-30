
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Playlist {
    char* title;
    char* singer;
    struct Playlist *next;
    struct Playlist *prev;
}Playlist;

void printSearch(bool exist, char* title, Playlist *dest);

void fromTheTop(Playlist **album){
    printf("before rewind: %s\n",(*album)->title);
    while((*album)->prev != NULL){
        *album = (*album) -> prev;
    }

    printf("after rewind: %s\n",(*album)->title);
}

void addSong(Playlist **album, char *title, char *singer) {
    /* 1. allocate node */
    Playlist *new_node
            = (Playlist *) malloc(sizeof(Playlist));
    if (new_node == NULL) {
        printf(" No memory is allocated.");
        exit(0);
    }

    Playlist *last = *album; /* used in step 5*/

    /* 2. put in the data */
    new_node->title = title;
    new_node->singer = singer;

    /* 3. This new node is going to be the last node, so
        make next of it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new
        node as head */
    if (*album == NULL) {
        new_node->prev = NULL;
        *album = new_node;
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;

    /* 7. Make last node as previous of new node */
    new_node->prev = last;

}

void displayPlaylistReverse(Playlist *album){
    Playlist *last = album;
    Playlist *temp = album;

    while (last->next != NULL) {
        last = temp;
        temp = temp->next;
    }

    printf("Playlist in Reverse:\n");
    while (last != NULL) {
        printf("%s, %s\n", last->title, last->singer);
        last = last->prev;
    }
    printf("\n");
}

void displayPlaylist(Playlist *album){
    Playlist *first = album;
    Playlist *temp = album;

    while(first->prev != NULL){
        first = temp;
        temp = temp -> prev;
    }

    printf("Playlist:\n");
    while (first != NULL) {
        printf("%s, %s\n", first->title, first->singer);
        first = first->next;
    }
    printf("\n");
}

void displayTest(Playlist *album){
    Playlist *first = album;

    printf("Playlist:\n");
    while (first != NULL) {
        printf("%s, %s\n", first->title, first->singer);
        first = first->next;
    }
    printf("\n");
}

void currentSong(Playlist *album){
    printf("Current Song:\n");
    printf("%s, %s\n", album->title, album->singer);
    printf("\n");
}

void nextSong(Playlist *album){
    Playlist *temp = album;

    printf("Next Song:\n");
    if(temp->next == NULL){
        printf("End of Playlist\n");
    } else{
        printf("%s, %s\n",temp->next->title, temp->next->singer);
    }
    printf("\n");
}

void previousSong(Playlist *album){
    Playlist *temp = album;

    printf("Previous Song:\n");
    if(temp->prev == NULL){
        printf("End of Playlist\n");
    } else{
        printf("%s, %s\n",temp->prev->title, temp->prev->singer);
    }
    printf("\n");
}

void searchSong(Playlist **album, char* title){
    Playlist *temp = *album;
    Playlist *dest = NULL;
    bool exist = true;

    while(temp->next != NULL) {
        if (!strcmp(temp->title, title)) {
            dest = temp;
        }
        temp = temp->next;
    }

    if(dest == NULL){
        exist = false;
    }

    printSearch(exist, title, dest);
}

void printSearch(bool exist, char* title, Playlist *dest){
    printf("Searched Song:\n");
    if(!exist){
        printf("%s, Does not exist\n", title);
    }else{
        printf("%s, %s\n", dest->title, dest->singer);
    }
    printf("\n");
}

bool deleteSearch(Playlist **album, char* title){
    Playlist *temp = *album;

    Playlist *dest = NULL;
    bool exist = true;

    while(temp->next != NULL) {
        if (!strcmp(temp->title, title)) {
            dest = temp;
        }
        temp = temp->next;
    }

    if(temp->next == NULL & !strcmp(temp->title, title)){
        dest = temp;
    }

    if(dest == NULL){
        exist = false;
    }

    return exist;
}

void deleteSong(Playlist **album, char* title){
    printf("Song Deleted:\n");
    if(*album == NULL){
        printf("Playlist is empty.\n");
        exit(EXIT_SUCCESS);
    }

    if(!deleteSearch(album, title)){
        printf("%s, does not exist so cannot delete\n", title);
        exit(EXIT_SUCCESS);
    }
    Playlist *dest = *album;

    while(dest->next->next != NULL && strcmp(dest->title, title)) {
        dest = dest->next;

        if(dest->next->next == NULL && !strcmp(dest->title, title)){
            dest = dest->next;
        }
    }



    printf("%s, %s\n", dest->title, dest->singer);

    if(!strcmp((*album)->title, title)){
        *album = dest->next;
        (*album)->prev = NULL;
    }else {
        if(dest->next != NULL){
            dest->next->prev = dest->prev;
        }

        if(dest->prev != NULL){
            dest->prev->next = dest->next;
        }
    }
    printf("\n");

}

int main() {
    Playlist *album = NULL;

    addSong(&album, "Memories", "Maroon 5");
    addSong(&album, "With or Without You", "U2");
    addSong(&album, "Nothing Else Matters", "Metallica");
    addSong(&album, "Maki Madni", "The Derek Trucks Band");
    addSong(&album, "Summer of 69", "Bryan Adams");
    addSong(&album, "Another Brick in the Wall", "Pink Floyd");
//    displayPlaylistReverse(album);
//    displayPlaylist(album);
//
//    currentSong(album);
//    nextSong(album);
//    previousSong(album);
//    searchSong(&album, "Ideal 30 days");
//    searchSong(&album, "Maki Madni");
    deleteSong(&album, "Memories");
    displayPlaylist(album);
//    deleteSong(&album, "Summer of 69");
//    displayPlaylist(album);
    deleteSong(&album, "Another Brick in the Wall");
    displayPlaylist(album);
//    displayPlaylistReverse(album);

    return 0;
}
