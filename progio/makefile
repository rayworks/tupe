
targets : vis prog pick zap diff

objs = ttyin.o p.o pick.o zap.o idiff.o
vs1 = vis1.o
vs2 = vis2.o
vs3 = vis3.o

vis : $(vs1) $(vs2) $(vs3)
	cc -o vs1.o $(vs1)
	cc -o vs2.o $(vs2)
	cc -o vs3.o $(vs3)

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
