//Galen Turoci
//gturoci
//Class CMPS 12B
//February 8th, 2018
//This program was used to test the ADT operations before implementing
//them into Dictionary.java.
//DictionaryTest.java

public class DictionaryTest {
	
	public static void main(String[] args) {
		String t;
		Dictionary DT = new Dictionary();
			
		DT.insert("1", "a");
		DT.insert("2", "b");
		//DT.insert("1", "d"); - throws "DuplicateKeyException"
		DT.insert("5", "f");
		DT.insert("6", "g");
		DT.insert("a", "3");
		DT.insert("3", "a");
		//DT.insert("a", "53"); - throws "DuplicateKeyException"
		System.out.println(DT);
		
		/*t = DT.lookup("13");
		System.out.println("key=13 "+(t==null?"not found":("value="+t)));
		t = DT.lookup("1");
		System.out.println("key=1 "+(t==null?"not found":("value="+t)));
		t = DT.lookup("2");
		System.out.println("key=2 "+(t==null?"not found":("value="+t))); //Should not be found
		t = DT.lookup("5");
		System.out.println("key=5 "+(t==null?"not found":("value="+t)));
		t = DT.lookup("6");
		System.out.println("key=6 "+(t==null?"not found":("value="+t)));
		t = DT.lookup("7");
		System.out.println("key=7 "+(t==null?"not found":("value="+t))); //Should not be found
		System.out.println();
		*/
		
		DT.delete("1");
		DT.delete("5");
		//DT.delete("7"); - throws "KeyNotFoundException"
		DT.delete("3");
		System.out.println(DT);
	}
}
