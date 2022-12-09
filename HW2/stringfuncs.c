#include "stringfuncs.h"

int isValidBarcode(const char* str)
{
	if (strlen(str) == 1) // buffer fix 
	{
		return 0;
	}
	int digits = checkDigitsCount(str);
	if ((digits > 5 || digits < 3) || (int)strlen(str) != BARCODE_SIZE - 1 || isLowercase(str) || !isValidCharacterPosition(str) || !IsAlphanumeric(str))
	{
		printf("Bad Barcode! Please follow the rules\n");
		return 0;
	}
	return 1;
}

int isValidAddressFormat(const char* str)
{
	int validTokenFormat = validTokens(str);
	int validSections = isValidAddressSections(str);
	if (validTokenFormat && validSections)
	{
		return 1;
	}
	return 0;
}

int checkDigitsCount(const char* str)
{
	int counter = 0;
	while (*str)
	{
		int isDigit = isdigit(*str);
		if (isDigit)
		{
			counter++;
		}
		str++;
	}
	return counter;
}

int isLowercase(const char* str)
{
	while (*str) {
		if (islower(*str))
		{
			return 1; // lower case found
		}
		str++;
	}
	return 0;
}

int isValidCharacterPosition(const char* str)
{
	return (isupper(*str) && isupper(str[BARCODE_SIZE - 2])); // First and last chars
}

int IsAlphanumeric(const char* str)
{
	while (*str)
	{
		if (!isalnum(*str) && !isspace(*str))
		{
			return 0;
		}
		str++;
	}
	return 1;
}

int isValidAddressSections(const char* str) // split to 3 sections and check
{
	int validCounter = 0;
	char* temp = _strdup(str);
	char* token = "#";
	char* street = strtok(temp, token);
	char* streetNum = strtok(NULL, token);
	char* city = strtok(NULL, token);
	if (strlen(street) > 0 && IsAlphanumeric(street))
	{
		validCounter++;
	}
	if (isValidStreetNumber(streetNum) && !IsAlphanumeric(streetNum));
	{
		validCounter++;
	}
	if (strlen(city) > 0 && IsAlphanumeric(city))
	{
		validCounter++;
	}
	free(temp);
	if (validCounter == 3)
	{
		return 1;
	}
	return 0;
}

int isValidStreetNumber(const char* str)
{
	while (*str)
	{
		if (!isdigit(*str))
		{
			return 0;
		}
		str++;
	}
	return 1;
}

int validTokens(const char* str)
{
	int tokenCounter = 0;
	char token = '#';
	while (*str)
	{
		if (*str == token)
		{
			tokenCounter++;
		}
		str++;
	}
	if (tokenCounter != 2)
	{
		return 0;
	}
	return 1;
}

char* fixAddressString(char* str)
{
	char* temp = "";
	while (*str)
	{

		str++;
	}
	return temp;
}