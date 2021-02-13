 .data 
	f: .word 1
	s: .word 1
	ptr2: .word 5
	
	last_idx: .word 0,0,0,0
	arr: 	.word 'a',1,2,'b',3,4
		.word 'c',5,6,'d',7,8
		.word 'e',9,10,'f',11,12
		.word 'g',13,14,'h',15,16
	rows: .word 4
	.eqv SIZE 4
.text
	
	
	
	
	#
	lw $t3, f
	lw $t2, s
	lw $t7, ptr2
	join_list_to_list:
	while:
		#loop condition
		slt $t3, $t7, $t4
		beq $t3, $zero, exit
		#index
		addi $t0, $zero, 0
	
		#value of ptr2
		
		addi $t7, $t7, 0
	
		#index to last idx 
		la $t6, last_idx
	
		#value of idx[f]
		
		lw $t5, last_idx($t3)
	
		#value of idx[s]
		
		lw $t4, last_idx($t2)
	
		
		#last_idxf = t5 //// f t3
		#s t2 
		#base = row index = 240
		#row
		mul $s7, $t2, 240
		#col 
		mul $s6, $t7, 12
		#address of row+col s7 has the beginig index of struct
		add  $s7, $s7, $s6
		#char c
		lw $s6, arr($s7)
		#int nofc
		addi $s7, $s7, 4 
		lw $s5, arr($s7)
		#int pri
		addi $s7, $s7, 4 
		lw $s4, arr($s7)
		##############Assign to arr
		#get asignee
		#row
		mul $s7, $t3, 240
		#col 
		mul $s4, $t5, 12
		#Calc index
		add $s7, $s7, $s4
		#Char
		sw $s6, arr($s7 )
		#Calc index
		addi $s7, $s7, 4
		# nofc
		sw $s5,  arr($s7 )
		#Calc index
		addi $s7, $s7, 4
		# nofc
		sw $s4,  arr($s7 )
		
		
		
		
		#increment 2 vars
		addi $t5, $t5, 1
		addi $t7, $t7, 1
		
		
		
		
		j while
	exit:
		#j actual_size[f]+=actual_size[s];
		#j destroy_list(s);
