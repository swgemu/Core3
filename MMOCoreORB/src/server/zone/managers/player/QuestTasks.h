#ifndef QUESTTASKS_H_
#define QUESTTASKS_H_

#include <system/lang/Integer.h>
#include <system/util/Vector.h>

#include "templates/datatables/DataTableIff.h"
#include "templates/datatables/DataTableRow.h"

class QuestTask : public Object  {

protected:
	String prerequisiteTasks;
	String exclusionTasks;
	String attachScript;
	String journalEntryTitle;
	String journalEntryDescription;
	Vector<int> tasksOnComplete;
	Vector<int> tasksOnFail;
	String taskName;
	bool isVisible;
	bool showSystemMessages;
	bool allowRepeats;
	String musicOnActivate;
	String target;
	String parameter;
	String grantQuestOnComplete;
	String grantQuestOnFail;
	String planetName;
	float locationX;
	float locationY;
	float locationZ;
	float radius;
	String experienceType;
	int experienceAmount;
	String factionName;
	int factionAmount;
	int bankCredits;
	String item;
	String signalName;

	void taskListStringToVector(String taskList) {
	}


public:
	QuestTask() {
	}

	void parseDataTableRow(const DataTableRow* row) {
		row->getValue(0, prerequisiteTasks);
		row->getValue(1, exclusionTasks);
		row->getValue(2, attachScript);
		row->getValue(3, journalEntryTitle);
		row->getValue(4, journalEntryDescription);
		String temp;
		row->getValue(5, temp);
		while (temp.contains(",")) {
			auto next = temp.subString(0, temp.indexOf(","));
			tasksOnComplete.add(Integer::valueOf(next));
			temp = temp.subString(temp.indexOf(",") + 1);
		}
		if (temp != "") {
			tasksOnComplete.add(Integer::valueOf(temp));
		}
		row->getValue(6, temp);
		while (temp.contains(",")) {
			auto next = temp.subString(0, temp.indexOf(","));
			tasksOnFail.add(Integer::valueOf(next));
			temp = temp.subString(temp.indexOf(",") + 1);
		}
		if (temp != "") {
			tasksOnFail.add(Integer::valueOf(temp));
		}
		row->getValue(7, taskName);
		row->getValue(8, isVisible);
		row->getValue(9, showSystemMessages);
		row->getValue(10, allowRepeats);
		row->getValue(11, musicOnActivate);
		row->getValue(12, target);
		row->getValue(13, parameter);
		row->getValue(14, grantQuestOnComplete);
		row->getValue(15, grantQuestOnFail);
		row->getValue(16, planetName);
		row->getValue(17, temp);
		locationX = Integer::valueOf(temp);
		row->getValue(18, temp);
		locationY = Integer::valueOf(temp);
		row->getValue(19, temp);
		locationZ = Integer::valueOf(temp);
		row->getValue(20, temp);
		radius = Integer::valueOf(temp);
		row->getValue(21, experienceType);
		row->getValue(22, experienceAmount);
		row->getValue(23, factionName);
		row->getValue(24, factionAmount);
		row->getValue(25, bankCredits);
		row->getValue(26, item);
		row->getValue(27, signalName);
	}

	String getAttachScript() {
		return attachScript;
	}

	String getPlanetName() {
		return planetName;
	}

	int getLocationX() {
		return locationX;
	}

	int getLocationY() {
		return locationY;
	}

	int getLocationZ() {
		return locationZ;
	}

	int getRadius() {
		return radius;
	}

};

class QuestTasks : public Object {

protected:
	Vector<QuestTask*> tasks;
public:
	QuestTasks() {
	}
	void parseDataTable(const DataTableIff& dTable) {
		for (int i = 0; i < dTable.getTotalRows(); ++i) {
			const DataTableRow* row = dTable.getRow(i);

			QuestTask* task = new QuestTask();
			task->parseDataTableRow(row);
			tasks.add(task);
		}
	}

	int getNumberOfTasks() {
		return tasks.size();
	}

	QuestTask* getTask(int taskNumber) {
		return tasks.get(taskNumber);
	}
};

#endif /* QUESTTASKS_H_ */