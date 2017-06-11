/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FRSDATA_H_
#define FRSDATA_H_

#include "engine/engine.h"

class FrsData : public Object {
	int councilType;
	int rank;

public:
	FrsData() : Object() {
		councilType = 0;
		rank = -1;
	}

	FrsData(const FrsData& data) : Object() {
		councilType = data.councilType;
		rank = data.rank;
	}

	FrsData& operator=(const FrsData& data) {
		if (this == &data)
			return *this;

		councilType = data.councilType;
		rank = data.rank;

		return *this;
	}

	bool operator==(FrsData data) {
		return
			councilType == data.councilType &&
			rank == data.rank;
	}

	void setCouncilType(int type) {
		councilType = type;
	}

	int getCouncilType() {
		return councilType;
	}

	void setRank(int newRank) {
		rank = newRank;
	}

	int getRank() {
		return rank;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return TypeInfo<int >::toBinaryStream(&councilType, stream) &&
				TypeInfo<int >::toBinaryStream(&rank, stream);
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		TypeInfo<int >::parseFromBinaryStream(&councilType, stream);
		TypeInfo<int >::parseFromBinaryStream(&rank, stream);

		return true;
	}
};

#endif /*FRSDATA_H_*/
