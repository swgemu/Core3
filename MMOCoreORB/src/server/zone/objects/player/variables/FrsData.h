/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FRSDATA_H_
#define FRSDATA_H_

#include "engine/engine.h"

#include "engine/util/json_utils.h"

class FrsData : public Object {
	int councilType;
	int rank;
	bool banished;

public:
	FrsData() : Object() {
		councilType = 0;
		rank = -1;
		banished = false;
	}

	FrsData(const FrsData& data) : Object() {
		councilType = data.councilType;
		rank = data.rank;
		banished = data.banished;
	}

	FrsData& operator=(const FrsData& data) {
		if (this == &data)
			return *this;

		councilType = data.councilType;
		rank = data.rank;
		banished = data.banished;

		return *this;
	}

	friend void to_json(nlohmann::json& j, const FrsData& f) {
		j["councilType"] = f.councilType;
		j["rank"] = f.rank;
		j["banished"] = f.banished;
	}

	bool operator==(const FrsData& data) const {
		return
			councilType == data.councilType &&
			rank == data.rank && banished == data.banished;
	}

	void setCouncilType(int type) {
		councilType = type;
	}

	int getCouncilType() const {
		return councilType;
	}

	void setRank(int newRank) {
		rank = newRank;
	}

	int getRank() const {
		return rank;
	}

	void setBanished(bool value) {
		banished = value;
	}

	bool isBanished() {
		return banished;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return TypeInfo<int >::toBinaryStream(&councilType, stream) &&
				TypeInfo<int >::toBinaryStream(&rank, stream) && TypeInfo<bool >::toBinaryStream(&banished, stream);
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		TypeInfo<int >::parseFromBinaryStream(&councilType, stream);
		TypeInfo<int >::parseFromBinaryStream(&rank, stream);
		TypeInfo<bool >::parseFromBinaryStream(&banished, stream);

		return true;
	}
};

#endif /*FRSDATA_H_*/
