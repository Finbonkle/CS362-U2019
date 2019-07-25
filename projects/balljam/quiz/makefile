
quiz:
	gcc -o quiz testme.c -coverage -fpic -lm
	-./quiz
	gcov testme.c -b

clean:
	rm -f quiz *.gcno *.gcda results.txt
