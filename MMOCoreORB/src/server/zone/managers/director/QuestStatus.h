/*
 * QuestStatus.h
 *
 *  Created on: Aug 9, 2014
 *      Author: swgemu
 */

#ifndef QUESTSTATUS_H_
#define QUESTSTATUS_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace managers {
namespace director {

class QuestStatus : public ManagedObject {
private:
	String key;
	String status;


public:
	QuestStatus() {
		key = "";
		status = "";
	}

	QuestStatus(const QuestStatus& q) {
		key = q.key;
		status = q.status;
	}

	QuestStatus& operator=(const QuestStatus& q) {
		if (this == &q)
			return *this;

		key = q.key;
		status = q.status;

		return *this;
	}

	const String& getKey() const {
		return key;
	}

	void setKey(const String& key) {
		this->key = key;
	}

	const String& getStatus() const {
		return status;
	}

	void setStatus(const String& status) {
		this->status = status;
	}
};

}
}
}
}

#endif /* QUESTSTATUS_H_ */
