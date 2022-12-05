#include "customer.h"

void printCustomer(const Customer* pCustomer)
{
	printf("Customer name: %s\n", pCustomer->name);
	printShoppingCart(&pCustomer->cart);
}

void initCustomer(Customer* pCustomer)
{
	Customer* tempCustomer = (Customer*)malloc(sizeof(Customer));
	tempCustomer->name = NULL;
	tempCustomer->cart = NULL;
	pCustomer = *tempCustomer;
}

void insertCustomerData(Customer* pCustomer, char* name)
{
	pCustomer->name = name;
	initShoppingCart(&pCustomer->cart);
}
