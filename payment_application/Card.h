/*
 * File:   Card.h
 * Author: Kareem Taha Abdelfattah Mohammed
 *
 * Created on September 24, 2022, 10:33 AM
 */

#ifndef Card_H
#define	Card_H

 /* Section : Includes */
#include <stdio.h>
#include <stdlib.h>

 /* Section : Macros Definition */
typedef unsigned char uint8;



/* Section : Macros Functions Declaration */

/* Section : Data Types Declaration */


typedef struct ST_cardData_t
{
	uint8 cardHolderName[25];
	uint8 primaryAccountNumber[20];
	uint8 cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	OK,
	WRONG_NAME,
	WRONG_EXP_DATE,
	WRONG_PAN
}EN_cardError_t;




/* Section : Function Declaration */

EN_cardError_t  getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t  getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t  getCardPAN(ST_cardData_t* cardData);


#endif	/* Card_H */

