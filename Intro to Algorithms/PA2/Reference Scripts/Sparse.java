//Galen Turoci
//gturoci
//pa3

import java.io.*;
import java.util.Scanner;

class Sparse {
	
	public static void main(String[] args) throws IOException {
	
		//Checks to see that the number of command line arguments are 2;
		//any more or less, and the program will quit
		if (args.length != 2) {
			System.err.println("Must have two strings on the command line.");
			System.exit(1);
		}
	
		//A scanner to look at the inside of the first file
		Scanner in = new Scanner(new File(args[0]));
	
		//A printwriter to write to the output file
		PrintWriter out = new PrintWriter(new FileWriter(args[1]));
	
		//A handful of variables to collect the data we need
		int n = in.nextInt(), a = in.nextInt(), b = in.nextInt(), row, column, i;
		double x;
		
		//The Matrices we will be using
		Matrix A = new Matrix(n);
		Matrix B = new Matrix(n);
		Matrix scalarMult = new Matrix(n);
		Matrix add = new Matrix(n);
		Matrix sub = new Matrix(n);
		Matrix transpose = new Matrix(n);
		Matrix mult = new Matrix(n);
	
		//Reading the first group of entries in the input file and placing them in Matrix A
		for (i = 0; i < a; i++) {
			in.nextLine();
			row = in.nextInt();
			column = in.nextInt();
			x = in.nextDouble();
			A.changeEntry(row, column, x);
		}
		in.reset();
		
		//Reading the first group of entries in the input file and placing them in Matrix B
		for (i = 0; i < b; i++) {
			in.nextLine();
			row = in.nextInt();
			column = in.nextInt();
			x = in.nextDouble();
			B.changeEntry(row, column, x);
		}
		in.close();
		
		//Let's print some Matrices!
		out.println("A has " + a + " non-zero entries: \n" + A);
		out.println("B has " + b + " non-zero entries: \n" + B);
		
		//scalarMult
		scalarMult = A.scalarMult(1.5);
		out.println("(1.5)*A = \n" + scalarMult);
	
		//add
		add = A.add(B);
		out.println("A+B = \n" + add);
		add = A.add(A);
		out.println("A+A = \n" + add);
		
		//sub
		sub = B.sub(A);
		out.println("B-A = \n" + sub);
		sub = A.sub(A);
		out.println("A-A = \n" + sub);
		
		//transpose
		transpose = A.transpose();
		out.println("Transpose(A) = \n" + transpose);
		
		//mult
		mult = A.mult(B);
		out.println("A*B = \n" + mult);
		mult = B.mult(B);
		out.println("B*B = \n" + mult);
		
		out.close();
		
	}
	
}