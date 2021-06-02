#ifndef SELECTPERFORMANCESUICALLBACK_H
#define SELECTPERFORMANCESUICALLBACK_H

#include "server/zone/objects/player/sui/SuiCallback.h"

class SelectPerformanceSuiCallback : public SuiCallback {
	int performanceType;
	bool bandCommand;
public:
	SelectPerformanceSuiCallback(ZoneServer* server, int type, bool bandCmd)
		: SuiCallback(server) {
		performanceType = type;
		bandCommand = bandCmd;

	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);
		int index = Integer::valueOf(args->get(0).toString());

		if (listBox == nullptr || index < 0 || index >= listBox->getMenuSize()) {
			if (performanceType == PerformanceType::MUSIC)
				player->sendSystemMessage("@performance:music_invalid_song"); // That is not a valid song name.
			else if (performanceType == PerformanceType::DANCE)
				player->sendSystemMessage("@performance:dance_unknown_self"); // You do not know that dance.

			return;
		}

		String performanceName = listBox->getMenuItemName(index);

		if (performanceType == PerformanceType::MUSIC) {
			if (player->isPlayingMusic()) {
				if (bandCommand)
					player->executeObjectControllerAction(STRING_HASHCODE("changebandmusic"), 0, performanceName);
				else
					player->executeObjectControllerAction(STRING_HASHCODE("changemusic"), 0, performanceName);
			} else {
				if (bandCommand)
					player->executeObjectControllerAction(STRING_HASHCODE("startband"), 0, performanceName);
				else
					player->executeObjectControllerAction(STRING_HASHCODE("startmusic"), 0, performanceName);
			}
		} else if (performanceType == PerformanceType::DANCE) {
			if (player->isDancing()) {
				player->executeObjectControllerAction(STRING_HASHCODE("changedance"), 0, performanceName);
			} else {
				player->executeObjectControllerAction(STRING_HASHCODE("startdance"), 0, performanceName);
			}
		}
	}
};

#endif /* SELECTPERFORMANCESUICALLBACK_H */
