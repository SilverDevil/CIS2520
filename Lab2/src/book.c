#include <stdio.h>
#include <stdlib.h>
#include "book.h"

Book* createBook(char * title, double price){
    Book* b = malloc(sizeof(Book));
    b->price  = price;
    b->name = title;
    return b;
}

char* getName(Book *b){
	return b->name;
}

double getPrice(Book * b){ 
    return b->price;
}

void printBook(void * book){
    Book *b = (Book *) book;
    printf("%s : %.3f\n", getName(b), getPrice(b) );
}