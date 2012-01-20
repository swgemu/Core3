/*
 * FactionRank.h
 *
 *  Created on: 15/01/2012
 *      Author: victor
 */

#ifndef FACTIONRANK_H_
#define FACTIONRANK_H_

#include "engine/engine.h"

#include "server/zone/templates/datatables/DataTableRow.h"

class FactionRank : public Object {
protected:
	String name;
	int cost;
	int delegateRatioFrom;
	int delegateRatioTo;

public:
	FactionRank() {
		cost = 0;
		delegateRatioFrom = 0;
		delegateRatioTo = 0;
	}

	FactionRank(const FactionRank& f) {
		name = f.name;
		cost = f.cost;
		delegateRatioFrom = f.delegateRatioFrom;
		delegateRatioTo = f.delegateRatioTo;
	}

	FactionRank& operator=(const FactionRank& f) {
		if (this == &f)
			return *this;

		name = f.name;
		cost = f.cost;
		delegateRatioFrom = f.delegateRatioFrom;
		delegateRatioTo = f.delegateRatioTo;

		return *this;
	}

	void readObject(DataTableRow* row) {
		row->getValue(1, name);
		row->getValue(2, cost);
		row->getValue(3, delegateRatioFrom);
		row->getValue(4, delegateRatioTo);
	}

	int getCost() const {
		return cost;
	}

	int getDelegateRatioFrom() const {
		return delegateRatioFrom;
	}

	int getDelegateRatioTo() const {
		return delegateRatioTo;
	}

	String getName() const {
		return name;
	}

	void setCost(int cost) {
		this->cost = cost;
	}

	void setDelegateRatioFrom(int delegateRatioFrom) {
		this->delegateRatioFrom = delegateRatioFrom;
	}

	void setDelegateRatioTo(int delegateRatioTo) {
		this->delegateRatioTo = delegateRatioTo;
	}

	void setName(const String& name) {
		this->name = name;
	}

};

#endif /* FACTIONRANK_H_ */
