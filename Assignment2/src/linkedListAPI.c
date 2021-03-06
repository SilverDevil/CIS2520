#include <stdio.h>
#include <stdlib.h>
#include "linkedListAPI.h"


List *initializeList(void (*printFunction) (void * toBePrinted), void (*deleteFunction)(void *toBeDeleted), int (*compareFunction)(const void *first, const void *second)){
    List *l = malloc(sizeof(List));
    
    if (l != NULL) {
        l->head = NULL;
        l->tail = NULL;
        l->deleteNode = deleteFunction;
        l->compare = compareFunction;
        l->printNode = printFunction;
    }

    return l;
}


Node *initializeNode(void *data, int priority){
    Node *n = malloc(sizeof(Node));
    
    if (n != NULL) {
        n->data = data;
        n->previous = NULL;
        n->next = NULL;
        n->priority = priority;
    }
    
    return n;
}


void insertFront(List *list, void *toBeAdded){
    Node *n = initializeNode(toBeAdded, 1);
    if (list->head == NULL && list->tail == NULL) {
        list->head = n;
        list->tail = n;
    } else {
        Node *temp = list->head;
        temp->previous = n;
        n->next = temp;
        list->head = n;
    }
}


void insertBack(List *list, void *toBeAdded){
    Node *n = initializeNode(toBeAdded, 1);
    if (list->head == NULL && list->tail == NULL) {
        list->head = n;
        list->tail = n;
    } else {
        Node *temp = list->tail;
        temp->next = n;
        n->previous = temp;
        list->tail = n;
    }
}


void deleteList(List *list){
    Node *cur = list->head;
    while (cur != NULL) {
        list->head = cur->next;
        list->deleteNode(cur->data);
        free(cur);
        cur = list->head;
    }
    free(list);
}


void insertSorted(List *list, void *toBeAdded, int priority){
    Node *n = initializeNode(toBeAdded, priority);
    if (list->head == NULL && list->tail == NULL) {
        list->head = n;
        list->tail = n;
    } else {
        Node *cur = list->head;
        Node *pos = NULL;
        while (cur != NULL && priority < cur->priority){
            pos = cur;
            cur = cur->next;
        }
        if(pos == NULL){
            pos = list->head;
            n->next = pos;
            pos->previous = n;
            list->head = n;
        } else if (cur == NULL){
            pos = list->tail;
            n->previous = pos;
            pos->next = n;
            list->tail = n;
        }else{
            pos->next = n;
            n->next = cur;
            n->previous = pos;
            cur->previous = n;
        }
    }
}


void *getFromFront(List *list){
    if(list != NULL){
        if(list->head != NULL){
            return list->head->data;
        }
    }

    return NULL;
}


void *getFromBack(List *list){
    if(list != NULL){
        Node *t = list->head;
        while(t->next != NULL){
            t = t->next;
        }
        return t->data;
    }

    return NULL;
}


void printForward(List *list){
    if(list != NULL){
        if(list->head == NULL){
            printf("List is empty.");
        }else{
            Node *cur = list->head;
            while(cur != NULL){
                list->printNode(cur->data);
                cur = cur->next;
            }
        }
    }
}


void printBackwards(List *list){
    if(list != NULL){
        if(list->tail == NULL){
            printf("List is empty.");
        }else{
            Node *cur = list->tail;
            while(cur != NULL){
                list->printNode(cur->data);
                cur = cur->previous;
            }
        }
    }
}


void *deleteNodeFromList(List *list, void *toBeDeleted){
    if(list->head == NULL || toBeDeleted == NULL){
        return NULL;
    }

    Node *cur = list->head;
    
    while(cur != NULL){
        if(list->compare(cur->data, toBeDeleted) == 0){
            //list->deleteNode(cur->data);
            
            if(cur->previous == NULL && cur->next == NULL){
                list->head = NULL;
                list->tail = NULL;
            }else if(cur->previous == NULL){
                cur->next->previous = NULL;
                list->head = cur->next;
            }else if(cur->next == NULL){
                cur->previous->next = NULL;
                list->tail = cur->previous;
            }else{
                cur->next->previous = cur->previous;
                cur->previous->next = cur->next;
            }
            
            void *data = cur->data;
            cur->data = NULL;
            free(cur);

            return data;
        }
        cur = cur->next;
    }

    return NULL;

}

int isEmpty(List *list){
    if(list->head == NULL){
        return 1;
    }
    return 0;
}


void changePriority(List *list){
    
    Node *cur = list->head;
    int count = 0;
    int curPrior = 1;
    while(cur != NULL){
        if(curPrior != cur->priority){
            count = 0;
            curPrior = cur->priority;
        }
        if(cur->priority >= 3 && count < 3){
            int tempPrior = cur->priority - 1;
            void *data = deleteNodeFromList(list, cur->data);
            insertSorted(list, data, tempPrior);
            count++;
        }
        cur = cur->next;
    }
}