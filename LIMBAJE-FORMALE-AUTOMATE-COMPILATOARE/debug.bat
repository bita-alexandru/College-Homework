del y.tab.h
del y.tab.c
del lex.yy.c

bison -d -t -v y.y
flex -d y.l

pause
gcc lex.yy.c y.tab.c

pause
a.exe

pause