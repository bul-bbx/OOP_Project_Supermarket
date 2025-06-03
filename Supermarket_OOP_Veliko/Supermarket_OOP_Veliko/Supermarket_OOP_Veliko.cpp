#include <iostream>
#include <fstream>
#include <string>
#include "Employee.h"
#include "Cashier.h"
#include "Manager.h"
#include "Category.h"

using namespace std;

Employee currentUser;
Category* cateogries;



void loadWorkers() {
    string input;
    ifstream workers ("Workers.txt");
    if (workers.is_open()) {
        while (workers.good()) {
            workers >> input;

        }
    }
}

int main()
{
    loadWorkers();
}
