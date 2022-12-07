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
	Product* tempProduct = initProduct();
	if (tempProduct == NULL)
	{
		printf("MEMORY ERROR\n");
		return;
	}
	printBarcodeInstructions();
	tempProduct->barcode = getBarcodeFromUser();
	if (tempProduct->barcode == NULL)
	{
		printf("MEMORY ERROR\n");
		return;
	}
	Product* prodExist = checkProductExists(pSupermarket, tempProduct); // doesnt malloc
	if (prodExist != NULL) // If exists
	{
		productExists(pSupermarket, prodExist); // add amount to existing
		freeProduct(tempProduct);
		return;
	}
	printf("Adding product with barcode %s:\n", tempProduct->barcode);
	addProductHelper(pSupermarket, tempProduct); // add new product
}

void productExists(Supermarket* pSupermarket, Product* pProduct)
{
	printf("Product with barcode %s already exists under the name: %s\n", pProduct->barcode, pProduct->productName);
	printf("Type amount to add to product:\n");
	int addAmount = (int)getNumberFromUser();
	int productPosition = getProductPosition(pSupermarket, pProduct);
	pSupermarket->productArr[productPosition]->stock += addAmount;
}

int getProductPosition(Supermarket* pSupermarket, Product* pProduct)
{
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		int equal = strcmp(pSupermarket->productArr[i]->barcode, pProduct->barcode);
		if (equal == 0)
		{
			return i;
		}
	}
	return -1;
}

void addProductHelper(Supermarket* pSupermarket, Product* pProduct)
{
	insertProductData(pProduct, pProduct->barcode);
	int arrSize = pSupermarket->productArrSize;
	Product** productArr = (Product**)realloc(pSupermarket->productArr, (arrSize + 1) * sizeof(Product*));
	if (productArr == NULL)
	{
		printf("MEMORY ERROR!\n");
		return;
	}
	productArr[arrSize] = pProduct;
	pSupermarket->productArrSize++;
	pSupermarket->productArr = productArr;
}

void addCustomer(Supermarket* pSupermarket)
{
	Customer* tempCustomer = initCustomer();
	if (tempCustomer == NULL)
	{
		printf("MEMORY ERROR\n");
		return;
	}
	printf("Enter customer name\n");
	tempCustomer->name = getNameFromUser(MAX_SIZE);
	if (tempCustomer->name == NULL)
	{
		printf("MEMORY ERROR\n");
		return;
	}
	Customer* custExists = checkCustomerExists(pSupermarket, tempCustomer); // doesnt malloc
	if (custExists != NULL) // exists
	{
		printf("Customer with this name already exists, returning\n");
		freeCustomer(tempCustomer);
		return;
	}
	addCustomerHelper(pSupermarket, tempCustomer); // add new customer
}

void addCustomerHelper(Supermarket* pSupermarket, Customer* pCustomer)
{
	Customer* customertoAdd = initCustomer();
	insertCustomerData(customertoAdd, pCustomer->name);
	int arrSize = pSupermarket->customerArrSize;
	Customer* tempArr = (Customer*)realloc(pSupermarket->customerArr, (arrSize + 1) * sizeof(Customer));
	if (tempArr == NULL)
	{
		printf("MEMORY ERROR!\n");
		return;
	}
	*(tempArr + arrSize) = *customertoAdd;
	pSupermarket->customerArr = tempArr;
	pSupermarket->customerArrSize++;
	printf("Added customer: %s\n", pCustomer->name);
}

void customerShopping(Supermarket* pSupermarket)
{
	if (!validMarket(pSupermarket)) // check can buy
	{
		return;
	}
	printMarket(pSupermarket);
	printf("Please enter customer name to start shopping\n");
	Customer* shoppingCustomer = initCustomer();
	if (shoppingCustomer == NULL)
	{
		printf("MEMORY ERROR\n");
		return;
	}
	shoppingCustomer->name = getNameFromUser(MAX_SIZE);
	if (shoppingCustomer->name == NULL)
	{
		printf("MEMORY ERROR\n");
		return;
	}
	customerShoppingHelper(pSupermarket, shoppingCustomer);
	freeCustomer(shoppingCustomer);
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

void customerShoppingHelper(Supermarket* pSupermarket, Customer* pCustomer)
{
	if (checkSupermarketStock(pSupermarket) == 0)
	{
		printf("Out of stock! returning\n");
		return;
	}

	int productPosition = getValidBarcodeAndPosition(pSupermarket);
	int numberToPurchase;
	int itemStock = pSupermarket->productArr[productPosition]->stock;
	do {
		printf("Please enter the amount to buy, cant be more than %d (or less than 0)\n", itemStock);
		numberToPurchase = getNumberFromUser();
	} while (numberToPurchase > itemStock || numberToPurchase < 0);

	putItemInCustomerCart(pSupermarket, numberToPurchase, productPosition, customerName);
	printf("Would you like to continue purchasing?\n");
	int proceedShopping = askUserToContinue();
	if (proceedShopping)
	{
		customerShoppingHelper(pSupermarket, customerName);
	}
}

void putItemInCustomerCart(Supermarket* pSupermarket, int numberToPurchase, int productPosition, char* customerName)
{
	pSupermarket->productArr[productPosition]->stock -= numberToPurchase; // reduce from stock
	int customerPos;
	printf("errorne\n");
	const char* barcode = pSupermarket->productArr[productPosition]->barcode;
	printf("errorke\n");
	int answer = checkCustomerExists(pSupermarket, customerName, &customerPos);
	printf("error1\n");
	int productPos = getProductPos(pSupermarket, barcode);
	printf("error2\n");
	Product tempProd = *pSupermarket->productArr[productPos];
	printf("debug?\n");
	addItemToCart(&pSupermarket->customerArr[customerPos].cart, &tempProd);
}

int getValidBarcodeAndPosition(const Supermarket* pSupermarket)
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

int validMarket(Supermarket* pSupermarket)
{
	if (pSupermarket->productArrSize == 0)
	{
		printf("No products exist yet, returning\n");
		return 0;
	}
	if (checkSupermarketStock(pSupermarket) == 0)
	{
		printf("No stock is available\n");
		return 0;
	}
	if (pSupermarket->customerArrSize == 0)
	{
		printf("No cusomters exist yet, returning\n");
		return 0;
	}
	return 1;
}

Customer* getCustomerToShop(const Supermarket* pSupermarket)
{
	Customer* shoppingCustomer = initCustomer();
	do {
		shoppingCustomer->name = getNameFromUser(MAX_SIZE);
		if (shoppingCustomer->name == NULL)
		{
			printf("MEMORY ERROR\n");
			return NULL;
		}
		printf("%s\n", shoppingCustomer->name);
		Customer* tempCustomer = checkCustomerExists(pSupermarket, shoppingCustomer);
		if (tempCustomer == NULL)
		{
			printf("Invalid name, please enter a customer that exists\n");
		}
	} while (!shoppingCustomer);
	return shoppingCustomer;
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
	Customer* tempCustomer = initCustomer();
	insertCustomerData(tempCustomer);
	printf("enter customer name:\n");
	char* name = getNameFromUser(MAX_SIZE);
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
}

void customerCheckout(const Supermarket* pSupermarket, const char* name, int customerPos)
{
	printf("Customer %s is eligible for checkout!\nprinting customer cart:\n", name);
	printShoppingCart(&pSupermarket->customerArr[customerPos].cart);
	printf("Price: %lf\n", calcShoppingCart(&pSupermarket->customerArr[customerPos].cart));
}

int getProductPos(const Supermarket* pSupermarket, const char* barcode)
{
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		if (pSupermarket->productArr[i]->barcode == barcode)
		{
			return i;
		}
	}
	return -1;
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
	printProductTypeHelper(pSupermarket, type);
}

void printProductTypeHelper(Supermarket* pSupermarket, int type)
{
	int counter = 0;
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		if (pSupermarket->productArr[i]->type == type)
		{
			printProduct(pSupermarket->productArr[i]);
			counter++;
		}
	}
	if (counter == 0)
	{
		printf("No products of type %s exist yet\n", productTypes[type]);
	}
	printf("\n");
}

Product* checkProductExists(const Supermarket* pSupermarket, Product* pProduct)
{
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		int compare = strcmp(pSupermarket->productArr[i]->barcode, pProduct->barcode);
		if (compare == 0) // equal
		{
			return pSupermarket->productArr[i];
		}
	}
	return NULL;
}

Customer* checkCustomerExists(const Supermarket* pSupermarket, Customer* pCustomer)
{
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		int equal = strcmp(pSupermarket->customerArr[i].name, pCustomer->name);
		if (equal == 0) // equal
		{
			return &pSupermarket->customerArr[i];
		}
	}
	return NULL;
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
