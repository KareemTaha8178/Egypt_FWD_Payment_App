/** ========================================**
 ** @Author: Kareem Taha Abdelfatah
 ** @Category: Payment Application
 ** @brief: Payment Application with credit card for """Egypt FWD"""
/** ========================================**/

#include<stdio.h>
#include<stdlib.h>
#include "Application.h"


ST_cardData_t cardData_1;
ST_terminalData_t termData_1;
ST_transaction transData_1;

void appStart(void) {
    getCardHolderName(&cardData_1);
    getCardExpiryDate(&cardData_1);
    getCardPAN(&cardData_1);

    getTransactionDate(&termData_1);
    isCardExpired(cardData_1, termData_1);
    setMaxAmount(&termData_1);
    getTransactionAmount(&termData_1);
    isBelowMaxAmount(&termData_1);

    recieveTransactionData(&transData_1);
    saveTransaction(&transData_1);
}

int main()
{

    appStart();
    return 0;
}
