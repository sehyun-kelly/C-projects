#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define EQUAL (0)

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
void exist(Playlist *temp, char* title);
void deleteSong(Playlist **album, char* title);
void free_album(Playlist** album);

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

    free_album(&album);

    return 0;
}

/**
 * Checks if the playlist is empty and terminates the program if it is
 * @param album Playlist**
 */
void checkNull(Playlist **album){
    if(*album == NULL){
        printf("Playlist is empty!\n");
        exit(EXIT_SUCCESS);
    }
}

/**
 * Adds songs to the album
 * @param album Playlist**
 * @param title char*
 * @param singer char*
 */
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

/**
 * Displays the playlist in reverse
 * @param album Playlist*
 */
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

/**
 * Displays the playlist in order
 * @param album Playlist*
 */
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

/**
 * Displays the current song
 * @param album Playlist*
 */
void currentSong(Playlist *album){
    checkNull(&album);
    printf("Current Song:\n");
    printf("%s, %s\n", album->title, album->singer);
    printf("\n");
}

/**
 * Displays the next song
 * @param album Playlist*
 */
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

/**
 * Displays the previous song
 * @param album Playlist*
 */
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

/**
 * Searches the given song in the playlist
 * @param album Playlist**
 * @param title char*
 */
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

/**
 * Prints the result of searchSong function
 * @param exist bool
 * @param title char*
 * @param dest Playlist*
 */
void printSearch(bool exist, char* title, Playlist *dest){
    printf("Searched Song:\n");
    if(!exist){
        printf("%s, Does not exist\n", title);
    }else{
        printf("%s, %s\n", dest->title, dest->singer);
    }
    printf("\n");
}

/**
 * Deletes the first song of the playlist
 * @param album Playlist**
 */
void delete_first(Playlist **album){
    checkNull(album);

    if ((*album)->next == NULL && (*album)->prev == NULL) {
        *album = NULL;
    } else {
        Playlist *temp = *album;
        *album = (*album)->next;
        (*album)->prev = NULL;
        free(temp);
    }
}

/**
 * Deletes the last song of the playlist
 * @param album Playlist**
 */
void delete_last(Playlist **album){
    checkNull(album);

    if((*album)->next == NULL && (*album)->prev == NULL){
        *album = NULL;
    }else{
        Playlist *temp = *album;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->prev->next = NULL;
        free(temp);
    }
}

/**
 * Checks if the song to delete exists in the playlist
 * @param temp Playlist*
 * @param title char*
 */
void exist(Playlist *temp, char* title){
    if(temp->next == NULL && strcmp(temp->title, title) != EQUAL){
        printf("%s, does not exist so cannot delete\n", title);
        exit(EXIT_SUCCESS);
    }
}

/**
 * Deletes the given song from the playlist
 * @param album Playlist**
 * @param title char*
 */
void deleteSong(Playlist **album, char* title){
    checkNull(album);
    printf("Song Deleted:\n");

    Playlist *temp1 = *album;
    Playlist *temp2 = NULL;

    while(temp1->next!= NULL && strcmp(temp1->title, title) != EQUAL) temp1 = temp1->next;
    exist(temp1, title);
    printf("%s, %s\n", temp1->title, temp1->singer);

    if(!strcmp(temp1->title, title) && temp1->prev == NULL) {delete_first(album);}
    else if(!strcmp(temp1->title, title) && temp1->next == NULL){delete_last(album);}
    else{
        temp2 = temp1->prev;
        temp1->next->prev = temp2;
        temp2->next = temp1->next;
        free(temp1);
    }
    printf("\n");
}

/**
 * Frees the memory of the remaining playlist
 * @param album Playlist**
 */
void free_album(Playlist** album){
    checkNull(album);

    if((*album)->prev == NULL){
        *album = NULL;
    }

    Playlist* current = *album;
    Playlist * temp = NULL;

    while(current != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }
}

