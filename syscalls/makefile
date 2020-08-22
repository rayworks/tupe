
targets : simple spell chkmail save waitfile timeout

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

waitfile : $(comm) waitfile.o
	cc -o _wtfile.o $(comm) waitfile.o

timeout :  $(comm) timeout.o
	cc -o _timeout.o $(comm) timeout.o


.PHONY : cleanobj
cleanobj :
	rm *.o
