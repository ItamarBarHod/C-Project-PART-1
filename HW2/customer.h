#pragma once
#include "shoppingcart.h"

typedef struct {
	char* name;
	Shoppingcart cart;
}Customer;

void printCustomer(const Customer* pCustomer);
void initCustomer(Customer* pCustomer);