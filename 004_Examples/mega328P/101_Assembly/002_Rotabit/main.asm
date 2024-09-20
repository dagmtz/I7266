; .include "m328pdef.inc"

	.def	mask 	= r16		; mask register
	.def	oLoopR 	= r18		; outer loop register
	.def	iLoopRl = r24		; inner loop register low
	.def	iLoopRh = r25		; inner loop register high

	.equ	oVal 	= 71		; outer loop value
	.equ	iVal 	= 14084		; inner loop value

	.cseg
	.org 	0x00
	ldi	mask,0xFF		; load 11111111 into mask register
	out     DDRD,mask		; write mask register to DDRD
	ldi	mask,0x00		; load 0 into mask register
	out     PORTD,mask		; write mask register to PORTD
	sec				; set carry flag

start:	rol	mask			; rotate left through carry the mask register
	brcs	init
	out	PORTD,mask		; write mask register to PORTD

	ldi	oLoopR,oVal		; initialize outer loop count

oLoop:	ldi	iLoopRl,LOW(iVal)	; intialize inner loop count in inner
	ldi	iLoopRh,HIGH(iVal)	; loop high and low registers

iLoop:	sbiw	iLoopRl,1		; decrement inner loop registers
	brne	iLoop			; branch to iLoop if iLoop registers != 0

	dec	oLoopR			; decrement outer loop register
	brne	oLoop			; branch to oLoop if outer loop register != 0

	rjmp    start			; stay in infinite loop

init:	sec
	rjmp	start