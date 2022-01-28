@echo on
gcc .\main.c -o test.exe -lws2_32 REM -lws2_32 is the forced import for winsock2.h
