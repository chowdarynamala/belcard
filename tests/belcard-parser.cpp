#include "belcard/belcard_parser.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace::std;
using namespace::belr;
using namespace::belcard;

int main(int argc, char *argv[]) {
	const char *file = NULL;
	
	if (argc < 2) {
		cerr << argv[0] << " <file to parse> - parse the content of a file" << endl;
		return -1;
	}
	file = argv[1];
	
	ifstream istr(file);
	if (!istr.is_open()) {
		return -1;
	}
	
	stringstream vcardStream;
	vcardStream << istr.rdbuf();
	string vcard = vcardStream.str();
	
	BelCardParser *parser = new BelCardParser();
	shared_ptr<BelCardList> belCards = parser->parse(vcard);
	cout << *belCards << endl;
	
	delete parser;
	return 0;
}