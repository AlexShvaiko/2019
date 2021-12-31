/*
 * asembler.c
 * The main file.
 *This file manages the assembling process.
 *It calls the first and second read methods, and then creates the output files.
 */

#include "asembler.h"

int flag=0;




/*asembler
 *
 *
 */


/*-------------------------------------------------------------------------------------------------------------------*/
int main(int argc,char * argv[])
{
	FILE *fp;




	fp=fopen(argv[1],"r");
	if(argc==1)
	{
	        printf("\n please  enter a file name\n");
	        return 0;
	}




	firstmain(fp);
	fclose(fp);
	secondmain(argv[1]);



	return 0;
}
