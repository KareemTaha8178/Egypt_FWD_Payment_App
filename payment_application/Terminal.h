/*
 * File:   Teminal.h
 * Author: Kareem Taha Abdelfattah Mohammed
 *
 * Created on September 24, 2022, 10:33 AM
 */

#ifndef Teminal_H
#define	Teminal_H

 /* Section : Includes */
#include <stdio.h>
#include <stdlib.h>
#include "Card.h"

 /* Section : Macros Definition */
typedef unsigned char uint8;



 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8 transactionDate[12];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
	OK_1,
	WRONG_DATE,
	EXPIRED_CARD,
	INVALID_CARD,
	INVALID_AMOUNT,
	EXCEED_MAX_AMOUNT,
	INVALID_MAX_AMOUNT
}EN_terminalError_t;



/* Section : Function Declaration */
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);


#endif	/* Teminal_H */
