#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"..\card\card.h"
#include"..\terminal\terminal.h"
#include"server.h"
// use this variable in funcation save transaction to store data in the array
uint32_t Sequence = 2;
ST_accountsDB_t server_sideaccounts[255] = { {100000,BLOCKED,"1234567890123456"},
{ 1000,RUNNING,"5807007076043875" },{ 1000,RUNNING,"7890123456789853" },{ 1000,RUNNING,"3259742852586334" },
{ 1000,RUNNING,"8897252256332225" },{ 1000,RUNNING,"0125885589655899" },{ 1000,RUNNING,"5575888855699666" },
{ 1000,RUNNING,"8879922585223651" },{ 1000,BLOCKED,"4453332214896335" }
};

//this variable to get the number of account in the global array if this account exit
int num_account=-1;
ST_transaction_t server_sidetransaction[255] = { 0 };


EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	
	
	
	if (isValidAccount(transData->cardHolderData) == ACCOUNT_NOT_FOUND) {
		transData->transState = FRAUD_CARD;
		return FRAUD_CARD;
	}
		if (server_sideaccounts[num_account].state == BLOCKED) {
			printf("this acount is BLOCKED\n");
			return DECLINED_STOLEN_CARD;
		}
		
		if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
			return DECLINED_INSUFFECIENT_FUND;
		server_sideaccounts[num_account].balance -= transData->terminalData.transAmount;
		printf("your new balance is: %f\n", server_sideaccounts[num_account].balance);
		transData->transactionSequenceNumber = Sequence;
		if (saveTransaction(transData) == SAVING_FAILED)
			return INTERNAL_SERVER_ERROR;
		return APPROVED;
	}

EN_serverError_t isValidAccount(ST_cardData_t cardData) {
	for (int i = 0;i < 255;i++) {
		if (strcmp(cardData.primaryAccountNumber, server_sideaccounts[i].primaryAccountNumber) == 0) {
			num_account = i;
			return SERVER_OK;
		}
	}
	printf("this account not found\n");
	return ACCOUNT_NOT_FOUND;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {

	if (termData->transAmount < server_sideaccounts[num_account].balance) {
		return SERVER_OK;
	}
	else {
		printf("amount is not enough \n");
		return LOW_BALANCE;
	}
}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
	uint32_t i = 0;
//	printf("%d\n", server_sidetransaction[i].transactionSequenceNumber);
	while (transData[i].transactionSequenceNumber != 0) {
		if (transData[i].transactionSequenceNumber == transactionSequenceNumber) {
			printf("the holder name is :%s\n", server_sidetransaction[i].cardHolderData.cardHolderName);
			printf("the expiry date is :%s\n", server_sidetransaction[i].cardHolderData.cardExpirationDate);
			printf("the primiry account number  is :%s\n", server_sidetransaction[i].cardHolderData.primaryAccountNumber);
			printf("the transaction date is :%s\n", server_sidetransaction[i].terminalData.transactionDate);
			printf("the maximum amount  is :%f\n", server_sidetransaction[i].terminalData.maxTransAmount);
			printf("the transaction amount  is :%f\n", server_sidetransaction[i].terminalData.transAmount);
			printf("the transaction sequence number is :%d\n", server_sidetransaction[i].transactionSequenceNumber);
			return SERVER_OK;
		}
		i++;
	}
	printf("the transaction not found\n");
	return TRANSACTION_NOT_FOUND;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	uint32_t i = Sequence - 2;
	if (i > 255) {
		printf("saving failed\n");
		return SAVING_FAILED;
	}
	else {
		server_sidetransaction[i].cardHolderData = transData->cardHolderData;
		printf("%s\n", transData->cardHolderData.cardHolderName);
		server_sidetransaction[i].terminalData = transData->terminalData;
		server_sidetransaction[i].transactionSequenceNumber = transData->transactionSequenceNumber;
		server_sidetransaction[i].transState = transData->transState;
		
		getTransaction(transData->transactionSequenceNumber, transData);
		Sequence++;
		
	}
}
		