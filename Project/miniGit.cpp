#include "Repository.h"
#include <sys/stat.h>
#include <iostream>
#include <fstream>

Repository::Repository() {
	int success = mkdir(".minigit", 777);
	commits = new doublyNode;
	commits->commitNumber = 0;
}

Repository::Repository(std::string existing_path) {
	std::fstream f;
	f.open(existing_path, std::fstream::in);
	if (f.fail()) {
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
	newn->fileVersion = name + std::to_string(commits->commitNumber);
	if(prev) prev->next = newn;
	else commits->head = newn;
	file_to_add.close();
}
