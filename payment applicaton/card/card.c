#include<stdio.h>
#include<string.h>
#include"card.h"
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("enter the holder name miniumum 20 char and max 24 char \n");
	gets(cardData->cardHolderName);
	int len_holder_name = strlen(cardData->cardHolderName);
	if (len_holder_name == 0 || len_holder_name < 20 || len_holder_name>24) {
		printf("invalid name \n");
		return WRONG_NAME;
	}
	else
		return OK;

}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("enter the expiry data in format:MM/YY\n");
	gets(cardData->cardExpirationDate);
	int length = strlen(cardData->cardExpirationDate);
	if (length == 0 || length < 5 || length>5) {
		printf("invalid expiry date\n");
		return WRONG_EXP_DATE;
	}
	if (cardData->cardExpirationDate[2] != '/') {
		printf("invalid expiry data format\n");
		return WRONG_EXP_DATE;
	}
	
	if (cardData->cardExpirationDate[0] == '1') {
		if (cardData->cardExpirationDate[1] > '2') {
			printf("invalid expiry date\n");
			return WRONG_EXP_DATE;
		}
	}
	
	else
		return OK;

}
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("enter the card pan miniumum 16 char maximumum 19 char \n");
	gets(cardData->primaryAccountNumber);
	int len = strlen(cardData->primaryAccountNumber);
	if (len == 0 || len < 16 || len>19) {
		printf("invalid card pan\n");
		return WRONG_PAN;
	}
	for (int i = 0;i < len;i++) {
		if (!(cardData->primaryAccountNumber[i] >= 'a' && cardData->primaryAccountNumber[i] <= 'z')) {
			if (!(cardData->primaryAccountNumber[i] >= 'A' && cardData->primaryAccountNumber[i] <= 'Z')) {
				if (!(cardData->primaryAccountNumber[i] >= '0' && cardData->primaryAccountNumber[i] <= '9')) {
					printf("invalid card pan\n");
					return WRONG_PAN;
				}
			}
		}
	}
			return OK;



	}
