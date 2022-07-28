#ifndef QUESTTASKS_H_
#define QUESTTASKS_H_

#include <system/lang/Integer.h>
#include <system/util/Vector.h>

#include "templates/datatables/DataTableIff.h"
#include "templates/datatables/DataTableRow.h"

class UnknownDatatableException : public sys::lang::Exception {
public:
	UnknownDatatableException() : Exception() {
	}

	UnknownDatatableException(const String& msg) : Exception(msg) {
	}
};

class QuestTask : public Object  {

protected:
	Vector<int> prerequisiteTasks;
	Vector<int> exclusionTasks;
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
	String experienceType;
	int experienceAmount;
	String factionName;
	int factionAmount;
	int bankCredits;
	String item;
	String planetName;
	float locationX;
	float locationY;
	float locationZ;
	float radius;
	String signalName;
	int minTime;
	int maxTime;
	String creatureType;
	String targetServerTemplate;
	String socialGroup;
	String requiredRegion;
	int count;
	int minDistance;
	int maxDistance;
	String direction;
	int rewardCredits;
	String lootItemName;
	int lootItemsRequired;
	int lootDropPercent;


public:
	QuestTask() {
	}

	void parseDataTableRow(const DataTableRow* row, const DataTableIff& dTable) {
		int columnCount = dTable.getTotalColumns();
		for (int i = 0; i < columnCount; i++) {
			String columnName = dTable.getColumnNameByIndex(i);
			if (columnName == "PREREQUISITE_TASKS") {
				String temp;
				row->getValue(i, temp);
				while (temp.contains(",")) {
					auto next = temp.subString(0, temp.indexOf(","));
					prerequisiteTasks.add(Integer::valueOf(next));
					temp = temp.subString(temp.indexOf(",") + 1);
				}
				if (temp != "") {
					prerequisiteTasks.add(Integer::valueOf(temp));
				}
			} else if (columnName == "EXCLUSION_TASKS") {
				String temp;
				row->getValue(i, temp);
				while (temp.contains(",")) {
					auto next = temp.subString(0, temp.indexOf(","));
					exclusionTasks.add(Integer::valueOf(next));
					temp = temp.subString(temp.indexOf(",") + 1);
				}
				if (temp != "") {
					exclusionTasks.add(Integer::valueOf(temp));
				}
			} else if (columnName == "ATTACH_SCRIPT") {
				row->getValue(i, attachScript);
			} else if (columnName == "JOURNAL_ENTRY_TITLE") {
				row->getValue(i, journalEntryTitle);
			} else if (columnName == "JOURNAL_ENTRY_DESCRIPTION") {
				row->getValue(i, journalEntryDescription);
			} else if (columnName == "TASKS_ON_COMPLETE") {
				String temp;
				row->getValue(i, temp);
				while (temp.contains(",")) {
					auto next = temp.subString(0, temp.indexOf(","));
					tasksOnComplete.add(Integer::valueOf(next));
					temp = temp.subString(temp.indexOf(",") + 1);
				}
				if (temp != "") {
					tasksOnComplete.add(Integer::valueOf(temp));
				}
			} else if (columnName == "TASKS_ON_FAIL") {
				String temp;
				row->getValue(i, temp);
				while (temp.contains(",")) {
					auto next = temp.subString(0, temp.indexOf(","));
					tasksOnFail.add(Integer::valueOf(next));
					temp = temp.subString(temp.indexOf(",") + 1);
				}
				if (temp != "") {
					tasksOnFail.add(Integer::valueOf(temp));
				}
			} else if (columnName == "TASK_NAME") {
				row->getValue(i, taskName);
			} else if (columnName == "IS_VISIBLE") {
				row->getValue(i, isVisible);
			} else if (columnName == "SHOW_SYSTEM_MESSAGES") {
				row->getValue(i, showSystemMessages);
			} else if (columnName == "ALLOW_REPEATS") {
				row->getValue(i, allowRepeats);
			} else if (columnName == "MUSIC_ON_ACTIVATE") {
				row->getValue(i, musicOnActivate);
			} else if (columnName == "TARGET") {
				row->getValue(i, target);
			} else if (columnName == "PARAMETER") {
				row->getValue(i, parameter);
			} else if (columnName == "GRANT_QUEST_ON_COMPLETE") {
				row->getValue(i, grantQuestOnComplete);
			} else if (columnName == "GRANT_QUEST_ON_FAIL") {
				row->getValue(i, grantQuestOnFail);
			} else if (columnName == "EXPERIENCE_TYPE") {
				row->getValue(i, experienceType);
			} else if (columnName == "EXPERIENCE_AMOUNT") {
				row->getValue(i, experienceAmount);
			} else if (columnName == "FACTION_NAME") {
				row->getValue(i, factionName);
			} else if (columnName == "FACTION_AMOUNT") {
				row->getValue(i, factionAmount);
			} else if (columnName == "BANK_CREDITS") {
				row->getValue(i, bankCredits);
			} else if (columnName == "ITEM") {
				row->getValue(i, item);
			} else if (columnName == "PLANET_NAME") {
				row->getValue(i, planetName);
			} else if (columnName == "LOCATION_X") {
				String temp;
				row->getValue(i, temp);
				locationX = Integer::valueOf(temp);
			} else if (columnName == "LOCATION_Y") {
				String temp;
				row->getValue(i, temp);
				locationY = Integer::valueOf(temp);
			} else if (columnName == "LOCATION_Z") {
				String temp;
				row->getValue(i, temp);
				locationZ = Integer::valueOf(temp);
			} else if (columnName == "RADIUS") {
				String temp;
				row->getValue(i, temp);
				radius = Integer::valueOf(temp);
			} else if (columnName == "SIGNAL_NAME") {
				row->getValue(i, signalName);
			} else if (columnName == "MIN_TIME") {
				row->getValue(i, minTime);
			} else if (columnName == "MAX_TIME") {
				row->getValue(i, maxTime);
			} else if (columnName == "CREATURE_TYPE") {
				row->getValue(i, creatureType);
			} else if (columnName == "TARGET_SERVER_TEMPLATE") {
				row->getValue(i, targetServerTemplate);
			} else if (columnName == "SOCIAL_GROUP") {
				row->getValue(i, socialGroup);
			} else if (columnName == "COUNT") {
				row->getValue(i, count);
			} else if (columnName == "REQUIRED_REGION") {
				row->getValue(i, requiredRegion);
			} else if (columnName == "MIN_DISTANCE") {
				row->getValue(i, minDistance);
			} else if (columnName == "MAX_DISTANCE") {
				row->getValue(i, maxDistance);
			} else if (columnName == "DIRECTION") {
				row->getValue(i, direction);
			} else if (columnName == "REWARD_CREDITS") {
				row->getValue(i, rewardCredits);
			} else if (columnName == "LOOT_ITEM_NAME") {
				row->getValue(i, lootItemName);
			} else if (columnName == "LOOT_ITEMS_REQUIRED") {
				row->getValue(i, lootItemsRequired);
			} else if (columnName == "LOOT_DROP_PERCENT") {
				row->getValue(i, lootDropPercent);
			}
		}
	}

	const Vector<int> getPrerequisiteTasks() const {
		return prerequisiteTasks;
	}

	const Vector<int> getExclusionTasks() const {
		return exclusionTasks;
	}

	const String getAttachScript() const {
		return attachScript;
	}

	const String getJournalEntryTitle() const {
		return journalEntryTitle;
	}

	const String getJournalEntryDescription() const {
		return journalEntryDescription;
	}

	const Vector<int> getTasksOnComplete() const {
		return tasksOnComplete;
	}

	const Vector<int> getTasksOnFail() const {
		return tasksOnFail;
	}

	const String getTaskName() const {
		return taskName;
	}

	bool getIsVisible() const {
		return isVisible;
	}

	bool getShowSystemMessages() const {
		return showSystemMessages;
	}

	bool getAllowRepeats() const {
		return allowRepeats;
	}

	const String getMusicOnActivate() const {
		return musicOnActivate;
	}

	const String getTarget() const {
		return target;
	}

	const String getParameter() const {
		return parameter;
	}

	const String getGrantQuestOnComplete() const {
		return grantQuestOnComplete;
	}

	const String getGrantQuestOnFail() const {
		return grantQuestOnFail;
	}

	const String getExperienceType() const {
		return experienceType;
	}

	int getExperienceAmount() const {
		return experienceAmount;
	}

	const String getFactionName() const {
		return factionName;
	}

	int getFactionAmount() const {
		return factionAmount;
	}

	int getBankCredits() const {
		return factionAmount;
	}

	const String getItem() const {
		return item;
	}

	const String getPlanetName() const {
		return planetName;
	}

	float getLocationX() const {
		return locationX;
	}

	float getLocationY() const {
		return locationY;
	}

	float getLocationZ() const {
		return locationZ;
	}

	float getRadius() const {
		return radius;
	}

	const String getSignalName() const {
		return signalName;
	}

	int getMinTime() const {
		return minTime;
	}

	int getMaxTime() const {
		return maxTime;
	}

	const String getCreatureType() const {
		return creatureType;
	}

	const String getTargetServerTemplate() const {
		return targetServerTemplate;
	}

	const String getSocialGroup() const {
		return socialGroup;
	}

	const String getRequiredRegion() const {
		return requiredRegion;
	}

	int getCount() const {
		return count;
	}

	int getMinDistance() const {
		return minDistance;
	}

	int getMaxDistance() const {
		return maxDistance;
	}

	const String getDirection() const {
		return direction;
	}

	int getRewardCredits() const {
		return rewardCredits;
	}

	const String getLootItemName() const {
		return lootItemName;
	}

	int getLootItemsRequired() const {
		return lootItemsRequired;
	}

	int getLootDropPercent() const {
		return lootDropPercent;
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
			task->parseDataTableRow(row, dTable);
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
