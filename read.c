/*
 * read.c
 *
 *  Created on: Jul 19, 2019
 *      Author: user
 */
#include "read.h"
int ic=STARTADDRESS,dc;


/*----------------------------------------------------------------------------------------------------------------------------*/
int getic()
{

return ic;


}
int getdc()
{

	return dc;
}





/*----------------------------------------------------------------------------------------------------------------------------*/

/* function calculating a negative number to 14 bits presentation  */
int negativenum(int x)
{
	int i=0,num=0;
	unsigned int y=1;

	x=(-x);

		x=(-x);
		while(i<NUMBITS)
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



return num;
}
/*---------------------------------------------------------------------------------------------------------------------------*/
/**/
/*---------------------------------------------------------------------------------------------------------------------------*/
void checkifmacro(char* cp,int line)
{
	int i;
	int x;
	struct symbol* macro;
	char buf[MAX_DOT_OP ];
	for(i=0;((*cp)!=',')&&(i<MAX_DOT_OP)&&((*cp)!=' ')&&((*cp)!='\0');i++,cp++)
	{
	 buf[i]=*cp;

	}
	buf[i]='\0';

	macro=searchsym(buf,head);
	if(macro!=NULL&&macro->type==1)
	{
		x=macro->address;

	 datahead=adddata(x,datahead);
	 blank(&cp);
	 data(cp,line);
	}
	else
	{
		 flag++;
		 printf("syntax error line  %d\n",line);
		 return;
	}


return;

}
/*adding a data to the linked list*/

/*--------------------------------------------------------------------------------------------------------------------------*/

void data(char *cp, int line)
{
	char data[MAXDATA+1];
		int i=0;
		int x;

		blank(&cp);/*Skip blanks*/

		   while(*cp!='\0')
		    {

			   if(*cp==',')
			   {
				  flag++;
				  printf("syntax error line  %d\n",line);
				  return;

			   }

			       blank(&cp);
			       i=0;
			       if(((*cp)>='A'&&(*cp)<='Z')||((*cp)>='a'&&(*cp)<='z'))
			       {
			    	   checkifmacro(cp,line);
			    	   return;

			       }
			       if(!((isdigit(*cp))||(*cp!='-')||*cp!='+'))
			       {
			    	   flag++;
			    	   printf("syntax error line  %d\n",line);
			    	   return;
			       }
			       if(*cp=='-'||*cp=='+')
			       {
			    	   data[i]=*cp;
			    	   i++;
			    	   cp++;
			    	   if(!isdigit(*cp))
			    	   {
			    		   flag++;
			    		   printf("syntax error line  %d\n",line);
			    		   return;

			    	   }

			       }
				   for(;(MAXDATA>=i)&&(isdigit(*cp));i++,cp++)
				    {
					   data[i]=*cp;

				    }
				   data[i]='\0';
				   blank(&cp);

				if(*cp==',')
				  {

					   cp++;
					   blank(&cp);
					   if(*cp=='\0')
					   {
						   flag++;
						   printf("syntax error line  %d\n",line);
						   return;
					   }

				   }

				x=atoi(data);
				if((x)>MAXINT||(x)<MININT)
				{
					flag++;
					printf("your date is out of range line %d\n",line);
			        return;
				}
				if(x<0)
				{
				 x=negativenum(x);
				}

                datahead=adddata(x,datahead);




		    }

return;

}
/*---------------------------------------------------------------------------------------------------------------------*/
/*adding characters to the linked list*/
void string1(char *cp, int line)
{
	int x;
	blank(&cp);
	if(*cp!='"')
	  {
		    flag++;
			printf("syntax error line  %d\n",line);

			return;

      }
	cp++;
	while(*cp!='"'&&(ic+dc)<MAXINT)
	{
		x=*cp;
		datahead=adddata(x,datahead);
		cp++;

	}
	cp++;

	datahead=adddata(0,datahead);
	blank(&cp);
	if(*cp!='\0')
	{
		flag++;
		printf("syntax error line  %d\n",line);
		return;

	}

return;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*checking if no syntax error in the entry declaration)*/
void entry(char *p, int line)
{
	int counter=0;
	blank(&p);

	while((*p!=' ')&&(counter<MAX_DOT_OP)&&(*p!='\0'))
	{
		p++;
	   counter++;
	}
	blank(&p);
	if(*p!='\0')
	{
	 flag++;
	 printf("syntax error line  %d\n",line);

	  return;
	}
return;
}
/*adding a  extern label to the lable linked list*/
/*-----------------------------------------------------------------------------------------------------------------------*/
void extern1(char *cp, int line)
{
	char buf[MAX_DOT_OP];
	int i;

    blank(&cp);

	for(i=0;(*cp!=' ')&&(i<MAX_DOT_OP)&&(*cp!='\0');i++,cp++)
		{
		  buf[i]=*cp;

		 }
		buf[i]='\0';
        blank(&cp);

			if(*cp!='\0')
				{
				flag++;
				printf("syntax error line  %d\n",line);

				return;}
	head=addsymboltab(buf,0,head,0,1,line);
    return;

}
/*-----------------------------------------------------------------------------------------------------------------------*/
/*adding a label to the linked list */
/*-----------------------------------------------------------------------------------------------------------------------*/

void islabele(char*cp,int line)
{
	char lable[COMMAX];
	int i;
			   for(i=0;((*cp)!=':')&&(i<MAX_DOT_OP-1);i++,cp++)
			    {
				   lable[i]=*cp;

			    }
			   if(*cp!=':')
			   {
				   flag++;
				   printf("syntax error line  %d\n",line);
				   return;
			   }
			   else
			   {
			    lable[i]='\0';
			    cp++;
			     if(*cp!=' ')
			     {
			     	flag++;
			    	printf("syntax error line  %d\n",line);
			    	return;
			     }



			   }

				blank(&cp);

			   if(*cp=='.')
			   {
			     head=addsymboltab(lable,dc,head,DATA ,0,line);
				isdot(cp,line);
			   }
			   if(((*cp)>='a'&&(*cp)<='z'))
			   {
				  head=addsymboltab(lable,ic,head,COMMAND,0,line);
				  iscomand(cp,line);
			   }



return;

}
/*checking stop syntax*/
/*----------------------------------------------------------------------------------------------------------------------------------*/
void stop(char *cp,int line)
{


		ic++;
		blank(&cp);

		if(*cp!='\0')
	 {
		 	flag++;
		 	printf("syntax error line  %d\n",line);
		 	return;
	 }
	return;

}
/*checking if the string is name of is register */
/*-----------------------------------------------------------------------------------------------------------------------------------------*/
int isreg(char buf[MAX_DOT_OP])
{
	int i=0;
	char * reg[]={"r0","r1","r2","r3","r4","r5","r6","r7"};
	while(i<REGNUM)
	{
	  if(!strcmp(buf,reg[i]))
		return 1;
	  i++;
	}

  return 0;


}
/*checking the syntax for using arrays*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------*/
void arrycheck(char **c,int line)
{
	int counter=0;
   while(**c!=']'&&**c!='\0')
   {
	   (*c)++;
	   counter++;
   }
   if(**c==']'&&counter!=0)
   {
	   (*c)++;
	   return;

   }
   else
   {
   		flag++;
   	    printf("syntax error line  %d\n",line);
   		return;

   		   }



return;

}



/*checking the the second operand with legal operand same with mov */

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/
void move2(char * cp,int line,int reg)
{
	int i;
		char buf[MAX_DOT_OP];

	if(*cp=='#')
   {
		flag++;
	 	printf("illegal destination object %d\n",line);
	 	return;

}
	for(i=0;((*cp)!=' ')&&(i<MAX_DOT_OP)&&(*cp!='\0')&&(*cp!='[')&&(*cp!=',');i++,cp++)
			{
			  buf[i]=*cp;

			 }
			buf[i]='\0';
			if(i==MAX_DOT_OP)
					{
						 flag++;
					     printf("Unknown  destination %d\n",line);
						 return;

					}
			blank(&cp);
			if(*cp==',')
			{
				        flag++;
				   	    printf("syntax error line  %d\n",line);
				   		return;



						}
			if(reg&&isreg(buf))
			{
				return;
			}

			if(isreg(buf)&&*cp!='[')
			{

				ic=ic+1;

			}
			if(*cp=='[')
			{
				arrycheck(&cp,line);
				ic=ic+2;


			}



			return;





}



/*checking the the first operand with legal operand same with mov */

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
void move(char * cp,int line)
{
	int reg=0,i;
	char buf[MAX_DOT_OP];


	blank(&cp);

	if(*cp=='#')
	{
		ic++;
		for(;*cp!=' '&&*cp!=','&&*cp!='\0';cp++);
		   if(*cp=='\0'||(*cp==' '&&*(cp+1)!=','))
		   {
			            flag++;
			   		 	printf("syntax error line  %d\n",line);
			   		 	return;

		   }


		   move2(cp,line,reg);
		   return;

	   }
	for(i=0;((*cp)!=' ')&&(i<MAX_DOT_OP)&&(*cp!=',')&&*cp!='\0'&&(*cp!='[');i++,cp++)
		{
		  buf[i]=*cp;

		 }
		buf[i]='\0';
		blank(&cp);


		if(i==MAX_DOT_OP)
		{
			 flag++;
		     printf("Unknown source %d \n ",line);
			 return;

		}
		if(*cp=='\0')
		{
			flag++;
			printf("syntax error line %d\n ",line);
			return;

		}
	if(!isreg(buf)&&*cp!='[')
		{
			ic=ic+1;

		}

	  if(*cp=='[')
	  {
		arrycheck(&cp,line);
		ic=ic+2;

	   }
		blank(&cp);
		if(*cp!=',')
		{
			flag++;
			printf("syntax error line %d\n ",line);
			return;

		}


		if(isreg(buf))
		{

			reg=1;
			ic++;

		}
		if(*cp==',')
		{
			cp++;
		}
		blank(&cp);




   move2(cp,line,reg);
   return;




}
/*Checking the second operand of comper */
/*-----------------------------------------------------------------------------------------------------------------------------------------*/
void comper2 (char *cp,int line,int reg)
{
    int i;
   char buf[MAX_DOT_OP];
   if(*cp=='#')
   		{
   			ic++;

   			for(i=0;*cp!=' '&&*cp!='\0'&&i<MAX_DOT_OP;i++,cp++)
   				blank(&cp);
   			   if(*cp!='\0')
   			   {
   				            flag++;
   				   		 	printf("syntax error line  %d\n",line);
   				   		 	return;

   			   }
   			   return;
   		}


	for(i=0;((*cp)!=' ')&&(i<MAX_DOT_OP)&&(*cp!='\0')&&(*cp!='[')&&*cp!=',';i++,cp++)
			{
			  buf[i]=*cp;

			 }
			buf[i]='\0';
			if(!strlen(buf))
			{
				flag++;
				printf("operand not found line %d \n",line);
				return;


			}

			if(i==MAX_DOT_OP)
					{
						 flag++;
					     printf("Unknown  destination %d \n",line);
						 return;

					}

	if(*cp==',')
	{
		        flag++;
		   	    printf("syntax error line  %d\n",line);
		   		return;



				}
			if(reg&&!isreg(buf)&&*cp!='[')
			{
							ic=ic+1;

			}
			if(*cp=='[')
			{
				arrycheck(&cp,line);
				ic=ic+2;


			}

			if(isreg(buf))
			{

					ic++;


			}


			return;
}



/*Checking the first operand of comper*/
/*---------------------------------------------------------------------------------------------------------------------------------------*/
void comper(char* cp,int line)
{
	int reg=0,i;
		char buf[MAX_DOT_OP];

		blank(&cp);


		if(*cp=='#')
		{
			ic++;

			for(;*cp!=' '&&*cp!=','&&*cp!='\0';cp++);
			blank(&cp);
			   if(*cp=='\0'||(*cp!=','))
			   {
				            flag++;
				   		 	printf("syntax error line  %d\n",line);
				   		 	return;

			   }

               cp++;
			   comper2(cp,line,reg);

			   return;

		   }

		for(i=0;((*cp)!=' ')&&(i<MAX_DOT_OP)&&(*cp!=',')&&*cp!='\0'&&(*cp!='[');i++,cp++)
			{
			  buf[i]=*cp;

			 }
			buf[i]='\0';
			if(!strlen(buf))
						{
							flag++;
							printf("operand not found line %d \n ",line);
							return;


						}


			if(i==MAX_DOT_OP)
			{
				 flag++;
			     printf("Unknown source %d \n",line);
				 return;

			}
			if(*cp=='\0')
			{
				flag++;
				printf("syntax error line %d \n",line);
				return;

			}

		  if(*cp=='[')
		  {
			arrycheck(&cp,line);
			ic=ic+2;

		   }
			blank(&cp);

			if(*cp!=',')
			{
				flag++;
				printf("syntax error line %d \n",line);
				return;

			}
			cp++;

			if(isreg(buf))
			{
				reg=1;

			}
			if(reg&&!isreg(buf)&&*cp!='{')
			{
							ic=ic+1;

			}
			comper2(cp,line,reg);
			return;


}
/*Checking syntax of commands without operands */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
void stop1(char *cp,int line)
{
	blank(&cp);

	if(*cp!='\0')
	{
		flag++;
		printf("syntax error line %d\n",line);
		return ;

	}
	ic++;
	return;




}

/*Checking all the command syntax  with same  legal operands of note*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
void not1(char *cp,int line)
{
	char buf[MAX_DOT_OP];
	int i=0;
	if(*cp=='#')
	{
		 flag++;
	     printf("Illegal operand line %d\n",line);
		 return ;


	}
	for(i=0;((*cp)!=' ')&&(i<MAX_DOT_OP)&&(*cp!=',')&&*cp!='\0'&&(*cp!='[');i++,cp++)
				{
				  buf[i]=*cp;

				 }
				buf[i]='\0';
				if(!strlen(buf))
							{
								flag++;
								printf("operand not found line %d\n ",line);
								return;


							}

				if(i==MAX_DOT_OP)
				{
					 flag++;
				     printf("Unknown source %d\n",line);
					 return;

				}


				if(!(isreg(buf))&&*cp!='[')
				{
					ic=ic+1;

					}

			  if(*cp=='[')
			  {
				arrycheck(&cp,line);
				ic=ic+2;

			   }

				if(isreg(buf))
				{
					ic++;

				}

				blank(&cp);
				if(*cp!='\0')
				{
					flag++;
				  printf("syntax error line %d \n ",line);
				return;
				}

				return;





}
/**/

/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
void print1(char * cp,int line)
{int i;
char buf[MAX_DOT_OP];

blank(&cp);

if(*cp=='#')
{
	ic++;
	for(;*cp!=' '&&*cp!=','&&*cp!='\0';cp++);
	blank(&cp);
	   if(*cp!='\0')
	   {
		            flag++;
		   		 	printf("syntax error line  %d\n",line);
		   		 	return;

	   }

	   return;

   }


for(i=0;((*cp)!=' ')&&(i<MAX_DOT_OP)&&(*cp!=',')&&*cp!='\0'&&(*cp!='[');i++,cp++)
	{
	  buf[i]=*cp;

	 }

	buf[i]='\0';
	if(!strlen(buf))
				{
					flag++;
					printf("operand not found line %d \n",line);
					return;


				}

	if(i==MAX_DOT_OP)
	{
		 flag++;
	     printf("Unknown source %d\n ",line);
		 return;

	}

if(!isreg(buf)&&*cp!='[')
	{
		ic=ic+1;

	}

  if(*cp=='[')
  {
	arrycheck(&cp,line);
	ic=ic+2;

   }
  if(isreg(buf))
  	{
  		ic++;

  		}
	blank(&cp);

	if(*cp!='\0')
	{
		flag++;
		printf("syntax error line %d ",line);
		return;

	}






}
/*---------------------------------------------------------------------------------------------------------------------------------------------*/
void  jmp(char *cp,int line)
{
	char buf[MAX_DOT_OP];
		int i=0;
		if(*cp=='#')
		{
			 flag++;
		     printf("Illegal operand line %d\n",line);
			 return ;


		}
		for(i=0;((*cp)!=' ')&&(i<MAX_DOT_OP)&&(*cp!=',')&&*cp!='\0'&&(*cp!='[')&&(*cp!=',');i++,cp++)
					{
					  buf[i]=*cp;

					 }
					buf[i]='\0';
					if(!strlen(buf))
								{
									flag++;
									printf("operand not found line %d \n",line);
									return;


								}

					if(i==MAX_DOT_OP)
					{
						 flag++;
					     printf("Unknown operand %d \n",line);
						 return;

					}

	if(*cp==',')
	{
		        flag++;
		   	    printf("syntax error line  %d\n",line);
		   		return;



				}
					if(*cp=='[')
					{

						arrycheck(&cp,line);
						printf("Illegal operand line %d\n",line);
						return;



					}
					blank(&cp);
					if(*cp!='\0')
						{
							flag++;
							printf("syntax error line %d \n",line);
							return;

						}
					  		ic++;

					  		return;




}
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

void lea2(char * cp,int line)
{
	int i;
   char buf[MAX_DOT_OP];


	if(*cp=='#')
   {
		flag++;
	 	printf("not illegal destination object %d\n",line);
	 	return;

    }
	for(i=0;((*cp)!=' ')&&(i<MAX_DOT_OP)&&(*cp!='\0')&&(*cp!='[')&&*cp!=',';i++,cp++)
			{
			  buf[i]=*cp;

			 }
			buf[i]='\0';
			if(i==MAX_DOT_OP)
					{
						 flag++;
					     printf("Unknown  destination %d\n",line);
						 return;
					}

	if(*cp==',')
	{
		        flag++;
		   	    printf("syntax error line  %d\n",line);
		   		return;



				}


			if(*cp=='[')
			{
				arrycheck(&cp,line);
				ic=ic+2;


			}

			if(isreg(buf))
			{

					ic++;


			}
			blank(&cp);
							if(*cp!='\0')
							{
								flag++;
							  printf("syntax error line %d \n ",line);
							return;
							}


			return;
}









/*---------------------------------------------------------------------------------------------------------------------------------------------------*/

void leap(char * cp,int line)
{
	char buf[MAX_DOT_OP];
		int i=0;
		if(*cp=='#')
		{
			 flag++;
		     printf("Illegal operand line %d\n",line);
			 return ;


		}
		for(i=0;((*cp)!=' ')&&(i<MAX_DOT_OP)&&(*cp!=',')&&*cp!='\0'&&(*cp!='[');i++,cp++)
					{
					  buf[i]=*cp;

					 }
					buf[i]='\0';
					if(!strlen(buf))
								{
									flag++;
									printf("operand not found line %d \n",line);
									return;


								}

					if(i==MAX_DOT_OP)
					{
						 flag++;
					     printf("Unknown source %d ",line);
						 return;

					}


					if(!(isreg(buf))&&*cp!='[')
					{
						ic=ic+1;

						}
					if(isreg(buf))
					{flag++;
				     printf("Illegal operand line %d\n",line);
					 return ;



					}


				  if(*cp=='[')
				  {
					arrycheck(&cp,line);
					ic=ic+2;

				   }
				  blank(&cp);
				  if(*cp!=',')
				  			{
				  				flag++;
				  				printf("syntax error line %d \n",line);
				  				return;

				  				}
				  cp++;
				  blank(&cp);
				  lea2(cp,line);



				  return;



}


/*---------------------------------------------------------------------------------------------------------------------------------------*/
void iscomand(char* cp,int line)
{

	char buf[LEGTH];
	int i;
	struct{
		char *name;
		void (*func)(char* p,int line);
	}
	cmd[]={
			{"mov",move},
			{"add",move},
			{"sub",move},
			{"cmp",comper},
			{"lea",leap},
			{"not",not1},
			{"clr",not1},
			{"inc",not1},
			{"dec",not1},
			{"jmp",jmp},
			{"red",not1},
			{"prn",print1},
			{"bne",jmp},
			{"jsr",jmp},
			{"rts",stop1},
			{"stop",stop1},
			{"Unknown command ",NULL}
	};

	      blank(&cp);
				   for(i=0;((*cp)!=' ')&&(i<LEGTH)&&(*cp)!='\0';i++,cp++)
				    {
					   buf[i]=*cp;

				    }
				   buf[i]='\0';
				   i=0;


				   while(cmd[i].func)
				   {
					   if(!strcmp(cmd[i].name,buf))
						 {
						   blank(&cp);
						   ic++;
						   (*(cmd[i].func))(cp,line);
						   return;


					}
					   i++;

				   }
				   printf("Unknown command line %d\n ",line );


				   return;



}
/*Checking if the lane staring with command or label */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

void comleb(char* cp,int line)
{
	char * temp;
	int i;

	blank(&cp);
	temp=cp;

	for(i=0;i<MAX_DOT_OP&&*temp!=':'&&*temp!=' ';i++,temp++);
	if(i==MAX_DOT_OP)
	{
		     flag++;
			 printf("syntax error line %d\n",line);
			 return ;


	}
	if(*temp==':')
	{
		temp++;

		islabele(cp,line);
         return;

	}
	else
	{

		   iscomand(cp,line);
				return;

	}
	return;




}
/*checking syntax of  define and adding to data */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void define1(char * cp,int line)
{
	char buf[MAX_DOT_OP];
	char data[MAXDATA+1];
	int i,x;
	blank(&cp);
	for(i=0;((*cp)!=' ')&&(i<MAX_DOT_OP)&&(*cp!='=');i++,cp++)
	{
	  buf[i]=*cp;

	 }
	buf[i]='\0';
	blank(&cp);
	if(i==MAX_DOT_OP)
	{

		if(*cp!=' '&&*cp!='=')
		{
			flag++;
			printf("syntax error line  %d\n",line);
		    return;

		}
	}
	 if(*cp!='=')
	 {
		 flag++;
		 printf("syntax error line  %d\n",line);
		 return;

	 }
	 cp++;
	 i=0;
	 blank(&cp);
	 if(!((isdigit(*cp))||(*cp=='-')||*cp=='+'))
	 			       {
	 			    	   flag++;
	 			    	   printf("1syntax error line  %d\n",line);
	 			    	   return;
	 			       }
	 			       if(*cp=='-'||*cp=='+')
	 			       {
	 			    	   data[i]=*cp;
	 			    	   i++;
	 			    	   cp++;
	 			    	   if(!isdigit(*(cp+1)))
	 			    	   {
	 			    		   flag++;
	 			    		   printf("1syntax error line  %d\n",line);
	 			    		   return;

	 			    	   }

	 			       }
	 				   for(;(MAXDATA>=i)&&(isdigit(*cp));i++,cp++)
	 				    {
	 					   data[i]=*cp;

	 				    }
	 				   data[i]='\0';
	 				   blank(&cp);
	 				   if(*cp!='\0')
	 				   {
	 					  flag++;
	 					  printf("syntax error line  %d\n",line);
	 					  return;

	 				   }
	 				  x=atoi(data);
	 				  				if((x)>4095||(x)<(-4096))
	 				  				{
	 				  					flag++;
	 				  					printf("your date is out of range line %d\n",line);
	 				  			        return;
	 				  				}
	 				  				if(x<0)
	 				  				{
	 				  				 x=negativenum(x);
	 				  				}

	 				                 head=addsymboltab(buf,x,head,MACRO,0,line);

return;
}
/* ignore blank space in the string */
/*-----------------------------------------------------------------------------------------------------------------------------------------*/
void blank(char **c)
{

	while (**c==' '&&**c!='\0')
	{
		(*c)++;
	}
	return;
}
/*--------------------------------------------------------------------------------------------------------------*/
/**/
void isdot(char *p,int line)
{
struct{
	char *name;
	void (*func)(char* p,int line);
}
cmd[]={
		{"data",data},
		{"string",string1},
		{"entry",entry},
		{"extern",extern1},
		{"define",define1},
		{"Unknown command ",NULL}
};
  char comand[MAX_COMANS_SIZE];
  int i=0;
  p++;
 for(i=0;((*p)!=' ')&&i<MAX_COMANS_SIZE&&*p!='\0';i++,p++)
 {
	 comand[i]=*p;

 }
 comand[i]='\0';
 if(*(p)!=' ')
 {
	 flag++;
	 printf("unknown command %d\n",line);
	 return ;
 }
 for(i=0;cmd[i].func!=NULL ;i++)
 {

	 if(strcmp(comand,cmd[i].name)==0)
		 break;
 }
 if(cmd[i].func==NULL)
	 printf("Unknown command line %d\n",line);

	 else
	 {

		 (*(cmd[i].func))(p,line);
	 }
return;

}
/*----------------------------------------------------------------------------------------------------------------------*/
void firstcheck(char* cp,int line)
{


if(*cp==';'||*cp=='\0')
{

		  return;
}
if(((*cp)>='A'&&(*cp)<='Z')||((*cp)>='a'&&(*cp)<='z'))
{
	  comleb(cp,line);
	  return ;
}

if(*cp=='.')
	  {
		  isdot(cp,line);
		  return ;
	  }


return;
}
/*----------------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------*/

FILE * readline (FILE *p,int line)
{
	int c,counter=0;

	char buf[BUF_SIZE];
	char* cp=buf;


	   do {
	      c=fgetc(p);
	      if( feof(p) ) {
	         break ;
	      }
	      if(c=='\n'||c=='\r')/*Checking for windows file  */
	      {

	    	  buf[counter]='\0';
	      }

	      else
	      buf[counter]=c;

	      counter++;


	   } while(counter<BUF_SIZE&&c!='\n');
	   buf[counter]='\0';
	   blank(&cp);
	   firstcheck(cp,line);
	   if(c=='\r')
	   {
		fseek(p,SEEK_CUR,1)  ;
	   }


	    return p;
}
/*------------------------------------------------------------------------------------------------------------------------------*/

void dataadressup()
{
	struct symbol* curent=head;
	while(curent)
	{
		if(curent->type==2)
		{

			curent->address=curent->address+ic;

		}
		curent=curent->next;

	}
	return ;
}


/*-------------------------------------------------------------------------------------------------------------------*/


void firstmain(FILE * fp)
{
int counter=1;
	do
	{
		fp=readline(fp,counter);
		counter++;

}while(!feof(fp));
 dataadressup();
}


