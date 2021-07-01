//Galen Turoci
//gturoci
//Class CMPS 12M
//March 7th, 2018
//Dictionary.java is a Binary Search Tree ADT that takes two strings,
//a key and a value, and places them in a Binary Search Tree.
//Dictionary.java

public class Dictionary implements DictionaryInterface {

	// Node
	private class Node {
		String key;
		String value;
		Node left;
		Node right;
		
		Node(String k, String v) {
			key = k;
			value = v;
			left = null;
			right = null;
		}
	}


	private Node head; //Reference to the first item
	private int numItems; //Number of items in the Dictionary

	//Dictionary()
	//constructor for the Dictionary class
	public Dictionary() {
		head = null;
		numItems = 0;
	}

	//findKey()
	//returns a reference to the Node at position key in this Dictionary
	//NEEDS TESTING
	private Node findKey(Node N, String key) {
		if (N == null || key.equals(N.key))
			return N;
		if (key.compareTo(N.key)<0)
			return findKey(N.left, key);
		else
			return findKey(N.right, key);
	}
	
	private Node findParent(Node N, Node M) {
		Node P = null;
		if (N != M) {
			P = M;
			while (P.right != N && P.left != N) {
				if (P.key.compareTo(N.key)<0)
					P = P.left;
				else
					P = P.right;
			}
		}
		return P;
	}
	
	private Node findLeftmost(Node N) {
		Node X = N;
		if (X != null) {
			while (N.left != null)
				N = N.left;
		}
		return N;
	}
	
	private StringBuffer printInOrder(Node N, StringBuffer s) {
		if (N != null) {
			printInOrder(N.left, s);
			s.append(N.key).append(" ");
			s.append(N.value);
			s.append("\n");
			printInOrder(N.right, s);
		}
		return s;
	}

	// public functions -----------------------------------------------------------

	// isEmpty()
	// returns true if Dictionary is empty, false otherwise
	// pre: none
	public boolean isEmpty() {
		return (numItems == 0);
	}

	// size()
	// returns the number of (key, value) pairs in this Dictionary
	// pre: none
	public int size() {
		return numItems;
	}

	// lookup()
	// returns value associated with the given key, or null reference if no such key exists
	// pre: none
	//NEEDS TESTING
	public String lookup(String key) {
		Node N = head;
		N = findKey(N, key);
		if (N == null)
			return null;
		else
			return N.value;
	}

	// insert()
	// inserts new (key,value) pair into D
	// pre: lookup(D, k)==NULL
	//NOT DONE - FIX
	public void insert(String key, String value) throws DuplicateKeyException {
		Node N = head;
		Node A, B;
		N = findKey(N, key);
		if (N != null)
				throw new DuplicateKeyException("Cannot insert duplicate keys.");
		if (isEmpty())
			head = new Node(key, value);
		else {
			N = new Node (key, value);
			B = null;
			A = head;
			while (A != null) {
				B = A;
				if (key.compareTo(A.key)<0)
					A = A.left;
				else
					A = A.right;
			}
			if (key.compareTo(B.key)<0)
				B.left = N;
			else
				B.right = N;
		}
		numItems++;
	}

	// delete()
	// deletes pair with the key k
	// pre: lookup(D, k)!=NULL
	//NEEDS TESTING
	public void delete(String key) throws KeyNotFoundException {
		Node N = head;
		Node P, S;
		N = findKey(N, key);
		if (N == null)
			throw new KeyNotFoundException("Cannot delete non-existent key.");
		if (N.left == null && N.right == null) {
			if (numItems == 1)
				head = null;
			else {
				P = findParent(N, head);
				if (P.right == N)
					P.right = null;
				else
					P.left = null;
			}
		} else if (N.right == null) {
			if (N==head)
				head = N.left;
			else {
				P = findParent(N, head);
				if (P.right == N)
					P.right = N.left;
				else
					P.left = N.left;
			}
		} else if (N.left == null) {
			if (N == head)
				head = N.right;
			else {
				P = findParent(N, head);
				if (P.right == N)
					P.right = N.right;
				else
					P.left = N.right;
			}
		} else {
			S = findLeftmost(N.right);
			N.key = S.key;
			N.value = S.value;
			P = findParent(S, N);
			if (P.right == S)
				P.right = S.right;
			else
				P.left = S.right;
		}
		numItems--;
	}

	// makeEmpty()
	// Makes this Dictionary empty
	// pre: none
	public void makeEmpty() {
		head = null;
		numItems = 0;
	}

	// printDictionary()
	// pre: none
	// prints a text representation of D to the file pointed to by out
	//NOT DONE - FIX
	public String toString() {
		StringBuffer s = new StringBuffer();
		return new String(printInOrder(head, s));
	}
}
