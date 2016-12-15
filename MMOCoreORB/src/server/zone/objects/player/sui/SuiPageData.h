/*
 * SuiPageData.h
 *
 *  Created on: Nov 7, 2013
 *      Author: crush
 */

#ifndef SUIPAGEDATA_H_
#define SUIPAGEDATA_H_

#include "engine/engine.h"
#include "SuiCommand.h"
#include "server/zone/objects/creature/CreatureObject.h"

class SuiPageData : public Logger, public Object {
	int32 id;
	String rootPage;
	uint64 targetNetworkId;
	float forceCloseDistance;
	uint64 unknownNetworkId;

	Vector<Reference<SuiCommand*> > commands;
	VectorMap<String, String> storedData;
	VectorMap<byte, Reference<SuiCommand*> > callbacks;

public:
	SuiPageData(const String& rootPage) : Object() {
		init(rootPage, 0, 0);
	}

	SuiPageData(const String& rootPage, const uint64& targetNetworkId, const float& forceCloseDistance) : Object() {
		init(rootPage, targetNetworkId, forceCloseDistance);
	}

	void setProperty(const String& widget, const String& property, const UnicodeString& value);
	UnicodeString getPropertyValue(const String& widget, const String& property);
	void addDataItem(const String& widget, const String& property, const UnicodeString& value);
	void clearDataSource(const String& dataSource);
	void addDataSourceContainer(const String& parent, const String& name);
	void clearDataSourceContainer(const String& dataSourceContainer);
	void addChildWidget(const String& parent, const String& type, const String& name);
	void subscribeToEvent(const byte& eventType, const String& parent, const String& callback);
	void subscribeToPropertyForEvent(const byte& eventType, const String& widget, const String& property);

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	void sendTo(CreatureObject* creo);
	void sendUpdateTo(CreatureObject* creo);

	void setStoredData(const String& key, const String& value) {
		if (storedData.contains(key))
			storedData.drop(key);

		storedData.put(key, value);
	}

	void deleteStoredData(const String& key) {
		storedData.drop(key);
	}

	String getStoredData(const String& key) {
		if (!storedData.contains(key))
			return "";

		return storedData.get(key);
	}

	void setPageId(int pageId) {
		id = pageId;
	}

	int32 getPageId() {
		return id;
	}

	void setForceCloseDistance(float dist) {
		forceCloseDistance = dist;
	}

	float getForceCloseDistance() {
		return forceCloseDistance;
	}

	void setTargetNetworkId(uint64 id) {
		targetNetworkId = id;
	}

	SuiCommand* getCommand(int index) {
		return commands.get(index);
	}

	uint64 getTargetNetworkId() {
		return targetNetworkId;
	}

	inline String& getRootPage() {
		return rootPage;
	}

private:
	inline void init(const String& rootPage, const uint64& targetNetworkId, const float& forceCloseDistance) {
		this->id = 0;

		this->rootPage = rootPage;
		this->targetNetworkId = targetNetworkId;
		this->forceCloseDistance = forceCloseDistance;
		this->unknownNetworkId = 0;
	}

};

#endif /* SUIPAGEDATA_H_ */
