//Galen Turoci
//gturoci
//Class CMPS 12B
//February 8th, 2018
//Dictionary.java takes a collection of (key, value) pairs and stores them,
//then implements the DictionaryInterface in order to allow the user to
//manipulate those pairs
//Dictionary.java

public class Dictionary implements DictionaryInterface {
	
	//private inner Node class
	private class Node {
		String key;
		String value;
		Node next;

		Node(String k, String v) {
			key = k;
			value = v;
			next = null;
		}
	}

	//Fields for the Dictionary class
	private Node head;		//reference to first Node in List
	private Node tail;		//reference to the last Node in the List
	private int numItems;	//number of items in this Dictionary
	
	//Dictionary()
	//constructor for the Dictionary class
	public Dictionary() {
		head = null;
		numItems = 0;
	}

	//private helper function -------------------------------------------------

	//findKey()
	//returns a reference to the Node at position key in this Dictionary
	private Node findKey(String key) {
		Node N = head;
		while (N != null && !key.equals(N.key)) {
			N = N.next;
			if (N == null)
				return null;
		}
		return N;
	}

	//ADT operations ----------------------------------------------------------

	//isEmpty()
	//pre: none
	//post: returns true if this Dictionary is empty, false otherwise
	public boolean isEmpty() {
		return (numItems == 0);
	}

	//size()
	//pre: none
	//post: returns the number of elements in this Dictionary
	public int size() {
		return numItems;
	}

	//lookup()
	//pre: 1 <= key <= size()
	//post: returns value at position key in this Dictionary
	public String lookup(String key) {
		Node N = head;
		while (N != null && !key.equals(N.key))
			N = N.next;
		if (N == null)
			return null;
		else
			return N.value;
	}

	//insert()
	//inserts new value into this Dictionary at position key
	//pre: key is not already in Dictionary
	//post: !isEmpty()
	public void insert(String key, String value) throws DuplicateKeyException {
		Node N = head;
		N = findKey(key);
		if (N != null)
				throw new DuplicateKeyException("Cannot insert duplicate keys.");
		if (isEmpty())
			head = new Node(key, value);
		else {
			N = head;
			while (N.next != null)
				N = N.next;
			N.next = new Node(key, value);
			tail = N.next; //sets tail to the last created Node, which is also the last Node in the list
		}
		numItems++;
	}

	//delete()
	//deletes given key from this Dictionary
	//pre: key is in Dictionary
	//post: there is one less (key, value) pair in the Dictionary
	public void delete(String key) throws KeyNotFoundException {
		Node N = findKey(key);
		if (N == null)
			throw new KeyNotFoundException("Cannot delete non-existent key.");
		if (numItems == 1)
			head = head.next;
		else if (head.key.equals(key))
			head = head.next;
		else {
			N = head;
			while (!key.equals(N.next.key))
				N = N.next;
			N.next = N.next.next;
		}
		numItems--;
	}

	//makeEmpty()
	//pre: none
	//post: isEmpty()
	public void makeEmpty() {
		head = null;
		numItems = 0;
	}

	//toString()
	//pre: none
	//post:  prints current state to stdout
	//Overrides Object's toString() method
	public String toString() {
		StringBuffer sb = new StringBuffer();
		
		for (Node N = head; N!=null; N=N.next) {
			sb.append(N.key).append(" ");
			sb.append(N.value);
			sb.append("\n");
		}
		return new String(sb);
	}

}
