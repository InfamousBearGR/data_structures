#include "Menus.h"
#include <iostream>
#include "BinarySearchTree.h"
#include "Sorting.h"
#include "HashTable.h"

void BSTMenu1(vector<AvgDataUnit*> arrayIn) { //Menu for BST sorted by day
	bool done = false; //breaks the while loop if "Exit" is selected

	BSTNode* tree = sortedArrayToBST(arrayIn, 0, arrayIn.size() - 1); //create tree

	while (!done) {
		string choice = "";
		int choicenum = 0;
		cout << "Choose function:" << endl <<
			"1: Show BST in in-order traversal" << endl <<
			"2: Search average temperature by day" << endl <<
			"3: Edit average temperature on day" << endl <<
			"4: Delete record of day" << endl <<
			"5: Exit" << endl;
		while (choicenum < 1 || choicenum>5) {
			cin >> choice;
			choicenum = atoi(choice.c_str()); //parse int
			if (choicenum < 1 || choicenum>5) {
				cout << "Incorrect input, try again" << endl;
			}
		}

		switch (choicenum) {
		case 1: //traverse
			inOrderTraversal(tree);
			break;
		case 2: //search
		{
			string timestamp = "";
			cout << "Please input day in format Year-Month-Day (all numbers)" << endl;
			cin >> timestamp;
			BSTNode* search = searchBST(tree, timestamp);
			if (search != NULL) {
				cout << "Average temperature for this day is " << search->data->getAvgTemp() << " degrees" << endl;
			}
		}
		break;
		case 3: //edit
		{
			string timestamp = "";
			cout << "Please input day in format Year-Month-Day (all numbers)" << endl;
			cin >> timestamp;
			BSTNode* search = searchBST(tree, timestamp);


			if (search != NULL) {

				float in = 0;
				string sin = "";
				cout << "Please input new temperature in floating number format" << endl;
				cin >> sin;
				in = atof(sin.c_str()); //parse float value

				search->data->setAvgTemp(in);
				cout << "Temperature updated: " << search->data->getAvgTemp() << endl;
			}
		}
		break;
		case 4: //delete
		{
			string timestamp = "";
			cout << "Please input day in format Year-Month-Day (all numbers)" << endl;
			cin >> timestamp;

			BSTNode* search = searchBST(tree, timestamp); //find node
			if (search != NULL) { //check type of node
				if (search->left == NULL && search->right == NULL) { //no children = leaf
					BSTdeleteNode(tree, search);
				}
				else if (search->left == NULL) { //1 child (right)
					AvgDataUnit* temp = search->right->data;
					BSTdeleteNode(tree, search->right);
					search->data = temp;
				}
				else if (search->right == NULL) { //1 child (left)
					AvgDataUnit* temp = search->left->data;
					BSTdeleteNode(tree, search->left);
					search->data = temp;
				}
				else { //2 children
					BSTNode* rightmin = BSTfindMin(search->right);
					AvgDataUnit* temp = rightmin->data;
					BSTdeleteNode(tree, rightmin);
					search->data = temp;
				}
			}
		}
		break;
		case 5: //also default, exit
		default:
			done = true;
			break;
		}
		system("pause");
		system("cls");
	}
}

void BSTMenu2(vector<AvgDataUnit*> arrayIn) { //Menu for BST sorted by temperature
	bool done = false; //breaks the while loop if "Exit" is selected
	quickSortAvg(arrayIn, 0, arrayIn.size() - 1); //need to sort the new array
	BSTNode* tree = sortedArrayToBST(arrayIn, 0, arrayIn.size() - 1); //create tree

	while (!done) {
		string choice = "";
		int choicenum = 0;
		cout << "Choose function:" << endl <<
			"1: Find day with minimum average temperature" << endl <<
			"2: Find day with maximum average temperature" << endl <<
			"3: Exit" << endl;
		while (choicenum < 1 || choicenum>3) {
			cin >> choice;
			choicenum = atoi(choice.c_str()); //parse int
			if (choicenum < 1 || choicenum>3) {
				cout << "Incorrect input, try again" << endl;
			}
		}

		switch (choicenum) {
		case 1: //min temperature
			BSTShowMin(tree);
			break;
		case 2: //max temperature
			BSTShowMax(tree);
			break;
		case 3: //also default, exit
		default:
			done = true;
			break;
		}
		system("pause");
		system("cls");
	}
}

void HashMenu(vector<AvgDataUnit*> arrayIn) {//menu for hash table
	AvgDataUnit*** ht; //empty hash table. Triple pointer = array of buckets of objects
	ht = createHashTable(arrayIn); //create it
	bool done = false; //breaks the while loop if "Exit" is selected

	while (!done) {
		string choice = "";
		int choicenum = 0;
		cout << "Choose function:" << endl <<
			"1: Search average temperature by day" << endl <<
			"2: Edit average temperature on day" << endl <<
			"3: Delete record of day" << endl <<
			"4: Exit" << endl;
		while (choicenum < 1 || choicenum>4) {
			cin >> choice;
			choicenum = atoi(choice.c_str()); //parse int
			if (choicenum < 1 || choicenum>4) {
				cout << "Incorrect input, try again" << endl;
			}
		}

		switch (choicenum) {
		case 1: //search
		{
			string timestamp = "";
			cout << "Please input day in format Year-Month-Day (all numbers)" << endl;
			cin >> timestamp;
			int search = hashFunction(timestamp); //find bucket
			if (ht[search] != NULL) { //check if bucket is empty
				AvgDataUnit* search2 = hashSearch(ht[search], timestamp);
				if (search2 != NULL) { //check if item exists
					cout << "Average temperature for this day is " << search2->getAvgTemp() << " degrees" << endl;
				}
			}
		}
		break;
		case 2: //edit
		{
			string timestamp = "";
			cout << "Please input day in format Year-Month-Day (all numbers)" << endl;
			cin >> timestamp;

			int search = hashFunction(timestamp); //find bucket
			if (ht[search] != NULL) { //check if bucket is empty
				AvgDataUnit* search2 = hashSearch(ht[search], timestamp); //find item
				if (search2 != NULL) { //check if item exists
					float in = 0;
					string sin = "";
					cout << "Please input new temperature in floating number format" << endl;
					cin >> sin;
					in = atof(sin.c_str()); //parse float

					search2->setAvgTemp(in);
					cout << "Temperature updated: " << search2->getAvgTemp() << endl;
				}
			}
		}
		break;
		case 3: //delete
		{
			string timestamp = "";
			cout << "Please input day in format Year-Month-Day (all numbers)" << endl;
			cin >> timestamp;

			int search = hashFunction(timestamp); //find bucket
			if (ht[search] != NULL) { //check if bucket is empty
				hashDelete(ht[search], timestamp);
			}
		}
		break;
		case 4: //also default, exit
		default:
			done = true;
			break;
		}
		system("pause");
		system("cls");

	}
}

void MainMenu(vector<AvgDataUnit*> arrayIn) { //general menu to choose between all menus
	bool done = false; //breaks the while loop if "Exit" is selected
	while (!done) {
		string choice = "";
		int choicenum = 0;
		cout << "Choose data structure:" << endl <<
			"1: BST" << endl <<
			"2: Chain Hash Table" << endl <<
			"3: Exit" << endl;
		while (choicenum < 1 || choicenum>3) {
			cin >> choice;
			choicenum = atoi(choice.c_str()); //parse int
			if (choicenum < 1 || choicenum>3) {
				cout << "Incorrect input, try again" << endl;
			}
		}

		switch (choicenum) {
		case 1: //redirect to BST menu
			system("cls");
			BSTMenu(arrayIn);
			break;
		case 2: //redirect to hash menu
			system("cls");
			HashMenu(arrayIn);
			break;
		case 3: //also default, exit
		default:
			done = true;
			break;
		}
		system("cls");
	}
}

void BSTMenu(vector<AvgDataUnit*> arrayIn) { //Menu to choose between the 2 BST menus
	bool done = false; //breaks the while loop if "Exit" is selected
	while (!done) {
		string choice = "";
		int choicenum = 0;
		cout << "Choose BST type:" << endl <<
			"1: Sorted by day" << endl <<
			"2: Sorted by average temperature" << endl <<
			"3: Exit" << endl;
		while (choicenum < 1 || choicenum>3) {
			cin >> choice;
			choicenum = atoi(choice.c_str()); //parse int
			if (choicenum < 1 || choicenum>3) {
				cout << "Incorrect input, try again" << endl;
			}
		}

		switch (choicenum) {
		case 1: //sorted by day
			system("cls");
			BSTMenu1(arrayIn);
			break;
		case 2: //sorted by avg temp
			system("cls");
			BSTMenu2(arrayIn);
			break;
		case 3: //also default, exit
		default:
			done = true;
			break;
		}
		system("cls");
	}
}
