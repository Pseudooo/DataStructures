#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct {
	size_t elem_size, alloc;
	int length;
	void* arr;
} ArrayList;

ArrayList* al_initsize(const size_t elem_size, const size_t init_size);
ArrayList* al_init(const size_t elem_size);

int al_append(ArrayList* arr, void* data);
int al_prepend(ArrayList* arr);

int al_push(ArrayList* arr, void* data);
int al_pop(ArrayList* arr);

int al_set(ArrayList* arr, int index, void* data);
int al_get(ArrayList* arr, int index, void* dest);

void al_dispose(ArrayList* arr);

#endif 