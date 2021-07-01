#DecryptChar: Decrypts a single character using a single key character
#Functionally exactly the same as EncryptChar

DecryptChar:

	#Find ASCII value of cipher char (char to decrypt), assign value to $t0
	rem $t0, $a0, 128
	
	#Find ACSCII value of key char, assign value to $t1
	rem $t1, $a1, 128
	
	#Add $t0 and $t1, store result in $v0
	add $v0, $t0, $t1
	
	#Subtract 65 from $v0 so it is back an ASCII character again
	sub $v0, $v0, 65
	
		#If 96<$a0 && $a0<123 && $v0>122, subtract 26 from $v0 and return
		bgt $v0, 122, __decsub26
	
		#If 64<$a0 && $a0<91 && $v0>90, subtract 26 from $v0 and return
		bgt $v0, 90, __decsub26
	
	
	#Load $v0 into $a2 and resume Encryption
	la $a2, ($v0)
		b __decresume
	
	
	#This branch subtracts 26 from the character in $v0 so it is once again an alphabetic character
	__decsub26:
	sub $v0, $v0, 26
	
	#Load $v0 into $a2 and resume Encryption
	la $a2, ($v0)
		b __decresume