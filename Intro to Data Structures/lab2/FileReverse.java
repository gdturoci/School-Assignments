//Galen Turoci
//gturoci
//CMPS 12M
//January 18th, 2018
//This program takes an array of Strings and reverses them, then prints those results to a given file.
//File name: FileReverse.java

import java.io.*;
import java.util.Scanner;

class FileReverse {

	public static String stringReverse(String s, int n) {
		
		if (n>0) {
			//convert s to a string array
			String[] word = s.split("\\s+");
			
			//reverse the elements of that array
			word[word.length-n] = word[n-1];
			
			//call stringReverse again
			s = stringReverse(s, n-1);
			
			//convert the string array back into a string
			s = word.toString();
			
			return s;
		}
		return s;
	}
	
	public static void main(String[] args) throws IOException {
		
		//create necessary variables
		Scanner in = null;
		PrintWriter out = null;
		String token;
		String RevToken;
		int StrNum;
		
		//checks to see the number of command line arguments is at least 2
		if (args.length<2) {
			System.out.println("Usage: FileReverse <input file> <output file>");
			System.exit(1);
		}
		
		//opens files
		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));
		
		//reads words from in, reverses those words and prints them to out
		while (in.hasNextLine()) {
			token = in.next();
			StrNum = token.length();
			RevToken = stringReverse(token, StrNum);
			out.println(RevToken);
		}
		
		//closes files
		in.close();
		out.close();
	}
	
}