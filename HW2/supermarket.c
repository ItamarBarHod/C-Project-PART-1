#include "supermarket.h"
#include "stringfuncs.h"
#include "address.h"

void initSuperMarket(Supermarket* pSupermarket)
{
	printf("Enter supermarket name\n");
	pSupermarket->marketName = getNameFromUser();
	initAddress(&pSupermarket->marketAddress);
	pSupermarket->customerArr = NULL;
	pSupermarket->customerArrSize = 0;
	pSupermarket->productArr = NULL;
	pSupermarket->productArrSize = 0;
}

void printMarket(const Supermarket* pSupermarket) // TODO
{
	//printAddress(&pSupermarket->marketAddress);
	if (pSupermarket->productArrSize == 0)
	{
		printf("no products exist yet\n");
		return;
	}
	if (pSupermarket->customerArrSize == 0)
	{
		printf("no customers exist yet\n");
		return;
	}
	printf("Product Name | BARCODE | Type | Price | Stock \n");
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		printProduct(pSupermarket->productArr[i]);
	}
	printf("\n");
}

void addProduct(Supermarket* pSupermarket)
{
	printf("Enter product barcode Code should be of 7 length exactly\n");
	printf("UPPER CASE letter and digits\n");
	printf("Must have 3 to 5 digits\n");
	printf("First and last chars must be UPPER CASE letter\n");
	printf("For example A12B40C\n\n");
	char* barcode = getBarcodeFromUser();
	int productPos;
	int productExists = checkProductExists(pSupermarket, barcode, &productPos);
	if (productExists)
	{
		printf("Product with barcode %s already exists under the name: %s\n", barcode, pSupermarket->productArr[productPos]->productName);
		printf("Type amount to add to product:\n");
		int addAmount = (int)getNumberFromUser();
		pSupermarket->productArr[productPos]->stock += addAmount;
	}
	else
	{
		printf("Adding product with barcode %s:\n", barcode);
		addProductHelper(pSupermarket, barcode);
	}
}

void addProductHelper(Supermarket* pSupermarket, char* barcode)
{
	Product* tempProduct = initProduct();
	insertProductData(tempProduct, barcode);
	int arrSize = pSupermarket->productArrSize;
	Product** initProdArr = (Product**)realloc(pSupermarket->productArr, (arrSize + 1) * sizeof(Product*));
	if (initProdArr == NULL)
	{
		printf("MEMORY ERROR!\n");
		return;
	}
	*(initProdArr + pSupermarket->productArrSize) = tempProduct;
	pSupermarket->productArrSize++;
}

void addCustomer(Supermarket* pSupermarket)
{
	printf("enter customer name:\n");
	char* name = getNameFromUser();
	int customerExists = checkCustomerExists(pSupermarket, name, NULL); // check if null works!
	if (customerExists)
	{
		printf("customer with this name already exists, returning\n");
	}
	else
	{
		printf("added customer\n");
		addCustomerHelper(pSupermarket, name);
	}
	return;
}

void addCustomerHelper(Supermarket* pSupermarket, char* name)  // TODO
{
	Customer* customer = initCustomer();
	insertCustomerData(customer, name);
	int arrSize = pSupermarket->customerArrSize;
	Customer* tempArr = (Customer*)malloc(pSupermarket->customerArr, (arrSize + 1) * sizeof(Customer));
	if (tempArr == NULL)
	{
		printf("MEMORY ERROR!\n");
		return;
	}
	*(tempArr + arrSize) = *customer;
	pSupermarket->customerArrSize++;
}

void customerShopping(Supermarket* pSupermarket)
{
	printf("not finished yet\n");
}

void printCustomerShoppingCart(const Supermarket* pSupermarket)
{
	printf("enter customer name:\n");
	char* name = getNameFromUser();
	int customerPos;
	int validName = checkCustomerExists(pSupermarket, name, &customerPos);
	if (validName) {
		printf("printing customer cart:\n");
		printCustomer(&pSupermarket->customerArr[customerPos]);
	}
	else
	{
		printf("customer with this name does not exist, returning to main menu\n");
	}
	return;
}

void customerPay(Supermarket* pSuperMarket)
{
	if (pSuperMarket->customerArrSize == 0)
	{
		printf("no customers exist yet\n");
		return;
	}
	printf("enter customer name:\n");
	char* name = getNameFromUser();
	int customerPos;
	int validCustomer = checkCustomerExists(pSuperMarket, name, &customerPos);
	if (!validCustomer)
	{
		printf("No such customer exists, returning to main menu\n");
	}
	else
	{
		int cartSize = pSuperMarket->customerArr[customerPos].cart.shoppingCartSize;
		if (cartSize > 0) {
			customerCheckout(pSuperMarket, name, customerPos);
		}
		else
		{
			printf("This customer has no items yet, returning to main menu\n");
		}
	}
	return;
}

void customerCheckout(Supermarket* pSupermarket, char* name, int customerPos)
{
	printf("Customer %s is eligible for checkout!\nprinting customer cart:\n", name);
	printShoppingCart(&pSupermarket->customerArr[customerPos].cart);
	printf("Price: %lf\n", calcShoppingCart(&pSupermarket->customerArr[customerPos].cart));
	returnShoppingCart(&pSupermarket->customerArr[customerPos].cart); // reduce from supermarket data
}

void printProductType(const Supermarket* pSupermarket)
{
	if (pSupermarket->productArrSize == 0)
	{
		printf("no products exist yet\n");
		return;
	}
	int type = getProductTypeFromUser();
	printf("Printing product of type: %s\n", productTypes[type]);
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		if (pSupermarket->productArr[i]->type == type)
		{
			printProduct(pSupermarket->productArr[i]);
		}
	}
	printf("\n");
}

int checkProductExists(const Supermarket* pSupermarket, const char* barcode, int* productPos)
{
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		int compare = strcmp(pSupermarket->productArr[i]->barcode, barcode);
		if (compare == 0) // equal
		{
			*productPos = i;
			return 1;
		}
	}
	return 0;
}

int checkCustomerExists(const Supermarket* pSupermarket, const char* pCustomerName, int* customerPos)
{
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		int compare = strcmp(pSupermarket->customerArr[i].name, pCustomerName);
		if (compare == 0) // equal
		{
			*customerPos = i;
			return 1;
		}
	}
	return 0;
}

void deleteSuperMarket(Supermarket* pSupermarket)
{
	for (int i = 0; i < pSupermarket->customerArrSize; i++) {
		free(&pSupermarket->customerArr[i]);
	}
	pSupermarket->customerArr = NULL;
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		free(pSupermarket->productArr[i]);
	}
	pSupermarket->productArr = NULL;
}
