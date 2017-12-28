/*
 * FactionRank.h
 *
 *  Created on: 15/01/2012
 *      Author: victor
 */

#ifndef FACTIONRANKS_H_
#define FACTIONRANKS_H_

#include <algorithm>

#include "FactionRank.h"
#include "system/util/Vector.h"

class DataTableIff;

class FactionRanks {
protected:
	Vector<FactionRank> ranks;

public:
	FactionRanks();
	FactionRanks(const FactionRanks& f);

	void readObject(DataTableIff* table);

	const FactionRank& getRank(int index) {
		return ranks.get(index);
	}

	int getCount() {
		return ranks.size();
	}
};


#endif /* FACTIONRANK_H_ */
