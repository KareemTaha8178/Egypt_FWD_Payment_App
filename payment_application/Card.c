/* Section : Includes */
#include "Card.h"

/* Section : Macros Definition */


/* Section : Macros Functions Declaration */

/* Section : Data Types Declaration */


/* Section : Function Declaration */

EN_cardError_t  getCardHolderName(ST_cardData_t* cardData) {
	EN_cardError_t ret = OK;
	uint8 count = 0, it = 0;
	printf("Enter your card name [20-24] : ");
	gets(cardData->cardHolderName);
	while(cardData->cardHolderName[it] != '\0') {
		if (cardData->cardHolderName[it] != ' ') {
			if ((cardData->cardHolderName[it] >= 'a' && cardData->cardHolderName[it] <= 'z') || (cardData->cardHolderName[it] >= 'A' && cardData->cardHolderName[it] <= 'Z')) {
				count++;
			}
		}
		it++;
	}
	if (count < 20 || count > 24) {
		printf("WRONG_NAME. \n");
		ret = WRONG_NAME;
	}
	return ret;
}


EN_cardError_t  getCardExpiryDate(ST_cardData_t* cardData) {
	EN_cardError_t ret = OK;
	uint8 expirydate[6], count = 0;
	printf("Enter your card expiry date like format [09/23] : ");
	scanf_s("%s", expirydate, 6);
	for (int i = 0; i < 6; i++)  if (expirydate[i] >= '0' && expirydate[i] <= '9' && i != 2) count++;
	if (expirydate[2] == '/') count++;
	if (((expirydate[0] == '1') && (expirydate[1] > '2')) || (expirydate[0] > '1')) count++;
	if (count != 5) {
		printf("WRONG_EXP_DATE. \n");
		ret = WRONG_EXP_DATE;
	}
	else {
		for (int i = 0; i < 6; i++) {
			cardData->cardExpirationDate[i] = expirydate[i];
		}
	}
	return ret;
}


EN_cardError_t  getCardPAN(ST_cardData_t* cardData) {
	EN_cardError_t ret = OK;
	uint8 CardPAN[20], count = 0, flag = 1;
	printf("Enter your card primary account number [16-20] : ");
	scanf_s("%s", cardData->primaryAccountNumber, 20);
	while (cardData->primaryAccountNumber[count] != '\0') {
		if (cardData->primaryAccountNumber[count] > '9' || cardData->primaryAccountNumber[count] < '0') {
			flag = 0;
		}
		count++;
	}
	if (count < 16 || count > 20 || flag == 0) {
		printf("WRONG_PAN. \n");
		ret = WRONG_PAN;
	}
	return ret;
}
