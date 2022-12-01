#include <stdio.h>
#include "supermarket.h"

int main()
{
	Supermarket market;
	initSuperMarket(&market);
	int flag = 1;
	int option;
	while (flag)
	{
		printf("enter an option:\n");
		scanf(" %d", &option);
		switch (option)
		{
		case 1:
			printMarket(&market);
			break;
		case 2:
			addProduct(&market);
			break;
		case 3:
			addCustomer(&market);
			break;
		case 4:
			startPurchasing(&market);
			break;
		case 5:
			printShoppingCart(&market);
			break;
		case 6:
			customerPayment(&market);
			break;
		case 7:
			printProductType(&market);
			break;
		case 8:
			flag = 0;
			printf("Bye bye!\n");
			break;
		default:
			printf("no such option!\n\n");
			break;
		}
	}
	deleteSuperMarket(&market); //free
}