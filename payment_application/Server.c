/* Section : Includes */
#include "Server.h"
/* Section : Macros Definition */

/* Section : Macros Functions Declaration */

/* Section : Data Types Declaration */
static ST_accountsDB_t DB_arr[255] = { {10000.1, RUNNING, "1256974582315987456"},
								{20000.5, RUNNING, "4545848151514212544"},
								{41070.8, RUNNING, "1237984561234658987"},
								{74000.2, RUNNING, "3216544987456132798"},
								{12050.2, BLOCKED, "6547789123654987321"},
								{14600.4, BLOCKED, "6489715248962468452"},
								{14090.6, RUNNING, "6549871234566798732"},
								{18040.6, BLOCKED, "3215467895136544897"},
								{18040.6, RUNNING, "3215467895138784894"},
								{18040.6, BLOCKED, "3215467895145454898"} };



uint32 number_account;

uint32 sequence_Number = 0;	

ST_transaction arr_transaction[255] = {0};


/* Section : Function Declaration */
EN_transStat_t recieveTransactionData(ST_transaction* transData) {
	EN_transStat_t ret = APPROVED;
	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND) {
		transData->transState = FRAUD_CARD;
		printf("FRAUD_CARD. \n");
		ret = FRAUD_CARD;
	}
	else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		printf("DECLINED_INSUFFECIENT_FUND. \n");
		ret = DECLINED_INSUFFECIENT_FUND;
	}
	else if (isBlockedAccount(&DB_arr[number_account]) == DECLINED_STOLEN_CARD) {
		transData->transState = DECLINED_STOLEN_CARD;
		printf("DECLINED_STOLEN_CARD. \n");
		ret = DECLINED_STOLEN_CARD;
	}
	else if (saveTransaction(transData) == SAVING_FAILED) {
		printf("INTERNAL_SERVER_ERROR. \n");
		ret = INTERNAL_SERVER_ERROR;
	}
	else {
		printf("Done recieveTransactionData Successfully\n");
		transData->transState = APPROVED;
		DB_arr[number_account].balance -= transData->terminalData.transAmount;
		printf("Your balance now is :- %.2f", DB_arr[number_account].balance);
	}
	return ret;
}


EN_transStat_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	EN_transStat_t ret = APPROVED;
	if (DB_arr[number_account].state == BLOCKED) {
		printf("Your Account is BLOCKED\n");
		ret = DECLINED_STOLEN_CARD;
	}
	else printf("Your Account is Running\n");
	return ret;
}


EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	EN_serverError_t ret = OK_2;
	uint8 flag = 0;
	for (int i = 0; i < 255; i++) {
		// strcmp() returns 0 if the two strings are equal.
		if (strcmp((cardData->primaryAccountNumber), (DB_arr[i].primaryAccountNumber)) == 0) {
			number_account = i;
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		printf("ACCOUNT_NOT_FOUND. \n");
		ret = ACCOUNT_NOT_FOUND;
	}
	else printf("Your account is Valid\n");
	return ret;
}


EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	EN_serverError_t ret = OK_2;
	if (termData->transAmount > DB_arr[number_account].balance) {
		printf("LOW_BALANCE. \n");
		ret = LOW_BALANCE;
	}
	return ret;
}



EN_serverError_t saveTransaction(ST_transaction* transData) {
	EN_serverError_t ret = OK_2;
	if (transData->transactionSequenceNumber >= 255) {
		printf("Erorr\n");
		ret = SAVING_FAILED;
	}
	else {
		transData->transactionSequenceNumber = (sequence_Number + 1);
		arr_transaction[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
		arr_transaction[transData->transactionSequenceNumber].terminalData = transData->terminalData;
		arr_transaction[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber;
		arr_transaction[transData->transactionSequenceNumber].transState = transData->transState;
		sequence_Number++;
		printf("Done Save Successfully\n");
	}
	return ret;
}



EN_serverError_t getTransaction(uint32 transactionSequenceNumber, ST_transaction* transData) {
	EN_serverError_t ret = OK_2;
	if (arr_transaction[transactionSequenceNumber].transactionSequenceNumber == 0) {
		printf("Transaction not Found.\n");
		ret = TRANSACTION_NOT_FOUND;
	}
	else {
		printf("Card Holder Name is :- %s\n", arr_transaction[transactionSequenceNumber].cardHolderData.cardHolderName);
		printf("Primary Account number is :- %s\n", arr_transaction[transactionSequenceNumber].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date is :- %s\n", arr_transaction[transactionSequenceNumber].cardHolderData.cardExpirationDate);
		printf("Transaction Date is :- %s\n", arr_transaction[transactionSequenceNumber].terminalData.transactionDate);
		printf("Transaction Amount is :- %.2f\n", arr_transaction[transactionSequenceNumber].terminalData.transAmount);
		printf("Transaction Sequence number is :- %d\n", arr_transaction[transactionSequenceNumber].transactionSequenceNumber);
	}
	return ret;
}