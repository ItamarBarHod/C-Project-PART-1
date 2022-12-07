#include "supermarket.h"
#include "stringfuncs.h"
#include "address.h"

void initSuperMarket(Supermarket* pSupermarket)
{
	printf("Enter supermarket name\n");
	pSupermarket->marketName = getNameFromUser(MAX_SIZE);
	getAddressData(&pSupermarket->marketAddress);
	pSupermarket->customerArr = NULL;
	pSupermarket->customerArrSize = 0;
	pSupermarket->productArr = NULL;
	pSupermarket->productArrSize = 0;
}

void printMarket(const Supermarket* pSupermarket) // TODO
{
	if (pSupermarket->productArrSize == 0)
	{
		printf("no products exist yet\n");
		return;
	}
	printf("Market name: %s \n", pSupermarket->marketName);
	//printAddress(&pSupermarket->marketAddress);
	printf("Product Name ------------ | BARCODE | Type  -------- | Price ------ | Stock \n");
	printf("----------------------------------------------------------------------------\n");
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		printProduct(pSupermarket->productArr[i]);
	}
	printf("\nNumber of customers: %d\n", pSupermarket->customerArrSize);
	if (pSupermarket->customerArrSize > 0)
	{
		printCustomers(pSupermarket);
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

void addProductHelper(Supermarket* pSupermarket, const char* barcode)
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
	pSupermarket->productArr = initProdArr;
	pSupermarket->productArrSize++;
}

void addCustomer(Supermarket* pSupermarket)
{
	printf("Enter customer name\n");
	char* name = getNameFromUser(MAX_SIZE);
	int customerExists = checkCustomerExists(pSupermarket, name, NULL);
	if (customerExists)
	{
		printf("Customer with this name already exists, returning\n");
	}
	else
	{
		printf("Added customer: %s\n", name);
		addCustomerHelper(pSupermarket, name);
	}
	return;
}

void addCustomerHelper(Supermarket* pSupermarket, const char* name)
{
	Customer* customer = initCustomer();
	insertCustomerData(customer, name);
	int arrSize = pSupermarket->customerArrSize;
	Customer* tempArr = (Customer*)realloc(pSupermarket->customerArr, (arrSize + 1) * sizeof(Customer));
	if (tempArr == NULL)
	{
		printf("MEMORY ERROR!\n");
		return;
	}
	*(tempArr + arrSize) = *customer;
	pSupermarket->customerArr = tempArr;
	pSupermarket->customerArrSize++;
}

void customerShopping(Supermarket* pSupermarket)
{
	if (pSupermarket->productArrSize == 0)
	{
		printf("No products exist yet, returning\n");
		return;
	}
	if (checkSupermarketStock(pSupermarket) == 0)
	{
		printf("No stock is available\n");
		return;
	}

	if (pSupermarket->customerArrSize > 0)
	{
		printMarket(pSupermarket);
		printf("Please enter customer name to start shopping\n");
		char* ShoppingCustomerName = getCustomerNameToShop(pSupermarket);
		customerShoppingHelper(pSupermarket, ShoppingCustomerName);
	}
	else {
		printf("No customers exist yet! returning\n");
	}
}

int checkSupermarketStock(const Supermarket* pSupermarket)
{
	int stockCounter = 0;
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		stockCounter += pSupermarket->productArr[i]->stock;
	}
	return stockCounter;
}

void customerShoppingHelper(Supermarket* pSupermarket, const char* customerName)
{
	if (checkSupermarketStock(pSupermarket) == 0)
	{
		printf("Out of stock! returning\n");
		return;
	}
	int barcodePosition = getValidBarcodePosition(pSupermarket);
	int numberToPurchase;
	int itemStock = pSupermarket->productArr[barcodePosition]->stock;
	do {
		printf("Please enter the amount to buy, cant be more than %d (or less than 0)\n", itemStock);
		numberToPurchase = getNumberFromUser();
	} while (numberToPurchase > itemStock || numberToPurchase < 0);

	pSupermarket->productArr[barcodePosition]->stock -= numberToPurchase; // reduce from stock

	printf("Would you like to continue purchasing?\n");
	int proceedShopping = askUserToContinue();
	if (proceedShopping)
	{
		customerShoppingHelper(pSupermarket, customerName);
	}
}

int getValidBarcodePosition(const Supermarket* pSupermarket)
{
	int barcodePosition;
	printf("Please enter a the product's barcode\n");
	do {
		char* barcode = getBarcodeFromUser();
		barcodePosition = getBarcodePosition(pSupermarket, barcode);
		if (barcodePosition == -1) // check exists
		{
			printf("Barcode does not exist! please re-enter\n");
		}
	} while (barcodePosition == -1);
	return barcodePosition;
}

int getBarcodePosition(const Supermarket* pSupermarket, const char* barcode)
{
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		int equal = strcmp(pSupermarket->productArr[i]->barcode, barcode);
		if (equal == 0)
		{
			return i;
		}
	}
	return -1;
}

char* getCustomerNameToShop(const Supermarket* pSupermarket)
{
	char* shoppingCustomerName = NULL;
	int validName;
	do {
		char* shoppingCustomerName = getNameFromUser(MAX_SIZE);
		printf("%s\n", shoppingCustomerName);
		validName = checkCustomerExists(pSupermarket, shoppingCustomerName, NULL);
		if (!validName)
		{
			printf("Invalid name, please enter a customer that exists\n");
		}
	} while (!validName);
}

void printCustomerShoppingCart(const Supermarket* pSupermarket)
{
	printf("enter customer name:\n");
	char* name = getNameFromUser(MAX_SIZE);
	int customerPos;
	int validName = checkCustomerExists(pSupermarket, name, &customerPos);
	if (validName) {
		int cartSize = pSupermarket->customerArr[customerPos].cart.shoppingCartSize;
		if (cartSize > 0)
		{
			printf("printing customer cart:\n");
			printCustomer(&pSupermarket->customerArr[customerPos]);
		}
		else {
			printf("customer has no items in his cart yet!\n");
		}
	}
	else
	{
		printf("customer with this name does not exist, returning to main menu\n");
	}
	return;
}

void printCustomers(const Supermarket* pSupermarket)
{
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		printf("%d:", i + 1);
		printCustomer(&pSupermarket->customerArr[i]);
	}
}

void customerPay(const Supermarket* pSupermarket)
{
	if (pSupermarket->customerArrSize == 0)
	{
		printf("no customers exist yet\n");
		return;
	}
	printf("enter customer name:\n");
	printCustomers(pSupermarket);
	char* name = getNameFromUser(MAX_SIZE);
	int customerPos;
	int customerExists = checkCustomerExists(pSupermarket, name, &customerPos);
	if (!customerExists)
	{
		printf("No such customer exists, returning to main menu\n");
	}
	else
	{
		int cartSize = pSupermarket->customerArr[customerPos].cart.shoppingCartSize;
		if (cartSize > 0) {
			customerCheckout(pSupermarket, name, customerPos);
		}
		else
		{
			printf("This customer has no items yet, returning to main menu\n");
		}
	}
	return;
}

void customerCheckout(const Supermarket* pSupermarket, const char* name, int customerPos)
{
	printf("Customer %s is eligible for checkout!\nprinting customer cart:\n", name);
	printShoppingCart(&pSupermarket->customerArr[customerPos].cart);
	printf("Price: %lf\n", calcShoppingCart(&pSupermarket->customerArr[customerPos].cart));
}

int getProductPos(const Supermarket* pSupermarket, const Shoppingitem item)
{
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		if (pSupermarket->productArr[i]->barcode == item.barcode)
		{
			return i;
		}
	}
}

void printProductType(const Supermarket* pSupermarket)
{
	if (pSupermarket->productArrSize == 0)
	{
		printf("no products exist yet\n");
		return;
	}
	int type = getProductTypeFromUser();
	printf("Product Name ------------ | BARCODE | Type  -------- | Price ------ | Stock \n");
	printf("----------------------------------------------------------------------------\n");
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
			*productPos = i; // check if works, else put if
			return 1;
		}
	}
	return 0;
}

int checkCustomerExists(const Supermarket* pSupermarket, char* pCustomerName, int* customerPos)
{
	char* customerTemp = pCustomerName;
	customerTemp = _strlwr(customerTemp);
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		char* existTemp = pSupermarket->customerArr[i].name;
		existTemp = _strlwr(existTemp);
		int compare = strcmp(existTemp, customerTemp); // check ABC != abc
		if (compare == 0) // equal
		{
			if (customerPos == NULL)
			{
				return 1;
			}
			*customerPos = i;
			return 1;
		}
	}
	return 0;
}

void deleteSuperMarket(Supermarket* pSupermarket)
{
	free(pSupermarket->marketName);
	// pSupermarket->marketName = NULL;
	for (int i = 0; i < pSupermarket->customerArrSize; i++) {
		free(&pSupermarket->customerArr[i]);
	}
	// pSupermarket->customerArr = NULL;
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		free(pSupermarket->productArr[i]);
	}
	// pSupermarket->productArr = NULL;
	free(pSupermarket);
}
