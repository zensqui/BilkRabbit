@echo on
:: -lws2_32 is the forced import for winsock2.h
gcc .\main.c -o test.exe -lws2_32 
