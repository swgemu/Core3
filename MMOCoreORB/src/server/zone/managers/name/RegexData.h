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
	RegexData(String filter, int filterType) {
		regexEntry = new std::regex(filter.toCharArray(), std::regex_constants::icase);

		type = filterType;
		phrase = filter;
	}

	~RegexData() {
		delete regexEntry;
		regexEntry = nullptr;
	}

	std::regex* getRegexEntry() const {
		return regexEntry;
	}

	int getFilterType() const {
		return type;
	}

	String getRegexPhrase() const {
		return phrase;
	}
};

#endif /* REGEXDATA */
