#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include<string.h>

#define MAX_STRING_LENGTH 100

//function extract_chars, which reads each line of input
//and separates the characters according to type.
void extract_chars(char* s, char* a, char* d, char* p, char* w);
	
//function main which takes command line arguments 
int main(int argc, char* argv[]) {
	FILE* in; //handle for input file                  
	FILE* out; //handle for output file                 
	char* line; //string holding input line              
	char* alpha; //string holding all alphabetic chars 
	char* num; //string holding all numeric chars
	char* punc; //string holding all punctuation chars
	char* white; //string holding all whitespace chars
	int li = 1, ai = 0, ni = 0, pi = 0, wi = 0;
	
	//check command line for correct number of arguments 
	if (argc != 3) {
		printf("Usage: %s input-file output-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//open input file for reading 
	if ((in=fopen(argv[1], "r"))==NULL) {
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	//open output file for writing 
	if ((out=fopen(argv[2], "w"))==NULL) {
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	//allocate strings line and alpha_num on the heap 
	line = calloc(MAX_STRING_LENGTH+1, sizeof(char));
	alpha = calloc(MAX_STRING_LENGTH+1, sizeof(char));
	num = calloc(MAX_STRING_LENGTH+1, sizeof(char));
	punc = calloc(MAX_STRING_LENGTH+1, sizeof(char));
	white = calloc(MAX_STRING_LENGTH+1, sizeof(char));
	assert(line!=NULL && alpha!=NULL && num!=NULL && punc!=NULL && white!=NULL);

	//read each line in input file, extract alpha-numeric characters 
	while (fgets(line, MAX_STRING_LENGTH, in) != NULL) {
		fprintf(out, "line %d contains:\n", li);
		extract_chars(line, alpha, num, punc, white);
		ai = strlen(alpha);
		ni = strlen(num);
		pi = strlen(punc);
		wi = strlen(white);
		if (strlen(alpha) == 1) {
			fprintf(out, "1 alphabetic character: %s\n", alpha);
		} else if (strlen(alpha) != 1) {
			fprintf(out, "%d alphabetic characters: %s\n", ai, alpha);
		} if (strlen(num) == 1) {
			fprintf(out, "1 numeric character: %s\n", num);
		} else if (strlen(num) != 1) {
			fprintf(out, "%d numeric characters: %s\n", ni, num);
		} if (strlen(punc) == 1) {
			fprintf(out, "1 punctuation character: %s\n", punc);
		} else if (strlen(punc) != 1) {
			fprintf(out, "%d punctuation characters: %s\n", pi, punc);
		} if (strlen(white) == 1) {
			fprintf(out, "1 whitespace character: %s\n", white);
		} else if (strlen(white) != 1) {
			fprintf(out, "%d whitespace characters: %s\n", wi, white);
		}
		li++;
		fprintf(out, "\n");
	}

	//free heap memory 
	free(line);
	free(alpha);
	free(num);
	free(punc);
	free(white);

	// close input and output files 
	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}

//function definition
void extract_chars(char* s, char* a, char* d, char* p, char* w) {
	int i = 0, ai=0, di=0, pi=0, wi=0;
	
	while (s[i] != '\0' && i<MAX_STRING_LENGTH) {
		if (isalpha(s[i]))
			a[ai++] = s[i];
		else if (isdigit(s[i]))
			d[di++] = s[i];
		else if (ispunct(s[i]))
			p[pi++] = s[i];
		else if (isspace(s[i]))
			w[wi++] = s[i];
		i++;
	}
	
	a[ai] = '\0';
	d[di] = '\0';
	p[pi] = '\0';
	w[wi] = '\0';
}