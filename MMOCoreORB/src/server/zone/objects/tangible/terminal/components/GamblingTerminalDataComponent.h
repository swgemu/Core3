/*
 * GamblingTerminalDataComponent.h
 */

#ifndef GAMBLINGTERMINALDATACOMPONENT_H_
#define GAMBLINGTERMINALDATACOMPONENT_H_

#include "server/zone/objects/scene/components/DataObjectComponent.h"

class GamblingTerminalDataComponent : public DataObjectComponent {
protected:

	uint64 bank;
	String game;

public:
	GamblingTerminalDataComponent() {
		bank = 0;
		game = "default";
		addSerializableVariable("bank", &bank);
		addSerializableVariable("game", &game);
	}

	virtual ~GamblingTerminalDataComponent() {

	}

	/**
	 * Set the game for this terminal
	 */
	void setGame(String g) {
		game = g;
	}

	/**
	 * Get the game for this terminal
	 */
	String getGame() {
		return game;
	}

	/**
	 * Get the bank for this terminal
	 */
	uint64 getBank() {
		return bank;
	}

	/**
	 * Remove money form this games bank
	 */
	void deductFromBank(uint64 amount) {
		if (amount < bank)
			bank -= amount;
	}

	/**
	 * Add money to this games bank
	 */
	void addToBank(uint64 amount) {
		bank += amount;
	}

	/**
	 * Is this a gambling terminal data component
	 */
	bool isGamblingTerminalData() {
		return true;
	}
};


#endif /* GAMBLINGTERMINALDATACOMPONENT_H_ */
