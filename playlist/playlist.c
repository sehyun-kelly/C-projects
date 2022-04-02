
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

void addSong(Playlist **album, char *title, char *singer);
void currentSong(Playlist *album);
void searchSong(Playlist **album, char* title);
void printSearch(bool exist, char* title, Playlist *dest);
void displayPlaylist(Playlist *album);
void displayPlaylistReverse(Playlist *album);
void nextSong(Playlist *album);
void previousSong(Playlist *album);
void delete_first(Playlist **album);
void delete_last(Playlist **album);
void deleteSong(Playlist **album, char* title);

int main() {
    Playlist *album = NULL;

    addSong(&album, "Memories", "Maroon 5");
    addSong(&album, "With or Without You", "U2");
    addSong(&album, "Nothing Else Matters", "Metallica");
    addSong(&album, "Maki Madni", "The Derek Trucks Band");
    addSong(&album, "Summer of 69", "Bryan Adams");
    addSong(&album, "Another Brick in the Wall", "Pink Floyd");
    displayPlaylistReverse(album);
    displayPlaylist(album);

    currentSong(album);
    nextSong(album);
    previousSong(album);
    searchSong(&album, "Ideal 30 days");
    searchSong(&album, "Maki Madni");
    deleteSong(&album, "Memories");

    return 0;
}

void checkNull(Playlist **album){
    if(*album == NULL){
        printf("Playlist is empty!\n");
        exit(EXIT_SUCCESS);
    }
}

void addSong(Playlist **album, char *title, char *singer) {
    Playlist *new_album = (Playlist *) malloc(sizeof(Playlist));
    if (new_album == NULL) {
        printf("No memory is allocated.");
        exit(EXIT_SUCCESS);
    }

    Playlist *last = *album;

    new_album->title = title;
    new_album->singer = singer;
    new_album->next = NULL;

    if (*album == NULL) {
        new_album->prev = NULL;
        *album = new_album;
        return;
    }

    while (last->next != NULL) last = last->next;

    last->next = new_album;
    new_album->prev = last;
}

void displayPlaylistReverse(Playlist *album){
    checkNull(&album);
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
    checkNull(&album);
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

void currentSong(Playlist *album){
    checkNull(&album);
    printf("Current Song:\n");
    printf("%s, %s\n", album->title, album->singer);
    printf("\n");
}

void nextSong(Playlist *album){
    checkNull(&album);
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
    checkNull(&album);
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
    checkNull(album);
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

void delete_first(Playlist **album){
    checkNull(album);

    if((*album)->next == NULL){
        *album = NULL;
    }else{
        Playlist *temp = *album;
        *album = (*album)->next;
        (*album)->prev = NULL;
        free(temp);
    }
}

void delete_last(Playlist **album){
    checkNull(album);

    if((*album)->next == NULL){
        *album = NULL;
    }else{
        Playlist * temp = *album;

        while(temp->next != NULL){
            temp = temp->next;
        }

        temp->prev->next = NULL;
        free(temp);
    }
}

void deleteSong(Playlist **album, char* title){
    checkNull(album);
    printf("Song Deleted:\n");
    if(*album == NULL){
        printf("Playlist is empty.\n");
        exit(EXIT_SUCCESS);
    }

    Playlist *dest = *album;
    Playlist *dest2 = NULL;

    while(dest->next!= NULL && strcmp(dest->title, title)) {
        dest = dest->next;
    }

    if(dest->next == NULL && strcmp(dest->title, title)){
        printf("%s, does not exist so cannot delete\n", title);
        exit(EXIT_SUCCESS);
    }

    printf("%s, %s\n", dest->title, dest->singer);

    if(!strcmp(dest->title, title) && dest->prev == NULL) {delete_first(album);}
    else if(!strcmp(dest->title, title) && dest->next == NULL){delete_last(album);}
    else{
        dest2 = dest->prev;
        dest->next->prev = dest2;
        dest2->next = dest->next;
        free(dest);
    }
    printf("\n");
}

