/*
 * File:   Server.h
 * Author: Kareem Taha Abdelfattah Mohammed
 *
 * Created on September 24, 2022, 10:33 AM
 */

#ifndef Server_H
#define	Server_H

 /* Section : Includes */
#include <stdio.h>
#include <stdlib.h>
#include "Card.h"
#include "Terminal.h"

 /* Section : Macros Definition */
typedef unsigned char uint8;
typedef unsigned int uint32;


 /* Section : Macros Functions Declaration */

/* Section : Data Types Declaration */

typedef enum EN_transState_t
{
	APPROVED,
	DECLINED_INSUFFECIENT_FUND,
	DECLINED_STOLEN_CARD,
	INTERNAL_SERVER_ERROR
}EN_transStat_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transStat_t transState;
	uint32 transactionSequenceNumber;
}ST_transaction;


typedef enum EN_serverError_t
{
	OK_2,
	SAVING_FAILED,
	TRANSACTION_NOT_FOUND,
	ACCOUNT_NOT_FOUND,
	LOW_BALANCE
}EN_serverError_t;

typedef struct ST_accountsDB_t
{
	float balance;
	uint8 primaryAccountNumber[20];
}ST_accountsDB_t;





/* Section : Function Declaration */

EN_transStat_t	 recieveTransactionData(ST_transaction* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction* transData);
EN_serverError_t getTransaction(uint32 transactionSequenceNumber, ST_transaction* transData);



#endif	/* Server_H */



