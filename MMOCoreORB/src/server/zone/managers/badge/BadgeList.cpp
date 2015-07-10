#include "BadgeList.h"


BadgeList::BadgeList() {
	badges.setNullValue(NULL);
	names.setNullValue(NULL);
#ifdef GROUP_BADGES
	categories.setNullValue(NULL);
	types.setNullValue(NULL);
#endif
}

BadgeList::~BadgeList() {/*
	HashTableIterator<int, Badge*> iterator = badges.iterator();
	while(iterator.hasNext()) {
		Badge* badge = iterator.getNextValue();
		if (badge)
			delete badge;
	}
	for (int i = 0; i < categories.size(); i++) {
		Vector<Badge*> * list = categories.elementAt(i);
		if (list)
			delete list;
	}

	for (int i = 0 ; i  < types.size(); i++) {
		Vector<Badge*> * list = types.elementAt(i);
		if (list)
			delete list;
	}*/
}

void BadgeList::add(Badge* badge) {
	if (badge == NULL) return;

	badges.put(badge->getIndex(), badge);
	names.put(badge->getKey(), badge);

#ifdef GROUP_BADGES
	const int category = badge->getCategory();

	Vector<const Badge*>* cats = categories.get(category);
	if (cats == NULL) {
		cats = new Vector<const Badge*>();
		categories.put(category, cats);
	}
	cats->add(badge);
	
	const String type = badge->getTypeString();

	Vector<const Badge*>* tps = types.get(type);
	if (tps == NULL) {
		tps = new Vector<const Badge*>();
		types.put(type, tps);
	}
	tps->add(badge);
#endif
}
