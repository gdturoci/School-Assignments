//Galen Turoci
//gturoci
//Class CMPS 12B
//January 30th, 2018
//This exception is run whenever the program detects the user has attempted
//to enter a (key, value) pair using a key that has already been used.
//DuplicateKeyException.java

public class DuplicateKeyException extends RuntimeException {
	public DuplicateKeyException (String s) {
		super(s);
	}
}