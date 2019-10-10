#include "../includes_usr/fileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char *filename) {
	books.clear();
	ifstream myfile;
	myfile.open(filename, ios::in);

	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	string ofstuff = "";

	while (getline(myfile, ofstuff)) {
		stringstream ss(ofstuff);
		string id = "";
		string title = "";
		string author = "";
		string state = "";
		string loan = "";
		getline(ss, id, ',');
		getline(ss, title, ',');
		getline(ss, author, ',');
		getline(ss, state, ',');
		getline(ss, loan, ',');
		book tmp;
		tmp.book_id = stoi(id, nullptr, 10);
		tmp.title = title;
		tmp.author = author;
		tmp.state = static_cast<book_checkout_state>(stoi(state, nullptr, 10));
		tmp.loaned_to_patron_id = stoi(loan, nullptr, 10);
		books.push_back(tmp);
	}

	if (books.size() < 1) {
		return NO_BOOKS_IN_LIBRARY;
	}

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char *filename) {
	//std::string myfile = "bookfile.txt";
	ofstream myfile;
	myfile.open(filename);

	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	if (books.empty()) {
		return NO_BOOKS_IN_LIBRARY;
	}
	for (int i = 0; i < books.size(); i++) {
		myfile << books[i].book_id << "," << books[i].title << ","
				<< books[i].author << "," << books[i].state << ","
				<< books[i].loaned_to_patron_id << "\n";
	}

	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char *filename) {
	patrons.clear();

	ifstream myfile;
	myfile.open(filename, ios::in);

	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	string ofstuff = "";

	while (getline(myfile, ofstuff)) {
		stringstream ss(ofstuff);
		string id = "";
		string name = "";
		string loan = "";
		getline(ss, id, ',');
		getline(ss, name, ',');
		getline(ss, loan, ',');
		patron tmp;
		tmp.patron_id = stoi(id, nullptr, 10);
		tmp.name = name;
		tmp.number_books_checked_out = stoi(loan, nullptr, 10);
		patrons.push_back(tmp);
	}

	if (patrons.size() < 1) {
		return NO_PATRONS_IN_LIBRARY;
	}
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char *filename) {
	ofstream myfile;
	myfile.open(filename);

	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	if (patrons.empty()) {
		return NO_PATRONS_IN_LIBRARY;
	}
	for (int i = 0; i < patrons.size(); i++) {
		myfile << patrons[i].patron_id << "," << patrons[i].name << ","
				<< patrons[i].number_books_checked_out << "\n";
	}

	return SUCCESS;
}
