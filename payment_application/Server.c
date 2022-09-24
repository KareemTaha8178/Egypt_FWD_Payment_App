/* Section : Includes */
#include "Server.h"
/* Section : Macros Definition */


/* Section : Macros Functions Declaration */

/* Section : Data Types Declaration */
ST_accountsDB_t DB_arr[255] = { {1000.1, "1256974582315987456"},
								{2000.5, "4545848151514212544"},
								{4100.8, "1237984561234658987"},
								{7400.2, "3216544987456132798"},
								{1200.2, "6547789123654987321"},
								{1400.4, "6489715248962468452"},
								{1400.6, "6549871234566798732"},
								{1800.6, "3215467895136544897"}, };

ST_accountsDB_t* refrence;

ST_transaction arr_transaction[255] = {0};


/* Section : Function Declaration */
EN_transStat_t recieveTransactionData(ST_transaction* transData) {
	EN_transStat_t ret = APPROVED;
	if (isValidAccount(&transData->cardHolderData) != OK_2) {
		printf("DECLINED_STOLEN_CARD. \n");
		ret = DECLINED_STOLEN_CARD;
		return ret;
	}
	if (isAmountAvailable(&transData->terminalData) != OK_2) {
		printf("DECLINED_INSUFFECIENT_FUND. \n");
		ret = DECLINED_INSUFFECIENT_FUND;
		return ret;
	}
	return ret;
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	EN_serverError_t ret = OK_2;
	uint8 flag = 0;
	for (int i = 0; i < 8; i++) {
		// strcmp() returns 0 if the two strings are equal.
		if (strcmp(cardData->primaryAccountNumber, DB_arr[i].primaryAccountNumber) == 0) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		printf("DECLINED_STOLEN_CARD. \n");
		ret = DECLINED_STOLEN_CARD;
	}
	return ret;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	EN_serverError_t ret = OK_2;
	if (termData->transAmount > refrence->balance) {
		printf("LOW_BALANCE. \n");
		ret = LOW_BALANCE;
	}
	return ret;
}
EN_serverError_t saveTransaction(ST_transaction* transData) {
	EN_serverError_t ret = OK_2;
	arr_transaction[transData->transactionSequenceNumber].terminalData = transData->terminalData;
	arr_transaction[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
	arr_transaction[transData->transactionSequenceNumber].transState = transData->transState;
	return ret;
}
EN_serverError_t getTransaction(uint32 transactionSequenceNumber, ST_transaction* transData) {
	EN_serverError_t ret = OK_2;
	if (arr_transaction[transactionSequenceNumber].transactionSequenceNumber == 0 || (transactionSequenceNumber > transData->transactionSequenceNumber)) {
		printf("TRANSACTION_NOT_FOUND. \n");
		ret = TRANSACTION_NOT_FOUND;
	}
	return ret;
}