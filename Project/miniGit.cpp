#include "miniGit.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

Repository::Repository() {
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

Repository::~Repository() {
	while(commits) {
		while (commits->head) {
			singlyNode *temp = commits->head;
			commits->head = commits->head->next;
			delete temp;
		}
		doublyNode* temp = commits;
		commits = commits->previous;
		delete temp;
	}
}

void Repository::Add() {
	std::cout << "Please enter a file name: ";
	std::string name;
	std::getline(std::cin, name);
	
	std::fstream file_to_add;
	file_to_add.open(name, std::fstream::in);
	while (file_to_add.fail()) {
		std::cout << "File cannot be found, or is open in another program. Doublecheck spelling\nPlease try again: ";
		std::getline(std::cin, name);
		file_to_add.open(name);
	}
	
	singlyNode *prev = nullptr;
	singlyNode *n = commits->head;
	while(n) {
		if (n->fileName == name) {
			std::cout << "File already added\n";
			file_to_add.close();
			return;
		}
		prev = n;
		n = n->next;
	}
	singlyNode *newn = new singlyNode;
	newn->fileName = name;
	newn->fileVersion = name + ".0";
	newn->versionNumber = 0;
	if(prev) prev->next = newn;
	else commits->head = newn;
	file_to_add.close();
}

void Repository::Status() {	//Basic implementation, for debugging purposes
	singlyNode *n = commits->head;
	if(!n) std::cout << "No files are being tracked yet\n";
	while(n) {
		std::cout << "Tracked files: " << n->fileName << std::endl;
		n = n->next;
	}
}

void Repository::Remove() {
	std::cout << "Please enter a file name: ";
        std::string name;
        std::getline(std::cin, name);
	
	if(commits->head->fileName == name) {
		singlyNode* temp = commits->head->next;
		delete commits->head;
		commits->head = commits->head->next;
		return;
	}

	singlyNode *prev = commits->head;
        singlyNode *n = commits->head;
        while(n) {
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
	if(!commits->head) {
		std::cout << "No changes added, nothing to commit!\n";
		return;
	}
	singlyNode *n = commits->head;
	std::cout << commits->commitNumber << std::endl;
	while(n) {
		std::fstream file;
		std::fstream file2;
		std::fstream out;
		file.open(n->fileName, std::fstream::in);
		file2.open(".minigit/" + n->fileVersion, std::fstream::in);
		std::string line = "";
		if(file2.fail()){
			out.open(".minigit/" + n->fileVersion, std::fstream::out);
			while (getline(file,line)) out << line << "\n";
		} else {
			file.close();
			file2.close();
			int changed = checkChanges(n);

			if(changed) {
				file.open(n->fileName, std::fstream::in);
				++n->versionNumber;
				n->fileVersion = n->fileName + "." + std::to_string(n->versionNumber);
				out.open(".minigit/" + n->fileVersion, std::fstream::out);
				while (getline(file, line)) out << line << "\n";
			}
		}
		file.close();
		out.close();
		n=n->next;
	}

	doublyNode* newn = new doublyNode;
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
	while (getline(file, line)) {
        	if(!getline(file2, compare)) {
                	++changed;
                        break;
                }
                if (line != compare) {
                        ++changed;
                        break;
                }
       }
       if (getline(file2, compare)) ++changed;
       file.close();
       file2.close();
       return changed;
}

void Repository::nodeCopy(doublyNode* source, doublyNode* dest) {
	singlyNode* n = source->head;
	singlyNode* temp = nullptr;
	while(n) {
		singlyNode* newn = new singlyNode;
		newn->fileName = n->fileName;
		newn->fileVersion = n->fileVersion;
		newn->versionNumber = n->versionNumber;
		if(temp) temp->next = newn;
		else dest->head = newn;
		temp = newn;
		n = n->next;
	}
}

void Repository::Checkout() {
	singlyNode* n = commits->head;
	int changes = 0;
	while(n){
		if( checkChanges(n)) ++changes;
		n = n->next;
	}
	if (changes) {
		std::cout << "warning, there are uncommitted local changes. This will destroy all of your changes. Proceed? (Y/n)\n";
		do {
			std::string input;
			std::getline(std::cin, input);
			if (input == "n") return;
			if (input == "Y") break;
			std::cout << "invalid option, try again\n";
		} while(1);
	}

}
