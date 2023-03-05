#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../card/card.h"
#include"terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("enter the transaction date in format :DD/MM/YYYY\n");
	scanf("%s",termData->transactionDate);
	int len = strlen(termData->transactionDate);
	if (len == 0 || len < 10) {
		printf("invalid transaction date\n");
		return WRONG_DATE;
	}
	if (termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/') {
		printf("invalid transaction date \n");
		return WRONG_DATE;
	}
	else
		return OK;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	if (termData.transactionDate[8] < cardData.cardExpirationDate[3]) {
		return OK;
	}
	if (termData.transactionDate[8] == cardData.cardExpirationDate[3]) {
		if (termData.transactionDate[9] < cardData.cardExpirationDate[4]) {
			return OK;
		}
		if (termData.transactionDate[9] == cardData.cardExpirationDate[4]) {
			if (termData.transactionDate[3] < cardData.cardExpirationDate[0]) {
				return OK;
			}
			if (termData.transactionDate[3] == cardData.cardExpirationDate[0]){
				if (termData.transactionDate[4] < cardData.cardExpirationDate[1])
					return OK;
				else
				{
					printf("EXPIRED CARD\n");
					return EXPIRED_CARD;
				}
			}
			else
			{
				printf("EXPIRED CARD\n");
				return EXPIRED_CARD;
			}
		}
		else {
			printf("EXPIRED CARD\n");
			return WRONG_DATE;
		}
		}
		else {
			printf("EXPIRED CARD\n");
			return EXPIRED_CARD;
		}
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	float trans_amount = 0;
	printf("enter the transaction amount\n");
	scanf(" %f",&trans_amount);

	if (trans_amount<= 0) {
		printf("invalid amount \n");
		return INVALID_AMOUNT;
	}
	else {
		termData->transAmount = trans_amount;
		return OK;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	float max_amount;
	printf("enter the maximum amount \n");
	scanf("%f",&max_amount);
	if (max_amount<= 0) {
		printf("invalid amount \n");
		return INVALID_MAX_AMOUNT;
	}
	else {
		termData->maxTransAmount = max_amount;
		return TERMINAL_OK;
	}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount) {
		printf("you EXCEED maximum amount\n");
		return EXCEED_MAX_AMOUNT;
	}
	else
		return TERMINAL_OK;
}

