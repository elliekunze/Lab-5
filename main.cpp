#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "extrafile.h"
using namespace std;

    string nameShip, nameWeapon, nameClass; //done
    short lengthShip; //done
    float warp; //done
    void combinedScore(vector<extrafile>&rhs);
    void mostPowerWeapon(vector<extrafile>&rhs);
    void weakShip(vector<extrafile>&rhs);
    int shield, numWeapon, lengthName, lengthWeapon, lengthClass;
    unsigned int countShip; //done
    unsigned int tracker = 0;
    void loadingData (string filename);
    void printAllShips();
    void unarmedPrint(vector<extrafile>&rhs);
    vector<extrafile> ships;
    vector<extrafile::inventory> weapons;

int main()
{
    cout << "Which fileType(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl;
    int option;
    cin >> option;

    if (option == 1) {
       loadingData("friendlyships.shp");
    }

    else if (option == 2) {
        loadingData("enemyships.shp");
    }

    else if (option == 3) {
        loadingData("friendlyships.shp");
        loadingData("enemyships.shp");
    }

    else {
        cout << "Incorrect option type" << endl;
    }

    cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships";

    cin >> option;

    if (option == 1) {
        printAllShips();
    }

    if (option == 2) {
        mostPowerWeapon(ships);
    }

    if (option == 3) {
        combinedScore(ships);
    }

    if (option == 4) {
        weakShip(ships);
    }

    if (option == 5) {
        unarmedPrint(ships);
    }

    return 0;
}

    void loadingData(string filename) {
        ifstream file (filename, ios_base::binary);
        file.read((char*)&countShip, sizeof(countShip));
        for (unsigned int i = 0; i < countShip; i++) {
            file.read((char*)&lengthName, sizeof(lengthName)); //fox video
            char* arr = new char[lengthName + 1];
            file.read(arr, lengthName);
            nameShip = arr;
            delete[] arr; //dont forget to delete

            file.read((char*)&lengthClass, sizeof(lengthClass));
            char* arr2 = new char[lengthClass+1];
            file.read(arr2, lengthClass); //create a new arr or temp
            nameClass = arr2;
            delete[] arr2;

            file.read((char*)&lengthShip, sizeof(lengthShip)); //reading what the characters hsould look like
            file.read((char*)&shield, sizeof(shield));
            file.read((char*)&warp, sizeof(warp));
            file.read((char*)&numWeapon, sizeof(numWeapon));
            weapons.clear(); //ensures the weapons vector is empty after each iteration
            for (int j = 0; j < numWeapon; j++) {
                file.read((char*)&lengthWeapon, sizeof(lengthWeapon));
                char* arr3 = new char[lengthWeapon + 1];

                file.read(arr3, lengthWeapon);
                nameWeapon = arr3;
                int powerRate; //will be used to determine how much power there is

                file.read((char*)&powerRate, sizeof(powerRate));
                float consumption_;

                file.read((char*)&consumption_, sizeof(consumption_));
                weapons.push_back(extrafile::inventory(nameWeapon, powerRate, consumption_)); //push weapon to the back of vector
            }
            ships.push_back(extrafile(nameShip, nameClass, lengthShip, shield, warp, numWeapon, weapons));
            tracker++;
        }
    }

void combinedScore(vector<extrafile>& rhs) { //looking at the score combined
    int shipsTargeted;
    int total;
    int combinedScore = 0;
    int countPower = 0;
    for (unsigned int i = 0; i < rhs.size(); i++) { //basically same procedure, looking for right hand side being at zero
        total = 0;
        for (unsigned int j = 0; j < rhs.at(i).weapons.size(); j++) { //weapons.size
            total += rhs.at(i).weapons.at(j).findPower();
        }
        if (total > combinedScore) { //total greater than combnined score since we are looking for most powerful
            combinedScore = total;
            shipsTargeted = i;
        }
    }
    cout << "Name: " << rhs.at(shipsTargeted).findName() << endl;
    cout << "Class: " << rhs.at(shipsTargeted).findClass() << endl;
    cout << "Length: " << rhs.at(shipsTargeted).getLength() << endl;
    cout << "Shield capacity: " << rhs.at(shipsTargeted).shield() << endl;
    cout << "Maximum Warp: " << rhs.at(shipsTargeted).findWarp() << endl;
    cout << "Armaments:" << endl;
    for (int k = 0; k < rhs.at(shipsTargeted).sizeWeapon(); k++) {
        countPower += rhs.at(shipsTargeted).weapons.at(k).findPower();
        cout << rhs.at(shipsTargeted).weapons.at(k).getNameWeapon() << ", " << rhs.at(shipsTargeted).weapons.at(k).findPower() << ", " << rhs.at(shipsTargeted).weapons.at(k).getCons() << endl;
    }
    cout << "Total firepower: " << countPower << endl;
    cout << endl;
}

        void mostPowerWeapon(vector<extrafile>& rhs) { //which weapon is most powerful
            int powerHigh = 0;
            int shipsTargeted = 0;
            int countPower = 0;
            for (unsigned int i = 0; i < rhs.size(); i++) {
                for (int k = 0; k < rhs.at(i).sizeWeapon(); k++) {
                    if (rhs.at(i).weapons.at(k).findPower() > powerHigh) { //if power is not the hihgest
                        powerHigh = rhs.at(i).weapons.at(k).findPower();
                        shipsTargeted = i; //set ships target to i
                    }
                }
            }
            cout << "Name: " << rhs.at(shipsTargeted).findName() << endl; //printing most powerful weapon statements
            cout << "Class: " << rhs.at(shipsTargeted).findClass() << endl;
            cout << "Length: " << rhs.at(shipsTargeted).getLength() << endl;
            cout << "Shield capacity: " << rhs.at(shipsTargeted).shield() << endl;
            cout << "Maximum Warp: " << rhs.at(shipsTargeted).findWarp() << endl;
            cout << "Armaments:" << endl;
            for (int j = 0; j <
                            rhs.at(shipsTargeted).sizeWeapon(); j++) { //most power so look for targered ships and what size weapon there is. vector
                countPower += rhs.at(shipsTargeted).weapons.at(j).findPower();
                cout << rhs.at(shipsTargeted).weapons.at(j).getNameWeapon() << ", "
                     << rhs.at(shipsTargeted).weapons.at(j).findPower() << ", "
                     << rhs.at(shipsTargeted).weapons.at(j).getCons() << endl;
            } //check to make sure above line in correct
            cout << "Total firepower: " << countPower << endl;
            cout << endl;
        }

void printAllShips() { //printing throguh all ships
    for (unsigned int i = 0; i < tracker; i++) {
        int countPower = 0; //counting how much total power there is
        cout << "Name: " << ships.at(i).findName() << endl; //standard
        cout << "Class: " << ships.at(i).findClass() << endl;
        cout << "Length: " << ships.at(i).getLength() << endl;
        cout << "Shield capacity: " << ships.at(i).shield() << endl;
        cout << "Maximum Warp: " << ships.at(i).findWarp() << endl;
        cout << "Armaments:" << endl;
        if (ships.at(i).sizeWeapon() == 0) {
            cout << "Unarmed" << endl; //no weapons means its unarmed
        }
        else {
            for (int j = 0; j < ships.at(i).sizeWeapon(); j++) {
                countPower += ships.at(i).weapons.at(j).findPower(); //line under needs coma seperation
                cout << ships.at(i).weapons.at(j).getNameWeapon() << ", " << ships.at(i).weapons.at(j).findPower() << ", " << ships.at(i).weapons.at(j).getCons() << endl;
            }
            cout << "Total firepower: " << countPower << endl;
        }
        cout << endl;
    }
}


void unarmedPrint(vector<extrafile>& rhs) { //when we print what exactly is unarmed
    for (unsigned int i = 0; i < rhs.size(); i++) { //this int needs to be exaact so unsigned int
        if (rhs.at(i).sizeWeapon() == 0) {
            cout << "Name: " << rhs.at(i).findName() << endl; //order on lab 5
            cout << "Class: " << rhs.at(i).findClass() << endl;
            cout << "Length: " << rhs.at(i).getLength() << endl;
            cout << "Shield capacity: " << rhs.at(i).shield() << endl;
            cout << "Maximum Warp: " << rhs.at(i).findWarp() << endl;
            cout << "Armaments:" << endl; //domt need to find anything
            cout << "Unarmed" << endl;
            cout << endl;
        }
    }
}

            void weakShip(vector<extrafile>& rhs) { //weakest ship
                int shipsTargeted = 0;
                int total;
                int combinedLow = 0;
                int countPower = 0;
                for (int y = 0; y < rhs.at(0).sizeWeapon(); y++) {
                    combinedLow += rhs.at(0).weapons.at(y).findPower(); //make sure to look at 0
                }
                for (unsigned int i = 0; i < rhs.size(); i++) {
                    total = 0;
                    if (rhs.at(i).sizeWeapon() == 0) {
                        continue; //doesnt matter if 0
                    }
                    for (unsigned int j = 0; j < rhs.at(i).weapons.size(); j++) { //need an unsigned int. looking at weapons at size
                        total += rhs.at(i).weapons.at(j).findPower();
                    }
                    if (total < combinedLow) { //if the total is less than the combined lowest score
                        combinedLow = total;
                        shipsTargeted = i;
                    }
                }

                cout << "Name: " << rhs.at(shipsTargeted).findName() << endl; //standard procedure
                cout << "Class: " << rhs.at(shipsTargeted).findClass() << endl;
                cout << "Length: " << rhs.at(shipsTargeted).getLength() << endl;
                cout << "Shield capacity: " << rhs.at(shipsTargeted).shield() << endl;
                cout << "Maximum Warp: " << rhs.at(shipsTargeted).findWarp() << endl;
                cout << "Armaments:" << endl;

                for (int k = 0; k < rhs.at(shipsTargeted).sizeWeapon(); k++) { //because weak ship, look at what ships have been rargeted and what size the weapon is
                    countPower += rhs.at(shipsTargeted).weapons.at(k).findPower();
                    cout << rhs.at(shipsTargeted).weapons.at(k).getNameWeapon() << ", " << rhs.at(shipsTargeted).weapons.at(k).findPower() << ", " << rhs.at(shipsTargeted).weapons.at(k).getCons() << endl;
                }
                cout << "Total firepower: " << countPower << endl;
                cout << endl;
            }
