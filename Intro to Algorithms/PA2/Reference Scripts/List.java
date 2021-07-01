//Galen Turoci
//gturoci
//pa3

class List {

	private class Node {
		// Fields
		Object data;
		Node next;
		Node prev;
      
		// Constructor
		Node(Object data) { 
		this.data = data;
		next = null; 
		prev = null;
		}
      
		// toString():  overrides Object's toString() method
		public String toString() { 
			return String.valueOf(data); 
		}
      
		// equals(): overrides Object's equals() method
		public boolean equals(Object x) {
			boolean eq = false;
			Node that;
			if (x instanceof Node) {
				that = (Node) x;
				eq = ((this.data).equals(that.data));
			}
			return eq;
		}
	}

	// Fields
	private Node front;
	private Node back;
	private Node cursor;
	private int length;
	private int index;

	// Constructor ------------------------------------------------------------
	List() { 
		front = back = cursor = null; 
		length = 0;
		index = -1;
	}


	//Access Functions --------------------------------------------------------

	//length()
	//Returns the number of elements in this List.
	int length() { 
		return length; 
	}
	
	//index()
	//Returns the index of the cursor element if it is defined
	//returns -1 otherwise
	int index() {
		return index;
	}

	//front() 
	//Returns front element.
	//Pre: length()>0
	Object front() {
		if (this.length <= 0)
			throw new RuntimeException("List Error: front() called on empty List");
		return front.data;	
	}
	
	//back()
	//Returns back element
	//Pre: length()>0
	Object back() {
		if (this.length <= 0)
			throw new RuntimeException("List Error: back() called on empty List");
		return back.data;
	}
	
	//get()
	//Returns cursor element
	//Pre: length()>0, index()>=0
	Object get() {
		if (this.length <= 0 || this.index() < 0)
			throw new RuntimeException("List Error: get() called on an empty List");
		if (cursor == null)
			throw new RuntimeException("List Error: get() called on a null cursor");
		return cursor.data;
	}
	
	//equals(Object x)
	//Returns true if and only if this Object and x are the same
	//integer sequence. The states of the cursors in the two Lists
	//are not used in determining equality
	//overrides Object's equals() method
	public boolean equals(Object x) {
		boolean eq  = false;
		List that;
		Node Y, Z;
		if (x instanceof List) {
			that = (List) x;
			eq = (this.length == that.length);
			Y = this.front;
			Z = that.front;
			while (eq && Y != null) {
				eq = (Y.equals(Z));
				Y = Y.next;
				Z = Z.next;
			}
		}
		return eq;
	}

	// Manipulation Procedures -------------------------------------------------
	
	//clear()
	//Resets this List to its original empty state
	void clear() {
		while (this.length > 0)
			deleteFront();
	}
	
	//moveFront()
	//If List is non-empty, places the cursor under the front element
	//Does nothing otherwise
	void moveFront() {
		if (this.length > 0) {
			cursor = front;
			index = 0;
		}
	}
	
	//moveBack()
	//If List is non-empty, places the cursor under the back element,
	//otherwise does nothing.
	void moveBack() {
		if (this.length > 0) {
			cursor = back;
			index = length - 1;
		}
	}
	
	//movePrev()
	//If cursor is defined and not at front, moves cursor one step toward
	//front of this List, if cursor is defined and at front, cursor becomes
	//undefined, if cursor is undefined does nothing.
	void movePrev() {
		if (cursor == front)
			cursor = null;
		else
			cursor = cursor.prev;
		index--;
	}
	
	//moveNext()
	//If cursor is defined and not at back, moves cursor one step toward
	//back of this List, if cursor is defined and at back, cursor becomes
	//undefined, if cursor is undefined does nothing.
	void moveNext() {
		if (cursor == back) {
			cursor = null;
			index = -1;
		}
		else {
			cursor = cursor.next;
			index++;
		}
	}
	
	//prepend(Object data)
	//Prepends data to the front of this List.
	void prepend(Object data) {
		Node N = new Node(data);
		if (this.length == 0)
			front = back = N;
		else { 
			front.prev = N;
			N.next = front;
			front = N;
		}
		if (cursor != null)
			index++;
		length++;
	}

	//append(Object data)
	//Appends data to back of this List.
	void append(Object data) {
		Node N = new Node(data);
		if (this.length == 0)
			front = back = N;
		else { 
			back.next = N;
			N.prev = back;
			back = N; 
		}
		length++;
	}
	
	//insertBefore(Object data)
	//Insert a new element before the cursor
	//Pre: length()>0, index()>=0
	void insertBefore(Object data) {
		if (this.length <= 0 || this.index() < 0)
			throw new RuntimeException("List Error: insertBefore() called on an empty List");
		else if (cursor == front)
			prepend(data);
		else {
			Node N = new Node(data);
			Node M = cursor.prev;
			cursor.prev = N;
			N.prev = M;
			M.next = N;
			N.next = cursor;
			length++;
			index++;
		}
	}
	
	//insertAfter(Object data)
	//Inster a new element after the cursor
	//Pre: length()>0, index()>=0
	void insertAfter(Object data) {
		if (this.length <= 0 || this.index() < 0)
			throw new RuntimeException("List Error: insertAfter() called on an empty List");
		else if (cursor == back)
			append(data);
		else {
			Node N = new Node(data);
			Node M = cursor.next;
			cursor.next = N;
			N.next = M;
			M.prev = N;
			N.prev = cursor; 
			length++;
		}
	}
	
	//deleteFront()
	//Deletes front element from this List.
	//Pre: length()>0
	void deleteFront() {
		if (this.length <= 0)
			throw new RuntimeException("List Error: deleteFront() called on empty List");
		if (this.length == 1) {
			front = back = cursor = null;
			index = -1;
		} else {
			front = front.next;
			index--;
		}
		length--;
	}
	
	//deleteBack()
	//Deletes the back element from this List
	//Pre: length()>0
	void deleteBack(){
		if (this.length <= 0)
			throw new RuntimeException("List Error: deleteBack() called on empty List");
		if (this.length == 1) {
			back = front = cursor = null;
			index = -1;
		} else {
			if (cursor == back) {
				cursor = null;
				index = -1;
			}
			back = back.prev;
		}
		length--;
	}
	
	//delete()
	//Deletes the cursor element, making cursor undefined
	//Pre: length()>0, index()>=0
	void delete() {
		if (this.length <= 0 || this.index() < 0)
			throw new RuntimeException("List Error: delete() called on an empty List");
		if (cursor == back)
			deleteBack();
		else if (cursor == front)
			deleteFront();
		else {
			Node N = cursor.next;
			cursor = cursor.prev;
			cursor.next = N;
			index = -1;
			length--;
		}
	}

	// Other Functions ---------------------------------------------------------

	// toString()
	// Overides Object's toString() method.
	public String toString(){
		StringBuffer sb = new StringBuffer();
		Node N = front;
		while (N != null) {
			sb.append(N.toString());
			sb.append(" ");
			N = N.next;
		}
		return new String(sb);
	}
}