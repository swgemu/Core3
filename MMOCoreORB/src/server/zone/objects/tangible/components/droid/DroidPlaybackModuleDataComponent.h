/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DROIDPLAYBACKMODULEDATACOMPONENT_H_
#define DROIDPLAYBACKMODULEDATACOMPONENT_H_

#include "BaseDroidModuleComponent.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackObserver.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace components {
namespace droid {

class DroidPlaybackModuleDataComponent : public BaseDroidModuleComponent {

protected:
	bool active;
	bool recording;
	int recordingTrack;
	String recordingSong;
	int recordingInstrument;
	int totalTracks;
	int selectedIndex;
	Vector<String> tracks; // Recorded Tracks
	Vector<int> instruments; // instrument for a given track
	ManagedReference<DroidPlaybackObserver*> observer;
	// states of recording
	enum {
		STATE_WAITING_TO_RECORD = 1,
		STATE_RECORDING_TRACK   = 2
	};

	Vector<uint64> listeners;

public:
	DroidPlaybackModuleDataComponent();
	~DroidPlaybackModuleDataComponent();
	String getModuleName();
	void initializeTransientMembers();
	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);
	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);
	int getBatteryDrain();
	void deactivate();
	String toString();
	void onCall();
	void onStore();
	bool isActive();
	void addListener(uint64 id);
	virtual bool isStackable() { return true; }
	virtual void addToStack(BaseDroidModuleComponent* other);
	virtual void copy(BaseDroidModuleComponent* other);
	void deleteTrack(CreatureObject* player, int slotIndex);
	void setTrack( CreatureObject* player, String song, int instrument);
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
	bool isPlayingMusic();
	String getCurrentTrack();
	int getCurrentInstrument();
	void sessionTimeout(CreatureObject* player, int state);
	void songChanged(CreatureObject* player);
	void songStopped(CreatureObject* player);
	void startRecordingSession(CreatureObject* entertainer, int index);
	void playSong(CreatureObject* player, int index);
	bool trackEmpty(int index);
	void stopTimer();
	void doFlourish(int number);
private:
	void stopRecording(CreatureObject* player, bool success);
	int writeObjectMembers(ObjectOutputStream* stream);
	bool readObjectMember(ObjectInputStream* stream, const String& name);
};

} // droid
} // components
} // tangible
} // objects
} // zone
} // server
using namespace server::zone::objects::tangible::components::droid;

#endif /* DROIDPLAYBACKMODULEDATACOMPONENT_H_ */
