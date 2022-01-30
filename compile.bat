@echo on
::pass arguements folder and then the file name less the .c
:: -lws2_32 is the forced import for winsock2.h
gcc %CD%\%1.c -o %CD%\test%1.exe -lws2_32 
