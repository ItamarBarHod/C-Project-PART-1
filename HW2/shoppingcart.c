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
		return;
	}
	tempCart->shoppingCartSize = 0;
	tempCart->itemsArr = NULL;
	return tempCart;
}

void returnShoppingCart(Shoppingcart* pShoppingCart) // needs to be in supermarket plus reduce from products
{
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		free(&pShoppingCart->itemsArr[i]);
	}
	pShoppingCart->shoppingCartSize = 0;
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

void addItemToCart(Shoppingcart* pShoppingCart, const Shoppingitem* pShoppingitem) // check works
{
	pShoppingCart->shoppingCartSize++;
	Shoppingitem* temp = (Shoppingitem*)(malloc(pShoppingCart->shoppingCartSize * sizeof(Shoppingitem)));
	if (temp == NULL)
	{
		printf("MEMORY ERROR\n");
		return;
	}
	realloc(temp, pShoppingCart->itemsArr);
	pShoppingCart->itemsArr = NULL;
	temp[pShoppingCart->shoppingCartSize - 1] = *pShoppingitem;
}