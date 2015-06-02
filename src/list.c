#include "list.h"
/*********************/
/* Static functions. */
/*********************/
static Link *createLink(void *data){
    Link *link = (Link*)malloc(sizeof(Link));
    if(link == NULL){
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    link->data = data;
    link->next = NULL;
    return link;
}
/*************************/
/* Function definitions. */
/*************************/
LinkedList *createLinkedList(){
    LinkedList *returnList = (LinkedList*)malloc(sizeof(LinkedList));
    if(returnList == NULL){
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    returnList->head = NULL;
    returnList->tail = NULL;
    return returnList;
}
void destroyLinkedList(LinkedList *list){
    Link *link = list->head;
    while(link != NULL){
        Link *next = link->next;
        free(link);
        link = next;
    }
    free(list);
}
void pushData(LinkedList *list, void *data){

    Link *new_link = createLink(data);

    /* If the list is empty. */
    if(list->head == NULL){
        list->head = new_link;
        list->tail = new_link;
    }
    /* If the list has data in it. */
    else{
        list->tail->next = new_link;
        list->tail       = new_link;
    }
}
void popData(LinkedList *list, void *data){
    Link *prev = NULL;
    Link *link = list->head;
    while(link->data != data){
        prev = link;
        link = link->next;
    }
    if(link == list->head){
        list->head = link->next;
    }else{
        prev->next = link->next;
    }
    if(link == list->tail){
        list->tail = NULL;
    }
    free(link);
}
