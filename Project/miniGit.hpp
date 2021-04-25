#include <string>

struct singlyNode {
	std::string fileName;
	std::string fileVersion;
	int versionNumber;
	singlyNode *next = nullptr;
};

struct doublyNode {
	int commitNumber = 0;
	singlyNode *head = nullptr;
	doublyNode *previous = nullptr;
	doublyNode *next = nullptr;
};

class Repository {
private:
	doublyNode* commits;
	void nodeCopy(doublyNode* source, doublyNode* dest);
	int checkChanges(singlyNode* n);
public:
	Repository();
	~Repository();
	void Add();
	void Status();
	void Remove();
	void Commit();
	void Checkout();
	Repository(std::string existing_path);
};
