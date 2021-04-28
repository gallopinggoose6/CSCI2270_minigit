#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include "miniGit.hpp"

Repository* getRepository();
Repository* init();


enum userActions { //actions that act as an adapter for the switch statement.
	Unknown,
	Init,
	Help,
	Exit,
	Add,
	Remove,
	Commit,
	Checkout,
};

userActions getAction(std::string input) { //map values to actions, providing greater customizability and support of multiple synonyms of commands.
	if(input == "init") return Init;
	if(input == "help") return Help;
	if(input == "exit") return Exit;
	if(input == "quit") return Exit;
	if(input == "add") return Add;
	if(input == "remove") return Remove;
	if(input == "commit") return Commit;
	if(input == "checkout") return Checkout;
	if(input == "q") return Exit;
	return Unknown;
}

int main(int argc, char* argv[]) {	//main user-interaction loop
	Repository *res = getRepository();	//Get an available repository
	std::string welcome = "Welcome to minigit!\nWritten by Tyler Renken for CSCI2270 at the Univeristy of Colorado\nTo get started, type 'help' for a list of options\n";
	std::cout << welcome;	//Welcome message
	if (res) std::cout << "Existing repository has been found and initialized\n"; //Skeleton framework for adding Serialization and Deserialization later
	else std::cout << "No existing repository has been found and initialized\n";
	while(1) {
		std::string user_option;
		std::getline(std::cin, user_option);
		switch (getAction(user_option)) {
			case Init:
				if (!res) res = init();
				else std::cout << "Repository already open\n"; //get new repository
				break;
			case Help:
				std::cout << "available commands: init, help, exit, add, remove, commit, checkout\n";
				break;
			case Exit:
				delete res; //clean up memory
				return 0;
			case Add:			//Process commmands
				if(res) res->Add();
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
	delete res; 	//should never happen, but if so, clean up memory
	return 0;
}

Repository* getRepository() {	//Get a repository
	struct stat directory;
	if (!stat(".minigit", &directory)) {
		return new Repository(".minigit/.REPO"); //Uses existing repository (not fully implemented in Phase 1
	}
	return nullptr;
	
}

Repository* init() {	//Get a repository
	return new Repository();	
}
