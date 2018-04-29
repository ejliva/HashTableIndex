#pragma once
#include "stdafx.h"
#include "Slot.h"
#include <iostream>
#include <string>
#define MAXHASH 1000

template <class T>
class HashTable
{

private:
	int size;
	int count;
	int *Probe;

	//new slot
	Slot<T> *slots = new Slot<T>[MAXHASH];
	Slot<T> newSlot;
public:
	//constructor
	HashTable()
	{
		size = MAXHASH;
		count = 0;

		//create probe
		Probe = new int[MAXHASH];
		for (int i = 0; i < MAXHASH - 1; i++)
		{
			Probe[i] = i;
		}
		//random probe array
		for (int i = 0; i < MAXHASH - 1; i++)
		{
			int r = rand() % MAXHASH;
			int temp = Probe[i];
			Probe[i] = Probe[r];
			Probe[r] = temp;
		}
	}

	//deconstructor
	~HashTable()
	{
	}

	/*
	This inserts a new key/value pair and duplicates are not allowed.
	This function should return true if the key/value pair is successful and false if not successful
	if successful the number of collisions occuring during the insert operation should be returned in collision.
	*/
	bool insert(int key, T value, int &collisions)
	{
		T found;
		//this checks for key duplicates
		if (find(key, found)) {
			return false;
		}//end if
		else {
			//check table if full
			if ((int)alpha() == 1) {
				cout << "The Hash Table is full." << endl;
				return false;
			}//end else

			int home; //home position
			int pos = joaat_hash(&key);
			home = pos;
			for (int i = 1; !(slots[pos].isEmpty()) && !(slots[pos].isTombstone()); i++)
			{
				pos = (home + probe(key, i)) % size;
				collisions++; //increment collision
				if (slots[pos].getKey() == key) {
					return false;
				}
			}
			newSlot = new Slot<T>(key, value);
			slots[pos] = newSlot;
			count++; //increment count
		}
		return true;
	}// end of insert function
	 /*
	 If there is a record with the given key in the hash table, it is deleted and the function returns true
	 otherwise the function returns false
	 */
	bool remove(int key)
	{
		int home; //home position
		int pos = joaat_hash(&key);
		home = pos;
		for (int i = 1; (!(slots[pos].getKey() == key) && !(slots[pos].isEmpty())); i++)
		{
			pos = (home + probe(key, i)) % MAXHASH; //next
		}//end for
		if (slots[pos].getKey() == key) {
			newSlot = new Slot<T>();
			newSlot.kill();
			slots[pos] = newSlot;
			count--; //decrement count
			return true;
		}//end if
		else {
			return false;
		}//end else

	}//end of remove function

	 /*
	 If a record with the given key is found in the hash table, the function returns true
	 and a copy of the value is returned in value. Otherwise the function return false.
	 */
	bool find(int key, T& value)
	{
		int home; //home position
		int pos = joaat_hash(&key);
		home = pos;
		for (int i = 1; (!(slots[pos].getKey() == key) && !(slots[pos].isEmpty())); i++)
		{
			pos = (home + probe(key, i)) % MAXHASH; //next
		}//end for
		if (slots[pos].getKey() == key) {
			value = slots[pos].getValue();
			return true; //key found
		}//end if
		else {
			return false;
		}//end else

	}
	//This function returns loading factor of the hashtable.
	float alpha()
	{
		return  ((float)count) / size;
	}

	//This is the Jenkins one-at-a-time hash function
	int joaat_hash(int *key)
	{

		int hash = 0;
		size_t i;
		for (i = 0; i < 4; i++)
		{
			hash += ((*key) >> (i * 8)) & 0xFF;
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		if (hash < 0) {
			hash *= -1;

		}

		hash %= MAXHASH;
		return hash;
	}
	//This is the Pseudo-random probe function
	int probe(int Key, int i)
	{
		return  Probe[i - 1];
	}

};//end of hash table class

  //This is the Node class for linked list implementation
class Node {

private:
	string lastName;
	string firstName;
	int uid;
	string year;
	Node *next;

public:
	//default constructor
	Node() {
		lastName = "";
		firstName = "";
		uid = 0;
		year = "";
		next = nullptr;
	}

	//parameterized constructor
	Node(string lastName, string firstName, int uid, string year) {
		this->lastName = lastName;
		this->firstName = firstName;
		this->uid = uid;
		this->year = year;
		next = nullptr;
	}

	//this function returns next
	Node* getNext() {
		return this->next;
	}

	//this function sets next node
	void setNext(Node* newNode) {
		this->next = newNode;
	}

	//This function returns uid
	int getUid() {
		return this->uid;
	}

	//This is the print function
	void print(ostream& os) {
		os << "-------------------" << endl;
		os << "Last Name: " << lastName << endl;
		os << "First Name: " << firstName << endl;
		os << "UID: " << uid << endl;
		os << "Year: " << year << endl;
		os << "-------------------" << endl;
	}

}; //end of Node class

   //This is the student class.
class Student
{
private:
	Node *head;
public:
	//constructor
	Student() {
		head = nullptr;
	}

	//deconstructor
	~Student() {

	}

	//This is the insert function
	Node* insert(string lastName, string firstName, int uid, string year)
	{
		Node *node = new Node(lastName, firstName, uid, year);
		if (find(node)) {
			cout << "This student is already in the database" << endl;
			return nullptr;
		}//end if
		else {
			Node *current;
			if (head == nullptr) {
				head = node;
				return node;
			}//end if
			else {
				current = head;
				while (current->getNext() != nullptr) {
					current = current->getNext();
				}//end while
				current->setNext(node);
				return node;
			}//end else
		}//end else
		return nullptr;
	}//end of insert

	 /*
	 This is the remove function
	 */
	bool remove(int uid) {
		Node *current = head;
		Node *previous = head;
		if (current->getUid() == uid)
		{
			if (current->getNext() == nullptr) {
				head = nullptr;
				delete current;
			}//end if
			else {
				head = current->getNext();
				delete current;
			}//end else

			return true;
		}//end if
		else
		{
			while (current->getNext() != nullptr && current->getNext()->getUid() != uid) {
				previous = current;
				current = current->getNext();
			}//end while
			previous->setNext(current->getNext());
			delete current;
			return true;
		}//end else
		return false;
	}//end of remove

	 //This is the find function
	bool find(Node *find)
	{
		Node *current;
		bool node = false;
		if (head == nullptr)
		{
			node = false;
		}//end if
		else {
			if (head == find)
			{
				node = true;
			}//end if
			else {
				current = head;
				while (current->getNext() != nullptr)
				{
					current = current->getNext();
					if (current == find) {
						node = true;
						break;
					}//end if
				}//end while
			}//end else
		}//end else
		return node;
	}//end find
};//end of student class
