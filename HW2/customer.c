#include "customer.h"

void printCustomer(const Customer* pCustomer)
{
	printf("Customer name: %s\n", pCustomer->name);
	printShoppingCart(&pCustomer->cart);
}

Customer* initCustomer()
{
	Customer* tempCustomer = (Customer*)malloc(sizeof(Customer));
	if (tempCustomer == NULL)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	tempCustomer->name = NULL;
	return tempCustomer;
}

void insertCustomerData(Customer* pCustomer, char* name)
{
	pCustomer->name = name;
	initShoppingCart(&pCustomer->cart);
}
