#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list_node_t {
    void* data;
    struct linked_list_node_t* next;
} linked_list_node_t;

void create_array_of_linked_list_ptrs(linked_list_node_t*** destination, int size) {
    *destination = (linked_list_node_t**)calloc(size, sizeof(struct linked_list_node_t));
}

void create_link_list(linked_list_node_t** destination) {   
    (*destination)->data = NULL;
    (*destination)->next = NULL;
}

void destroy_linked_list(linked_list_node_t** head) {

    while ((*head) != NULL) {
        linked_list_node_t* current = *head;
        (*head) = (*head) -> next;
        free(current);
    }
}

void get_element_of_array_of_linked_list_ptrs(linked_list_node_t** array, int index, linked_list_node_t** destination){
    *destination = array[index];
}

void set_element_of_array_of_linked_list_ptrs(linked_list_node_t** array, int index,linked_list_node_t**  head) {
    *(array + index) = *head;
}

void destroy_array_of_linked_list_ptrs(linked_list_node_t*** array) {
    free(*array);
}

void resize_array_of_linked_list_ptrs(linked_list_node_t*** destination, linked_list_node_t*** array, int size, int new_size){
    *destination = realloc(*destination, new_size * sizeof(linked_list_node_t*));
    for (int i = 5; i < 10; i++) {
        (*destination)[i] = &(*array)[i-5];
    }
}

typedef struct song_t {
    const char* name;
    float duration;
} song_t;

void create_song(song_t* destination, const char* name, float duration) {
    destination->name = name;
    destination->duration = duration;
}

void add_to_linked_list(linked_list_node_t** head, const void* data) {
    linked_list_node_t *current = (linked_list_node_t*)calloc(1, sizeof(linked_list_node_t));
    current->data = data;
    current->next = NULL;
    if ((*head)->data == NULL) {
        *head = current;
    }
    else {
        linked_list_node_t* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = current;
    }
}

void remove_from_linked_list(linked_list_node_t** destination, linked_list_node_t** head, const void* data) {

    linked_list_node_t* current = *head;
    linked_list_node_t* previous = NULL;

    while (current != NULL && current->data != data) {
        previous = current;
        current = current->next;
    }

    if (current != NULL) {
        if (previous != NULL) {
            previous->next = current->next;
        } else {
            *head = current->next;
        }
    }
    *destination = *head;
    free(current);
}

linked_list_node_t** array_of_playlist_ptrs = NULL;
linked_list_node_t** array_of_playlist_ptrs2 = NULL;

int main(void){
    create_array_of_linked_list_ptrs(&array_of_playlist_ptrs, 5);
    for (int i = 0; i < 5; i++) {
        linked_list_node_t* playlist = calloc(1, sizeof(linked_list_node_t));
        create_link_list(&playlist);
        set_element_of_array_of_linked_list_ptrs(array_of_playlist_ptrs, i, &playlist);
    }

    create_array_of_linked_list_ptrs(&array_of_playlist_ptrs2, 5);
    for (int k = 0; k < 5; k++) {
        linked_list_node_t* playlist2 = calloc(1, sizeof(linked_list_node_t));
        create_link_list(&playlist2);
        set_element_of_array_of_linked_list_ptrs(array_of_playlist_ptrs, k, &playlist2);
    }

    resize_array_of_linked_list_ptrs(&array_of_playlist_ptrs, &array_of_playlist_ptrs2, 5, 10);
    const char* songs[40] = {
        "Stairway to Heaven", "Bohemian Rhapsody", "Imagine", "Bu Şehir Beni Boğuyor",
        "American Pie", "Let It Be", "Yesterday", "Brown Sugar",
        "Layla", "Sweet Child o' Mine", "Rocket Man", "Angie",
        "Piano Man", "Lola", "Born to Run", "American Woman",
        "Roxanne", "Go Your Own Way", "Smoke on the Water", "Brown Eyed Girl",
        "Lean on Me", "More Than a Feeling", "Stayin' Alive", "Dreams",
        "I Want to Hold Your Hand", "Maggie May", "Let's Get It On", "Hotel California",
        "Bennie and the Jets", "Reelin' in the Years", "Boogie Wonderland", "You're So Vain",
        "Dancing Queen", "Margaritaville", "Crazy Little Thing Called Love", "Superstition",
        "Hotel California", "Sweet Home Alabama", "Rocket Man", "What a Life"
    };

    float duration[40];
    for (int z = 0; z < 40; z++) {
        duration[z] = 10 * ((float)rand() / RAND_MAX);
    }

    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < 4; k++) {
            song_t* song = (song_t*)calloc(1, sizeof(song_t));
            create_song(song, songs[4*i+k], duration[4*i+k]);
            add_to_linked_list(&array_of_playlist_ptrs[i], (const void*)song);
        }
    }

    for(int i = 0; i < 10; i++){

        remove_from_linked_list(&array_of_playlist_ptrs[i], &(array_of_playlist_ptrs[i]), (const void*)(array_of_playlist_ptrs[i] -> next -> data));
        
    }

    for(int i = 0; i < 10; i++){
        linked_list_node_t* playlist_temp;
        get_element_of_array_of_linked_list_ptrs(array_of_playlist_ptrs, i, &playlist_temp);
        printf("Playlist #%d\n", i);
        while (playlist_temp != NULL) {
            printf("    Name: %s, Duration: %f\n", ((song_t*)(playlist_temp -> data)) -> name, ((song_t*)(playlist_temp -> data)) -> duration);
            playlist_temp = playlist_temp -> next;
        }
    }

    for(int i = 0; i < 10; i++){
        destroy_linked_list((array_of_playlist_ptrs + i));
    }

    destroy_array_of_linked_list_ptrs(&array_of_playlist_ptrs);
    return 0;
}