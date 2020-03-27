NAME: JAY ABI-SAAD
ID: 260801368

THIS ASSIGNMENT WAS BUILT USING: mimi.cs.mcgill.ca

TO COMPILE AND RUN THE CODE:
1) gcc -c shell.c interpreter.c shellmemory.c cpu.c kernel.c pcb.c ram.c memorymanager.c
2) gcc -o mykernel shell.o interpreter.o shellmemory.o cpu.o kernel.o pcb.o ram.o memorymanager.o
3) ./mykernel

RULES:
-Please make sure to always add an extra empty trailing line in EACH of the txt files. My code ASSUMES that this is the case.
-Regarding errors, the assignment document is EXTREMELY unclear, and Piazza was full of contradicting messages,
 therefore, here are MY assumptions on the errors based on the assignment doc:
 i)When running exec, if one of the scripts does not exist, then the WHOLE exec command is cancelled. (ram is cleared and exec aborted)
 ii)When running exec, if there are duplicates of scripts, then the WHOLE exec command is cancelled. (ram is cleared and exec aborted)
 iii)When running exec, if one of the scripts makes the ram go over the limit, then the WHOLE exec command is cancelled. (ram is cleared and exec aborted)

 IMPORTANT NOTES:
 - The "./mykernel < testfile.txt" command seems to not read the tesfile.txt lines well. Please just compile and run the program in the regular way (gcc).
 - The executable doesn't seem to have access to the .txt files. Again, please just compile and run the program in the regular way (gcc).