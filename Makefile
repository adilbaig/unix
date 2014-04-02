clocks :
	gcc -Wall -W -O2 -lrt -g -o bin/clocks time/clocks.c
	
timeofday :
	gcc -Wall -W -O2 -lrt -g -o bin/timeofday time/timeofday.c