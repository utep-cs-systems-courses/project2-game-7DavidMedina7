	.arch msp430g2553
	.p2align 1,0
	.text

	.extern SecCnter
	.extern DimCnter
	.extern SeCnter2
	.extern LED_GREEN
	.extern LED_RED		
	.extern P1OUT
	.global dim_light

dim_light:
	mov #0, r12
	call #buzzer_set_period
	add #1, &SecCnter2
	cmp #256, &SecCnter2
	jnc Out

	mov #0, &SecCnter2
	cmp #4, &DimCnter
	jnc Out1
	mov #0, &DimCnter
	jmp Out

Out1:
	add #1, &DimCnter

Out:
	cmp #4, &SecCnter
	jnc Out2
	mov #0, &SecCnter	
	bis #0x01, &P1OUT

			;not LED_GREEN
	bic #0x40, &P1OUT
	jmp outFinal

Out2:
	cmp &SecCnter, &DimCnter
	jnc Out3
	add #1, &SecCnter
	jmp outFinal

Out3:
			;not LED_RED
	bic #0x01, &P1OUT
	bis #0x40, &P1OUT
	add #1, &SecCnter

outFinal:
	pop r0









	
