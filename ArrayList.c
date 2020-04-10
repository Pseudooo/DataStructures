#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include "ArrayList.h"

// * * * * * * * * * * * * CONSTRUCTORS

/**
	Will initialize an ArrayList and return its pointer
	Will return null if any allocation fails internally
*/
ArrayList* al_initsize(const size_t elem_size, const size_t init_size)
{

	// Attempt alloc 
	ArrayList* arr = malloc(sizeof(ArrayList));
	if(arr == NULL) return NULL;

	arr->elem_size = elem_size;
	arr->alloc = elem_size * init_size; // init capacity of ten items
	arr->length = 0; // init empty

	// Attempt to allocate internal array
	arr->arr = malloc(arr->alloc);
	if(arr->arr == NULL)
	{
		// Clear ArrayList on failure
		free(arr);
		return NULL;
	}

	// Return pointer
	return arr;

}

ArrayList* al_init(const size_t elem_size)
{
	return al_initsize(elem_size, 10);
}

/**
	Adds a new value onto the end of the array
	1 - Success
	0 - Failed to reallocate array (No changes made)
*/
int al_append(ArrayList* arr, void* data)
{

	// Increase length and check if a realloc is needed
	if(++arr->length * arr->elem_size > arr->alloc)
	{
		// Calculate new allocated size (Copied from cython)
		int newAlloc = (arr->alloc << 3) + (arr->alloc < 9 ? 3 : 6);
		arr->alloc = newAlloc;

		// Attempt realloc
		void* newArr = realloc(arr->arr, arr->alloc);
		if(newArr == NULL)
			return 0; // Realloc failed

		// Assign array
		arr->arr = newArr;
	}

	// Set the last element to be the given value
	return al_set(arr, arr->length - 1, data);

}

/**
	Set a specific index within the defined array
	1 - Success
	0 - Index Out Of Bounds
*/
int al_set(ArrayList* arr, int index, void* data)
{
	
	if(index >= arr->length)
		return 0;

	memcpy(arr->arr + (index * arr->elem_size), data, arr->elem_size);
	return 1;
	
}

/**
	Get the value at a specific index within the defined array
	1 - Success
	0 - Index Out Of Bounds
*/
int al_get(ArrayList* arr, int index, void* dest)
{

	if(index >= arr->length)
		return 0;

	memcpy(dest, arr->arr + (index * arr->elem_size), arr->elem_size);
	return 1;

}