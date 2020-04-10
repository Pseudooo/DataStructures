#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include "ArrayList.h"

// Helper function definitions
int al_grow_arr(ArrayList* arr, const int extSize, const int offset);

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
   -1 - Invalid Offset
*/
int al_grow_arr(ArrayList* arr, const int extSize, const int offset)
{

	if(offset > extSize)
		return -1;

	// Grow array
	arr->length += extSize;

	if(arr->length * arr->elem_size > arr->alloc)
	{
		// Realloc needed (Stole from cython teehee)
		int newAllocSize = (arr->alloc << 3) + (arr->alloc < 9 ? 3 : 6);

		void* newArr = malloc(newAllocSize);
		if(newArr == NULL)
		{
			// Malloc failed, reset length
			arr->length -= extSize;
			return 0;
		}
		
		// Malloc was success, copy old array over with offset
		memcpy(newArr + (offset*arr->elem_size), arr->arr, arr->alloc);
		free(arr->arr); // Free old array
		arr->alloc = newAllocSize;
		arr->arr = newArr; // Assign pointer to new array
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

	if(!al_grow_arr(arr, 1, 0))
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

	// Grow array with an offset from beginning
	if(!al_grow_arr(arr, 1, 1))
		return 0;

	al_set(arr, 0, data);
	return 1;

}

/**
	Removes value at the front of the array
	1 - Success
	0 - Empty Array Failure
   -1 - Failed to allocate space in mem
*/
int al_pop(ArrayList* arr)
{

	if(arr->length == 0)
		return 0;

	void* buff = malloc(arr->elem_size);
	if(buff == NULL) 
		return -1;

	// Shift elements to front
	for(int i = 0; i < arr->length - 1; i++)
		al_get(arr, i+1, arr->arr + (arr->elem_size*i));

	arr->length--;
	return 1;

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