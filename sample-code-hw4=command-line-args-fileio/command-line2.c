#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	if (argc !=3){
		printf ("Usage: a.exe <int> <filename>\n");
		return 1;
	}
	
	int i = atoi(argv[1]);
	char *fname = argv[2];
	printf("Program name: %s\n", argv[0]);
	printf("Line width: %d\n", i);
	printf("Filename: %s\n", fname);
	
	strcat(fname,".txt");
	printf("Full Filename: %s\n", fname);
	
	return 0;
}