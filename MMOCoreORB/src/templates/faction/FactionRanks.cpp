/*
 * FactionRanks.cpp
 *
 *  Created on: 15/01/2012
 *      Author: victor
 */

#include "FactionRanks.h"
#include "templates/datatables/DataTableIff.h"

FactionRanks::FactionRanks() {

}

FactionRanks::FactionRanks(const FactionRanks& f) {
	ranks = f.ranks;
}

void FactionRanks::readObject(DataTableIff* table) {
	int size = table->getTotalRows();

	for (int i = 0; i < size; ++i) {
		DataTableRow* row = table->getRow(i);

		FactionRank rank;
		rank.readObject(row);

		ranks.add(rank);
	}
}
