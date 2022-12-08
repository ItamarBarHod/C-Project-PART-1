#include "supermarket.h"

void createSuperMarket(Supermarket* pSupermarket)
{
	printf("Enter supermarket name\n");
	pSupermarket->marketName = getNameFromUser(MAX_SIZE);
	if (pSupermarket->marketName == NULL)
	{
		printf("MEMORY ERROR\n");
		return;
	}
	// pSupermarket->marketAddress = *getAddressData();
	//if (&pSupermarket->marketAddress == NULL)
	//{
	//	printf("MEMORY ERROR\n");
	//	return;
	//}
	pSupermarket->customerArr = NULL;
	pSupermarket->customerArrSize = 0;
	pSupermarket->productArr = NULL;
	pSupermarket->productArrSize = 0;
}

void printMarket(const Supermarket* pSupermarket) // TODO
{
	if (pSupermarket->productArrSize == 0)
	{
		printf("Error: no products exist yet\n");
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
	Product* tempProduct = createNewProduct(); // malloc
	if (tempProduct == NULL)
	{
		return;
	}
	Product* prodExist = checkProductExists(pSupermarket, tempProduct); // doesnt malloc
	if (prodExist != NULL)
	{
		addStockToProduct(pSupermarket, tempProduct);
		freeProduct(tempProduct); // free
		return;
	}
	printf("Adding product with barcode %s:\n", tempProduct->barcode);
	addProductHelper(pSupermarket, tempProduct);
}

void addProductHelper(Supermarket* pSupermarket, Product* pProduct)
{
	insertProductData(pProduct);
	if (pProduct->productName == NULL)
	{
		printf("MEMORY ERROR\n");
		freeProduct(pProduct);
		return;
	}
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

void addStockToProduct(Supermarket* pSupermarket, Product* pProduct)
{
	Product* ProdExists = checkProductExists(pSupermarket, pProduct);
	printf("Product with barcode %s already exists under the name: %s\n", ProdExists->barcode, ProdExists->productName);
	printf("Type amount to add to product:\n");
	int addAmount = (int)getNumberFromUser();
	int productPosition = getProductPos(pSupermarket, pProduct);
	pSupermarket->productArr[productPosition]->stock += addAmount;
}

void addCustomer(Supermarket* pSupermarket)
{
	printf("Please enter customer name to add\n");
	Customer* tempCustomer = createNewCustomer(); // malloc
	if (tempCustomer == NULL)
	{
		return;
	}
	Customer* custExists = checkCustomerExists(pSupermarket, tempCustomer);
	if (custExists != NULL) // exists
	{
		printf("Error: Customer with this name already exists, returning\n");
		freeCustomer(tempCustomer); // free
		return;
	}
	addCustomerHelper(pSupermarket, tempCustomer); // add new customer
}

void addCustomerHelper(Supermarket* pSupermarket, Customer* pCustomer)
{
	int arrSize = pSupermarket->customerArrSize;
	Customer* tempArr = (Customer*)realloc(pSupermarket->customerArr, (arrSize + 1) * sizeof(Customer));
	if (tempArr == NULL)
	{
		printf("MEMORY ERROR!\n");
		return;
	}
	tempArr[arrSize] = *pCustomer;
	pSupermarket->customerArr = tempArr;
	pSupermarket->customerArrSize++;
	printf("Added customer: %s\n", pCustomer->name);
}

void customerShopping(Supermarket* pSupermarket)
{
	if (!validMarket(pSupermarket))
	{
		return; // prints errors inside
	}
	printMarket(pSupermarket);
	printf("Please enter existing customer name to start shopping\n");
	Customer* shoppingCustomer = createNewCustomer(); // malloc
	if (shoppingCustomer == NULL)
	{
		return;
	}
	Customer* customerExists = checkCustomerExists(pSupermarket, shoppingCustomer);
	if (customerExists != NULL)
	{
		customerShoppingHelper(pSupermarket, shoppingCustomer);
		freeCustomer(shoppingCustomer); // free
		return;
	}
	printf("Error: Customer doesnt exist, returning\n");
}

void customerShoppingHelper(Supermarket* pSupermarket, Customer* pCustomer)
{
	if (getSupermarketEntireStock(pSupermarket) == 0)
	{
		printf("Error: Market out of stock! returning\n");
		return; // will free
	}
	Product* existingProduct = getExistingProductFromUser(pSupermarket);
	if (existingProduct == NULL)
	{
		printf("MEMORY ERROR\n");
		return;
	}
	int amount = getAmountToBuyFromUser(pSupermarket, existingProduct);
	putItemInCustomerCart(pSupermarket, pCustomer, existingProduct, amount);

	printf("Would you like to continue shopping?\n");
	int proceedShopping = askUserToContinue();
	if (proceedShopping)
	{
		customerShoppingHelper(pSupermarket, pCustomer);
	}
}

void putItemInCustomerCart(Supermarket* pSupermarket, const Customer* pCustomer, Product* pProduct, int amount)
{
	int productPos = getProductPos(pSupermarket, pProduct);
	pSupermarket->productArr[productPos]->stock -= amount; // reduce from stock
	int customerPos = getCustomerPos(pSupermarket, pCustomer);
	Shoppingcart* cart = &pSupermarket->customerArr[customerPos].cart;
	int itemPos = getItemPos(cart, pProduct);
	printf("Product: %s (%s) stock left: %d\n", pProduct->productName, pProduct->barcode, pProduct->stock);
	int itemExists = checkItemExists(cart, pProduct);
	if (itemExists)
	{
		int itemPos = getItemPos(cart, pProduct);
		cart->itemsArr[itemPos]->amount += amount;
	}
	else
	{
		addItemToCart(&pSupermarket->customerArr[customerPos].cart, pProduct, amount);
	}
}

int getAmountToBuyFromUser(const Supermarket* pSupermarket, const Product* pProduct)
{
	int productPos = getProductPos(pSupermarket, pProduct);
	int itemStock = pSupermarket->productArr[productPos]->stock;
	int amount;
	do {
		printf("Please enter the amount to buy, cant be more than %d (or less than 0)\n", itemStock);
		amount = (int)getNumberFromUser();
	} while (amount > itemStock || amount < 0);
	return amount;
}

Product* getExistingProductFromUser(const Supermarket* pSupermarket)
{
	Product* tempProduct = NULL;
	Product* existProduct; // local
	do {
		Product* tempProduct = createNewProduct(); // malloc
		if (tempProduct == NULL)
		{
			return NULL;
		}
		existProduct = checkProductExists(pSupermarket, tempProduct);
		if (existProduct == NULL) // DOESNT EXIST
		{
			printf("Error: Barcode does not exist! please re-enter\n");
			freeProduct(tempProduct); // free
		}
	} while (existProduct == NULL);
	return existProduct;
}

int checkBarcodeExists(const Supermarket* pSupermarket, const char* barcode)
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

int getSupermarketEntireStock(const Supermarket* pSupermarket)
{
	int stockCounter = 0;
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		stockCounter += pSupermarket->productArr[i]->stock;
	}
	return stockCounter;
}

int validMarket(Supermarket* pSupermarket)
{
	if (pSupermarket->productArrSize == 0)
	{
		printf("No products exist yet, returning\n");
		return 0;
	}
	if (getSupermarketEntireStock(pSupermarket) == 0)
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

void printCustomerShoppingCart(const Supermarket* pSupermarket)
{
	printf("Printing existing customers:\n");
	printCustomers(pSupermarket);
	Customer* tempCustomer = createNewCustomer(); // malloc
	if (tempCustomer == NULL)
	{
		return;
	}
	int customerPos = getCustomerPos(pSupermarket, tempCustomer);
	Customer* custExists = checkCustomerExists(pSupermarket, tempCustomer);
	if (custExists != NULL) // exists
	{
		int cartSize = pSupermarket->customerArr[customerPos].cart.shoppingCartSize;
		if (cartSize > 0)
		{
			printf("Printing customer %s cart:\n", custExists->name);
			printCustomer(&pSupermarket->customerArr[customerPos]);
			printShoppingCart(&pSupermarket->customerArr[customerPos].cart);
		}
		else
		{
			printf("Error: customer has no items in his cart yet!\n");
		}
	}
	else // customer doesnt exist
	{
		printf("Error: customer with this name does not exist, returning to main menu\n");
	}
	freeCustomer(tempCustomer); // free
}

void printCustomers(const Supermarket* pSupermarket)
{
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		printf("%d: ", i + 1);
		printCustomer(&pSupermarket->customerArr[i]);
	}
}

void customerCheckout(const Supermarket* pSupermarket)
{
	if (pSupermarket->customerArrSize == 0)
	{
		printf("Error: No customers exist yet\n");
		return;
	}
	printf("Printing existing customers:\n");
	printCustomers(pSupermarket);
	Customer* tempCustomer = createNewCustomer(); // malloc
	if (tempCustomer == NULL)
	{
		return;
	}
	Customer* custExists = checkCustomerExists(pSupermarket, tempCustomer); // doesnt malloc
	if (custExists == NULL)
	{
		printf("Error: No such customer exists, returning to main menu\n");
		freeCustomer(tempCustomer); // free
		return;
	}
	customerCheckoutHelper(pSupermarket, tempCustomer);
	freeCustomer(tempCustomer); // free
}

void customerCheckoutHelper(const Supermarket* pSupermarket, const Customer* pCustomer)
{
	int customerPos = getCustomerPos(pSupermarket, pCustomer); // already exists
	Shoppingcart* cart = &pSupermarket->customerArr[customerPos].cart;
	if (cart->shoppingCartSize > 0) {
		printShoppingCart(cart);
		printf("Price: %.2lf\n", calcShoppingCart(cart));
		deleteShoppingCart(cart);
		return;
	}
	// else no items
	printf("Error: This customer has no items yet, returning to main menu\n");

}

void printProductType(const Supermarket* pSupermarket)
{
	if (pSupermarket->productArrSize == 0)
	{
		printf("Error: No products exist yet\n");
		return;
	}
	int type = getProductTypeFromUser();
	printf("\nPrinting product of type: %s\n\n", productTypes[type]);
	printf("Product Name ------------ | BARCODE | Type  -------- | Price ------ | Stock \n");
	printf("----------------------------------------------------------------------------\n");
	printProductTypeHelper(pSupermarket, type);
}

void printProductTypeHelper(const Supermarket* pSupermarket, int type)
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
		printf("Error: No products of type %s exist yet\n", productTypes[type]);
	}
	printf("\n");
}

int getCustomerPos(const Supermarket* pSupermarket, const Customer* pCustomer)
{
	for (int i = 0; i < pSupermarket->customerArrSize; i++)
	{
		int equal = strcmp(pSupermarket->customerArr[i].name, pCustomer->name);
		if (equal == 0) // equal
		{
			return i;
		}
	}
	return -1;
}

int getProductPos(const Supermarket* pSupermarket, const Product* pProduct)
{
	for (int i = 0; i < pSupermarket->productArrSize; i++)
	{
		int equal = strcmp(pSupermarket->productArr[i]->barcode, pProduct->barcode);
		if (equal == 0) // equal
		{
			return i;
		}
	}
	return -1;
}

Product* checkProductExists(const Supermarket* pSupermarket, const Product* pProduct)
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

Customer* checkCustomerExists(const Supermarket* pSupermarket, const Customer* pCustomer)
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
	free(pSupermarket->marketName); // name
	for (int i = 0; i < pSupermarket->customerArrSize; i++) // customers
	{
		freeCustomer(&pSupermarket->customerArr[i]);
	}
	for (int i = 0; i < pSupermarket->productArrSize; i++) // products
	{
		freeProduct(pSupermarket->productArr[i]);
	}
	freeProduct(*pSupermarket->productArr);
}
