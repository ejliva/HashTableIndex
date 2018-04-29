#include "stdafx.h"
#include <iostream>
#include "HashTable.h"

using namespace std;


int main()
{
	////testing HashTable
	//HashTable<int> *newHash = new HashTable<int>();
	////set collision
	//int collision = 0;
	//int val = 0;
	////tesing insert
	//cout << "testing insert function" << endl;
	//cout << newHash->insert(00001, 48, collision) << endl;
	//cout << newHash->insert(00002, 88, collision) << endl;
	//cout << newHash->insert(00003, 97, collision) << endl;
	//cout << newHash->insert(00004, 11, collision) << endl;
	//cout << newHash->insert(00004, 24, collision) << endl;
	////tesing remove
	//cout << "testing remove function" << endl;
	//cout << newHash->remove(00001) << endl;
	////testing find
	//cout << "testing find function" << endl;
	//cout << newHash->find(00002, val) << endl;
	////testing alpha
	//cout << "testing alpha function" << endl;
	//cout << "alpha: " << newHash->alpha() << endl;

	//testing student
	//Student *st = new Student();
	//Node *newNode = new Node();
	//st->insert("liva", "earl", 00001, "sophomore");
	//st->insert("doe", "john", 00012, "freshman");
	//st->insert("James", "Lebron", 00123, "senior");
	//st->insert("Ball", "Lonzo", 01234, "Junior");

	////tesing remove
	//st->remove(00001);
	//st->remove(00022);

	//create student object
	Student *newStudent = new Student();
	//create hash object
	HashTable<Node*> *newHash = new HashTable<Node *>();
	Node *node;
	int collisions = 0;
	char letter;
	bool start = true;
	string lastName;
	string firstName;
	int uid;
	string year;

	//asks the user to enter I for insert, D for delete, S for search and Q for quit.
	while (start) {
		cout << "Would you like to (I)nsert or (D)elete a record or (S)earch for a record or (Q)uit?" << endl;
		cout << "Enter action: ";
		cin >> letter;

		switch (letter) {
			//inserts uid
		case 'I':
			cout << "Inserting a new Record." << endl;
			cout << "Last name: ";
			cin >> lastName;
			cout << "First name: ";
			cin >> firstName;
			cout << "UID: ";
			cin >> uid;
			cout << "Year: ";
			cin >> year;

			node = newStudent->insert(lastName, firstName, uid, year);
			if (node == nullptr) {
				cout << "Record already exists." << endl;
			}
			else {
				if (newHash->insert(uid, node, collisions))
				{
					cout << "Record Inserted." << endl;
				}
				else {
					cout << "Record cannot be inserted." << endl;
				}
			}
			break;
			//delete uid
		case 'D':
			cout << "Enter UID to delete: ";
			cin >> uid;

			if (newHash->remove(uid)) {
				cout << "Record Deleted." << endl;
				newStudent->remove(uid);
			}//end if
			else {
				cout << "Recordnot found. It cannot be deleted." << endl;
			}//end else
			break;
			//search for uid
		case 'S':
			cout << "Enter UID to search for: ";
			cin >> uid;
			Node *find;
			cout << "Searching..... ";
			if (newHash->find(uid, find)) {
				cout << "record found." << endl;
				find->print(cout);
			}//end if
			else {
				cout << "record not found." << endl;
			}//end else

			break;
			//quit program
		case 'Q':
			start = false;
			break;
		default:
			cout << "Please enter: (I) = insert, (D) = delete, (S) = search, and (Q) = quit" << endl;
			break;
		}//end switch
	}//end while

	system("pause");
	return 0;
}

