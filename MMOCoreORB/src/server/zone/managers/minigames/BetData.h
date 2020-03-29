#ifndef BETDATA_H_
#define BETDATA_H_

class BetData : public Object {

protected:
	int minBet, maxBet;

public:
	BetData() {
		minBet = 0;
		maxBet = 0;
	}

	~BetData() {
	}

	BetData(const BetData& obj) : Object() {
		minBet = obj.minBet;
		maxBet = obj.maxBet;
	}

	BetData(int minB, int maxB) : Object() {
		minBet = minB;
		maxBet = maxB;
	}

	int getMaxBet() {
		return maxBet;
	}

	int getMinBet() {
		return minBet;
	}
};

#endif /* BETDATA_H_ */
