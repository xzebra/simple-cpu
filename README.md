# simple-cpu

## Instructions

There are 100 registers and are represented in this format: **__R00__**, **__R01__**, ..., **__R99__**.<br>

**MOV Rxx Ryy** - copies the value from register Rxx to register Ryy<br>
**MOV d Rxx** - copies the numeric constant __d__ (specified as a decimal) to register Rxx<br>
**ADD Rxx Ryy** - calculates (Rxx + Ryy) MOD 2^32 and stores the result in Rxx<br>
**SUB Rxx Ryy** - calculates (Rxx - Ryy) MOD 2^32 and stores the result in Rxx<br>
**DEC Rxx** - decrements Rxx by one. Decrementing 0 causes an overflow and results in 2^32-1<br>
**INC Rxx** - increments Rxx by one. Incrementing 2^32-1 causes an overflow and results in 0<br>
**INV Rxx** - performs a bitwise inversion of register Rxx<br>
**JMP d** - unconditionally jumps to instruction number d (0-based). __d__ is guaranteed to be a valid instruction number<br>
**JZ d** - jumps to instruction d (0-based) only if R00 contains 0<br>