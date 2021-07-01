//Galen Turoci
//gturoci
//Class CMPS 12B
//January 11th, 2018
//Recursion recursively calls 3 different functions to reverse the elements of an array and then prints them.
//File Name: Recursion.java

class Recursion {

	//Reverses an array from left to right.
	static void reverseArray1 (int[] X, int n, int[] Y) {
		if (n>0) {
			Y[X.length-n]=X[n-1];
			reverseArray1(X, n-1, Y);
		}
	}
	
	//Reverses an array from right to left.
	static void reverseArray2(int[] X, int n, int[] Y) {
		if (n>0) {
			reverseArray2(X, n-1, Y);
			Y[X.length-n]=X[n-1];
		}
	}
	
	//Reverses an array by swapping the elements at the first and last positions
	//and then calling itself recursively over and over again.
	static void reverseArray3(int[] X, int i, int j) {
		if (i<j) {
			int temp=X[i];
			X[i]=X[j];
			X[j]=temp;
			reverseArray3(X, i+1, j-1);
		}
	}
	
	//Returns the index of the largest element in an array.
	static int maxArrayIndex(int[] X, int p, int r) {
		int q=(p+r)/2;
		if (p>r)
			return -1;
		else if (p<r) {
			int x = maxArrayIndex(X, p, q);
			int y = maxArrayIndex(X, q+1, r);
			if (X[x]>=X[y])
				return x;
			else if (X[x]<X[y])
				return y;
			else
				return x;
		}
		else
			return p;
	}
	
	//Returns the index of the smallest element in an array.
	static int minArrayIndex(int[] X, int p, int r) {
		int q=(p+r)/2;
		if (p>r)
			return -1;
		else if (p<r) {
			int x = minArrayIndex(X, p, q);
			int y = minArrayIndex(X, q+1, r);
			if (X[x]<=X[y])
				return x;
			else if (X[x]>X[y])
				return y;
			else
				return x;
		}
		else
			return p;
		
	}
	
	//Takes an array, reverses it 3 times, and gives the indexes of the largest and smallest elements.
	public static void main(String[] args) {
		int[] A = {-1, 2, 6, 12, 9, 2, -5, -2, 8, 5, 7};
		int[] B = new int[A.length];
		int[] C = new int[A.length];
		int minIndex = minArrayIndex(A, 0, A.length-1);
		int maxIndex = maxArrayIndex(A, 0, A.length-1);

		for(int x: A) System.out.print(x+" ");
		System.out.println();

		System.out.println("minIndex = " + minIndex );
		System.out.println("maxIndex = " + maxIndex );
		reverseArray1(A, A.length, B);
		for(int x: B) System.out.print(x+" ");
		System.out.println();

		reverseArray2(A, A.length, C);
		for(int x: C) System.out.print(x+" ");
		System.out.println();

		reverseArray3(A, 0, A.length-1);
		for(int x: A) System.out.print(x+" ");
		System.out.println();
	}
}