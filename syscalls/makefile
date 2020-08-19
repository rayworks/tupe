
targets : simple

cat = cat.o
readslow = readslow.o

simple : $(readslow) $(cat)
	cc -o _cat.o $(cat)
	cc -o _readslow.o $(readslow)

.PHONY : cleanobj
cleanobj :
	rm *.o
