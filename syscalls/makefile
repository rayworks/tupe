
targets : simple spell chkmail save

objs = ../progio/ttyin.o spname.o 
comm = err.o

cat = cat.o
readslow = readslow.o
cp = cp.o


err.o : err.h

simple : $(readslow) $(cat) $(cp) $(comm)
	cc -o _cat.o $(cat)
	cc -o _readslow.o $(readslow)
	cc -o _cp.o $(comm) $(cp) 

spell : $(objs)
	cc -o sp.o $(objs)

chkmail : $(comm) checkmail.o
	cc -o _chkmail.o $(comm) checkmail.o

save : $(comm) sv.o
	cc -o _save.o $(comm) sv.o


.PHONY : cleanobj
cleanobj :
	rm *.o
