#include "belcard/belcard_parser.hpp"
#include "belcard/belcard.hpp"

using namespace::std;
using namespace::belr;
using namespace::belcard;

BelCardParser::BelCardParser() {
	_grammar = _grammar_builder.createFromAbnf((const char*)vcard_grammar, make_shared<CoreRules>());
}

BelCardParser::~BelCardParser() {
	
}

shared_ptr<BelCard> BelCardParser::parse(const string &input) {
	string vcard = unfold(input);
	
	Parser<shared_ptr<BelCardGeneric>> parser(_grammar);
	
	BelCard::setHandlerAndCollectors(&parser);
	BelCardParam::setHandlerAndCollectors(&parser);
	BelCardFN::setHandlerAndCollectors(&parser);
	BelCardN::setHandlerAndCollectors(&parser);
	BelCardBirthday::setHandlerAndCollectors(&parser);
	BelCardAnniversary::setHandlerAndCollectors(&parser);
	BelCardGender::setHandlerAndCollectors(&parser);
	BelCardNickname::setHandlerAndCollectors(&parser);
	BelCardPhoto::setHandlerAndCollectors(&parser);
		
	size_t parsedSize = 0;
	shared_ptr<BelCardGeneric> ret = parser.parseInput("vcard", vcard, &parsedSize);
	shared_ptr<BelCard> belCard = dynamic_pointer_cast<BelCard>(ret);
	return belCard;
}

string BelCardParser::fold(string input) {
	size_t crlf = 0;
	size_t next_crlf = 0;
	
	while (next_crlf != string::npos) {
		next_crlf = input.find("\r\n", crlf);
		if (next_crlf != string::npos) {
			if (next_crlf - crlf > 75) {
				input.insert(crlf + 74, "\r\n ");
				crlf += 76;
			} else {
				crlf = next_crlf + 2;
			}
		}
	}
	
	return input;
}

string BelCardParser::unfold(string input) {
	size_t crlf = input.find("\r\n");
	
	while (crlf != string::npos) {
		if (isspace(input[crlf + 2])) {
			input.erase(crlf, 3);
		} else {
			crlf += 2;
		}
		
		crlf = input.find("\r\n", crlf);
	}
	
	return input;
}