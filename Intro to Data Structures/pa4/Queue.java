//Galen Turoci
//gturoci
//Class CMPS 12B
//February 20th, 2018
//The Queue ADT implements the Queue interface and is called as part of the Simulation program
//Queue.java

public class Queue implements QueueInterface {
	
	//private inner Node class
	private class Node {
		Object newItem;
		Node next;

		Node(Object nI) {
			newItem = nI;
			next = null;
		}
	}

	//Fields for the Queue class
	private Node head;		//reference to first Node in the Queue
	private Node tail;		//reference to last Node in the Queue
	private int numItems;	//number of items in the Queue
	
	//Queue()
	//Constructor for the Queue class
	public Queue() {
		head = null;
		numItems = 0;
	}
	
	//Helper Op-------------------------------------------------------------
	
	private Node findItem(Object item) {
		Node N = head;
		while (N != null && !item.equals(N.newItem)) {
			N = N.next;
			if (N == null)
				return null;
		}
		return N;
	}
	
	//ADT Ops---------------------------------------------------------------
	
	// isEmpty()
	// pre: none
	// post: returns true if this Queue is empty, false otherwise
	public boolean isEmpty() {
		return (numItems == 0);
	}

	// length()
	// pre: none
	// post: returns the length of this Queue.
	public int length() {
		return numItems;
	}

	// enqueue()
	// adds newItem to back of this Queue
	// pre: none
	// post: !isEmpty()
	public void enqueue(Object newItem) {
        if (isEmpty()) {
			head = new Node(newItem);
			tail = head;
        } else {
			tail.next = new Node(newItem);
			tail = tail.next;
		}
		numItems++;
	}

	// dequeue()
	// deletes and returns item from front of this Queue
	// pre: !isEmpty()
	// post: this Queue will have one fewer element
	public Object dequeue() throws QueueEmptyException {
		if (head == null)
			throw new QueueEmptyException("Called dequeue() on an empty Queue.");
		Node N = head;
		Node X = N.next;
		head = head.next;
		N.next = null;
		numItems--;
		return N;
	}

	// peek()
	// pre: !isEmpty()
	// post: returns item at front of Queue
	public Object peek() throws QueueEmptyException {
		Node N = head;
		if (N == null)
			throw new QueueEmptyException("Called peek() on an empty Queue.");
		else
			return N.newItem;
	}

	// dequeueAll()
	// sets this Queue to the empty state
	// pre: !isEmpty()
	// post: isEmpty()
	public void dequeueAll() throws QueueEmptyException {
		if (head == null)
			throw new QueueEmptyException("Called dequeueAll() on an empty Queue.");
		head = null;
		numItems = 0;
	}

	// toString()
	// overrides Object's toString() method
	public String toString() {
		StringBuffer sb = new StringBuffer();
		
		for (Node N=head; N!=null; N=N.next) { //MODIFY TO BE RECURSIVE LATER
			sb.append(N.newItem);
			sb.append(" ");
		}
		return new String(sb);
	}
	
}
