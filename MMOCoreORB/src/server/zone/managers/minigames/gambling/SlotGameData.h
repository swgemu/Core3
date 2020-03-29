#ifndef SLOTGAMERESULT_H_
#define SLOTGAMERESULT_H_

class SlotGameData : public Object {

protected:
	String slotPattern;
	Vector<short> resultList;
	int basePayout, maxPayout;
public:
	SlotGameData() {
		slotPattern = "";
		basePayout = 0;
		maxPayout = 0;
	}

	SlotGameData(String pattern, int base, int max) : Object() {
		slotPattern = pattern;
		basePayout = base;
		maxPayout = max;
	}

	int getBasePayout() {
		return basePayout;
	}

	int getMaxPayout() {
		return maxPayout;
	}

	void addResult(short result) {
		resultList.add(result);
	}

	bool isCorrectPattern(int patternNum) {
		return resultList.contains(patternNum);
	}

	String getSlotPattern() {
		return slotPattern;
	}
};

#endif /* SLOTGAMERESULT_H_ */
