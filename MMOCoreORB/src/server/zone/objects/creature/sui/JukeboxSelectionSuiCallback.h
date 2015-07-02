#ifndef JUKEBOXSELECTIONSUICALLBACK_H_
#define JUKEBOXSELECTIONSUICALLBACK_H_


#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/eventperk/Jukebox.h"
#include "server/zone/managers/player/JukeboxSong.h"

class JukeboxSelectionSuiCallback : public SuiCallback {
public:
	JukeboxSelectionSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);

		ManagedReference<SceneObject*> terminal = listBox->getUsingObject();

		if (terminal == NULL)
			return;

		ManagedReference<Jukebox*> jukebox = cast<Jukebox*>(terminal.get());

		if (jukebox == NULL)
			return;

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

		if (playerManager == NULL)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index == -1)
			return;

		JukeboxSong* song = playerManager->getJukeboxSong(index);

		String songFile = song->getSongFile();

		Locker clocker(jukebox, player);

		jukebox->stopPlaying();
		jukebox->startPlaying(songFile);
	}
};

#endif /* JUKEBOXSELECTIONSUICALLBACK_H_ */
