/* Section : Includes */
#include "Card.h"

/* Section : Macros Definition */


/* Section : Macros Functions Declaration */

/* Section : Data Types Declaration */


/* Section : Function Declaration */

EN_cardError_t  getCardHolderName(ST_cardData_t* cardData) {
	EN_cardError_t ret = OK;
	uint8 holdername[25], count = 0, it = 0;;
	printf("Enter your card name [20-24] : ");
	gets(holdername);

	while(holdername[it] != '\0') {
		if (holdername[it] != ' ') {
			if ((holdername[it] >= 'a' && holdername[it] <= 'z') || (holdername[it] >= 'A' && holdername[it] <= 'Z')) {
				count++;
			}
		}
		it++;
	}
	if (count < 20 || count > 24) {
		printf("WRONG_NAME. \n");
		ret = WRONG_NAME;
	}
	else {
		for (int i = 0; i < count; i++) {
			cardData->cardHolderName[i] = holdername[i];
		}
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
	if ((expirydate[0] == '1' && (expirydate[1] == '1' || expirydate[1] == '2')) || (expirydate[0] == '0')) count++;
	if (count != 6) {
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
	scanf_s("%s", CardPAN, 20);
	while (CardPAN[count] != '\0') {
		if (CardPAN[count] > '9' || CardPAN[count] < '0') {
			flag = 0;
		}
		count++;
	}
	if (count < 16 || count > 20 || flag == 0) {
		printf("WRONG_PAN. \n");
		ret = WRONG_PAN;
	}
	else {
		for (int i = 0; i < count; i++) {
			cardData->primaryAccountNumber[i] = CardPAN[i];
		}
	}
	return ret;
}
