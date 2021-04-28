#include <string>

struct singlyNode {	//based on template
	std::string fileName;
	std::string fileVersion;
	int versionNumber;	//added to simplify version incremention
	singlyNode *next = nullptr;
};

struct doublyNode {	//based on template
	int commitNumber = 0;
	singlyNode *head = nullptr;
	doublyNode *previous = nullptr;
	doublyNode *next = nullptr;
};

class Repository {
private:
	doublyNode* commits; //keeps track of the current uncommited link in the list
	void nodeCopy(doublyNode* source, doublyNode* dest);	//deep copy
	int checkChanges(singlyNode* n);	//scan local file and compare with committed file
	void recordCommits(); //save information to file.
	void readCommits(std::string path); //read information from file.
public:
	Repository();	//Constructor for new Repository
	~Repository();	//Deconstructor
	void Add();	//Actions
	void Remove();
	void Commit();
	void Checkout();
	Repository(std::string existing_path); //Constructor for existing Repository
};
