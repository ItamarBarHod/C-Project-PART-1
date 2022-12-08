#include "customer.h"
#include "userinput.h"

void printCustomer(const Customer* pCustomer)
{
	printf("Customer name: %s\n", pCustomer->name);
}

Customer* createNewCustomer()
{
	Customer* tempCustomer = (Customer*)malloc(sizeof(Customer));
	if (tempCustomer == NULL)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	tempCustomer->cart = *initShoppingCart();
	if (&tempCustomer->cart == NULL)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	printf("Enter customer name\n");
	tempCustomer->name = getNameFromUser(MAX_SIZE);
	if (tempCustomer->name == NULL)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	return tempCustomer;
}

void freeCustomer(Customer* pCustomer)
{
	free(pCustomer->name);
	for (int i = 0; i < pCustomer->cart.shoppingCartSize; i++)
	{
		freeShoppingItem(pCustomer->cart.itemsArr[i]);
	}
}