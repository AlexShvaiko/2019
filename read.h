/*
 * read.h
 *
 *  Created on: Jul 24, 2019
 *      Author: user
 */

#ifndef READ_H_
#define READ_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "structs.h"
#define FILES 3
void data(char *p, int line);
void string1(char *p, int line);
void entry(char *p, int line);
void extern1(char *p, int line);
void blank(char **c);
void isdot(char *,int);
void islabele(char*,int );
void comleb(char*,int );
void iscomand(char*,int );
struct  dataf *datahead;
struct symbol *addsymboltab(char  name1[],int addr,struct symbol *head,int type1,int ext1,int line);
struct  dataf *adddata(int vir,struct  dataf *head);
struct symbol* searchsym(char * s,struct symbol *head);
struct symbol* head;
struct  dataf *datahead;
extern int flag;
extern struct symbol* head;


#endif /* READ_H_ */

