#include "miniGit.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

Repository::Repository() {	//Create and initialize new repository object
	std::filesystem::create_directory(".minigit");
	commits = new doublyNode;
	commits->commitNumber = 0;
}

Repository::Repository(std::string existing_path) { //Skeleton framework for building Phase 2 later.
	std::fstream f;
	f.open(existing_path, std::fstream::in);
	if (f.fail()) {	//guaranteed to happen until Phase 2 implementation
		commits = new doublyNode;
		commits->commitNumber = 0;
	}
}

Repository::~Repository() {	//Deconstructor
	while(commits) {	//While a doublylinked node exist, keep deleting
		while (commits->head) {	//Delete all singly linked nodes
			singlyNode *temp = commits->head;
			commits->head = commits->head->next;
			delete temp;
		}
		doublyNode* temp = commits;	//delete doublylinked node itself
		commits = commits->previous;
		delete temp;
	}
}

void Repository::Add() {	//Add a new file to be tracked
	std::cout << "Please enter a file name: ";
	std::string name;
	std::getline(std::cin, name);
	
	std::fstream file_to_add;	//Determine if file is accessible
	file_to_add.open(name, std::fstream::in);
	while (file_to_add.fail()) {	//Require user to enter a valid file
		std::cout << "File cannot be found, or is open in another program. Doublecheck spelling\nPlease try again: ";
		std::getline(std::cin, name);
		file_to_add.open(name);
	}
	
	singlyNode *prev = nullptr;
	singlyNode *n = commits->head;
	while(n) {	//Parse to end of linked list, checking if the file already exists in the process
		if (n->fileName == name) {
			std::cout << "File already added\n";
			file_to_add.close();
			return;
		}
		prev = n;
		n = n->next;
	}
	singlyNode *newn = new singlyNode;	//Create new node
	newn->fileName = name;
	newn->fileVersion = name + ".0";	//Newly tracked files always begin with 0
	newn->versionNumber = 0;
	if(prev) prev->next = newn;
	else commits->head = newn;
	file_to_add.close();
}

void Repository::Remove() {
	std::cout << "Please enter a file name: ";
        std::string name;
        std::getline(std::cin, name);
	
	if(commits->head->fileName == name) {	//edge case for deleting the first node
		singlyNode* temp = commits->head->next;
		delete commits->head;
		commits->head = commits->head->next;
		return;
	}

	singlyNode *prev = commits->head;
        singlyNode *n = commits->head;
        while(n) {	//search for entry among nodes, delete and relink
                if (n->fileName == name) {
                        singlyNode* temp = n->next;
			delete n;
			prev->next = temp;
                        return;
                }
                prev = n;
                n = n->next;
        }
}

void Repository::Commit() {
	if(!commits->head) {	//checks that there are tracked files
		std::cout << "No changes added, nothing to commit!\n";
		return;
	}
	singlyNode *n = commits->head;
	std::cout << commits->commitNumber << std::endl;
	while(n) {	//Loop through all tracked files
		std::fstream file;
		std::fstream file2;
		std::fstream out;
		file.open(n->fileName, std::fstream::in);
		file2.open(".minigit/" + n->fileVersion, std::fstream::in);
		std::string line = "";
		if(file2.fail()){	//determines if there is an existing archived file creates a new one if one does not exist
			out.open(".minigit/" + n->fileVersion, std::fstream::out);
			while (getline(file,line)) out << line << "\n";	//copy
		} else {
			file.close();	//free up file handlers
			file2.close();
			int changed = checkChanges(n);	//determine if update to archived file is required

			if(changed) {
				file.open(n->fileName, std::fstream::in);
				++n->versionNumber;	//increment file version number
				n->fileVersion = n->fileName + "." + std::to_string(n->versionNumber);
				out.open(".minigit/" + n->fileVersion, std::fstream::out); //open new archive for writing
				while (getline(file, line)) out << line << "\n";	//copy
			}
		}
		file.close();
		out.close();
		n=n->next;	//check next file
	}

	doublyNode* newn = new doublyNode;	//Create and add new doublyLinked node
	newn->commitNumber = commits->commitNumber + 1;
	nodeCopy(commits, newn);
	newn->previous = commits;
	commits->next = newn;
	commits = newn;
}
int Repository::checkChanges(singlyNode* n) {
	std::fstream file;
	file.open(n->fileName, std::fstream::in);
	std::fstream file2;
	file2.open(".minigit/" + n->fileVersion, std::fstream::in);
	int changed = 0;
	std::string line, compare;
	while (getline(file, line)) {	//compare the files
        	if(!getline(file2, compare)) {	//if the source is larger than the archive, mark change
                	++changed;
                        break;
                }
                if (line != compare) {	//if the source and archive do not match, mark change
                        ++changed;
                        break;
                }
       }
       if (getline(file2, compare)) ++changed;	//if the archive is larger than the source, mark change
       file.close();
       file2.close();
       return changed;	//returns 0 for no changes
}

void Repository::nodeCopy(doublyNode* source, doublyNode* dest) { //deep copy
	singlyNode* n = source->head;
	singlyNode* temp = nullptr;
	while(n) {	//loop through all singlyNodes in soruce doublyNode
		singlyNode* newn = new singlyNode;	//create copy singlyNode.
		newn->fileName = n->fileName;
		newn->fileVersion = n->fileVersion;
		newn->versionNumber = n->versionNumber;
		if(temp) temp->next = newn;	//link to the end of the previous node
		else dest->head = newn;		//if is the first singlyNode, add to head of dest
		temp = newn;	//update temp
		n = n->next;	//traverse
	}
}

void Repository::Checkout() {
	singlyNode* n = commits->head;
	int changes = 0;
	while(n){	//check for uncommitted changes
		if( checkChanges(n)) ++changes;
		n = n->next;
	}
	if (changes) {
		std::cout << "warning, there are uncommitted local changes. This will destroy all of your changes. Proceed? (Y/n)\n";
		do {	//safety check, get a very precise input from the user
			std::string input;
			std::getline(std::cin, input);
			if (input == "n") return;
			if (input == "Y") break;
			std::cout << "invalid option, try again\n";
		} while(1);
	}
	int versionNum;
	std::cout << "Please enter a commit number\n";	//figure out what to checkout
	std::cin >> versionNum;
	std::string buffer;
	std::getline(std::cin, buffer);
	doublyNode* dn = commits;
	while(dn) {	//find the doublyNode
		if (dn->commitNumber == versionNum) break;
		dn = dn->previous;
	}
	if (!dn) {	//return error message if specified commit does not exist.
		std::cout << "invalid commitnumber";
		return;
	}
	n = dn->head;
	while (n) {	//copy contents of all files.
		std::cout << "Restoring " + n->fileName << "\n";
		std::fstream restore;
		std::fstream local;
		restore.open(".minigit/" + n->fileVersion, std::fstream::in);
		local.open(n->fileName, std::fstream::out);	//overwrite
		std::string line;
		while (getline(restore, line)) {
			local << line << "\n";	//copy
		}
		n = n->next;	//traverse all singlyNodes
	}
}
