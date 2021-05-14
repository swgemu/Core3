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
	bool currentlyRecording;
	int recordingTrack;
	int recordingPerformanceIndex;
	int totalTracks;
	int performanceIndex;
	Vector<int> trackList; // Recorded Tracks

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
	String getModuleName() const;
	void initializeTransientMembers();
	void fillAttributeList(AttributeListMessage* msg, CreatureObject* droid);
	void fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	int handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller);
	int getBatteryDrain();
	void deactivate();
	String toString() const;
	void onCall();
	void onStore();
	void addListener(uint64 id);
	virtual bool isStackable() { return true; }
	virtual void addToStack(BaseDroidModuleComponent* other);
	virtual void copy(BaseDroidModuleComponent* other);
	void deleteTrack(CreatureObject* player, int slotIndex);
	void setTrack( CreatureObject* player, int perfIndex);
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
	void sessionTimeout(CreatureObject* player, int state);
	void songChanged(CreatureObject* player);
	void songStopped(CreatureObject* player);
	void startRecordingSession(CreatureObject* entertainer, int index);
	void playSong(CreatureObject* player, int index);
	bool trackEmpty(int index);
	void stopTimer();
	void doFlourish(int number);
	String getTrackName(int perfIndex);
	int getMatchingIndex(DroidObject* droid, int perfIndex);

	inline bool isPlayingMusic() {
		return performanceIndex > 0;
	}

	inline int getPerformanceIndex() {
		return performanceIndex;
	}

	inline bool isRecording() {
		return currentlyRecording;
	}

	inline int getTotalTracks() {
		return trackList.size();
	}

	inline int getTrackPerformanceIndex(int index) {
		return trackList.get(index);
	}

	void writeJSON(nlohmann::json& j) const {
		BaseDroidModuleComponent::writeJSON(j);

		SERIALIZE_JSON_MEMBER(currentlyRecording);
		SERIALIZE_JSON_MEMBER(recordingTrack);
		SERIALIZE_JSON_MEMBER(recordingPerformanceIndex);
		SERIALIZE_JSON_MEMBER(totalTracks);
		SERIALIZE_JSON_MEMBER(trackList);
		SERIALIZE_JSON_MEMBER(observer);

	}
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
