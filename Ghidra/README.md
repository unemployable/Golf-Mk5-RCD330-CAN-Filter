# Golf Mk5 RCD330 CAN Filter - Ghidra Reverse Engineering Files #
## Chinese CAN Filter Black Box ##

These devices only seem to be available as part of an adapter cable.<BR>
I've found at least two versions, with only minor differences in the code.

Included are an original dumped binary, Ghidra package file (gzf) & an export of the decompiled 'C' code.
  
It makes use of Thomas Roth's excellent SVD-Loader scripts.

This is my first, amateur attempt to decompile an STM32 binary.<BR>
I have tried to include as many comments as possible, to assist with my understanding of the code.

The most interesting function is the CAN interrupt routine *FUN_CAN_INT_MAIN_080004d8()*, where the message filtering takes place.
  
It is far easier to navigate through the code when loaded into Ghidra via the gzf file.<BR>
The 'C' code is mostly structure definitions of the peripherals, but still helpful if you don't want to install Ghidra.
