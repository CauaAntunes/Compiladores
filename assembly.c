#ifndef ASM_H
#define ASM_H
#include "tac.h"
#include <stdio.h>
#include <string.h>

#define ASM_SIZE 2000

int printNumber = 0;

void asmVecDec(TAC* tac, char* asmString0, char* asmString1, char* tempString){
		  int vecSize;
		  int i;
		  TAC* tacTemp;

		  vecSize = atoi(tac->op2->text);//?

		  strcat(asmString0, "\n## TAC_VECDEC\n");
		  if(! tac->op1) //se nao for inicializado
		  {
		    sprintf(tempString, "	.comm %s, %i, 32\n", tac->op0->text, 4*vectorSize);
		  }else{
		    sprintf(tempString, "");
		    for(tacTemp = tac->prev; tacTemp->prev->type == TAC_SYMBOL; tacTemp = tacTemp->prev)
		    {} // vai ate o primeiro TAC_SYMBOL
		    for(tacTemp = tacTemp; tacTemp->type == TAC_SYMBOL; tacTemp = tacTemp->next)
		    {
		      if(tacTemp->op0->type == LIT_REAL)
		      {
			strcat(tempString, "	.long ");
			strcat(tempString, "111111" ); //?
			strcat(tempString, "\n");
		      }else{
			if(tacTemp->op0->type == LIT_CHAR)
			{
			  char* charVal[40];
			  sprintf(charVal, "%d", tacTemp->op1->text[1]);
			  strcat(tempString, "	.byte ");
			  strcat(tempString, charVal);
			  strcat(tempString, "\n");
			}else{
			  strcat(tempString, "	.long ");
			  strcat(tempString, tacTemp->op0->text );
			  strcat(tempString, "\n");
			}
		      }
		    }
		  }
		  strcat(asmString0, tempString);
	}

void asmVarDec(TAC* tac, char* asmString0, char* asmString1, char* tempString)
	{
		  strcat(asmString0, "\n## TAC_VARDEC\n");
		  if(tac->op1->type == LIT_REAL)
		  {
		    sprintf(tempString, "	.globl	%s\n	.type	%s, @object\n	.size	%s, 4\n%s:\n	.long	111111\n", tac->op0->text,tac->op0->text,tac->op0->text,tac->op0->text);
		  }else{
		    if(tac->op1->type == LIT_CHAR)
		    {
		      char* charVal[40];
		      sprintf(charVal , "%d", tac->op1->text[1]);
		      sprintf(tempString, " .globl	%s\n .type	%s, @object\n .size	%s, 1\n%s:\n  .byte	%s\n",  tac->op0->text,tac->op0->text,tac->op0->text,tac->op0->text, charVal);

		    }else{
		      sprintf(tempString, "	.globl	%s\n	.type	%s, @object\n	.size	%s, 4\n%s:\n	.long	%s\n", tac->op0->text,tac->op0->text,tac->op0->text,tac->op0->text, tac->op1->text);
		    }
		  }
		  strcat(asmString0, tempString);
	}

void asmBeginFun(TAC* tac, char* asmString0, char* asmString1, char* tempString){
	  strcat(asmString1, "\n## TAC_BEGGINFUN\n");
	  sprintf(tempString,"	.globl	%s\n	.type	%s, @function\n%s:\n	pushq	%%rbp\n	movq	%%rsp, %%rbp\n",tac->op0->text,tac->op0->text,tac->op0->text);
	  strcat(asmString1, tempString);
}

void asmReturn(TAC* tac, char* asmString0, char* asmString1, char* tempString)
{
  char* charVal[40];
  strcat(asmString1, "\n## TAC_RETURN\n");
  sprintf(charValue , "%d", tac->op1->text);
  sprintf(tempString, "	movl	$%s, %%eax",charVal);
  strcat(asmString1, tempString);
}

