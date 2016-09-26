CC := g++
Object = GraphList.o main.o

main : $(Object)
	$(CC) -o $@ $(Object)

$(Object) : GraphList.h

clean :
	rm main $(Object)


.PHONY : clean
