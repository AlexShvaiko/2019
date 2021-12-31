/*
 * dataf.c
 *
 *  Created on: Jul 17, 2019
 *      Author: user
 */


#include "dc.h"

/* adding data to the linked list adding to the end */

struct  dataf *adddata(int x,struct  dataf *head)
{
	struct  dataf *node=(struct  dataf * )malloc(sizeof(struct  dataf));
	struct  dataf *curent =head;

	node->variable=x;
	if(!head)
	{
		head=node;
	}
	else
	{
	 while(curent->next)
	 {
		curent=curent->next;
	 }

	curent->next=node;
	node->next=NULL;
	}
	dc++;



return head;
}












