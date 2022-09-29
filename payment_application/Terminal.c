/* Section : Includes */
#include "Terminal.h"

/* Section : Macros Definition */

/* Section : Macros Functions Declaration */

/* Section : Data Types Declaration */

/* Section : Function Declaration */
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	EN_terminalError_t ret = OK_1;
	printf("Enter the transaction date like [DD/MM/YYYY]: ");
	scanf_s("%s", termData->transactionDate, 12);
	if (strlen(termData->transactionDate) != 10 || ((termData->transactionDate[0] < '0') || (termData->transactionDate[0] > '9')) || ((termData->transactionDate[1] < '0') || (termData->transactionDate[1] > '9')) || (termData->transactionDate[2] != '/') || ((termData->transactionDate[3] < '0') || (termData->transactionDate[3] > '9')) || ((termData->transactionDate[4] < '0') || (termData->transactionDate[4] > '9')) || (termData->transactionDate[5] != '/') || ((termData->transactionDate[6] < '0') || (termData->transactionDate[6] > '9')) || ((termData->transactionDate[7] < '0') || (termData->transactionDate[7] > '9')) || ((termData->transactionDate[8] < '0') || (termData->transactionDate[8] > '9')) || ((termData->transactionDate[9] < '0') || (termData->transactionDate[9] > '9'))) {
		printf("Wrong TransactionDate. \n");
		ret = WRONG_DATE;
	}
	if ((termData->transactionDate[3] == '1') && (termData->transactionDate[4] > '2') || (termData->transactionDate[3] < '0') || termData->transactionDate[3] >= '2') {
		printf("Wrong TransactionDate. \n");
		ret = WRONG_DATE;
	}
	if (termData->transactionDate[0] == '3' && termData->transactionDate[1] > '0'){
		printf("Wrong TransactionDate. \n");
		ret = WRONG_DATE;
	}
	if (termData->transactionDate[0] >= '4') {
		printf("Wrong TransactionDate. \n");
		ret = WRONG_DATE;
	}
	return ret;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	EN_terminalError_t ret = OK_1;
	char str_y_card[3] = "";
	char str_m_card[3] = "";
	char str_y_now[3] = "";
	char str_m_now[3] = "";
	strncat(str_y_card, &(cardData.cardExpirationDate[3]), 1);
	strncat(str_y_card, &(cardData.cardExpirationDate[4]), 1);
	strncat(str_m_card, &(cardData.cardExpirationDate[0]), 1);
	strncat(str_m_card, &(cardData.cardExpirationDate[1]), 1);
	strncat(str_y_now, &(termData.transactionDate[8]), 1);
	strncat(str_y_now, &(termData.transactionDate[9]), 1);
	strncat(str_m_now, &(termData.transactionDate[3]), 1);
	strncat(str_m_now, &(termData.transactionDate[4]), 1);
	uint8 n_y = atoi(str_y_card);
	uint8 n_m = atoi(str_m_card);
	uint8 n_y_now = atoi(str_y_now);
	uint8 n_m_now = atoi(str_m_now);
	if (n_y < n_y_now || (n_y == n_y_now && n_m < n_m_now)) {
		printf("Card is Expired. \n");
		ret = EXPIRED_CARD;
	}
	return ret;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	EN_terminalError_t ret = OK_1;
	printf("Enter the transaction amount as float number : ");
	scanf_s("%f", &(termData->transAmount));
	if (termData->transAmount <= 0) {
		printf("Invalid Amount of Transaction. \n");
		ret = INVALID_AMOUNT;
	}
	return ret;
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	EN_terminalError_t ret = OK_1;
	if (termData->transAmount > termData->maxTransAmount) {
		printf("Your are exceed max amount of Transaction. \n");
		ret = EXCEED_MAX_AMOUNT;
	}
	return ret;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	EN_terminalError_t ret = OK_1;
	printf("Enter the transaction max amount : ");
	scanf_s("%f", &(termData->maxTransAmount));
	if (termData->maxTransAmount <= 0) {
		printf("Invalid Max Amount of Transaction. \n");
		ret = INVALID_MAX_AMOUNT;
	}
	return ret;
}
