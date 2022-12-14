#include "userinput.h"

int getProductTypeFromUser()
{
	int type;
	printf("Please enter a product type:\n0: Shelf\n1: Frozen\n2: Fridge\n3: FruitVegetable\n");
	do {
		scanf(" %d", &type);
		if (type < 0 || type >= eNofEnum)
		{
			printf("Error: Wrong type, please re-enter a number between 0 and 3\n");
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
			printf("Error: Please enter a NON NEGATIVE number!\n");
		}
	} while (num < 0);
	return num;
}

char* getNameFromUser(int maxNameSize)
{
	char temp[MAX_SIZE];
	char* name = NULL;
	do {
		fgets(temp, maxNameSize, stdin);
	} while (temp == NULL || strlen(temp) == 1);

	name = _strdup(temp); // malloc
	if (name == NULL)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	name[strlen(temp) - 1] = '\0';
	return name;
}

char* getBarcodeFromUser()
{
	char temp[MAX_SIZE];
	int validBarcode;
	char* barcode;
	do {
		fgets(temp, MAX_SIZE, stdin);
		validBarcode = isValidBarcode(temp);
	} while (!validBarcode || temp == NULL || strlen(temp) == 1);

	barcode = _strdup(temp); // malloc
	if (barcode == NULL)
	{
		printf("MEMORY ERROR\n");
		return NULL;
	}
	barcode[BARCODE_SIZE-1] = '\0';
	return barcode;
}

char* getAddressFromUser()
{
	int isvalidFormat;
	char* address;
	do {
		address = getNameFromUser(MAX_SIZE); // malloc
		if (address == NULL)
		{
			printf("MEMORY ERROR\n");
			return NULL;
		}
		isvalidFormat = isValidAddressFormat(address);
		if (!isvalidFormat)
		{
			printf("Error: Invalid address format, please re-enter\n");
			printf("example: vitkin#9#herzelia\n");
			free(address); // free if failed
		}
	} while (!isvalidFormat);
	return address;
}

int askUserToContinue()
{
	printf("Enter Y/y to continue, else enter a random character\n");
	char answer;
	do {
		answer = fgetc(stdin);
	} while (answer == '\n' || answer == '\0');
	if (answer == 'y' || answer == 'Y')
	{
		return 1;
	}
	return 0;
}