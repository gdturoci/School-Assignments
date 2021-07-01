//Galen Turoci
//gturoci
//CMPS 12M
//January 18th, 2018
//This program sorts and searches through an array of Strings and finds a specified target(s).
//File name: Search.java

import java.io.*;
import java.util.Scanner;

class Search {
	
	static void mergeSort(String[] word, int p, int r) {
		int q;
		if(p < r) {
			q = (p+r)/2;
			mergeSort(word, p, q);
			mergeSort(word, q+1, r);
			merge(word, p, q, r);
		}
	}
	
	static void merge(String[] word, int p, int q, int r) {
		int n1 = q-p+1;
		int n2 = r-q;
		String[] L = new String[n1];
		String[] R = new String[n2];
		int i, j, k;
		
		for (i=0; i<n1; i++)
			L[i] = word[p+i];
		
		for (j=0; j<n2; j++) 
			R[j] = word[q+j+1];
		
		i = 0; j = 0;
		for (k=p; k<=r; k++) {
			if (i<n1 && j<n2) {
				if (L[i].compareTo(R[j])<0) {
					word[k] = L[i];
					i++;
				} else {
					word[k] = R[j];
					j++;
				}
			} else if (i<n1) {
				word[k] = L[i];
				i++;
			} else { // j<n2
				word[k] = R[j];
				j++;
			}
		}
	}
	
	static int binarySearch(String[] A, int p, int r, String target){
		int q;
		if(p>r) {
			return -1;
		} else {
			q = (p+r)/2;
			if(target.equals(A[q])) {
				return q;
			} else if(target.compareTo(A[q])<0) {
				return binarySearch(A, p, q-1, target);
			} else { // target > A[q]
				return binarySearch(A, q+1, r, target);
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
	
		//Checks length of args, exits if less than 2
		if(args.length < 2){
			System.err.println("Usage: Search file target1 [target2 ..]");
			System.exit(1);
		}
		
		//Creation of necessary variables
		Scanner in = new Scanner(new File(args[0]));
		Scanner in1 = new Scanner(new File(args[0]));
		int lineCount = 0;
		int found;
		
		//Counts the number of lines in given file
		while (in.hasNextLine()) {
			in.nextLine();
			lineCount++;
		}
		in.close();
		
		//Creates a new String array, then fills that array with
		//the words found in the given file.
		String[] Words = new String[lineCount];
		for (int i=0; i<lineCount; i++)
			Words[i] = in1.nextLine();
		in1.close();
		
		//Sorts through the new String array
		mergeSort (Words, 0, Words.length-1);
		
		//Searches for the target words and the line they are on.
		for (int i=1; i<args.length; i++) {
			found = binarySearch(Words, 0, Words.length-1, args[i]);
			if (found == -1)
				System.out.println(args[i] + " not found");
			else
				System.out.println(args[i] + " found on line "+ (found+1));
		}
	}
}