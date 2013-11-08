/*
 * SuiPageData.h
 *
 *  Created on: Nov 7, 2013
 *      Author: crush
 */

#ifndef SUIPAGEDATA_H_
#define SUIPAGEDATA_H_

#include "engine/engine.h"

namespace server {
	namespace zone {
		namespace objects {
			namespace creature {
				class CreatureObject;
			}
		}
	}
}

using namespace server::zone::objects::creature;

#include "SuiCommand.h"

class SuiPageData : public Logger, public Object {
	static AtomicInteger lastId;

	int32 id;
	String rootPage;
	uint64 targetNetworkId;
	float forceCloseDistance;
	uint64 unknownNetworkId;

	Vector<Reference<SuiCommand*> > commands;
	VectorMap<byte, Reference<SuiCommand*> > callbacks;

public:
	SuiPageData(const String& rootPage) : Object() {
		init(rootPage, 0, 0);
	}

	SuiPageData(const String& rootPage, const uint64& targetNetworkId, const float& forceCloseDistance) : Object() {
		init(rootPage, targetNetworkId, forceCloseDistance);
	}

	void setProperty(const String& widget, const String& property, const UnicodeString& value);
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

	inline String& getRootPage() {
		return rootPage;
	}

private:
	inline void init(const String& rootPage, const uint64& targetNetworkId, const float& forceCloseDistance) {
		this->id = lastId.increment();

		this->rootPage = rootPage;
		this->targetNetworkId = targetNetworkId;
		this->forceCloseDistance = forceCloseDistance;
		this->unknownNetworkId = 0;
	}

};

#endif /* SUIPAGEDATA_H_ */
