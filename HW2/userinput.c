#include "userinput.h"

int getProductTypeFromUser()
{
	int type;
	printf("please enter a product type:\n0: Shelf\n1: Frozen\n2: Fridge\n3: FruitVegetable\n");
	do {
		scanf(" %d", &type);
		if (type < 0 || type >= eNofEnum)
		{
			printf("wrong type, please re-enter a number between 0 and 3\n");
		}
	} while (type < 0 || type >= eNofEnum);
	return type;
}


float getNumberFromUser()
{
	float price;
	do {
		scanf(" %f", &price);
		if (price < 0)
		{
			printf("please enter a NON NEGATIVE number!\n");
		}
	} while (price < 0);
	return price;
}

char* getNameFromUser(int maxStrSize)
{
	char temp[MAX_SIZE];
	printf("Max size: 254 letters\n");
	fgetc(stdin); // clear buffer
	do {
		fgets(temp, maxStrSize, stdin);
		if (temp == NULL)
		{
			printf("Please re-enter\n");
		}
	} while (temp == NULL);
	char* str = _strdup(temp);
	return str;
}

char* getBarcodeFromUser()
{
	char temp[MAX_SIZE];
	int validBarcode;
	fgetc(stdin);
	do {
		fgets(temp, BARCODE_SIZE, stdin);
		validBarcode = isValidBarcode(temp);
	} while (!validBarcode || temp == NULL);
	char* barcode = (char*)malloc(strlen(temp) * sizeof(char));
	if (barcode == NULL)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	barcode = _strdup(temp);
	return barcode;
}

char* getAddressFromUser()
{
	int validAddressFormat;
	char* address;
	printf("Please enter address, format: Street name#House number#City\n");
	do {
		address = getNameFromUser(MAX_SIZE);
		validAddressFormat = isValidAddressFormat(address);
	} while (!validAddressFormat);
	return address;
}
