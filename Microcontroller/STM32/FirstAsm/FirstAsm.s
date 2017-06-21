		GLOBAL Reset_Handler
		AREA Reset, CODE, READONLY
		ENTRY
Reset_Handler
		MOV	r0, #0x123
		EOR r1,r1,r1
		MOV r1,r0
	
stop	B	stop
		END