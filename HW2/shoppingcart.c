#include "shoppingcart.h"

void printShoppingCart(const Shoppingcart* pShoppingCart)
{
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		printShoppingItem(&pShoppingCart->itemsArr[i]);
	}
	printf("\n");
}

void initShoppingCart(Shoppingcart* pShoppingCart)
{
	pShoppingCart->shoppingCartSize = 0;
	pShoppingCart->itemsArr = NULL;
}

void returnShoppingCart(Shoppingcart* pShoppingCart) // needs to be in supermarket plus reduce from products
{
	for (int i = 0; i < pShoppingCart->shoppingCartSize; i++)
	{
		free(pShoppingCart->itemsArr[i]);
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
	realloc(temp, pShoppingCart->itemsArr);
	temp[pShoppingCart->shoppingCartSize - 1] = *pShoppingitem;
	pShoppingCart->itemsArr = NULL;
}