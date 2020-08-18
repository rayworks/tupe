
targets : vis prog pick zap diff

objs = ttyin.o p.o pick.o zap.o idiff.o

vis : 
	cc -o vis1.o vis1.c 
	cc -o vis2.o vis2.c
	cc -o vis3.o vis3.c

ttyin.o : ttyin.h

prog : $(objs)
	cc -o prog.o ttyin.o p.o

pick : $(objs)
	cc -o pk.o ttyin.o pick.o

zap : $(objs) 
	cc -o zp.o ttyin.o zap.o

diff : $(objs)
	cc -o idf.o ttyin.o idiff.o

.PHONY : cleanobj
cleanobj :
	rm *.o
