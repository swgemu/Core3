/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FEATURES_H_
#define FEATURES_H_

#include "system/lang.h"

class Features : public HashTable<String, String> {

public:
	Features();
	~Features();

	bool loadFeatures();

	inline bool hasFeature(const String& key) {
		return containsKey(key);
	}
};

#endif /* FEATURES_H_ */
