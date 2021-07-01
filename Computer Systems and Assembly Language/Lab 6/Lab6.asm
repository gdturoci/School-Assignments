#Galen Turoci
#gturoci@ucsc.edu
#Lab 6: Vigenere Cipher
#Section 01A: Michael Powell
#Due 03/09/2018 (Extended to 03/11/18)

#PseudoCode:
	#EncryptString:
		#1. Initialize Counter and store original key register
		#2. Start Encryption loop
		#3. Get the plaintext char to encrypt and key char
		#4. Check if counter at 30
		#4a. If it is, end
		#5. Check if current key char is null
		#5a. If it is, reset to the start of the key
		#6. Check if current Plaintext char is an alphabetic character
		#6a. If it is, run EncryptChar on that character
		#6b. If it is not, put that character in the cipher as-is.
		#7. Increment the registers and counter by 1
		#7a. If current plaintext char is null, end
		#8. Restart loop
	#EncryptChar:
		#1. Find the ASCII values of the plaintext and key chars
		#2. Add those values together
		#2a. Subtract 65 from the result so it is back in the range of the alphabet
		#3. Check to see if the result is beyond the range of (upper or lower) alphabetic characters still
		#3a. If it is, subtract 26 so we have the proper result
		#4. Resume Encryption
	#DecryptString:
		#1. Initialize Counter and store original key register
		#2. Start Decryption loop
		#3. Get the cipher char to decrypt and key char
		#4. Check if counter at 30
		#4a. If it is, end
		#5. Check if current key char is null
		#5a. If it is, reset to the start of the key
		#6. Check if current cipher char is an alphabetic character
		#6a. If it is, run DecryptChar on that character
		#6b. If it is not, put that character in the plaintext as-is.
		#7. Increment the registers and counter by 1
		#7a. If current Cipher char is null, end
		#8. Restart loop
	#DecryptChar:
		#1. Find the ASCII values of the Cipher and key chars
		#2. Add those values together
		#2a. Subtract 65 from the result so it is back in the range of the alphabetic characters
		#3. Check to see if the result is beyond the range of (upper or lower) alphabetic characters still
		#3a. If it is, subtract 26 so we have the proper result
		#4. Resume Decryption


#Encrypts a null-terminated string of length 30 or less using a keystring
EncryptString:
	
	#Initialize counter
	li $t7, 0
	
	#Store the original key register in $t4
	la $t4, ($a1)
	
	#Store the current value of $ra
	la $t8, ($ra)
	
	#Loop that runs through EncryptChar <31 times
	__Encrypt:
		
		#Get Plaintext char from $a0, put in $t2
		lb $t2, ($a0)
		
		#Get Key char from $a1, put in $t3
		lb $t3, ($a1)
		
			#If counter >30, end
			bgt $t7, 30, __end
			
			#If no more Plaintext characters, end
			beqz $t2, __end 
		
			#If Key char == /0 (null), reset $t3 to the beginning of the keystring
			beqz $t3, __reset
			
		__continue:
			#Run __InAlphabet($a0); if $a0 is in the alphabet, returntrue will run and thus EncryptChar will run
			b __InAlphabet
			
			__returntrue:
				#Store $a0's contents in $t5
				la $t5, ($a0)
				
				#Store $a1's contents in $t6
				la $t6, ($a1)
				
				#Load t2's contents into $a0
				la $a0, ($t2)
				
				#Load t3's contents into $a1
				la $a1, ($t3)
					
				#Run EncryptChar
				jal EncryptChar
		
		__resume:
			#Place $a0's original contents back in it
			la $a0, ($t5)
		
			#Place $a1's original contents back in it
			la $a1, ($t6)
			
			#Store the contents of $v0 into $a2
			sb $v0, ($a2)
		
			#Increment all the registers
			addi $a0, $a0, 1 #Plaintext register
			addi $a1, $a1, 1 #Key Register
			addi $a2, $a2, 1 #Cipher Register
		
			#Increment counter
			addi $t7, $t7, 1
		
			#Restart loop
			b __Encrypt


#Determines if a given character is in the alphabet or not
__InAlphabet:

	#If char is <65, return false
	blt $t2, 65, __returnfalse
	
	#If char is >122, return false
	bgt $t2, 122, __returnfalse
	
	#If char is (64<)$t0<91, return true
	blt $t2, 91, __returntrue
	
	#If char is 96<$t0(<123), return true
	bgt $t2, 96, __returntrue
	
	#Else, return false
	b __returnfalse
	

#Else (!__InAlphabet($a0) - If the given char in $t2 is not in the alphabet)
__returnfalse:

	#Store $a0's contents in $t5
	la $t5, ($a0)
		
	#Store $a1's contents in $t6
	la $t6, ($a1)

	#$v0 = $t2
	la $v0, ($t2)

	#Decrement $a1/$t6
	subi $t6, $t6, 1
	
	#Resume Encryption
	b __resume


#Reset the key to its original register
__reset:
	#Puts the contents of $t4 (The original key register) into $a1
	la $a1, ($t4)
	
	#Grab the first byte of the key register
	lb $t3, ($a1)
	
	#Resum Encryption
	b __continue
	

#EncryptChar: Encrypts a single character using a single key character
EncryptChar:

	#Find ASCII value of plaintext char, assign value to $t0
	rem $t0, $a0, 128

	#Find ASCII value of key char, assign value to $t1
	rem $t1, $a1, 128

	#Add $t0 and $t1, store result in $v0
	add $v0, $t0, $t1
	
	#Subtract 65 from $v0
	sub $v0, $v0, 65

		#If plaintext char is lowercase
		bgt $t0, 96, __sublc
	
		#If plaintext char is uppercase
		blt $t0, 91, __subuc
	
	
#Checks to see if $v0 is still in the range of lowercase characters
__sublc:
		#If $v0 is no longer in the range of lowercase characters, subtract 26 and return
		bgt $v0, 122, __sub26
	
	#Else return to calling code
	jr $ra
	
#Checks to see if $v0 is still in the range of uppercase characters
__subuc:
		#If 90<$v0<97 (is no longer in the range of uppercase characters), subtract 26 and return
		bgt $v0, 90, __sub26
	
	#Else return to calling code
	jr $ra
	
#Subtracts 26 from $v0 and returns
__sub26:
	#Subtract 26 from $v0
	sub $v0, $v0, 26
	
	#Return to calling code
	jr $ra
	
#DecryptString: Decrypts a null-terminated string of length 30 or less using a keystring
#Functionally exactly the same as EncryptString	
DecryptString:
	
	#Initialize counter
	li $t7, 0
	
	#Store the original key register in $t4
	la $t4, ($a1)
	
	#Store the current value of $ra
	la $t8, ($ra)
	
	#Loop that runs through EncryptChar <31 times
	__Decrypt:
		#Get Cipher char from $a0, put in $t2
		lb $t2, ($a0)
		
		#Get Key char from $a1, put in $t3
		lb $t3, ($a1)
		
			#If counter >30, end
			bgt $t7, 30, __end
			
			#If no more Cipher characters, end
			beqz $t2, __end 
		
			#If Key char == /0 (null), reset $t3 to the beginning of the keystring
			beqz $t3, __decreset
			
		__deccontinue:
			#Run __decInAlphabet($a0); if $a0 is in the alphabet, decreturntrue will run and thus DecryptChar will run
			b __decInAlphabet
			
			__decreturntrue:
				#Store $a0's contents in $t5
				la $t5, ($a0)
				
				#Store $a1's contents in $t6
				la $t6, ($a1)
				
				#Load t2's contents into $a0
				la $a0, ($t2)
				
				#Load t3's contents into $a1
				la $a1, ($t3)
					
				#Run DecryptChar
				jal DecryptChar
		
		__decresume:
			#Place $a0's original contents back in it
			la $a0, ($t5)
		
			#Place $a1's original contents back in it
			la $a1, ($t6)
			
			#Store the contents of $v0 into $a2
			sb $v0, ($a2)
		
			#Increment all the registers
			addi $a0, $a0, 1 #Cipher register
			addi $a1, $a1, 1 #Key Register
			addi $a2, $a2, 1 #Plaintext Register
		
			#Increment counter
			addi $t7, $t7, 1
		
			#Restart loop
			b __Decrypt


#Determines if a given character is in the alphabet or not
__decInAlphabet:

	#If char is <65, return false
	blt $t2, 65, __decreturnfalse
	
	#If char is >122, return false
	bgt $t2, 122, __decreturnfalse
	
	#If char is (64<)$t0<91, return true
	blt $t2, 91, __decreturntrue
	
	#If char is 96<$t0(<123), return true
	bgt $t2, 96, __decreturntrue
	
	#Else, return false
	b __decreturnfalse
	

#Else (!__decInAlphabet($a0) - If the given char in $t2 is not in the alphabet)
__decreturnfalse:

	#Store $a0's contents in $t5
	la $t5, ($a0)
		
	#Store $a1's contents in $t6
	la $t6, ($a1)

	#$v0 = $t2
	la $v0, ($t2)

	#Decrement $a1/$t6
	subi $t6, $t6, 1
	
	#Resume Decryption
	b __decresume


#Reset the key to its original register
__decreset:
	#Puts the contents of $t4 (The original key register) into $a1
	la $a1, ($t4)
	
	#Grab the first byte of the key register
	lb $t3, ($a1)
	
	#Resume Decryption
	b __deccontinue
	

#DecryptChar: Decrypts a single character using a single key character
DecryptChar:

	#Find ASCII value of Cipher char, assign value to $t0
	rem $t0, $a0, 128

	#Find ASCII value of key char, assign value to $t1
	rem $t1, $a1, 128

	#Subtract $t0 and $t1, store result in $v0
	sub $v0, $t0, $t1
	
	#Add 65 to $v0
	add $v0, $v0, 65

		#If Cipher char is lowercase
		bgt $t0, 96, __addlc
	
		#If Cipher char is uppercase
		blt $t0, 91, __adduc
	
	
#Checks to see if $v0 is still in the range of lowercase characters
__addlc:
		#If $v0 is no longer in the range of lowercase characters, add 26 and return
		blt $v0, 97, __add26
	
	#Else return to calling code
	jr $ra
	
#Checks to see if $v0 is still in the range of uppercase characters
__adduc:
		#If $v0<65 (no longer in the range of uppercase characters), add 26 and return
		blt $v0, 65, __add26
	
	#Else return to calling code
	jr $ra
	
#Subtracts 26 from $v0 and returns
__add26:
	#Subtract 26 from $v0
	add $v0, $v0, 26
	
	#Return to calling code
	jr $ra
	
	
#Return to the calling code
__end:
	#Put the original value of $ra back into it
	la $ra ($t8)
	jr $ra
