#include <string>
#include <vector>

class Dictionary
{

public:

	std::vector< std::string > words;

	void readDICfile(std::string filename);

	bool checkIfWordExists(std::string word);

};
