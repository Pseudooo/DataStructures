package me.Pseudo.Queues;

import java.util.List;
import java.util.ArrayList;

/**
 * CircularBuffer that will contain n items at any given tim.
 * After n items have been pushed n-1th item will be overwritten
 * with n-2th item.
 * @author Pseudo
 * @param <T> The type of data in the buffer
 */
public class CircularQueue<T> {
	
	private int head = 0, tail = 0;

	private final ArrayList<T> content;
	
	/**
	 * Create a new CircularBuffer
	 * @param size of the buffer
	 */
	public CircularQueue(int size) {
		// Instantiate array of desired size
		this.content = new ArrayList<T>(size);
		for(int i = 0; i < size; i++) {
			this.content.add(null);
		}
	}
	
	/**
	 * Push an item to the front of the queue
	 * @param item to push
	 */
	public void push(T item) {
		
		if(this.head == this.tail && this.content.get(this.head) == null) {
			// Edge case of empty buffer
			this.content.set(this.head, item);
			return;
		}
		
		// Shift head modulo for wrapping
		this.head = (this.head + 1) % this.content.size();
		this.content.set(this.head, item);
		
		// Shift tail if required
		if(this.head == this.tail) {
			this.tail = (this.tail + 1) % this.content.size();
		}
		
	}
	
	/**
	 * Get an item indexed from the head
	 * @param n index from head
	 * @return element
	 */
	public T getItem(int n) {
		int i = this.head - n;
		if(i < 0) i += this.content.size();
		return this.content.get(i);
	}
	
	/**
	 * Get a certain quantity of contents
	 * @param n Offset from the start
	 * @param k Quantity of items to get
	 * @return List of items
	 */
	public List<T> page(int n, int k) {
		
		// Instantiate list
		List<T> page = new ArrayList<T>(k);
		
		// Index offset from head by n
		int i = this.head - n;
		
		// Iterate through k times populating page
		for(int j = 0; j < k; j++, i--) {
			
			// Handle wrapping of content
			if(i < 0) i += this.content.size();
			
			// Populate jth element
			page.add(this.content.get(i));
			
		}
		
		return page;
		
	}
	
	public List<T> asList() {
		return this.page(0, this.size());
	}
	
	/**
	 * Get current size of the buffer
	 * @return size
	 */
	public int size() {
		
		int diff = this.head - this.tail;
		
		// Diff = 0 means head and tail in same place
		if(diff == 0) {
			if(this.content.get(this.head) == null) {
				// If head is null then empty
				return 0;
			}else return 1; // Otherwise one item
		}
		
		if(diff < 0) {
			// Diff being negative means wrapping
			diff+=this.content.size();
		}
		
		return diff + 1;
		
	}
	
}
