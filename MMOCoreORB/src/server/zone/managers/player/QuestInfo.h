#ifndef QUESTINFO_H_
#define QUESTINFO_H_

#include "templates/datatables/DataTableRow.h"

class QuestInfo : public Object {

protected:
	String questName, questParent, journalSummary, questParameter, questTarget;
	String attachScript, taskOnComplete, taskOnFail;
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

	String getQuestParameter() {
		return questParameter;
	}

	String getJournalSummary() {
		return journalSummary;
	}

	String getAttachScript() {
		return attachScript;
	}

	String getTaskOnComplete() {
		return taskOnComplete;
	}

	String getTaskOnFail() {
		return taskOnFail;
	}

	String getQuestTarget() {
		return questTarget;
	}

	bool shouldSendSystemMessage() {
		return sendSystemMessage;
	}

	void parseDataTableRow(DataTableRow* row) {
		row->getValue(0, questName);
		row->getValue(1, questParent);
		row->getValue(2, attachScript);
		row->getValue(3, journalSummary);
		row->getValue(5, taskOnComplete);
		row->getValue(6, taskOnFail);
		row->getValue(7, questTarget);
		row->getValue(8, questParameter);
		row->getValue(11, sendSystemMessage);
	}
};

#endif /* QUESTINFO_H_ */
