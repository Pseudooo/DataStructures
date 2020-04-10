#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct {
    int i;
    int j;
} Vector;

typedef struct {
	int size, alloc;
	void* arr;
} ArrayList;

#endif 