#Galen Turoci
#gturoci@ucsc.edu
#Lab 5: Decimal to Binary Converter
#Section 01A: Michael Powell
#Due 02/28/2018

#This program takes an ascii string number, converts it to decimal, and then converts that to binary, then prints the result.

#Pseudocode:
#1. Take argument from user
#2. Print various statements as necessary
#3. Initialize mask to compare user's number to
#4. See if number is negative
#4a.	if number is negative, convert to 2SC 
#4c.	compare to mask and print
#5. If number is not negative, convert to decimal
#5b.	compare to mask and print
#6. end

.data
Prompt: .asciiz "User input number:"
newline: .asciiz "\n"
number: .asciiz "This number is binary is:"
print0: .asciiz "0"
print1: .asciiz "1"
.text

	#Print "User input number:"
	li $v0, 4
	la $a0, Prompt
	syscall
	
	#Print newline
	li $v0, 4
	la $a0, newline
	syscall
	
	#Load address of user's number into $t0
	lw $t0, ($a1)
	
	#Print number from user
	li $v0, 4
	la $a0, ($t0)
	syscall
	
	#Print newline
	li $v0, 4
	la $a0, newline
	syscall
	
	#Print "This number in binary is:"
	li $v0, 4
	la $a0, number
	syscall
	
	#Print newline
	li $v0, 4
	la $a0, newline
	syscall
	
	#Initialize mask
	addu $t3, $zero, 0x80000000
	
	#Load the first bit of $s0 into $t1
	lb $t1, ($t0)
		
		#If the input number is negative, convert to 2SC
		beq $t1, 45, negdec
		
		#check to see if character is null; if it is end
		beq $t1, 0, end
	
	#Else, convert to decimal
	posdec:
		#subtract current number by hex 30
		sub $t1, $t1, 0x30
		
		#add new number and old number x 10
		add $s0, $s0, $t1
		
		#add $t0 address by 1 to get next digit
		addi $t0, $t0, 1
		
		#load next digit into $t1
		lb $t1, ($t0)
		
			#check to see if new number is null; if it is start converting to binary
			beq $t1, 0, posnum
		
		#Multiply old number by 10 and store the result in $s0
		mul $s0, $s0, 10
		
		#restart the loop
		b posdec
	
	#Convert the positive number into binary
	posnum:
		#Compare the user's number and the mask, store the result in $t4
		and $t4, $s0, $t3
		
		#Move the mask's bit over by 1
		srl $t3, $t3, 1
		
			#If Bitwise AND == 0, print 0
			beqz $t4, printzero
			
			#if Bitwise AND >= 1, print 1
			bge $t4, 1, printone
		
	#2SC conversion
	negdec:
		#add $t0 address by 1 to get next digit
		addi $t0, $t0, 1
		
		#load next digit into $t1
		lb $t1, ($t0)
		
		negdec1:	
			#subtract current number by hex 30
			sub $t1, $t1, 0x30
		
			#add new number and old number x 10
			add $s0, $s0, $t1
		
			#add $t0 address by 1 to get next digit
			addi $t0, $t0, 1
		
			#load next digit into $t1
			lb $t1, ($t0)
		
				#check to see if new number is null; if it is subtract 1 and convert it to binary
				beq $t1, 0, sub1
		
			#Multiply old number by 10 and store the result in $s0
			mul $s0, $s0, 10
		
			#restart the loop
			b negdec1
		
	
	#subtract 1 from the number
	sub1:
		sub $s0, $s0, 1
		
		#start the printing
		b negnum
	
	#convert the negative number into two's complement
	negnum:
		#Compare the user's number and the mask, store the result in $t4
		and $t4, $s0, $t3
		
		#Move the mask's bit over by 1
		srl $t3, $t3, 1
		
			#If Bitwise AND == 0, print 1
			beqz $t4, negprintone
			
			#if Bitwise AND >= 1, print 0
			bge $t4, 1, negprintzero

	#print 0 for positive numbers
	printzero:
		li $v0, 4
		la $a0, print0
		syscall
		
		#if the mask is at 0, end
		blez $t3, end
		
		#else, restart loop
		b posnum
		
	#print 1 for positive numbers
	printone:
		li $v0, 4
		la $a0, print1
		syscall
		
		#if the mask is at 0, end
		blez $t3, end
		
		#else, restart loop
		b posnum
		
	#print 0 for negative numbers
	negprintzero:
		li $v0, 4
		la $a0, print0
		syscall
		
		#if the mask is at 0, end
		blez $t3, end
		
		#else, restart loop
		b negnum
		
	#print 1 for negative numbers
	negprintone:
		li $v0, 4
		la $a0, print1
		syscall
		
		#if the mask is at 0, end
		blez $t3, end
		
		#else, restart loop
		b negnum

	#This will cause the program to end
	end: 	
		li $v0, 10
		syscall
