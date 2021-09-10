
main : vector.o heap.o heapify.o pq_heap.o scheduler.o uid.o task.o MMI.o common.o
	gcc -shared -Wl,-soname,libwd.so -o libwd.so ./*.o; \
	gcc -pedantic-errors -Wall -Wextra -g -pthread -c -fPIC WD.c -I ./include/; \
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC user_app.c -I ./include/; \
	gcc WD.o -L. -lwd -lpthread -Wl,-rpath,./ -o WD.out; \
	gcc user_app.o -L. -lwd -lpthread -Wl,-rpath,./ -o user_app.out; \
		

vector.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC vector.c -I ./include/ 

heap.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC heap.c -I ./include/ 

heapify.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC heapify.c -I ./include/ 

pq_heap.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC pq_heap.c -I ./include/ 

scheduler.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC scheduler.c -I ./include/ 

uid.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC uid.c -I ./include/ 

task.o		:
	gcc -pedantic-errors -Wall -Wextra -g -c -fPIC task.c -I ./include/

MMI.o		:
	gcc -pedantic-errors -Wall -Wextra -g -pthread -c -fPIC MMI.c -I ./include/

common.o		:
	gcc -pedantic-errors -Wall -Wextra -g -pthread -c -fPIC common.c -I ./include/
		


clean:
	rm *.o; \
	rm *.so; \
	rm *.out
