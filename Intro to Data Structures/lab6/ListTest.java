//Galen Turoci
//gturoci
//Class CMPS 12M
//February 23th, 2018
//ListTest.java was used to test the various functions of List.java before fully implementing them.
//ListTest.java

public class ListTest {
	
	public static void main(String[] args) {
		List<String> TA = new List<String>();
		List<String> TB = new List<String>();
		List<List<String>> TC = new List<List<String>>();
		int i, j, k;

		TA.add(1, "one");
		TA.add(2, "two");
		TA.add(3, "three");
		TB.add(1, "ten");
		TB.add(2, "twenty");
		TB.add(3, "thirty");
		TC.add(1, TA);
		TC.add(2, TB);

		System.out.println("TA: "+TA);
		System.out.println("TB: "+TB);
		System.out.println("TC: "+TC);
		System.out.println("TA.equals(TA) is "+TA.equals(TA));
		System.out.println("TA.equals(TB) is "+TA.equals(TB));
		System.out.println("TA.equals(TC) is "+TA.equals(TC));
		System.out.println("TA.size() is "+TA.size());
		System.out.println("TB.size() is "+TB.size());
		System.out.println("TC.size() is "+TC.size());

		TA.remove(1);
		TB.remove(2);

		System.out.println("TA.size() is "+TA.size());
		System.out.println("TB.size() is "+TB.size());
		System.out.println("TB.get(1) is "+TB.get(1));
		System.out.println("TC: "+TC);
		System.out.println();
		try {
			System.out.println(TA.get(200));
		} catch(ListIndexOutOfBoundsException e) {
			System.out.println("Caught Exception: ");
			System.out.println(e);
			System.out.println("Continuing without interruption");
		} try {
			TA.add(200, "five thousand");
		} catch(ListIndexOutOfBoundsException e) {
			System.out.println("Caught Exception: ");
			System.out.println(e);
			System.out.println("Continuing without interruption");
		} try {
			TA.remove(200);
		} catch(ListIndexOutOfBoundsException e) {
			System.out.println("Caught Exception: ");
			System.out.println(e);
			System.out.println("Continuing without interruption");
		}
		System.out.println();
		System.out.println("TA.get(2) is "+TA.get(2));
		System.out.println("TC.get(1) is "+TC.get(1));
	}
}