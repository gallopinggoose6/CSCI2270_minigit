#include <string>

struct singlyNode {
	std::string fileName;
	std::string fileVersion;
	singlyNode *next;
};

struct doublyNode {
	int commitnumber;
	singlyNode *head;
	doublyNode *previous;
	doublyNode *next;
};

class Repository {
private:
	doublyNode commits;
public:
	Repository();
	Repository(std::string existing_path);
};
