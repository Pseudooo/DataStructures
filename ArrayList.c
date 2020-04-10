#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include "ArrayList.h"

// Helper function definitions
int al_grow_arr(ArrayList* arr, const int extSize);

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
	Grow the internal array by n elements.
	1 - Success
	0 - Realloc failure
*/
int al_grow_arr(ArrayList* arr, const int extSize)
{

	// Grow array
	arr->length += extSize;

	if(arr->length * arr->elem_size > arr->alloc)
	{
		// Realloc needed (Stole from cython teehee)
		int newAllocSize = (arr->alloc << 3) + (arr->alloc < 9 ? 3 : 6);
		int oldAllocSize = arr->alloc;
		arr->alloc = newAllocSize;

		void* newArr = realloc(arr->arr, arr->alloc);
		if(newArr == NULL)
		{
			// Realloc failed, reset internal alloc and length
			arr->length -= extSize;
			arr->alloc = oldAllocSize;

			return 0;
		}

	}
	return 1;

}

/**
	Adds a new value onto the end of the array
	1 - Success
	0 - Failed to reallocate array (No changes made)
*/
int al_append(ArrayList* arr, void* data)
{

	if(!al_grow_arr(arr, 1))
		return 0;

	// Set the last element to be the given value
	return al_set(arr, arr->length - 1, data);

}

/**
	Removes the last element of the array
	1 - Success
	0 - Empty Array Failure
*/
int al_prepend(ArrayList* arr)
{
	
	if(arr->length == 0)
		return 0;

	arr->length--;
	return 1;

}

/**
	Adds a new value to the front of the array
	1 - Success
	0 - Failed to realloc array
*/
int al_push(ArrayList* arr, void* data)
{
	
}

/**
	Removes value at the front of the array
	1 - Success
	0 - Empty Array Failure
*/
int al_pop(ArrayList* arr)
{

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

/**
	Will clear the ArrayList from memory
*/
void al_dispose(ArrayList* arr)
{
	free(arr->arr);
	free(arr);
}