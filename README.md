# simple-cpu

## Instructions

**MOV Rxx Ryy** - copies the value from register Rxx to register Ryy;
**MOV d Rxx** - copies the numeric constant __d__ (specified as a decimal) to register Rxx;
**ADD Rxx Ryy** - calculates (Rxx + Ryy) MOD 2^32 and stores the result in Rxx;
**DEC Rxx** - decrements Rxx by one. Decrementing 0 causes an overflow and results in 2^32-1;
**INC Rxx** - increments Rxx by one. Incrementing 232-1 causes an overflow and results in 0;
**INV Rxx** - performs a bitwise inversion of register Rxx;
**JMP d** - unconditionally jumps to instruction number d (1-based). __d__ is guaranteed to be a valid instruction number;
**JZ d** - jumps to instruction d (1-based) only if R00 contains 0;