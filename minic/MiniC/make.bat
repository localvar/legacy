yacc -h term.h -p -c intrprt.c minic.y
flex minic.l
del scanner.c
ren lexyy.c scanner.c
