/*
 * VendorDataComponent.h
 *
 *  Created on: 5/27/2012
 *      Author: kyle
 */

#ifndef VENDORDATACOMPONENT_H_
#define VENDORDATACOMPONENT_H_

#include "AuctionTerminalDataComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/managers/auction/AuctionsMap.h"
#include "server/zone/Zone.h"

class VendorDataComponent: public AuctionTerminalDataComponent {
protected:
	uint64 ownerId;

	Reference<Task*> vendorCheckTask;

	bool initialized;
	bool vendorSearchEnabled;
	bool disabled;
	bool registered;

	Time lastSuccessfulUpdate;

	int maintAmount;

	Time lastXpAward;
	int awardUsageXP;

	bool adBarking;

	Time emptyTimer;
	Time inactiveTimer;

	bool mail1Sent;
	bool mail2Sent;

	Vector<uint64> vendorBarks;
	uint64 lastBark;
	String barkMessage;
	String barkMood;
	String barkAnimation;

	float originalDirection;

public:
	/// 5 minutes
	enum {
		USEXPINTERVAL       = 5,

		// 60 Minutes
		VENDORCHECKINTERVAL = 60,
		VENDORCHECKDELAY    = 20,

		FIRSTWARNING        = 60 * 60 * 24 * 25, // 5 days
		SECONDWARNING       = 60 * 60 * 24 * 50, // 10 days
		EMPTYDELETE         = 60 * 60 * 24 * 14, // 14 days

		DELETEWARNING       = 60 * 60 * 24 * 100, // 100 days

		BARKRANGE           = 15, //Meters
		BARKINTERVAL        = 60 * 2 //Minutes
	};

public:
	VendorDataComponent();

	virtual ~VendorDataComponent() {
		if (vendorCheckTask != NULL)
			vendorCheckTask->cancel();
	}

	void initializeTransientMembers();

	void notifyObjectDestroyingFromDatabase();

	void sendVendorUpdateMail(bool isEmpty);

	void sendVendorDestroyMail();

	void runVendorUpdate();

	void setOwnerId(uint64 id) {
		ownerId = id;
	}

	uint64 getOwnerId() {
		return ownerId;
	}

	bool isVendorData() {
		return true;
	}

	inline void setInitialized(bool val) {
		initialized = val;
		updateUID();

		ManagedReference<SceneObject*> strongParent = parent.get();
		if (strongParent == NULL)
			return;

		originalDirection = strongParent->getDirectionAngle();
	}

	void setVendorSearchEnabled(bool enabled);

	inline void setDisabled(bool isDisabled) {
		disabled = isDisabled;
	}

	inline void setRegistered(bool reg) {
		registered = reg;

		/// This is just a precaution in case somehow items get lost
		/// and this would link up a missing auction list unless it was totally
		/// gone
		if (registered)
			updateUID();
	}

	inline int getOwnershipRightsOf(CreatureObject* player) {
		if (!initialized)
			return 2; // mark not initalized

		if (player->getObjectID() == ownerId) // Player owns this vendor
			return 0;
		else if (ownerId != 0) // someone else owns the vendor and its not a bazaar
			return 1;
		else
			return 2; // the vendor hasn't been initalized yet or it belongs to no one (bazaar)
	}

	inline bool isVendorOwner(CreatureObject* player) {
		return player->getObjectID() == ownerId;
	}

	inline bool isInitialized() {
		return initialized;
	}

	inline bool isVendorSearchEnabled() {
		return vendorSearchEnabled;
	}

	inline bool isDisabled() {
		return disabled;
	}

	inline bool isRegistered() {
		return registered;
	}

	inline void awardUseXP() {
		if (time(0) - lastXpAward.getTime() > USEXPINTERVAL * 60) {
			awardUsageXP++;
			lastXpAward.updateToCurrentTime();
		}
	}

	inline bool isAdBarkingEnabled() {
		return adBarking;
	}

	inline void setAdBarking(bool value) {
		vendorBarks.removeAll();
		adBarking = value;
	}

	inline bool isEmpty() {

		if (auctionManager == NULL)
			return false;

		ManagedReference<AuctionsMap*> auctionsMap =
				auctionManager->getAuctionMap();
		if (auctionsMap == NULL) {
			return false;
		}

		return auctionsMap->getVendorItemCount(parent.get(), true) == 0;
	}

	inline void setEmpty() {
		mail1Sent = false;
		mail2Sent = false;

		emptyTimer.updateToCurrentTime();
	}

	inline int getMaint() {
		return maintAmount;
	}

	inline bool isOnStrike() {
		return maintAmount <= 0;
	}

	void setAdPhrase(const String& message) {
		barkMessage = message;
	}

	void setAdMood(const String& mood) {
		barkMood = mood;
	}

	void setAdAnimation(const String& animation) {
		barkAnimation = animation;
	}

	bool hasBarkTarget(SceneObject* target) {
		return vendorBarks.contains(target->getObjectID());
	}

	void addBarkTarget(SceneObject* target) {
		vendorBarks.add(target->getObjectID());
	}

	bool canBark() {
		return (time(0) - lastBark > BARKINTERVAL);
	}

	void clearVendorBark(SceneObject* target) {
		vendorBarks.removeElement(target->getObjectID());
	}

	float getMaintenanceRate();

	void payMaintanence();

	void withdrawMaintanence();

	void handlePayMaintanence(int value);

	void handleWithdrawMaintanence(int value);

	void performVendorBark(SceneObject* target);

private:
	void addSerializableVariables();
};

#endif /* VENDORDATACOMPONENT_H_ */
