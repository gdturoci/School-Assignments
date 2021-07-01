//Galen Turoci
//gturoci
//pa3

class Matrix {
	
	private class Entry {
		//Fields
		int column;
		double value;
		
		//Constructor
		Entry(int column, double value) {
			this.column = column;
			this.value = value;
		}
		
		// toString():  overrides Object's toString() method - NOT SURE HOW TO WRITE THIS ONE
		public String toString() {
			String Entrystring = "";
			Entrystring += ("(" + column + ", " + value + ")");
			return Entrystring;
		}
		
		//equals(Object x)
		//Tells us if this entry and the entered entry are the same
		//overrides Object's equals() method
		public boolean equals(Object x) {
			boolean eq = false;
			Entry that;
			if (x instanceof Entry) {
				that = (Entry) x;
				eq = (this.value ==that.value);
			}
			return eq;
		}
		
	}
	
	//Fields
	private Entry column;
	private Entry value;
	private int NNZ;
	private List[] Rows;
	
	//Constructor--------------------------------------------
	
	//Makes a new n x n zero Matrix
	//Pre: n >= 1
	Matrix(int n) {
		if (n < 1)
			throw new RuntimeException("Matrix Error: Cannot construct a Matrix with no entries!");
		Rows = new List[n];
		for (int i = 0; i < n; i++) 
			Rows[i] = new List();
		NNZ = 0;
	}
	
	//Access Functions----------------------------------------
	
	//getSize()
	//Returns the size of the array of lists that is this matrix
	int getSize() {
		return Rows.length;
	}
	
	//getNNZ()
	//Returns the number of non-0 entries in this matrix
	int getNNZ() {
		return NNZ;
	}
	
	//equals(Object x)
	//Tells us if this matrix and that matrix are twinsies
	public boolean equals(Object x) {
		boolean eq = false;
		Matrix that;
		Entry e, ex;
		int y, z, i;
		double a, b;
		if (x instanceof Matrix) {
			that = (Matrix) x;
			
			eq = (this.getSize() == that.getSize());
			if (!eq)
				return eq;
			
			eq = (this.getNNZ() == that.getNNZ());
			if (!eq)
				return eq;
			
			for (i = 0; i < Rows.length; i++) {
				List ithRow = Rows[i];
				List ithRowx = that.Rows[i];
				
				eq = (ithRow.equals(ithRowx));
				if (!eq)
					return eq;
				
				if (ithRow.length() == 0 && ithRowx.length() == 0)
					continue;
			}
		}
		return eq;
	}
	
	//Manipulation procedures------------------
	
	//makeZero()
	//Sets this matrix to the 0 state
	void makeZero() {
		List ithRow = new List();
		for (int i = 0; i < Rows.length; i++) {
			ithRow = Rows[i];
			if (ithRow.length() == 0)
				continue;
			
			ithRow.clear();
		}
		NNZ = 0;
	}
	
	//copy()
	//Clones this matrix
	Matrix copy() {
		Matrix newM = new Matrix(Rows.length);
		List ithRow = new List();
		Entry e = null;
		int c, i;
		double x;
		
		for (i = 0; i < Rows.length; i++) {	
			ithRow = Rows[i];
			if (ithRow.length() == 0)
				continue;
			
			ithRow.moveFront();
			while (ithRow.index() >= 0) {
				e = (Entry) ithRow.get();
				c = e.column;
				x = e.value;
				newM.changeEntry(i+1, c, x);
				ithRow.moveNext();
			}
		}
		return newM;
	}
	
	//changeEntry(int i, int j, double x)
	//changes ith row, jth column of this matrix to x
	//pre: 1 <= i <= getSize(), 1 <= j <= getSize()
	void changeEntry(int i, int j, double x) {
		if (1 > i || i > this.getSize() || 1 > j || j > this.getSize())
			throw new RuntimeException("Matrix Error: Can't change what isn't there!");
		
		List ithRow = Rows[i-1];
		int c;
		Entry e;
		
		if (ithRow.length() == 0 && x != 0.0) {
			ithRow.append(new Entry(j, x));
			NNZ++;
		} else if (ithRow.length() != 0) {
			ithRow.moveFront();
			e = (Entry) ithRow.get();
			c = e.column;
			while (c < j && ithRow.index() != ithRow.length() - 1) {
				ithRow.moveNext();
				e = (Entry) ithRow.get();
				c = e.column;
			}
			if (c < j && x != 0.0) {
				ithRow.insertAfter(new Entry(j, x));
				NNZ++;
			} else if (c == j) {
				if (x != 0.0)
					e.value = x;
				else {
					ithRow.delete();
					NNZ--;
				}
			} else if (x != 0.0) {
				ithRow.insertBefore(new Entry(j, x));
				NNZ++;
			}
			ithRow.moveBack();
			ithRow.moveNext();
		}
	}
	
	//scalarMult(double x)
	//returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x) {
		Matrix newM = new Matrix(Rows.length);
		List ithRow = new List();
		Entry e;
		int c, i;
		double y;
		
		for (i = 0; i < Rows.length; i++) {
			ithRow = Rows[i];
			if (ithRow.length() == 0)
				continue;
			
			ithRow.moveFront();
			while (ithRow.index() >= 0) {
				e = (Entry) ithRow.get();
				c = e.column;
				y = e.value;
				newM.changeEntry(i+1, c, (x*y));
				ithRow.moveNext();
			}
		}
		return newM;
	}
	
	//add(Matrix M)
	//adds this Matrix with Matrix M
	//pre: getSize() == M.getSize()
	Matrix add(Matrix M) {
		if (this.getSize() != M.getSize())
			throw new RuntimeException("Matrix Error: Can't add Matrices of different sizes!");
		
		if (this.equals(M))
			return M.scalarMult(2.0);
		
		Matrix newM = new Matrix(Rows.length);
		List ithRow = new List();
		List ithRowM = new List();
		Entry e;
		Entry eM;
		int c, cM, i;
		double x = 0.0, y = 0.0;
		
		for (i = 0; i < Rows.length; i++) {
			ithRow = Rows[i];
			ithRowM = M.Rows[i];
			if (ithRow.length() == 0 && ithRowM.length() == 0)
				continue;
			
			ithRow.moveFront();
			ithRowM.moveFront();
			while (ithRow.index() >= 0 || ithRowM.index() >= 0) {
				c = 0;
				cM = 0;
				if (ithRow.length() != 0 && ithRow.index() != -1) {
					e = (Entry) ithRow.get();
					c = e.column;
					x = e.value;
				}
				if (ithRowM.length() != 0 && ithRowM.index() != -1) {
					eM = (Entry) ithRowM.get();
					cM = eM.column;
					y = eM.value;
				}
				
				if (c == cM) {
					newM.changeEntry(i+1, c, (x+y));
					ithRow.moveNext();
					ithRowM.moveNext();
				} else if (c != 0 && (c < cM || cM == 0)) {
					newM.changeEntry(i+1, c, x);
					ithRow.moveNext();
				} else {
					newM.changeEntry(i+1, cM, y);
					ithRowM.moveNext();
				}
			}
		}
		return newM;
	}
	
	//sub(Matrix M)
	//subtracts this matrix with Matrix M
	//pre: getSize() == M.getSize()
	Matrix sub(Matrix M) {
		if (this.getSize() != M.getSize())
			throw new RuntimeException("Matrix Error: Can't sub Matrices of different sizes!");
		
		Matrix newM = new Matrix(Rows.length);
		if (this.equals(M))
			return newM;
		
		List ithRow = new List();
		List ithRowM = new List();
		Entry e;
		Entry eM;
		int c, cM, i;
		double x = 0.0, y = 0.0;
		
		for (i = 0; i < Rows.length; i++) {
			ithRow = Rows[i];
			ithRowM = M.Rows[i];
			if (ithRow.length() == 0 && ithRowM.length() == 0)
				continue;
			
			ithRow.moveFront();
			ithRowM.moveFront();
			while (ithRow.index() >= 0 || ithRowM.index() >= 0) {
				c = 0;
				cM = 0;
				if (ithRow.length() != 0 && ithRow.index() != -1) {
					e = (Entry) ithRow.get();
					c = e.column;
					x = e.value;
				}
				if (ithRowM.length() != 0 && ithRowM.index() != -1) {
					eM = (Entry) ithRowM.get();
					cM = eM.column;
					y = eM.value;
				}
				
				if (c == cM) {
					newM.changeEntry(i+1, c, (x-y));
					ithRow.moveNext();
					ithRowM.moveNext();
				} else if (c != 0 && (c < cM || cM == 0)) {
					newM.changeEntry(i+1, c, -x);
					ithRow.moveNext();
				} else {
					newM.changeEntry(i+1, cM, -y);
					ithRowM.moveNext();
				}
			}
		}
		return newM;
	}
	
	//transpose()
	//Returns a new matrix that is the transpose of this one
	Matrix transpose() {
		Matrix newM = new Matrix(Rows.length);
		List ithRow = new List();
		Entry e;
		int x, i;
		double y;
		
		for (i = 0; i < Rows.length; i++) {
			ithRow = Rows[i];
			if (ithRow.length() == 0)
				continue;
			
			ithRow.moveFront();
			while (ithRow.index() >= 0) {
				e = (Entry) ithRow.get();
				x = e.column;
				y = e.value;
			
				newM.changeEntry(x, i+1, y);
				
				ithRow.moveNext();
			}
		}
		return newM;
	}
	
	//mult(Matrix M)
	//Returns a new matrix that is the product of this matrix with M
	//pre: getSize() == M.getSize()
	Matrix mult(Matrix M) {
		if (this.getSize() != M.getSize())
			throw new RuntimeException("Matrix Error: Can't mult Matrices of different sizes!");
		
		Matrix newM = new Matrix(Rows.length);
		List ithRow = new List();
		List ithRowM = new List();
		int a = Rows.length, b, c, i, j;
		double newY;
		Entry[] e = new Entry[a];
		Entry[] eM = new Entry[a];
		double[] y = new double[a];
		double[] yM = new double[a];
		
		for (i = 0; i < a; i++) {
			ithRow = Rows[i];
			if (ithRow.length() == 0)
				continue;
			
			for (b = 0; b < y.length; b++)
				y[b] = 0.0;
			
			ithRow.moveFront();
			for (b = 0; b < ithRow.length(); b++) {
				e[b] = (Entry) ithRow.get();
				y[e[b].column-1] = e[b].value;
				ithRow.moveNext();
			}
			
			for (j = 1; j <= a; j++) {
				for (b = 0; b < a; b++) {
					ithRowM = M.Rows[b];
					if (ithRowM.length() == 0)
						continue;
				
					ithRowM.moveFront();
					while (ithRowM.index() != j-1 && ithRowM.index() != ithRowM.length() - 1)
						ithRowM.moveNext();
				
					eM[b] = (Entry) ithRowM.get();
					yM[b] = eM[b].value;
				
					if (eM[b].column != j)
						yM[b] = 0.0;
				}
			
				c = 0;
				newY = 0.0;
				while (c < a) {
					newY += (y[c] * yM[c]);
					c++;
				}
			
				newM.changeEntry(i+1, j, newY);
			}
		}
		return newM;
	}
	
	//Other functions-------------------------------------------
	
	//toString()
	//overrides Object's toString() method
	public String toString() {
		StringBuffer sb = new StringBuffer();
		for (int i = 0; i < Rows.length; i++) {
			if (Rows[i].length() != 0) {
				sb.append((i+1) + ": ");
				sb.append(Rows[i]);
				sb.append("\n");
			}
		}
		return new String(sb);	
	}
	
}