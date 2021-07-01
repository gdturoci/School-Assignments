class Recursiontest {

	static void reverseArray1 (int[] X, int n, int[] Y) {
		if (n>0) {
			Y[X.length-n]=X[n-1];
			reverseArray1(X, n-1, Y);
		}
	}
	
	static void reverseArray2(int[] X, int n, int[] Y) {
		if (n>0) {
			reverseArray2(X, n-1, Y);
			Y[X.length-n]=X[n-1];
		}
	}
	
	static void reverseArray3(int[] X, int i, int j) {
		if (i<j) {
			int temp=X[i];
			X[i]=X[j];
			X[j]=temp;
			reverseArray3(X, i+1, j-1);
		}
	}
	
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
	
	public static void main(String[] args) {
		int[] A = {-1, 2, 6, 12, 9, 2, -5, -2, 8, 5, 7};
		int[] B = new int[A.length];
		int[] C = new int[A.length];
		
		int maxIndex = maxArrayIndex(A, 0, A.length-1);
		
		for(int x: A) System.out.print(x+" ");
		System.out.println();
		
		//System.out.println("minIndex = " + minIndex );
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