/*
 * TradeContainer.h
 *
 *  Created on: 06/06/2010
 *      Author: victor
 */

#ifndef TRADECONTAINER_H_
#define TRADECONTAINER_H_

#include "engine/engine.h"

class TradeContainer : public Serializable {
protected:

	uint64 tradeTargetPlayer;
	SortedVector<ManagedReference<SceneObject*> > itemsToTrade;
	bool acceptedTrade;
	bool verifiedTrade;
	int moneyToTrade;

public:
	TradeContainer() {
		tradeTargetPlayer = 0;
		itemsToTrade.setNoDuplicateInsertPlan();
		acceptedTrade = false;
		verifiedTrade = false;
		moneyToTrade = 0;

		addSerializableVariables();
	}

	TradeContainer(const TradeContainer& tr) : Object(), Serializable() {
		tradeTargetPlayer = tr.tradeTargetPlayer;
		itemsToTrade = tr.itemsToTrade;
		acceptedTrade = tr.acceptedTrade;
		verifiedTrade = tr.verifiedTrade;
		moneyToTrade = tr.moneyToTrade;

		addSerializableVariables();
	}

	TradeContainer& operator=(const TradeContainer& tr) {
		if (this == &tr)
			return *this;

		tradeTargetPlayer = tr.tradeTargetPlayer;
		itemsToTrade = tr.itemsToTrade;
		acceptedTrade = tr.acceptedTrade;
		verifiedTrade = tr.verifiedTrade;
		moneyToTrade = tr.moneyToTrade;

		return *this;
	}

	void addSerializableVariables() {
		addSerializableVariable("tradeTargetPlayer", &tradeTargetPlayer);
		addSerializableVariable("itemsToTrade", &itemsToTrade);
		addSerializableVariable("acceptedTrade", &acceptedTrade);
		addSerializableVariable("verifiedTrade", &verifiedTrade);
		addSerializableVariable("moneyToTrade", &moneyToTrade);
	}

	void clear() {
		tradeTargetPlayer = 0;
		itemsToTrade.removeAll();
		acceptedTrade = false;
		acceptedTrade = false;
		verifiedTrade = false;
		moneyToTrade = 0;
	}

    inline bool getAcceptedTrade() const {
		return acceptedTrade;
	}

    inline void addTradeItem(SceneObject* object) {
    	itemsToTrade.put(object);
    }

    inline SortedVector<ManagedReference<SceneObject*> >* getItemsToTrade() {
		return &itemsToTrade;
	}

    inline SceneObject* getTradeItem(int index) const {
    	return itemsToTrade.get(index);
    }

    inline int getTradeSize() const {
    	return itemsToTrade.size();
    }

    inline int getMoneyToTrade() const {
		return moneyToTrade;
	}

    inline uint64 getTradeTargetPlayer() const {
		return tradeTargetPlayer;
	}

    inline bool isTryingToTrade() const {
    	return tradeTargetPlayer != 0;
    }

    inline bool hasVerifiedTrade() const {
		return verifiedTrade;
	}

    inline void setAcceptedTrade(bool acceptedTrade) {
		this->acceptedTrade = acceptedTrade;
	}

    inline void setItemsToTrade(
			SortedVector<ManagedReference<SceneObject*> > itemsToTrade) {
		this->itemsToTrade = itemsToTrade;
	}

    inline void setMoneyToTrade(int moneyToTrade) {
		this->moneyToTrade = moneyToTrade;
	}

    inline void setTradeTargetPlayer(uint64 tradeTargetPlayer) {
		this->tradeTargetPlayer = tradeTargetPlayer;
	}

    inline void setVerifiedTrade(bool verifiedTrade) {
		this->verifiedTrade = verifiedTrade;
	}

};


#endif /* TRADECONTAINER_H_ */
