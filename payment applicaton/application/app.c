#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../card/card.h"
#include"../terminal/terminal.h"
#include"../server/server.h"
#include"app.h"
void appStart(void) {
	ST_cardData_t card_data;
	ST_terminalData_t term_data;
	ST_transaction_t trans_data = { 0 };
	EN_terminalError_t term_error;
	EN_cardError_t card_error;
	EN_transState_t trans_state;
read_cardname:
	card_error = getCardHolderName(&card_data);
	if (card_error == WRONG_NAME) {
		printf("please enter valid HOLDER NAME:\n");
		goto read_cardname;
	}

read_expirydate:
	card_error = getCardExpiryDate(&card_data);
	if (card_error == WRONG_EXP_DATE)
	{
		printf("please enter valid EXPIRT DATE:\n");
		goto read_expirydate;
	}
read_pan:
	card_error = getCardPAN(&card_data);
	if (card_error == WRONG_PAN) {
		printf("please enter valid PAN:\n");
		goto read_pan;
	}
read_maxamount:
	term_error = setMaxAmount(&term_data);
	if (term_error == INVALID_MAX_AMOUNT) {
		printf("please enter valid MAX AMOUNT:\n");
		goto read_maxamount;
	}
read_transdate:
	term_error = getTransactionDate(&term_data);
	if (term_error == WRONG_DATE) {
		printf("please enter valid TRANSACTION DATE:\n");
		goto read_transdate;
	}
	term_error = isCardExpired(card_data, term_data);
	if (term_error == EXPIRED_CARD) {
		printf("this card is expired\n");
		return;
	}
read_transamount:
	term_error = getTransactionAmount(&term_data);
	if (term_error == INVALID_AMOUNT) {
		printf("please enter valid TRANSACTION AMOUNT : \n");
		goto read_transamount;
	}
	term_error = isBelowMaxAmount(&term_data);
	if (term_error == EXCEED_MAX_AMOUNT)
		return;
	trans_data.cardHolderData = card_data;
	trans_data.terminalData = term_data;

	trans_state = recieveTransactionData(&trans_data);
	if (trans_state == DECLINED_STOLEN_CARD || trans_state == FRAUD_CARD) {
		printf("DECLINED STOLEN CARD \n");
		return;
	}
	else if (trans_state == DECLINED_INSUFFECIENT_FUND) {
		printf("DECLINED_INSUFFECIENT_FUND\n");
		return;
	}
	else if (trans_state == INTERNAL_SERVER_ERROR) {
		printf("INTERNAL_SERVER_ERROR\n");
		return;
	}
	else if (trans_state == APPROVED)
		printf("APPROVED\n");
	/*if (getTransaction(trans_data.transactionSequenceNumber, &trans_data) == TRANSACTION_NOT_FOUND) {
		return;
	}*/
		printf("sucssesfully operation\n");
}
