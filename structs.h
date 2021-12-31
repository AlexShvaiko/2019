/*
 * structs.h
 *
 *  Created on: Jul 24, 2019
 *      Author: user
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_
#define LABEL_LENGTH 31
#define BUF_SIZE 81
#define MAX_DOT_OP 30
#define MAX_COMANS_SIZE 7
#define COMMAX 4
#define MAXDATA 4
#define NUMBITS 14
#define NUMBITSCOM 12
#define REGNUM 8
#define LEGTH 5
#define MAXINT 4095
#define MININT -4096
#define STARTADDRESS 100
#define CODESTART 6
struct  dataf *datahead;
struct symbol{
	char name[LABEL_LENGTH];
	int address;/*address or value for macro*/
	int type;/*type 0 ,macro 1, command 2 ,*/
	int ext;/*external 1 ,*/
    struct symbol *next;

};

struct  dataf{

	int variable;

	struct  dataf *next;

}dataf;
typedef enum { ABSOLUTE = 0, EXTENAL = 1, RELOCATABLE = 2 } eraType;
typedef enum {COMMAND= 0, MACRO = 1, DATA= 2 } labeType;

struct entry{
	char name[LABEL_LENGTH];
	int address;/*address or value for macro*/
	int ext; /*exetern 1 ,entry 0*/

    struct entry *next;

};


/* Memory Word */

typedef struct /* 14 bits */
{
	unsigned int era : 2;

	union /* 12 bits */
	{
		/* Commands (only 12 bits) */
		struct
		{

			unsigned int dest : 2;		/* Destination op addressing method ID */
			unsigned int src : 2;		/* Source op addressing method ID */
			unsigned int opcode : 4;	/* Command ID */

		} cmdBits;

		/* Registers (only 12 bits) */
		struct
		{

			unsigned int destBits : 3;
			unsigned int srcBits : 3;
		} regBits;

		/* Other operands */
		int value : 12; /* (12 bits) */

	} valueBits; /* End of 12 bits union */

} memoryWord;






#endif /* STRUCTS_H_ */
