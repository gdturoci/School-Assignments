//Galen Turoci
//gturoci
//Class CMPS 12B
//January 30th, 2018
//This exception is thrown whenever the user searches for a key that is not
//contained in the Dictionary ADT.
//KeyNotFoundException.java

public class KeyNotFoundException extends RuntimeException {
	public KeyNotFoundException (String s) {
		super(s);
	}
}