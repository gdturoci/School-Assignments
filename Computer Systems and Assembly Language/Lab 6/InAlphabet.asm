#__InAlphabet: Determines if a given character is in the alphabet or not
__InAlphabet:
	
	#Find ASCII value of given char ($a0), store that value in $t0
	rem $t0, $a0, 128

		#If char is <65, return false
		blt $t0, 65, __returnfalse
	
		#If char is >122, return false
		bgt $t0, 122, __returnfalse
	
		#If char is (64<)$t0<91, return true
		blt $t0, 91, __returntrue
	
		#If char is 96<$t0(<123), return true
		bgt $t0, 96, __returntrue
	
		#Else, return false
		b __returnfalse