#EncryptChar: Encrypts a single character using a single key character
	#Pseudocode:
		#1. Assign $a1 (Key) numeric value based on its ASCII value, assign to register x
		#2. Assign $a0 numeric value based on its ASCII value, assign to register y
		#3. Add x and y registers to get z value, which is cipher character ($v0)
		#3a.	If 64<$a0<91 && 90<$v0, subtract  26 from $v0
		#3b.	If 96<$a0<123 && 122<$v0, subtract 26 from $v0
		#6. Return $v0
		
		#What to do if $a0 non-alphabetic char? end? return char at position of key?
EncryptChar:

	#Find ASCII value of plaintext char, assign value to $t0
	rem $t0, $a0, 128

	#Find ASCII value of key char, assign value to $t1
	rem $t1, $a1, 128
	
	#Add $t0 and $t1, store result in $v0
	add $v0, $t0, $t1

	#Subtract 65 from $v0 so it is back an ASCII character again
	sub $v0, $v0, 65

		#If 96<$a0 && $a0<123 && $v0>122, subtract 26 from $v0 and return
		bgt $v0, 122, __sub26
	
		#If 64<$a0 && $a0<91 && $v0>90, subtract 26 from $v0 and return
		bgt $v0, 90, __sub26
	
	#Return $v0 (Is this done by loading $v0 into $a2, then resuming EncryptString execution? Seems like it would be)
	la $a2, ($v0)
		b __resume

	
	#This branch subtracts 26 from the character in $v0 so it is once again an alphabetic character
	__sub26:
	sub $v0, $v0, 26
	
	#Return $v0
	la $a2, ($v0)
		b __resume