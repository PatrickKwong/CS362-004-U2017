#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	
	// Looking at the characters I need to hit to get from state 0 to state 9
	// I need to return rand the following ASCII characters:
	// '[', '(', '{', ' ', 'a', 'x', '}', ')', ']'
	// to fulfill 9 if statements to get from state 0 to state 9
	
	char c;
	
	// Implementation 1
	// random pick from a pool of just the characters needed to get to state 9
	// char chars[9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
	// c = chars[rand() % 9];
	
	// Implementation 2
	// range of ACSII Characters from Space to } 
	c = (rand() % (126 - 32) + 32);
	
	// Implementation 3
	// range of all ASCII characters
	// c = (rand() % 255);
	
    return c;
}

char *inputString()
{
    // TODO: rewrite this function
	// need to randomly create string - reset\0
	
	int i;
	int stringSize = 6;
	char *s = malloc(sizeof(char) * stringSize);
	
	// Implementation 1
	// random pick from a pool of just the characters needed fulfill the 10th if statement
	char chars[5] = {'r', 'e', 's', 't', '\0'};
	for (i = 0; i < stringSize; i++)
		s[i] = chars[rand() % 5];

	// Implementation 2
	// range of ACSII Characters from NULL (Dec. 0) to t (Dec. 116)
	// for (i = 0; i < stringSize; i++)
	//	s[i] = (rand() % 116);
	
	// Implementation 3
	// range of all ASCII characters
	//for (i = 0; i < stringSize; i++)
	//	s[i] = (rand() % 255);

	// return "reset";
    return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
