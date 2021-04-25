#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include "miniGit.hpp"

Repository* getRepository();
Repository* init();


enum userActions {
	Unknown,
	Init,
	Help,
	Exit,
	Add,
	Remove,
	Commit,
	Checkout,
	Status
};

userActions getAction(std::string input) {
	if(input == "init") return Init;
	if(input == "help") return Help;
	if(input == "exit") return Exit;
	if(input == "quit") return Exit;
	if(input == "add") return Add;
	if(input == "status") return Status;
	if(input == "remove") return Remove;
	if(input == "commit") return Commit;
	if(input == "checkout") return Checkout;
	if(input == "q") return Exit;
	return Unknown;
}

int main(int argc, char* argv[]) {
	Repository *res = getRepository();
	std::string welcome = "Welcome to minigit!\nWritten by Tyler Renken for CSCI2270 at the Univeristy of Colorado\nTo get started, type 'help' for a list of options\n";
	std::cout << welcome;
	if (res) std::cout << "Existing repository has been found and initialized\n"; //Skeleton framework for adding Serialization and Deserialization later
	else std::cout << "No existing repository has been found and initialized\n";
	while(1) {
		std::string user_option;
		std::getline(std::cin, user_option);
		switch (getAction(user_option)) {
			case Init:
				if (!res) res = init();
				else std::cout << "Repository already open\n";
				break;
			case Help:
				std::cout << "insert help information here\n";
				break;
			case Exit:
				return 0;
			case Add:
				if(res) res->Add();
				else std::cout << "Please initialize a repository first\n";
				break;
			case Status:
				if(res) res->Status();
				else std::cout << "Please initialize a repository first\n";
				break;
			case Remove:
				if(res) res->Remove();
				else std::cout << "Please initialize a repository first\n";
				break;
			case Commit:
				if(res) res->Commit();
				else std::cout << "Please initialize a repository first\n";
				break;
			case Checkout:
				if(res) res->Checkout();
				else std::cout << "Please initialize a repository first\n";
				break;
			default:
				std::cout << "Unrecognized command, if necessary please type 'help' for more options\n";
				break;
		}
	}
	return 0;
}

Repository* getRepository() {
	struct stat directory;
	if (!stat(".minigit", &directory)) {
		return new Repository(".minigit/.REPO"); //Uses existing repository (not fully implemented in Phase 1
	}
	return nullptr;
	
}

Repository* init() {
	return new Repository();	
}
