/*
 * readb.h
 *
 *  Created on: Aug 11, 2019
 *      Author: user
 */

#ifndef READB_H_
#define READB_H_
#include "structs.h"
#include  <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void blank(char**);
struct symbol* searchsym(char * s,struct symbol *head);
int getic();
int getdc();
int isreg(char buf[MAX_DOT_OP]);
memoryWord code[MAXINT];
int arraypointer;
struct entry * listentry;
extern struct symbol* head;
extern int flag;

#endif /* READB_H_ */
