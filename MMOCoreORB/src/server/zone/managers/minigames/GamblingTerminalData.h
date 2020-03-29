#ifndef GAMBLINGTERMINALDATA_H_
#define GAMBLINGTERMINALDATA_H_

class GamblingTerminalData : public Object {

protected:
	uint64 currentPlayerTurn, lastBetTime;
	int currentBet;
	Vector<uint64> currentPlayers;


public:
	GamblingTerminalData() {
		currentPlayerTurn = 0;
		currentBet = 0;
		lastBetTime = 0;
	}

	~GamblingTerminalData() {
	}

	GamblingTerminalData(const GamblingTerminalData& obj) : Object() {
		currentPlayerTurn = obj.currentPlayerTurn;
		currentBet = obj.currentBet;
		lastBetTime = obj.lastBetTime;
	}

	GamblingTerminalData(uint64 curTurn, int curBet, uint64 lastBet) : Object() {
		currentPlayerTurn = curTurn;
		currentBet = curBet;
		lastBetTime = lastBet;
	}

	bool isCurrentPlayer(uint64 playerID) {
		return currentPlayers.contains(playerID);
	}

	void addCurrentPlayer(uint64 playerID) {
		currentPlayers.add(playerID);
	}

	void removeCurrentPlayer(uint64 playerID) {
		if (currentPlayerTurn == playerID)
			currentPlayerTurn = 0;

		currentPlayers.remove(playerID);
	}

	Vector<uint64> getCurrentPlayers() {
		return currentPlayers;
	}

	void setCurrentPlayerTurn(uint64 player) {
		currentPlayerTurn = player;
	}

	uint64 getCurrentPlayerTurn() {
		return currentPlayerTurn;
	}

	int getCurrentBet() {
		return currentBet;
	}

	void setCurrentBet(int newBet) {
		currentBet = newBet;
	}

	uint64 getLastBetTime() {
		return lastBetTime;
	}

	void setLastBetTime(uint64 newTime) {
		lastBetTime = newTime;
	}
};

#endif /* GAMBLINGTERMINALDATA_H_ */
