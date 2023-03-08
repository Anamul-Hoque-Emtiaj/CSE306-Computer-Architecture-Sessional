	addi $t1,$zero,3
	subi $t2,$zero,2
	addi $t2,$t2,4
	add $t0,$t1,$t2
	sub $t3,$t1,$t2
	nor $t4,$t0,$t2
	sw $t1,3($t2)
	addi $t2,$zero,1
	addi $t3,$zero,2
	lw $t2, 4($t2)
	or $t0,$t0,$t2
	andi $t2,$t4,1
	ori $t1,$t1,5
	and $t1,$t2,$t4
