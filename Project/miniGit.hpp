#include <string>

struct singlyNode {
	std::string fileName;
	std::string fileVersion;
	singlyNode *next = nullptr;
};

struct doublyNode {
	int commitNumber;
	singlyNode *head = nullptr;
	doublyNode *previous = nullptr;
	doublyNode *next = nullptr;
};

class Repository {
private:
	doublyNode* commits;
public:
	Repository();
	~Repository();
	void Add();
	Repository(std::string existing_path);
};
