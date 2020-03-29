#ifndef GAMBLINGGAMEDATA_H_
#define GAMBLINGGAMEDATA_H_

class GamblingGameData : public Object {

protected:
	int gameType, minPlayers, maxPlayers, minBet, maxBet;

public:
	GamblingGameData() {
		gameType = 0;
		minPlayers = 0;
		maxPlayers = 0;
		minBet = 0;
		maxBet = 0;
	}

	GamblingGameData(int type, int minP, int maxP, int minB, int maxB) : Object() {
		gameType = type;
		minPlayers = minP;
		maxPlayers = maxP;
		minBet = minB;
		maxBet = maxB;
	}

	int getMinPlayers() {
		return minPlayers;
	}

	int getMaxPlayers() {
		return maxPlayers;
	}

	int getMinBet() {
		return minBet;
	}

	int getMaxBet() {
		return maxBet;
	}
};

#endif /* GAMBLINGGAMEDATA_H_ */
