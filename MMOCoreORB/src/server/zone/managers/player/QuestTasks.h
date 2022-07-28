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
				row->getValue(i, prerequisiteTasks);
			}
			if (columnName == "EXCLUSION_TASKS") {
				row->getValue(i, exclusionTasks);
			}
			if (columnName == "ATTACH_SCRIPT") {
				row->getValue(i, attachScript);
			}
			if (columnName == "JOURNAL_ENTRY_TITLE") {
				row->getValue(i, journalEntryTitle);
			}
			if (columnName == "JOURNAL_ENTRY_DESCRIPTION") {
				row->getValue(i, journalEntryDescription);
			}
			if (columnName == "TASKS_ON_COMPLETE") {
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
			}
			if (columnName == "TASKS_ON_FAIL") {
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
			}
			if (columnName == "TASK_NAME") {
				row->getValue(i, taskName);
			}
			if (columnName == "IS_VISIBLE") {
				row->getValue(i, isVisible);
			}
			if (columnName == "SHOW_SYSTEM_MESSAGES") {
				row->getValue(i, showSystemMessages);
			}
			if (columnName == "ALLOW_REPEATS") {
				row->getValue(i, allowRepeats);
			}
			if (columnName == "MUSIC_ON_ACTIVATE") {
				row->getValue(i, musicOnActivate);
			}
			if (columnName == "TARGET") {
				row->getValue(i, target);
			}
			if (columnName == "PARAMETER") {
				row->getValue(i, parameter);
			}
			if (columnName == "GRANT_QUEST_ON_COMPLETE") {
				row->getValue(i, grantQuestOnComplete);
			}
			if (columnName == "GRANT_QUEST_ON_FAIL") {
				row->getValue(i, grantQuestOnFail);
			}
			if (columnName == "EXPERIENCE_TYPE") {
				row->getValue(i, experienceType);
			}
			if (columnName == "EXPERIENCE_AMOUNT") {
				row->getValue(i, experienceAmount);
			}
			if (columnName == "FACTION_NAME") {
				row->getValue(i, factionName);
			}
			if (columnName == "FACTION_AMOUNT") {
				row->getValue(i, factionAmount);
			}
			if (columnName == "BANK_CREDITS") {
				row->getValue(i, bankCredits);
			}
			if (columnName == "ITEM") {
				row->getValue(i, item);
			}
			if (columnName == "PLANET_NAME") {
				row->getValue(i, planetName);
			}
			if (columnName == "LOCATION_X") {
				String temp;
				row->getValue(i, temp);
				locationX = Integer::valueOf(temp);
			}
			if (columnName == "LOCATION_Y") {
				String temp;
				row->getValue(i, temp);
				locationY = Integer::valueOf(temp);
			}
			if (columnName == "LOCATION_Z") {
				String temp;
				row->getValue(i, temp);
				locationZ = Integer::valueOf(temp);
			}
			if (columnName == "RADIUS") {
				String temp;
				row->getValue(i, temp);
				radius = Integer::valueOf(temp);
			}
			if (columnName == "SIGNAL_NAME") {
				row->getValue(i, signalName);
			}
			if (columnName == "MIN_TIME") {
				row->getValue(i, minTime);
			}
			if (columnName == "MAX_TIME") {
				row->getValue(i, maxTime);
			}
			if (columnName == "CREATURE_TYPE") {
				row->getValue(i, creatureType);
			}
			if (columnName == "TARGET_SERVER_TEMPLATE") {
				row->getValue(i, targetServerTemplate);
			}
			if (columnName == "SOCIAL_GROUP") {
				row->getValue(i, socialGroup);
			}
			if (columnName == "COUNT") {
				row->getValue(i, count);
			}
			if (columnName == "REQUIRED_REGION") {
				row->getValue(i, requiredRegion);
			}
			if (columnName == "MIN_DISTANCE") {
				row->getValue(i, minDistance);
			}
			if (columnName == "MAX_DISTANCE") {
				row->getValue(i, maxDistance);
			}
			if (columnName == "DIRECTION") {
				row->getValue(i, direction);
			}
			if (columnName == "REWARD_CREDITS") {
				row->getValue(i, rewardCredits);
			}
			if (columnName == "LOOT_ITEM_NAME") {
				row->getValue(i, lootItemName);
			}
			if (columnName == "LOOT_ITEMS_REQUIRED") {
				row->getValue(i, lootItemsRequired);
			}
			if (columnName == "LOOT_DROP_PERCENT") {
				row->getValue(i, lootDropPercent);
			}
		}
	}

	const String& getprerequisiteTasks() const {
		return prerequisiteTasks;
	}
	
	const String& getExclusionTasks() const{
		return exclusionTasks;
	}
	
	const String& getAttachScript() const {
		return attachScript;
	}
	
	const String& getJournalEntryTitle() const{
		return journalEntryTitle;
	}
	
	const String& getJournalEntryDescription() const{
		return journalEntryDescription;
	}
	
	const Vector<int> getTasksOnComplete() const{
		return tasksOnComplete;
	}
	
	const Vector<int> getTasksOnFail() const{
		return tasksOnFail;
	}
	
	const String& getTaskName() const{
		return taskName;
	}
	
	const bool getIsVisible() const{
		return isVisible;
	}
	
	const bool getShowSystemMessages() const {
		return showSystemMessages;
	}
	
	const bool getAllowRepeats() const {
		return allowRepeats;
	}
	
	const String& getMusicOnActivate() const {
		return musicOnActivate;
	}
	
	const String& getTarget() const {
		return target;
	}
	
	const String& getParameter() const {
		return parameter;
	}
	
	const String& getGrantQuestOnComplete() const {
		return grantQuestOnComplete;
	}
	
	const String& getGrantQuestOnFail() const {
		return grantQuestOnFail;
	}
	
	const String& getExperienceType() const {
		return experienceType;
	}
	
	const int getExperienceAmount() const {
		return experienceAmount;
	}
	
	const String& getFactionName() const {
		return factionName;
	}
	
	const int getFactionAmount() const{
		return factionAmount;
	}
	
	const int getBankCredits() const {
		return factionAmount;
	}
	
	const String& getItem() const {
		return item;
	}
	
	const String& getPlanetName() const {
		return planetName;
	}
	
	const float getLocationX() const {
		return locationX;
	}
	
	const float getLocationY() const {
		return locationY;
	}
	
	const float getLocationZ() const {
		return locationZ;
	}
	
	const float getRadius() const{
		return radius;
	}
	
	const String& getSignalName() const {
		return signalName;
	}
	
	const int getMinTime() const {
		return minTime;
	}
	
	const int getMaxTime() const {
		return maxTime;
	}
	
	const String& getCreatureType() const {
		return creatureType;
	}
	
	const String& getTargetServerTemplate() const {
		return targetServerTemplate;
	}
	
	const String& getSocialGroup() const {
		return socialGroup;
	}
	
	const String& getRequiredRegion() const {
		return requiredRegion;
	}
	
	const int getCount() const {
		return count;
	}
	
	const int getMinDistance() const {
		return minDistance;
	}
	
	const int getMaxDistance() const {
		return maxDistance;
	}
	
	const String& getDirection() const {
		return direction;
	}
	
	const int getRewardCredits() const {
		return rewardCredits;
	}
	
	const String& getLootItemName() const {
		return lootItemName;
	}
	
	const int getLootItemsRequired() const {
		return lootItemsRequired;
	}
	
	const int getLootDropPercent() const {
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
