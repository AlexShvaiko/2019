/*
 * simtab.c
 *
 *  Created on: Jul 17, 2019
 *      Author: user
 */

#include "symtab.h"
#include "structs.h"
#define MAXNAME 31
#define COMNUM 20


const char *com[]={"r0","r1","r2","r3","r4","r5","r6","r7","mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop","data","string","entry","extern"};/*Reserved words*/


int islegal(char *s, struct symbol *head)
{
	int i;
	struct symbol *curent=head;
	for(i=0;i<COMNUM;i++)
	{
		if(!strcmp(s,com[i]))
		{

			return 1;
		}
	}
	while(curent)
		{


			if(strcmp(s,curent->name))
			{
				curent=curent->next;

	        }
			else
			{

				return 1;
			}


		}


return 0;



}
/*Adding a symbol to linked list adding  to top of the list  */
/*_________________________________________________________________________________________________________________________________________________________________*/

struct symbol* addsymboltab(char *name,int addr,struct symbol *head,int type1,int ext1,int line)
{
	struct symbol * node;

	if(islegal(name,head))
	{
	 printf("illegal name  in line %d \n ",line);
	 return head ;

	}

	node=(struct symbol *)malloc(sizeof(struct symbol));
	if(!node)
	{
		printf("no free memory ");
		return NULL ;
	}

	strcpy(node->name,name);
	node->address=addr;
	node->type=type1;
	node->ext=ext1;
	if(head==NULL)
	{
		head=node;
		head->next=NULL;
	}
	else
	{
		node->next=head;
	    head=node;
	}

    return head ;
}

/*__________________________________________________________________________________________________________________________________________________-*/

/*function searching a symbol in the symbol linked list and returns a number of node in the linked list .return -1if not found */
struct symbol* searchsym(char * s,struct symbol *head)
{


	while(head)
	{

		if(!strcmp(s,head->name))
		{
			return head;
		}

		if(strcmp(s,head->name))
		{
			head=head->next;


        }



	}

   return NULL ;

   }
/*____________________________________________________________________________________________________________________________________________*/












