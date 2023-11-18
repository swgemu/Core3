#ifndef REGEXDATA
#define REGEXDATA

#include "engine/engine.h"
#include <regex>

class RegexData : public Object {

protected:
	std::regex* regexEntry;
	String phrase;
	int type;

public:
	RegexData(String filter, int filterType) : Object() {
		regexEntry = new std::regex(filter.toCharArray(), std::regex_constants::icase);
		type = filterType;
		phrase = filter;
	}

	~RegexData() {
	}

	std::regex* getRegexEntry() {
		return regexEntry;
	}

	int getFilterType() {
		return type;
	}

	String getRegexPhrase() {
		return phrase;
	}
};

#endif /* REGEXDATA */
