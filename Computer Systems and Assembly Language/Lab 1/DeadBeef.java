// Galen Turoci
// Lab 1

class DEADBEEF {
	public static void main(String[] args) {
		for (int i=1; i<=1000; i++) {
			int dead = i%4;
			int beef = i%9;
			if (dead == 0 && beef == 0)
				System.out.println("DEADBEEF");
			else if (dead == 0)
				System.out.println("DEAD");
			else if (beef == 0)
				System.out.println("BEEF");
			else
				System.out.println(i);
		}
	}
}