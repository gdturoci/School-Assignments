#EncryptString: Encrypts a null-terminated string of length 30 or less using a keystring

EncryptString:
	
	#Initialize counter
	li $t7, 0
	
	#Store the first byte of the key in its own register
	lb $t4, ($a1)
	
	#Loop that runs through EncryptChar <31 times
	__Encrypt:
	
		#If counter >31, end
		bgt $t7, 31, __end
		
		#Get Plaintext char from $a0, put in $t2
		lb $t2, ($a0)
		
		#Get Key char from $a1, put in $t3
		lb $t3, ($a1)
		
			#If Key char == /0 (null), reset $t3 to the beginning of the keystring
			beqz $t3, __reset
			
			__reset:
				la $t3, ($t4)
			
			#Run __InAlphabet($a0); if $a0 is in the alphabet, returntrue will run and thus EncryptChar will run
			b __InAlphabet
			
			__returntrue:
				b EncryptChar
		#Else (!__InAlphabet($a0) - If the given char in $s0 is not in the alphabet)
			__returnfalse:
				#$a2 = $s0
				la $a2, ($t2)
			
				#Decrement $a1
				sub $a1, $a2, 1
		
		
		__resume:	
		#Increment all the registers
		addi $a0, $a0, 1 #Plaintext register
		addi $a1, $a1, 1 #Key Register
		addi $a2, $a2, 1 #Cipher Register
		
		#Increment counter
		addi $t7, $t7, 1
		
		#Restart loop
		b __Encrypt