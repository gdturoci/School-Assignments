#Galen Turoci
#gturoci@ucsc.edu
#Lab 4: DEADBEEF in MIPS
#Section 01A: Michael Powell
#Due 02/16/2018

#This program takes all the numbers from 1 to N, and at multiples of 4 prints "DEAD",
#at multiples of 9 prints "BEEF", and at multiples of 4 and 9 prints "DEADBEEF".

.data
Prompt:	.asciiz "Please enter a number N: "	#Prompts the user for a number
Dead: 	.asciiz "DEAD"	#Prints if $t0%4==0
Beef: 	.asciiz "BEEF"	#Prints if $t0%9==0
DeadBeef: .asciiz "DEADBEEF"	#Prints if $t0%4 && $t0%9 == 0
newline: .asciiz "\n"	#Prints a new line
.text
	#Ask user for number (N)
	li $v0, 4
	la $a0, Prompt
	syscall
	
	#Get N from user
	li $v0, 5
	syscall
	
	#Store N from user
	move $t1, $v0

	Loop: #Our loop that iterates from 1-N

		#Start a new counter at 1
		li $v0, 1
		
		#Increment the counter
		addi $t0, $t0, 1
		move $a0, $t0
		
		#Register for DEAD
		li $t2, 4	#This sets $t2 = 4
		div $t0, $t2 	#This divides current counter iteration by 4
		mfhi $t4	#This stores the remainder of the above equation in $t4
		
		#Register for BEEF
		li $t3, 9	#This sets $t3 = 9
		div $t0, $t3	#This divides current counter iteration by 9
		mfhi $t5	#This stores the remainder of the above equation in $t5
		
		#Condition for DEADBEEF
		add $t6, $t5, $t4	#This adds the remainders of the above two equations and stores the result in $t6
		
			#If $t1%4==0 && $t1%9==0, print DEADBEEF
			beqz $t6, DEADBEEF	#This only evaluates to true when $t4+$t5=0, AKA when the counter is a multiple of 4x9.

			#If $t1%4==0, print DEAD
			beqz $t4, DEAD
		
			#If $t1%9==0, print BEEF
			beqz $t5, BEEF
		
		#Print the number, only if none of the words were printed
		syscall
		
		#New line after each printed number
		li $v0, 4
		la $a0, newline
		syscall
		
			#Check if we should exit loop
			beq $t0, $t1, end
		
		#Go back to beginning
		b Loop	#This will only occur if the only thing that happened is the counter was incremented

	#This will cause the program to end
	end: 	
		li $v0, 10
		syscall
	
	#This prints the word "DEAD" to the I/O stream iff the counter is a multiple of 4	
	DEAD:
		li $v0, 4
		la $a0, Dead
		syscall
		#Put a new line after the word is printed
		la $a0, newline
		syscall
			#Checks if the counter==N; if it does, end the program
			beq $t0, $t1, end
		b Loop
		
	#This prints the word "BEEF" to the I/O stream iff the counter is a multiple of 9
	BEEF:
		li $v0, 4
		la $a0, Beef
		syscall
		#Put a new line after the word is printed
		la $a0, newline
		syscall
			#Checks if the counter==N; if it does, end the program
			beq $t0, $t1, end
		b Loop
		
	#This prints the word "DEADBEEF" to the I/O stream iff the counter is a multiple of 4x9
	DEADBEEF:
		li $v0, 4
		la $a0, DeadBeef
		syscall
		#Put a new line after the word is printed
		la $a0, newline
		syscall
			#Checks if the counter==N; if it does, end the program
			beq $t0, $t1, end
		b Loop
