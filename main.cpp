#include <iostream>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

char loadCharacter() {
    string input = "";
    char character = {0};

    while(true) {
        getline(cin, input);

        if(input.length() == 1) {
            character = input[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie" << endl;
    }
    return character;
}

string replaceToUppercase(string word) {
    transform(word.begin(), word.end(), word.begin(), :: tolower);
    word[0] = :: toupper(word[0]);
    return word;
}

string loadLine() {
    string input;
    getline(cin, input);
    return input;
}

struct User {

    string username;
    string password;
    int id;

};

struct Person {
    int id;
    int userId;
    string name;
    string lastname;
    string phoneNumber;
    string email;
    string address;
};

//------------------------------------------Address Book---------------------------------


vector<Person> loadPersonsToFile(int idUser) {
    Person person;
    vector<Person> personVector;
    fstream file;
    file.open("addressBook.txt", ios::in);

    int IdNumber;
    int idUserWithFile;
    string id, idUserWithFileString, name, lastname, phoneNumber, email, address;

    while(file.good()) {
        getline(file, id, '|');
        getline(file, idUserWithFileString, '|');
        getline(file, name, '|');
        getline(file, lastname, '|');
        getline(file, phoneNumber, '|');
        getline(file, email, '|');
        getline(file, address, '|');
        if(!file.good()) {
            break;
        }
        idUserWithFile = atoi(idUserWithFileString.c_str());
        IdNumber = atoi(id.c_str());

        if(idUserWithFile == idUser) {
            person.id = IdNumber;
            person.userId = idUser;
            person.name = name;
            person.lastname = lastname;
            person.phoneNumber = phoneNumber;
            person.email = email;
            person.address = address;
            personVector.push_back(person);
        }

    }
    file.close();
    return personVector;
}

void addPersonToFile(Person person,int userId) {
    fstream file;
    file.open("addressBook.txt", ios::out | ios::app);

    file << person.id << '|';
    file << person.userId << '|';
    file << person.name << '|';
    file << person.lastname << '|';
    file << person.phoneNumber << '|';
    file << person.email << '|';
    file << person.address << '|' << endl;

    file.close();
}

int lastPersonId() {

    string textLine = "";
    string idToConvert = "";
    int lastID = 0;

    fstream file;
    file.open("addressBook.txt", ios::in);
    if (!file.good())
        return 0;
    else {
        int i = 0;
        while (getline(file, textLine)) {
            if (textLine[0] != ' ') {
                idToConvert = "";
                i = 0;
                while (textLine[i] != '|') {
                    idToConvert += textLine[i];
                    i++;
                }
            }
        }
        lastID = atoi(idToConvert.c_str());
        return lastID;
    }
}


vector<Person> addPerson(vector<Person> personVector, int userId) {
    Person person;
    int id = 0;
    string name, lastname, phoneNumber, email, address;

    system("cls");
    cout << "+------------------------------------+" << endl;
    cout << "|     >>>DODAWANIE NOWEJ OSOBY<<<    |" << endl;
    cout << "|------------------------------------|" << endl << endl;

    cout << "Podaj imie: ";
    name = loadLine();
    cout << "Podaj nazwisko: ";
    lastname = loadLine();
    cout << "Podaj nr telefonu: ";
    phoneNumber = loadLine();
    cout << "Podaj e-mail: ";
    email = loadLine();
    cout << "Podaj adres: ";
    address = loadLine();

    name = replaceToUppercase(name);
    lastname = replaceToUppercase(lastname);

    person.id = lastPersonId() + 1;
    person.userId = userId;
    person.name = name;
    person.lastname = lastname;
    person.phoneNumber = phoneNumber;
    person.email = email;
    person.address = address;

    personVector.push_back(person);
    addPersonToFile(person, userId);

    cout << endl << "Osoba zostala dodana.";
    Sleep(1300);
    return personVector;
}



void writeToScreen(vector<Person> personVector,int numberOfPerson) {
    cout << setw(25) << left << "id: " << personVector[numberOfPerson].id << endl;
    cout << setw(25) << left << "imie: " << personVector[numberOfPerson].name << endl;
    cout << setw(25) << left << "nazwisko: " << personVector[numberOfPerson].lastname << endl;
    cout << setw(25) << left << "numer telefonu: " << personVector[numberOfPerson].phoneNumber << endl;
    cout << setw(25) << left << "e-mail: " << personVector[numberOfPerson].email << endl;
    cout << setw(25) << left << "adres: " << personVector[numberOfPerson].address << endl;
    cout << "---------------------------------------------" << endl;
}

void showAllPersons(vector<Person> personVector) {
    system("cls");
    cout << "+-----------------------------------------+" << endl;
    cout << "|       >>>LISTA WSZYSTKICH OSOB<<<       |" << endl;
    cout << "|-----------------------------------------|" << endl << endl;

    if(personVector.empty()) {
        cout << "Ksiazka adresowa jest pusta." << endl;
        Sleep(1500);
    } else {
        for(int i = 0; i < personVector.size(); i++) {
            writeToScreen(personVector, i);
        }
        system("pause");
    }
}


void findByName(vector<Person> personVector) {
    system("cls");
    cout << "+-----------------------------------------------+" << endl;
    cout << "|       >>>ZNAJDZ OSOBE PO JEJ IMIENIU<<<       |" << endl;
    cout << "|-----------------------------------------------|" << endl << endl;


    string name ="";
    bool found = false;
    cout << "Podaj imie osoby: ";
    name = loadLine();
    name = replaceToUppercase(name);

    for(int i = 0; i < personVector.size(); i++) {
        if(name == personVector[i].name) {
            writeToScreen(personVector, i);
            found = true;
        }
    }

    if(!found) {
        cout << "Nie ma osoby o takim imieniu w ksiazce adresowej.";
        Sleep(2000);
    } else {
        system("pause");
    }
}

void findByLastname(vector<Person> personVector) {
    system("cls");
    cout << "+------------------------------------------------+" << endl;
    cout << "|       >>>ZNAJDZ OSOBE PO JEJ NAZWISKU<<<       |" << endl;
    cout << "|------------------------------------------------|" << endl << endl;

    string lastname ="";
    bool found = false;
    cout << "Podaj nazwisko osoby: ";
    lastname = loadLine();
    lastname = replaceToUppercase(lastname);

    for(int i = 0; i < personVector.size(); i++) {
        if(lastname == personVector[i].lastname) {
            writeToScreen(personVector, i);
            found = true;
        }
    }

    if(!found) {
        cout << "Nie ma osoby o takim nazwisku w ksiazce adresowej.";
        Sleep(2000);
    } else {
        system("pause");
    }
}



void deletePersonFromFile(int idNumber) {

    fstream file;
    fstream temp;
    file.open("addressBook.txt", ios::in);
    temp.open("temp.txt", ios::out);
    if (file.good() && temp.good()) {
        string loadedLine;
        while (getline(file, loadedLine)) {
            if (loadedLine[0] - '0' == idNumber)
                continue;
            temp << loadedLine << endl;
        }
    }
    file.close();
    file.clear();
    temp.close();
    temp.clear();
    remove("addressBook.txt");
    rename("temp.txt", "addressBook.txt");
}

vector<Person> choiceDeleteMenu(vector<Person> personVector, int idNumber, int userId) {

    char character;
    cout << "Czy na pewno chcesz usunac? <t/n>" << endl;
    cin >> character;
    cin.ignore();

    switch(character) {
    case 't':
        deletePersonFromFile(idNumber);
        personVector.erase(personVector.begin(),personVector.end());
        personVector = loadPersonsToFile(userId);
        cout << "Osoba o numerze Id " << idNumber << " zostala usunieta";
        break;
    case 'n':
        return personVector;
        break;
    default:
        cout << "Wybrales nieprawidlowy znak.";
    }

    return personVector;
}

vector<Person> deleteOnePersonMenu(vector<Person> personVector, int idUser) {

    int idNumber;
    int iteratorNumberId;
    bool found = false;
    string id;

    system("cls");
    cout << "+---------------------------------+" << endl;
    cout << "|     >>>USUWANIE ZNAJOMYCH<<<    |" << endl;
    cout << "|---------------------------------|" << endl << endl;

    cout << "Podaj numer ID osoby ktora chcesz usunac z listy: ";
    getline(cin, id);
    idNumber = atoi(id.c_str());

    for(int i = 0; i < personVector.size(); i++) {
        if(personVector[i].id == idNumber) {
            iteratorNumberId = i;
            writeToScreen(personVector, i);
            found = true;
        }
    }

    if(found) {
        personVector = choiceDeleteMenu(personVector, idNumber, idUser);
        Sleep(1500);
    } else {
        cout << "Nie ma osoby o takim numerze ID";
        Sleep(1500);
    }
    return personVector;
}


void updatePersonInFile(vector<Person> personVector,int i)
{
    Person person;
	fstream file;
	fstream temp;
	file.open("addressBook.txt", ios::in);
	temp.open("temp.txt", ios::out);
	if (file.good() && temp.good())
	{
		string loadedLine;
		while (getline(file, loadedLine))
		{
			if (loadedLine[0] - '0' == personVector[i].id)
			{
				temp << personVector[i].id << "|";
				temp << personVector[i].userId << "|";
				temp << personVector[i].name << "|";
				temp << personVector[i].lastname << "|";
				temp << personVector[i].phoneNumber << "|";
				temp << personVector[i].email << "|";
				temp << personVector[i].address << "|" << endl;
				continue;
			}
			temp << loadedLine << endl;
		}
	}
	file.close();
	file.clear();
	temp.close();
	temp.clear();
	remove("addressBook.txt");
	rename("temp.txt", "addressBook.txt");
}



vector<Person> changeName(vector<Person> personVector, int i) {
    string name;
    cout<<"Podaj nowe imie: ";
    getline(cin, name);
    name = replaceToUppercase(name);
    personVector[i].name = name;
    updatePersonInFile(personVector, i);
    cout<< "Imie zostalo zmienione";
    Sleep(1000);

    return personVector;
}

vector<Person> changeLastname(vector<Person> personVector, int i) {
    string lastname;
    cout<<"Podaj nowe nazwisko: ";
    getline(cin, lastname);
    lastname = replaceToUppercase(lastname);
    personVector[i].lastname = lastname;
    updatePersonInFile(personVector, i);
    cout<< "Nazwisko zostalo zmienione";
    Sleep(1000);

    return personVector;
}

vector<Person> changePhoneNumber(vector<Person> personVector, int i) {
    string phoneNumber;
    cout<<"Podaj nowy numer telefonu: ";
    getline(cin, phoneNumber);
    personVector[i].phoneNumber = phoneNumber;
    updatePersonInFile(personVector, i);
    cout<< "Numer telefonu zostal zmieniony";
    Sleep(1000);

    return personVector;
}

vector<Person> changeEmail(vector<Person> personVector, int i) {
    string email;
    cout<<"Podaj nowy adres e-mail: ";
    getline(cin, email);
    personVector[i].email = email;
    updatePersonInFile(personVector, i);
    cout<< "E-mail zostal zmieniony";
    Sleep(1000);

    return personVector;
}

vector<Person> changeAddress(vector<Person> personVector, int i) {
    string address;
    cout<<"Podaj nowy adres zamieszkania: ";
    getline(cin, address);
    personVector[i].address = address;
    updatePersonInFile(personVector, i);
    cout<< "Adres zamieszkania zostal zmieniony";
    Sleep(1000);

    return personVector;
}

vector<Person> choiceChangePersonDetails(vector<Person> personVector, int i, char character) {

    switch(character) {
    case '1':
        personVector = changeName(personVector, i);
        break;
    case '2':
        personVector = changeLastname(personVector, i);
        break;
    case '3':
        personVector = changePhoneNumber(personVector, i);
        break;
    case '4':
        personVector = changeEmail(personVector, i);
        break;
    case '5':
        personVector = changeAddress(personVector, i);
        break;
    case '9':
        return personVector;
    default :
        cout << "Podales nieprawidlowy znak.";
    }

    return personVector;
}

void menuChoiceChangingPersonDetails() {
    cout << "|---------------------------------|" << endl;
    cout << "|1.Edycja imienia                 |" << endl;
    cout << "|2.Edycja nazwiska                |" << endl;
    cout << "|3.Edycja numeru telefonu         |" << endl;
    cout << "|4.Edycja adresu e-mail           |" << endl;
    cout << "|5.Edycja adresu zamieszkania     |" << endl;
    cout << "|9.Wyjscie                        |" << endl;
    cout << "+---------------------------------+" << endl;
}

vector<Person> changePersonDetails(vector<Person> personVector) {
    string id;
    bool found = false;
    int idNumber;
    int iteratorNumberId;
    char character;

    system("cls");
    cout << "+---------------------------------+" << endl;
    cout << "|      >>>EDYCJA ZNAJOMYCH<<<     |" << endl;
    cout << "|---------------------------------|" << endl << endl;

    cout<<"Podaj id osoby:"<<endl;
    getline(cin, id);
    idNumber = atoi(id.c_str());

    for(int i = 0; i < personVector.size(); i++) {
        if(personVector[i].id == idNumber) {
            iteratorNumberId = i;
            found = true;
        }
    }

    if(found) {
        menuChoiceChangingPersonDetails();
        character = loadCharacter();
        personVector = choiceChangePersonDetails(personVector, iteratorNumberId, character);
    } else {
        cout<< "Nie ma osoby o takim numerze ID"<<endl;
        Sleep(1500);
    }
    return personVector;
}

void addVectorToFile(vector<User> userVector) {
    fstream file;
    file.open("UserAccount.txt", ios::out | ios::app);

    for(int i = 0; i < userVector.size(); i++) {
        file << userVector[i].id << '|';
        file << userVector[i].username << '|';
        file << userVector[i].password << '|' << endl;
    }
    file.close();
}

vector<User> changeAccountPassword(vector<User> userVector, int userId) {
    string password;
    system("cls");
    cout << "+---------------------------------+" << endl;
    cout << "|       >>>EDYCJA HASLA<<<        |" << endl;
    cout << "+---------------------------------+" << endl << endl;

    cout << "Podaj nowe haslo: ";
    getline(cin, password);

    for(int i = 0; i < userVector.size(); i++) {
        if(userVector[i].id == userId) {
            userVector[i].password = password;
            remove("UserAccount.txt");
            addVectorToFile(userVector);
            cout << endl << "Haslo zostalo zmienione" << endl << endl;
            Sleep(1500);
        }
    }
    return userVector;
}


void menuAddressBook(vector<User> userVector, int userId) {

    vector<Person> personVector;
    personVector = loadPersonsToFile(userId);
    personVector = loadPersonsToFile(userId);
    char character;
    while(true) {
        system("cls");
        cout << "+---------------------------------+" << endl;
        cout << "|      >>>> Menu Glowne <<<<      |" << endl;
        cout << "|---------------------------------|" << endl;
        cout << "|1.Dodaj adresata                 |" << endl;
        cout << "|2.Znajdz adresata po imieniu     |" << endl;
        cout << "|3.Znajdz adresata po nazwisku    |" << endl;
        cout << "|4.Wyswietl wszystkich adresatow  |" << endl;
        cout << "|5.Edytuj adresata                |" << endl;
        cout << "|6.Usun adresata                  |" << endl;
        cout << "|9.Wyloguj                        |" << endl;
        cout << "+---------------------------------+" << endl;
        cout << "|      >>>> Edycja Konta <<<<     |" << endl;
        cout << "|---------------------------------|" << endl;
        cout << "|7.Zmien haslo                    |" << endl;
        cout << "+---------------------------------+" << endl;

        character = loadCharacter();

        switch(character) {
        case '1':
            personVector = addPerson(personVector, userId);
            break;
        case '2':
            findByName(personVector);
            break;
        case '3':
            findByLastname(personVector);
            break;
        case '4':
            showAllPersons(personVector);
            break;
        case '5':
            personVector = changePersonDetails(personVector);
            break;
        case '6':
            personVector = deleteOnePersonMenu(personVector, userId);
            break;
        case '7':
            userVector = changeAccountPassword(userVector, userId);
            break;
        case '9':
            cout << "Do zobaczenia!";
            Sleep(1000);
            return;
        }

    }
}

//--------------------------------------Register and login-----------------------------------------


bool findUsernameInDataBase(vector<User> userVector, string username) {

    for(int i = 0; i < userVector.size(); i++) {

        if(userVector[i].username == username) {
            return true;
        }
    }
    return false;
}

vector<User> loadUserAccountFile() {
    User user;
    vector<User> userVector;
    fstream file;
    file.open("UserAccount.txt", ios::in);

    int idNumber;
    string id, username, password;

    while(file.good()) {
        getline(file, id, '|');
        getline(file, username, '|');
        getline(file, password, '|');

        if(!file.good()) {
            break;
        }

        idNumber = atoi(id.c_str());

        user.id = idNumber;
        user.username = username;
        user.password = password;
        userVector.push_back(user);


    }
    file.close();
    return userVector;
}


void addUserToFile(User user) {
    fstream file;
    file.open("UserAccount.txt", ios::out | ios::app);

    file << user.id << '|';
    file << user.username << '|';
    file << user.password << '|' << endl;

    file.close();
}

vector<User> registerUser(vector<User> userVector) {

    User user;
    string username;
    string password;
    int id;

    cout << "Podaj nazwe uzytkownika: ";
    username = loadLine();

    while(true)

        if(findUsernameInDataBase(userVector, username)) {

            cout << "Uzytkownik o takiej nazwie juz istnieje, podaj inna nazwe uzytkownika: ";
            username = loadLine();

        } else {

            cout << "Podaj haslo: ";
            password = loadLine();

            if(userVector.empty()) {
                id = 1;
            } else {
                id = userVector[userVector.size()-1].id + 1;
            }

            user.username = username;
            user.password = password;
            user.id = id;
            userVector.push_back(user);
            addUserToFile(user);
            cout << "Utworzyles konto, mozesz sie teraz zalogowac.";
            Sleep(1500);
            return userVector;
        }
}


int loginUser(vector<User> userVector) {

    string username;
    string password;
    cout << "Podaj nazwe uzytkownika: ";
    username = loadLine();
    const int TRIALS = 3;
    int i = 0;
    while(i < userVector.size()) {

        if(userVector[i].username == username) {

            for(int j = 0; j < TRIALS; j++) {
                cout << ">> Liczba prob: " << TRIALS - j << endl;
                cout << "Podaj haslo: ";
                password = loadLine();
                if(userVector[i].password == password) {

                    cout << "Zalogowales sie.";
                    Sleep(1500);
                    return userVector[i].id;
                }

            }
            cout << "Podales 3 razy nieprawidlowe haslo.";
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie istnieje uzytkownik o takiej nazwie.";
    Sleep(1500);
    return 0;
}

void menuLoginAndRegister() {

    vector<User> userVector;
    char character;
    int userId = 0;

    while(true) {
        userVector = loadUserAccountFile();
        system("cls");
        cout << "+---------------------------------+" << endl;
        cout << "|      >>>> Menu Glowne <<<<      |" << endl;
        cout << "|---------------------------------|" << endl;
        cout << "|1.Rejestracja                    |" << endl;
        cout << "|2.Logowanie                      |" << endl;
        cout << "|3.Wyjscie                        |" << endl;
        cout << "+---------------------------------+" << endl;

        character = loadCharacter();

        switch(character) {

        case '1':
            userVector = registerUser(userVector);
            break;
        case '2':
            userId = loginUser(userVector);
            if(userId != 0) {
                menuAddressBook(userVector, userId);
            }
            break;
        case '3':

            cout << "Do zobaczenia!";
            Sleep(1000);
            exit('0');
        }

    }

}

int main() {


    menuLoginAndRegister();


    return 0;
}
