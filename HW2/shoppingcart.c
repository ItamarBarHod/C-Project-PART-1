#include "shoppingcart.h"

void printShoppingCart(const Shoppingcart* pShoppingCart)
{
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		printShoppingItem(&pShoppingCart->itemsArr[i]);
	}
	printf("\n");
}

Shoppingcart* initShoppingCart()
{
	Shoppingcart* tempCart = (Shoppingcart*)malloc(sizeof(Shoppingcart));
	if (tempCart == NULL)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	tempCart->shoppingCartSize = 0;
	tempCart->itemsArr = NULL;
	return tempCart;
}

double calcShoppingCart(const Shoppingcart* pShoppingCart)
{
	double sum = 0;
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		int amount = pShoppingCart->itemsArr[i].amount;
		double price = pShoppingCart->itemsArr[i].price;
		sum += amount * price;
	}
	return sum;
}

void deleteShoppingCart(Shoppingcart* pShoppingCart)
{
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		free(&pShoppingCart->itemsArr[i]);
	}
	pShoppingCart = NULL;
}

void addItemToCart(Shoppingcart* pShoppingCart, const Shoppingitem* pShoppingitem) // check works
{
	int cartSize = pShoppingCart->shoppingCartSize;
	Shoppingcart* temp = (Shoppingcart*)realloc(pShoppingCart, (cartSize + 1) * sizeof(Shoppingitem*));
	if (temp == NULL)
	{
		printf("MEMORY ERROR\n");
		return;
	}
	// temp->itemsArr[pShoppingCart->shoppingCartSize] = pShoppingitem; // TODO
	pShoppingCart->shoppingCartSize++;
}