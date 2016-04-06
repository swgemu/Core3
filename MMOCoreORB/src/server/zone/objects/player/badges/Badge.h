/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BADGE_H_
#define BADGE_H_

#include "engine/engine.h"
#include "templates/datatables/DataTableRow.h"

class Badge {

public:
	enum /*Type*/ {
		ACCUMULATION,
		INTEREST,
		EXPLORATION,
		MASTER,
		EVENT,
		CONTENT,
		UNKNOWN
	};


	Badge();
	//Badge(Badge&) = default;

	void readFromRow(DataTableRow* row);


	inline int getIndex() const {
		return index;
	}
	
	inline const String getKey() const{
		return key;
	}

	inline const String getMusic() const {
		return music;
	}

	inline int getCategory() const {
		return category;
	}
	
	inline int getShow() const {
		return show;
	}

	inline const String getTypeString() const {
		return typeString;
	}

	inline /*Type*/uint8 getType() const {
		return type;
	}

	inline int getTypeInt() const {
		return static_cast<int>(type);
	}

	inline bool getHasMusic() const {
		return hasMusic;
	}


private:

	static uint8 getTypeFromString(const String& string);

	int index;
	int category;
	int show;
	/*Type type;*/
	uint8 type;
	bool hasMusic;
	String key;
	String music;
	String typeString;
};
#endif /*BADGE_H_*/
