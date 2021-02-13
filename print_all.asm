.data 
	# char => nofc => pr
	res: .word 'a',1,2,'b',3,4
	last_idx_res: .word 24
	x: .asciiz " repeated "
	time: .asciiz " time/s ,prirority is: "
	
	pir: .asciiz " ,prirority is:"
	end: .asciiz "\n" 
.text
	#li $v0, 1
	#lw $a0, struct
	
	#index
	addi $t0, $zero, 0
	# aX1 prirority is 2./n
	#print_all_requests:
	while:
		beq $t0, 24, exit
		#name of P
		lw $t1, res($t0)
		addi $t0, $t0, 4
		li $v0, 11
		move $a0, $t1
		syscall
		# text
		li $v0, 4
		la $a0, x
		syscall
		#  nofc
		lw $t1, res($t0)
		addi $t0, $t0, 4
		li $v0, 1
		move $a0, $t1
		syscall
		# text
		li $v0, 4
		la $a0, time
		syscall
		# pirority
		lw $t1, res($t0)
		addi $t0, $t0, 4
		li $v0, 1
		move $a0, $t1
		syscall
		#text
		li $v0, 4
		la $a0, end
		syscall
		
		j while
	exit:
