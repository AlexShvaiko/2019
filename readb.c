/*
 * read2.c
 *Second read checking  the  the code and comparing to the data base that was created due a first read
 */
#include "readb.h"

/*crating a file with a file name s+end */

FILE * fileopen(char *s,char *end,char *type)
{
	FILE *fp;
	char *temp;
		temp=strtok(s,".");
		temp=strcat(s,end);

fp=fopen(temp,type);


return fp;
}
/************************************************************************************************************************************/


/*changing presentation for 12 bits for negative numbers*/
int negativenum2(int x)
{
	int i=0,num=0;
	unsigned int y=1;

	x=(-x);
	while(i<NUMBITSCOM)
		{
			if(!(x&y))
			{

				num=num|y;

			}
			i++;
			y=y<<1;
		}
    num=num+1;



	return num;
			}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*adding entry/extern to linked list */
void addentry(struct entry * head ,char *name,int adr,int ext)
{
 struct entry *curent ;
 struct entry *node ;
  node=(struct entry *)malloc(sizeof(struct entry));
  curent=head;
   strcpy(node->name,name);
   node->ext=ext;
   node->address=(adr);

	if(head==NULL)
	{
		listentry=node;

	}
	else
	{
		while(curent->next)
		{
			curent=curent->next;


		}
		curent->next=node;

	}




	return;
}


/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Coding to the array function without operands */
void rts2(char *cp,int opcode)
{
	code[arraypointer].valueBits.cmdBits.opcode=opcode;
	code[arraypointer].era= ABSOLUTE;
	arraypointer++;
	return;



}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Checking if the label  is a macro returns -1 if its not macro or the label not found
 * */
int checkmacro(char *cp)
{
	int val=0,i;
	struct symbol * temp;
	char buf[MAX_DOT_OP];
	char * ctemp=cp;

    for(i=0;*cp!=' '&&*cp!='['&&*cp!=','&&i<MAX_DOT_OP&&*cp!='\0';i++,cp++)
					    {
						   buf[i]=*cp;

					    }
					     buf[i]='\0';
       temp=searchsym(buf,head);

if(temp==NULL||temp->type!=1)
{
	flag++;
	printf("the operand %s is not macro \n",ctemp);
	return -1;

}
val=temp->address;




return val;
}



/* coding a number or a macro to the array */
/*--------------------------------------------------------------------------------------------------------------------------------*/
void addnum(char *cp)
{

		char data[MAXDATA+1];
		int i=0,x;
		blank(&cp);


		 if(*cp=='-'||*cp=='+')
		 {
			 data[i]=*cp;
			 cp++;
			 i++;

		 }


 for(;(MAXDATA>=i&&isdigit(*cp))||(MAXDATA>=i&&isalpha(*cp)&&*cp!=','&&*cp!=' '&&*cp!= ']'&&*cp!='\0');i++,cp++)
{
		 					   data[i]=*cp;

		 }
		 				   data[i]='\0';
		 				   blank(&cp);
	if(!isalpha(data[0]))

	{
		x=atoi(data);
	}

		if(isalpha(data[0]))
		{

			x=checkmacro(data);
		}


		 	if(x<0)
		 	{
		 		 x=negativenum2(x);
		 		}
     if(x!=-1)
     {



		code[arraypointer].valueBits.value=x;
		code[arraypointer].era= ABSOLUTE;

     }

		arraypointer++;
		return;
}
/*-----------------------------------------------------------------------------------------------------------------*/
/*adding a label code to the array*/
void codelabel(char *cp)
{
	struct symbol *temp;
	temp=searchsym(cp,head);
 if(temp==NULL)
 {
	 flag++;
	 printf("Declaration not found %s\n",cp);
	 return;
 }
 if(temp->ext==1)
 {
	 addentry(listentry,cp,arraypointer+STARTADDRESS,1);
	 code[arraypointer].era=EXTENAL ;
	 arraypointer++;
	 return;


 }
 else
 {
	 code[arraypointer].valueBits.value=temp->address;
	 code[arraypointer].era=RELOCATABLE ;
 }


 arraypointer++;
 return;

}
/*-----------------------------------------------------------------------------------------------------------------------------*/
/*coding a register to the array*/
void codereg(char *cp,char * buf)
{
	int i=0;
	struct reg{
		char* name;
		int val;
	}
	reg[]={{"r0",0},{"r1",1},{"r2",2},{"r3",3},{"r4",4},{"r5",5},{"r6",6},{"r7",7},{"  ",EOF}};

 while(reg[i].val!=EOF)
 {
	 if(!strcmp(buf,reg[i].name))
	 {
		 break;
	 }
	 i++;

 }
 if(reg[i].val==EOF)
 {
	 return;
 }
 if(*cp==',')

	 code[arraypointer].valueBits.regBits.srcBits=reg[i].val;

 else
	 code[arraypointer].valueBits.regBits.destBits=reg[i].val;


 arraypointer++;

 return;


}


/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*checking a operand before coding */
void addoneoperand (char *cp)
{
 char buf[MAX_DOT_OP];
 int i;

 blank(&cp);

 if(*cp=='#')
 {
	 cp++;
	 addnum(cp);
	 return;

 }
 else{


    for(i=0;*cp!=' '&&*cp!='['&&*cp!=','&&i<MAX_DOT_OP&&*cp!='\0';i++,*cp++)
					    {
						   buf[i]=*cp;

					    }
					     buf[i]='\0';
 }
     blank(&cp);
     if(isreg(buf))
     {
    	 codereg(cp,buf);
    	 return;

     }


     if(*cp==','||*cp==','||*cp=='\0'||*cp==' ')
     {
    	 codelabel(buf);
     }
     if(*cp=='[')
     {
    	 codelabel(buf);
    	 addnum(cp+1);
     }





return;
}










/*coding all function with only one operand */


/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void not2(char * cp,int opcode)
{
	char *temp;
		char buf[MAX_DOT_OP];
		int i;
		int des;
		blank(&cp);
		temp=cp;

			if(*temp=='#')
				{
					des=0;
					for(;*temp!='\0';temp++);

				}
			else
			{
			for(i=0;*temp!=' '&&*temp!='['&&*temp!=','&&i<MAX_DOT_OP&&*temp!='\0'&&*temp!='\n';i++,*temp++)
		    {
			   buf[i]=*temp;

		    }
		     buf[i]='\0';


			if(isreg(buf))
			{
				des=3;

			}
			  if((*temp=='\0'||*temp=='\n'||*temp==' ')&&!isreg(buf))
				 {
							des=1;
							blank(&temp);
							temp++;


				}
			  if(*temp=='[')
			  		{
			  			des=2;
			  			for(;*temp!=' '&&temp!='\0';temp++);
			  			 temp++;

			  				}
			}


			 code[arraypointer].valueBits.cmdBits.opcode=opcode;
			 code[arraypointer].valueBits.cmdBits.dest=des;
			 code[arraypointer].valueBits.cmdBits.src=ABSOLUTE;
			 code[arraypointer].era= ABSOLUTE;



			 arraypointer++;
			 addoneoperand (cp);
			 return;




}
/* this  checking if the command  is entry if yes adding to the linked list  */

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void dot(char * cp)
{
	int i=0;
	struct symbol* curent;
	char  buf[MAX_COMANS_SIZE];
	for(i=0;*cp!=' ';i++,cp++)
	 {
		buf[i]=*cp;

	 }
	 buf[i]='\0';
	 blank(&cp);

	 if(!strcmp(buf,"entry"))
	 {
		 for(i=0;*cp!=' '&&*cp!='\0'&&*cp!='\n';i++,cp++)
		 		 		 	 {
		 		 		 		buf[i]=*cp;

		 		 		 	 }

		 		 		      buf[i]='\0';
		 		 		   curent= searchsym(buf,head);

		 		 		   if(curent==NULL)
		 		 		   {
		 		 			   printf("entry label not found line %s\n",buf);
		 		 			   flag++;
		 		 			   return;
		 		 		   }


		 		      addentry(listentry ,curent->name,curent->address,ABSOLUTE);
		 		      return;

	 }







return;

}
/*coding the registers if used if both of the operands are registers */
/*--------------------------------------------------------------------------------------------------------------------*/
void coderegisters(char *cp)
{
	int reg1,reg2;

	for(;!isdigit(*cp);cp++);
	reg1=atoi(cp);
	for(;!isdigit(*cp);cp++);
	reg2=atoi(cp);
	code[arraypointer].valueBits.regBits.srcBits=reg1;
	code[arraypointer].valueBits.regBits.destBits=reg2;

	arraypointer++;
	return;




}










/*Checking all tow operand commands and transfer the operand to coding functions
 * coding the function to the array.
 * */

/*--------------------------------------------------------------------------------------------------------------------*/
void mov2(char *cp,int opcode)
{
	char *temp;
	char buf[MAX_DOT_OP];
	int i;
	int sor=0,des;
	blank(&cp);
	temp=cp;

	if(*temp=='#')
	{
		sor=0;
		for(;*temp!=',';temp++);
	}
	else
	{

		for(i=0;*temp!=' '&&*temp!='['&&*temp!=','&&i<MAX_DOT_OP;i++,*temp++)
						    {
							   buf[i]=*temp;

						    }
						   buf[i]='\0';
						   blank(&temp);
						   if(isreg(buf))
						   {

							   sor=3;
							   temp++;

						   }
						   if(*temp==','&&!isreg(buf))
						   {
							   sor=1;
							   blank(&temp);
							   temp++;


						   }
						   if(*temp=='[')
						   {
							   sor=2;
							   for(;*temp!=',';temp++);
							   temp++;

						   }

	}
	blank(&temp);
	if(*temp=='#')
		{
			des=0;
			for(;*temp!='\0';temp++);

		}
	else
	{
	for(i=0;*temp!=' '&&*temp!='['&&*temp!=','&&i<MAX_DOT_OP&&*temp!='\0'&&*temp!='\n';i++,*temp++)
    {
	   buf[i]=*temp;

    }
     buf[i]='\0';

	if(isreg(buf))
	{
		des=3;

	}
	  if((*temp=='\0'||*temp=='\n')&&!isreg(buf))
		 {
								   des=1;
								   blank(&temp);
								   temp++;


		}
	  if(*temp=='[')
	  		{
	  			des=2;
	  			for(;*temp!=' '&&temp!='\0';temp++);
	  			 temp++;

	  				}
	}


	  code[arraypointer].valueBits.cmdBits.opcode=opcode;


	 code[arraypointer].valueBits.cmdBits.dest=des;
	 code[arraypointer].valueBits.cmdBits.src=sor;
	 code[arraypointer].era=ABSOLUTE ;



	 arraypointer++;
	 if(sor==3&&des==3)
	 {
		 coderegisters(cp);
		 return;
	 }


 addoneoperand (cp);
 for(;*cp!=',';cp++);
 cp++;
 addoneoperand (cp);



return;

}
/*checking the comand and use a correct function */
/*-------------------------------------------------------------------------------------------------------------------*/
void command(char *cp)
{
	 int i=0;
	 char buf[MAX_DOT_OP];


	struct{
			char *name;
			int opcode;
			void (*func)(char *cp,int opcode);
		}
		cmd2[]={
				{"mov",0,mov2},
				{"cmp",1,mov2},
				{"add",2,mov2},
				{"sub",3,mov2},
				{"not",4,not2},
				{"lea",5,mov2},
				{"clr",6,not2},
				{"inc",7,not2},
				{"dec",8,not2},
				{"jmp",9,not2},
				{"bne",10,not2},
				{"red",11,not2},
				{"prn",12,not2},
				{"jsr",13,not2},
				{"rts",14,rts2},
				{"stop",15,rts2},
				{"Unknown command ",0,NULL}
		};


		for(i=0;*cp!=' '&&cp!='\0'&&*cp!='\n'&&i<MAX_DOT_OP;i++,cp++)
		 {
			    buf[i]=*cp;



				}
			   buf[i]='\0';

			   i=0;



		  while(cmd2[i].func!=NULL)
			{


			  if(!strcmp(cmd2[i].name,buf))
			 {

					(*(cmd2[i].func))(cp,cmd2[i].opcode);
					return;
			}
					 i++;
			 }




	return;

}

/*labelorcomand-checking if the line starting with label or command if it command
 * passing the original  pointer else passing the label and passing pointer the pointer to command function
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
void labelorcomand(char *cp)
{
	char *temp=cp;


	for(;*temp!=':'&&*temp!=' '&&*temp!='\0';temp++);
	if(*temp==':')
	{
		temp++;
		blank(&temp);
		command(temp);

	}
	else
	{

	  command(cp);
	  return;



	}


return;

}





/*------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Checking if the line starting this command ,label or avoiding blanks and comments */
void firs2tcheck(char * cp)
{
	blank(&cp);
	if(*cp==';'||*cp=='\0')
	{

		return;
	}


	if(((*cp)>='A'&&(*cp)<='Z')||((*cp)>='a'&&(*cp)<='z'))
	{

		labelorcomand(cp);


		  return ;
	}

	if(*cp=='.')
		  {
		    cp++;

		    dot(cp);


			  return ;
		  }


	 return;
	}



/*------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*reading from file  char bay char and saving a string string */
FILE * read2(FILE *fp)
{
	char buf[BUF_SIZE];
	char *cp=buf;
	int c;
	int counter=0;


	do {
		      c=fgetc(fp);
		      if( feof(fp) ) {
		         break ;
		      }
		      if(c=='\n'||c=='\r')/*Checking for windows file  */
		      {

		    	  buf[counter]='\0';
		      }

		      else
		      buf[counter]=c;

		      counter++;


		   } while(counter<BUF_SIZE&&c!='\n'&&c!='\r');

    blank(&cp);

	firs2tcheck(cp);
	 if(c=='\r')
		   {
			fseek(fp,SEEK_CUR,1);
		   }

return fp;
}
/*printing the entry labels to the file
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------*/
void printentry(FILE *fp)
{
	struct entry*cur=listentry;
	while(cur!=NULL)
	{

		if(cur->ext==0)
		{

			fprintf(fp,"%d\t%s\n",cur->address,cur->name) ;
		}

		cur=cur->next;
	}

	return;

}
/*printing the externs from the linked  list to the file*/
/*----------------------------------------------------------------------------------------------------------------------------------*/
void printext(FILE *fp)
{
	struct entry*cur=listentry;
	while(cur!=NULL)
	{

		if(cur->ext==1)
		{

			fprintf(fp,"%d\t%s\n",cur->address,cur->name) ;
		}

		cur=cur->next;
	}

	return;

}
/*converting the 14 bits number to base 4 sends back  a string only for memoryWord struct  */
/*----------------------------------------------------------------------------------------------------------------------------------*/
char * changebase( memoryWord cur )
{
	char * str;
	unsigned int temp2,mask=3;
	int i=CODESTART-1;
	str=(char*)malloc(8*sizeof(char));
	while(i>=0)
	{


		temp2=cur.valueBits.value&mask;
		cur.valueBits.value=cur.valueBits.value>>2;
		if(temp2==0)
		{
			str[i]='*';

		}
		if(temp2==1)
				{
					str[i]='#';

				}
		if(temp2==2)
			{
				str[i]='%';

				}
		if(temp2==3)
		{
			 str[i]='!';

			}


      --i;


	}
	temp2=cur.era;
	temp2=temp2&mask;
	if(temp2==0)
			{
				str[CODESTART]='*';

			}
			if(temp2==1)
					{
						str[CODESTART]='#';

					}
			if(temp2==2)
				{
					str[CODESTART]='%';

					}
			if(temp2==3)
			{
				 str[CODESTART]='!';

				}
			str[CODESTART+1]='\0';





return str;
}
/*converting a data to base 4  returns a string  */
/*-------------------------------------------------------------------------------------------------------------------------------*/
char *printdata(struct  dataf *cur)
{
	char * str;
		unsigned int temp2,mask=3;
		int i=CODESTART;
		str=(char*)malloc(8*sizeof(char));
		str[7]='\0';
		while(i>=0)
		{

			temp2=cur->variable&mask;
			cur->variable=cur->variable>>2;




			if(temp2==0)
			{
				str[i]='*';

			}
			if(temp2==1)
					{
						str[i]='#';

					}
			if(temp2==2)
				{
					str[i]='%';

					}
			if(temp2==3)
			{
				 str[i]='!';

				}


	      --i;


		}
		return str;




}





/* printing in to the object file */

/*---------------------------------------------------------------------------------------------------------------------------------*/
void printcode(FILE *fp)
{
	char  * str;
	int i=0,counter=100;
	int ic,dc;
    ic=getic();
    dc=getdc();
    fprintf(fp,"  %d\t%d\n",ic-STARTADDRESS,dc);
    while(counter<ic)
    {
    	str=changebase(code[i]);
    	fprintf(fp,"%d\t%s\n",counter,str);
    	counter++;
    	i++;

    	free(str);
    }
    while(datahead)
    {
    	str=printdata(datahead);
    	fprintf(fp,"%d\t%s\n",ic,str);
    	datahead=datahead->next;
    	ic++;
    	free(str);
    }


return;
}




/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void addfiles(char *name)
{
	FILE *fpod;
	FILE *fpext;
	FILE *fpent;
	fpod=fileopen(name,".ob","w");
	fpext=fileopen(name,".ext","w");
	fpent=fileopen(name,".ent","w");

	printentry(fpent);
	fclose(fpent);
	printext(fpext);
	fclose(fpext);
	printcode(fpod);
	fclose(fpod);



return;

}

/**/



/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Reading function*/
int secondmain(char * name)
{

	FILE *fp=fopen(name,"r");

 do
 	{
 		fp=read2(fp);;


 }while(!feof(fp));

 if(flag==0)
 {
	 addfiles(name);
 }
 fclose(fp);


	return 0;
}
