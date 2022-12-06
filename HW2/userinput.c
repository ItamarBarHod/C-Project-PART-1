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
	float num;
	do {
		scanf(" %f", &num);
		if (num < 0)
		{
			printf("please enter a NON NEGATIVE number!\n");
		}
	} while (num < 0);
	return num;
}

char* getNameFromUser(int maxStrSize)
{
	char temp[MAX_SIZE];
	do {
		fgets(temp, maxStrSize, stdin);
		if (temp == NULL)
		{
			printf("Please re-enter\n");
		}
	} while (temp == NULL);
	char* str = _strdup(temp);
	int tempSize = strlen(temp);
	str[tempSize - 1] = '\0';
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
	char* barcode = _strdup(temp);
	int tempSize = strlen(temp);
	barcode[tempSize - 1] = '\0';
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

int askUserToContinue()
{
	printf("enter Y/y to continue, else enter a random character\n");
	char answer;
	do {
		answer = getchar();
	} while (answer == '\0');
	if (answer == 'y' || answer == 'Y')
	{
		return 1;
	}
	return 0;
}