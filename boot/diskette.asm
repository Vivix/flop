org 7c3eh

	call enter_vga

;***************
;* LET'S GET FREAKY
	mov al,64h
	mov cx,0c82h
lappy:
	stosb
	loop lappy
;
	mov al,32h
	mov cx,0780h
lappy2:
	stosb
	loop lappy2

;***************
;* DECODER
;*
decoder:				;es should be set up by enter_vga
	mov si,disk
	xor di,di			;zero di for 0,0 xy
	mov cx,33h			;length, in lines, of our image
.lp:
	mov bl,[si]			;get x
	inc si				;keep incrementing our reading addr

	xor ax,ax
	xor dx,dx			;zero dx just in case of garbage
	lodsb				;calculate our position on every line to keep func size down
	mov dl,al
	shl ax,6
	shl dx,8
	add ax,dx			;(ax * 2^8) + (bx * 2^6)
	add al,bl			;add x to our row number

	mov di,ax			;[es:di]

	mov al,[si]			;set our colour
	inc si				;mlf originally used a colour table, but 256 is already a colour table.

	push cx				;store our line decrement counter
	xor cx,cx
	mov cl,[si]			;get our line len
	inc si

.write_loop:
	stosb
	loop .write_loop
	pop cx
	loop .lp

;***Write our message, slow but SMALL.
wrut:
	mov ah,02h
	xor bh,bh
	mov dh,03h
	mov dl,00h
	int 10h				;set our initial cursor position

	mov si,string
.lp:
	mov ah,09h
	mov bh,14h
	mov bl,05h
	mov cx,01h
	lodsb
	or al,al
	jz .end
	int 10h				;write our character

	inc byte [.cursor]
	mov ah,02h
	xor bh,bh
	mov dh,03h
	mov dl,[.cursor]
	int 10h				;increment our cursor
	jmp .lp
.cursor:	db	0
.end:


;********END****
	xor ah,ah
	int 16h

jmp $	;do a soft reboot here.

;	call exit_vga
;	mov ax,4c00h
;	int 21h		;dos exit. used for org 100h tests.

;===nodisk.mlf
;body = 0ch
;hair = 2bh
;eyes = 4fh
;drk  = 12h
;mth  = 04h
disk:
db 06h,01h,0ch,01h,0ah,01h,0ch,01h
db 06h,02h,2bh,04h,0ah,02h,0ch,01h
db 03h,03h,2bh,07h,0ah,03h,0ch,01h,0bh,03h,2bh,02h
db 02h,04h,2bh,06h,08h,04h,0ch,04h,0ch,04h,2bh,01h
db 02h,05h,2bh,03h,05h,05h,0ch,02h,07h,05h,12h,02h,09h,05h,0ch,03h,0ch,05h,2bh,01h
db 01h,06h,2bh,03h,04h,06h,0ch,03h,07h,06h,4fh,02h,09h,06h,12h,01h,0ah,06h,0ch,02h,0ch,06h,2bh,01h
db 01h,07h,2bh,01h,03h,07h,0ch,04h,07h,07h,4fh,02h,09h,07h,12h,01h,0ah,07h,0ch,02h,0ch,07h,2bh,01h
db 03h,08h,0ch,01h,04h,08h,04h,02h,06h,08h,0ch,02h,08h,08h,12h,01h,09h,08h,0ch,03h,0ch,08h,2bh,01h
db 04h,09h,04h,02h,06h,09h,0ch,05h,0bh,09h,2bh,02h
db 06h,0ah,0ch,05h,0bh,0ah,2bh,02h
db 05h,0bh,0ch,05h,0ah,0bh,2bh,03h
db 04h,0ch,0ch,05h,09h,0ch,0ch,03h
db 04h,0dh,0ch,06h,0ah,0dh,2bh,01h,0bh,0dh,0ch,02h
db 03h,0eh,0ch,08h,0bh,0eh,2bh,01h,0ch,0eh,0ch,02h
db 03h,0fh,0ch,0ch
db 00h,10h,0fh,0a0h,0a0h,10h,0fh,0a0h

;**************
;* FUNCTIONS
;*
enter_vga:
	mov ax,0013h		;change into mode 13
	int 10h
	push 0a000h			;set up [es:di] for printing to video memory
	pop es
	ret

;exit_vga:
;	mov ax,0003h		;change into mode 03 (should be 80x25 16clr textmode)
;	int 10h
;	ret

string: db 22h,"I am not a system disk!",22h,0