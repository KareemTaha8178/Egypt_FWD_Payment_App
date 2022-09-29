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
ST_accountsDB_t st_account;

void appStart(void) {

    getCardHolderName(&cardData_1);
    getCardExpiryDate(&cardData_1);
    getTransactionDate(&termData_1);
    isCardExpired(cardData_1, termData_1);
    if (isCardExpired(cardData_1, termData_1) != OK_1) {
        printf("Your transaction is refused.\n");
        return 0;
    }
    getCardPAN(&cardData_1);
    isValidAccount(&cardData_1);
    if (isValidAccount(&cardData_1) != OK_2) {
        printf("Your transaction is refused.\n");
        return 0;
    }
    setMaxAmount(&termData_1);
    getTransactionAmount(&termData_1);
    isBelowMaxAmount(&termData_1);
    if (isBelowMaxAmount(&termData_1) != OK_1) {
        printf("Your transaction is refused.\n");
        return 0;
    }
    isAmountAvailable(&termData_1);
    if (isAmountAvailable(&termData_1) != OK_2) {
        printf("Your transaction is refused.\n");
        return 0;
    }
    isBlockedAccount(&st_account);
    if (isBlockedAccount(&st_account) != APPROVED) {
        printf("Your transaction is refused.\n");
        return 0;
    }

    transData_1.cardHolderData = cardData_1; // UPDATE CARD_HOLDER_DATA
    transData_1.terminalData = termData_1;
    saveTransaction(&transData_1);

    //getTransaction(transData_1.transactionSequenceNumber, &transData_1);

    recieveTransactionData(&transData_1);
}

int main()
{

    appStart();
    return 0;
}
