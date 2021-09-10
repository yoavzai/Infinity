#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "exercise.h"

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1b[0m"
#define REQUIRE(cond) ((cond) ? printf(GREEN"SUCCESS\n") : printf(RED"FAIL\n"))
#define WORD_SIZE sizeof(size_t)

void AtoiTest()
{
	REQUIRE(Atoi("1111101001101111001101111", 2) == 32824943);
	REQUIRE(Atoi("2021202200100122", 3) == 32824943);
	REQUIRE(Atoi("1331031321233", 4) == 32824943);
	REQUIRE(Atoi("31400344233", 5) == 32824943);
	REQUIRE(Atoi("3131315155", 6) == 32824943);
	REQUIRE(Atoi("546002354", 7) == 32824943);
	REQUIRE(Atoi("175157157", 8) == 32824943);
	REQUIRE(Atoi("67680318", 9) == 32824943);
	REQUIRE(Atoi("32824943", 10) == 32824943);
	REQUIRE(Atoi("1758a958", 11) == 32824943);
	REQUIRE(Atoi("ABabABb", 12) == 32824943);
	REQUIRE(Atoi("6A53A58", 13) == 32824943);
	REQUIRE(Atoi("450662B", 14) == 32824943);
	REQUIRE(Atoi("2D35D98", 15) == 32824943);
	REQUIRE(Atoi("1F4dE6F", 16) == 32824943);
	REQUIRE(Atoi("1620420", 17) == 32824943);
	REQUIRE(Atoi("H6c79H", 18) == 32824943);
	REQUIRE(Atoi("d4GCFB", 19) == 32824943);
	REQUIRE(Atoi("A53273", 20) == 32824943);
	REQUIRE(Atoi("80G8KB", 21) == 32824943);
	REQUIRE(Atoi("682G2J", 22) == 32824943);
	REQUIRE(Atoi("526JLA", 23) == 32824943);
	REQUIRE(Atoi("42MBHN", 24) == 32824943);
	REQUIRE(Atoi("390JMI", 25) == 32824943);
	REQUIRE(Atoi("2JLFFL", 26) == 32824943);
	REQUIRE(Atoi("27KI9H", 27) == 32824943);
	REQUIRE(Atoi("-1PB8FB", 28) == -32824943);
	REQUIRE(Atoi("1HBPOH", 29) == 32824943);
	REQUIRE(Atoi("1AFM4N", 30) == 32824943);
	REQUIRE(Atoi("14GQ24", 31) == 32824943);
	REQUIRE(Atoi("V9NJF", 32) == 32824943);
	REQUIRE(Atoi("RMD98", 33) == 32824943);
	REQUIRE(Atoi("OJ59H", 34) == 32824943);
	REQUIRE(Atoi("LUKUI", 35) == 32824943);
	REQUIRE(Atoi("JJJVZ", 36) == 32824943);
	printf(RESET);
}

void PrintUniqueTest()
{
	PrintUnique("abs", "baaaaassu", "sopopoppon");
	PrintUnique("1-k2ef-0k", "f12enbv", "k0-f");
	PrintUnique("yoav", "tomer", "hadass");
	PrintUnique("1234", "125", "12345");
}

int main()
{
	AtoiTest();
	PrintUniqueTest();
	WhichEndian();

	return 0;
}

