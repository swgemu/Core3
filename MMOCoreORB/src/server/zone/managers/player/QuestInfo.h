#ifndef QUESTINFO_H_
#define QUESTINFO_H_

#include "engine/engine.h"

class QuestInfo : public Object {

protected:
	String questName, questParent;
	bool sendSystemMessage;

public:
	QuestInfo() {
		sendSystemMessage = true;
	}

	String getQuestName() {
		return questName;
	}

	String getQuestParent() {
		return questParent;
	}

	bool shouldSendSystemMessage() {
		return sendSystemMessage;
	}

	void parseDataTableRow(DataTableRow* row) {
		row->getValue(0, questName);
		row->getValue(1, questParent);

		int sendMsg = 1;
		row->getValue(12, sendMsg);

		sendSystemMessage = sendMsg == 1;
	}
};

#endif /* QUESTINFO_H_ */
