/*
 * TerminalListVector.h
 *
 *  Created on: Jul 4, 2012
 *      Author: kyle
 */

#ifndef TERMINALLISTVECTOR_H_
#define TERMINALLISTVECTOR_H_

#include "engine/engine.h"

class TerminalItemList : public SortedVector<ManagedReference<AuctionItem*> >, public ReadWriteLock {
protected:
	bool searchable;

public:
	TerminalItemList() {
		searchable = false;
	}

	inline void setSearchable(bool value) {
		searchable = value;
	}

	inline bool isSearchable() {
		return searchable == true;
	}
};

class TerminalRegionList : public VectorMap<uint64, Reference<TerminalItemList*> >, public ReadWriteLock {

};

class TerminalPlanetList : public VectorMap<String, Reference<TerminalRegionList*> >, public ReadWriteLock {

};

class TerminalGalaxyList : public VectorMap<String, Reference<TerminalPlanetList*> >, public ReadWriteLock {

};

class TerminalListVector : public SortedVector<Reference<TerminalItemList*> > {

};


#endif /* TERMINALLISTVECTOR_H_ */
