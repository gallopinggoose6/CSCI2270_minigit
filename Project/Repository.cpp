#include "Repository.h"
#include <sys/stat.h>

Repository::Repository() {
	int success = mkdir(".minigit", 777);
}

Repository::Repository(std::string existing_path) {

}
