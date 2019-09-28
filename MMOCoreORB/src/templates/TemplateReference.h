/*
 * TemplateReference.h
 *
 *  Created on: 16/07/2010
 *      Author: victor
 */

#ifndef TEMPLATEREFERENCE_H_
#define TEMPLATEREFERENCE_H_

#include "templates/manager/TemplateManager.h"

#include "engine/util/json_utils.h"

template<class O> class TemplateReference : public Reference<O> {
#ifdef ODB_SERIALIZATION
	int crc = 0;
#endif
public:
	TemplateReference() : Reference<O>() {
	}

	TemplateReference(TemplateReference& ref) : Reference<O>(ref) {
#ifdef ODB_SERIALIZATION
		crc = ref.crc;
#endif
	}

	TemplateReference(const TemplateReference& ref) : Reference<O>(ref) {
#ifdef ODB_SERIALIZATION
		crc = ref.crc;
#endif
	}

	TemplateReference(const O obj) : Reference<O>(obj) {
	}

	TemplateReference& operator=(const TemplateReference& ref) {
		if (this == &ref)
			return *this;

		Reference<O>::updateObject(ref);

#ifdef ODB_SERIALIZATION
		crc = ref.crc;
#endif

		return *this;
	}

	bool operator==(const TemplateReference& ref) {
		return Reference<O>::get() == ref.get();
	}

	bool operator==(const O ref) {
		return Reference<O>::get() == ref;
	}

	bool toString(String& str) const {
#ifdef ODB_SERIALIZATION
		str = String::valueOf(crc);

		return true;
#else
		if (Reference<O>::get() != nullptr)
			str = String::valueOf((Reference<O>::get())->getServerObjectCRC());
		else
			str = String::valueOf(0);

		return true;
#endif
	}

	friend void to_json(nlohmann::json& j, const TemplateReference& r) {
		String str;
		r.toString(str);

		j = str;
	}

	bool parseFromString(const String& str, int version = 0) {
		SharedObjectTemplate* obj = TemplateManager::instance()->getTemplate(UnsignedLong::valueOf(str));

		if (obj == nullptr) {
			Reference<O>::updateObject(nullptr);
			return false;
		}

		Reference<O>::updateObject((O) obj);

		return true;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
#ifdef ODB_SERIALIZATION
		stream->writeInt(crc);

		return true;
#else
		O object = Reference<O>::get();

		if (object != nullptr)
			stream->writeInt(object->getServerObjectCRC());
		else
			stream->writeInt(0);

		return true;
#endif
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		uint32 oid = stream->readInt();

#ifdef ODB_SERIALIZATION
		crc = oid;

		return true;
#else

		SharedObjectTemplate* obj = TemplateManager::instance()->getTemplate(oid);

		if (obj == nullptr) {
			Reference<O>::updateObject(nullptr);
			return false;
		}

		Reference<O>::updateObject((O) obj);

		return true;
#endif
	}
};


#endif /* TEMPLATEREFERENCE_H_ */
