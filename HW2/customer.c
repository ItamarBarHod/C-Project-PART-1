#include "customer.h"
#include "userinput.h"

void printCustomer(const Customer* pCustomer)
{
	printf("Customer name: %s\n", pCustomer->name);
}

Customer* createNewCustomer()
{
	//Customer* newCustomer = NULL;
	//char* customerName = NULL;
	//Shoppingcart* tempCart = NULL;
	//	newCustomer = (Customer*)malloc(sizeof(Customer)); // malloc
	//if (!newCustomer)
	//{
	//	freeNewCustomer(newCustomer, tempCart, customerName);
	//	return NULL;
	//}
	//tempCart = initShoppingCart(); // malloc
	//if (!tempCart)
	//{
	//	freeNewCustomer(newCustomer, tempCart, customerName);
	//	return NULL;
	//}
	//char* customerName = getNameFromUser(MAX_SIZE); // malloc
	//if (!customerName)
	//{
	//	freeNewCustomer(newCustomer, tempCart, customerName);
	//	return NULL;
	//}
	//newCustomer->cart = *tempCart;
	//newCustomer->name = customerName;
	//return newCustomer;

	//Customer*	newCustomer = (Customer*)malloc(sizeof(Customer)); // malloc
	//if (!newCustomer)
	//{
	//  printf("MEMORY ERROR\n");
	//	return NULL;
	//}
	//newCustomer->cart = *initShoppingCart();
	//if (!&newCustomer->cart)
	//{
	//	free(newCustomer);
	//	return NULL;
	//}
	//printf("Enter customer name\n");
	//newCustomer->name = getNameFromUser(MAX_SIZE);
	//if (!newCustomer->name)
	//{
	//	free(newCustomer->cart.itemsArr);
	//	free(newCustomer);
	//	return NULL;
	//}
	//return newCustomer;
}

void freeCustomer(Customer* pCustomer)
{
	free(pCustomer->name);
	for (int i = 0; i < pCustomer->cart.shoppingCartSize; i++)
	{
		freeShoppingItem(pCustomer->cart.itemsArr[i]);
	}
}

//void freeNewCustomer(Customer* newCustomer, Shoppingcart* tempCart, char* customerName)
//{
//	free(newCustomer);
//	free(tempCart);
//	deleteShoppingCart(tempCart);
//	free(customerName);
//}