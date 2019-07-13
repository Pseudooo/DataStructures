# Data Structures

The following is a collection of data structures that I've found myself needing to make for various projects I've undertaken, all of the files in question are free to use for anyone.

***

## Contents
 - [CircularQueue](#Circular-Queue)
 
***

## Circular Queue
[Code](https://github.com/Pseudooo/DataStructures/blob/master/DataStructures/src/me/Pseudo/Queues/CircularQueue.java)
 - push(Object object) ~ Adds a new item to the front of the queue, shifting all others back by one. If length is at max then oldest item is discarded. O(1)
 - get(int n) ~ Returns the nth most recent item. O(1)
 - page(int n, int k) ~ Returns a list of length k of indexes from n to n+k. O(k)
 - asArray() ~ returns a list of n items in queue O(n)
 - size() ~ Returns integer of how many items are in the queue O(1)
