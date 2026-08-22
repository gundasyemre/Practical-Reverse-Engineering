### Decompile sub_11732

I have no idea what the arguments or even the calling convention is (probably custom because reads [ecx] or [edx] without assigning them ) , but the most likely programming construct is switch-case because :

1-) esi register is assigned with a type int and then ;
2-) the code jumps to different routines after short blocks of decrementing the esi register , so ;
3-) dec followed by a jz can be thought of case 1 ; 2 dec instrutions followed by a jz can be thought of case 2.