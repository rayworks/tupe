
targets : simple spell

objs = ../progio/ttyin.o spname.o

cat = cat.o
readslow = readslow.o
cp = cp.o

simple : $(readslow) $(cat) $(cp)
	cc -o _cat.o $(cat)
	cc -o _readslow.o $(readslow)
	cc -o _cp.o $(cp)

spell : $(objs)
	cc -o sp.o $(objs)

.PHONY : cleanobj
cleanobj :
	rm *.o
