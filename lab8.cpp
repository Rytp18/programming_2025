#include <iostream>
#include <string>

using namespace std;

struct Season {
    string seasonName;
    string month1;
    string month2;
    string month3;
    string nextSeason;
};

Season seasons[4];

void initializeSeasons() {
    seasons[0] = { "Winter", "December", "January", "February", "Spring" };
    seasons[1] = { "Spring", "March", "April", "May", "Summer" };
    seasons[2] = { "Summer", "June", "July", "August", "Autumn" };
    seasons[3] = { "Autumn", "September", "October", "November", "Winter" };
}

void swapMonths() {
    int seasonA, monthA, seasonB, monthB;

    cout << "Enter first season index (0-3): ";
    cin >> seasonA;
    cout << "Enter first month index (1-3): ";
    cin >> monthA;
    cout << "Enter second season index (0-3): ";
    cin >> seasonB;
    cout << "Enter second month index (1-3): ";
    cin >> monthB;

    if (seasonA < 0 || seasonA > 3 || seasonB < 0 || seasonB > 3 ||
        monthA < 1 || monthA > 3 || monthB < 1 || monthB > 3) {
        cout << "Invalid input!" << endl;
        return;
    }

    string* monthPtrA;
    string* monthPtrB;

    switch (monthA) {
    case 1: monthPtrA = &seasons[seasonA].month1; break;
    case 2: monthPtrA = &seasons[seasonA].month2; break;
    case 3: monthPtrA = &seasons[seasonA].month3; break;
    }

    switch (monthB) {
    case 1: monthPtrB = &seasons[seasonB].month1; break;
    case 2: monthPtrB = &seasons[seasonB].month2; break;
    case 3: monthPtrB = &seasons[seasonB].month3; break;
    }

    string temp = *monthPtrA;
    *monthPtrA = *monthPtrB;
    *monthPtrB = temp;

    cout << "Months swapped successfully!" << endl;
}

void displayYear() {
    cout << endl << "Full year starting from Winter:" << endl;

    for (int i = 0; i < 4; i++) {
        string seasonName;
        switch (i) {
        case 0: seasonName = "Winter"; break;
        case 1: seasonName = "Spring"; break;
        case 2: seasonName = "Summer"; break;
        case 3: seasonName = "Autumn"; break;
        }

        cout << seasonName << "["
            << seasons[i].month1 << ", "
            << seasons[i].month2 << ", "
            << seasons[i].month3 << "] ";
    }
    cout << endl << endl;
}

void viewElement() {
    int index;
    cout << "Enter season index to view (0-3): ";
    cin >> index;

    if (index < 0 || index > 3) {
        cout << "Invalid index!" << endl;
        return;
    }

    cout << endl << "Season Details:" << endl;
    cout << "Season Name: " << seasons[index].seasonName << endl;
    cout << "Month 1: " << seasons[index].month1 << endl;
    cout << "Month 2: " << seasons[index].month2 << endl;
    cout << "Month 3: " << seasons[index].month3 << endl;
    cout << "Next Season: " << seasons[index].nextSeason << endl;
    cout << endl;
}

void createNewElement() {
    int index;
    cout << "Enter season index to modify (0-3): ";
    cin >> index;

    if (index < 0 || index > 3) {
        cout << "Invalid index!" << endl;
        return;
    }

    cout << "Enter season name: ";
    cin >> seasons[index].seasonName;
    cout << "Enter month 1: ";
    cin >> seasons[index].month1;
    cout << "Enter month 2: ";
    cin >> seasons[index].month2;
    cout << "Enter month 3: ";
    cin >> seasons[index].month3;
    cout << "Enter next season: ";
    cin >> seasons[index].nextSeason;

    cout << "Season updated successfully!" << endl;
}

int main() {
    initializeSeasons();

    int choice;

    do {
        cout << "=== Magic Calendar Menu ===" << endl;
        cout << "1. Swap months between seasons" << endl;
        cout << "2. Display full year" << endl;
        cout << "3. View season details" << endl;
        cout << "4. Create/modify season" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            swapMonths();
            break;
        case 2:
            displayYear();
            break;
        case 3:
            viewElement();
            break;
        case 4:
            createNewElement();
            break;
        case 5:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }

        cout << "=============================" << endl;

    } while (choice != 5);

    return 0;
}
