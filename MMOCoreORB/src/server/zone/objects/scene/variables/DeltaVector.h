/*
 * DeltaVector.h
 *
 *  Created on: 13/07/2009
 *      Author: TheAnswer
 */

#ifndef DELTALIST_H_
#define DELTALIST_H_

#include "engine/engine.h"
#include "server/zone/packets/DeltaMessage.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
namespace variables {

template <class E> class DeltaVector : public Variable {
protected:
	ArrayList<E> vector;
	uint32 updateCounter;

	mutable UniqueReference<ReadWriteLock*> mutex;

public:
	DeltaVector() : vector(1, 1), updateCounter(1), mutex(nullptr) {
	}

	DeltaVector(int initsize, int incr) : vector(initsize, incr), updateCounter(1), mutex(nullptr) {
	}

	DeltaVector(const DeltaVector& v) : vector(v.vector), updateCounter(v.updateCounter), mutex(nullptr) {
	}

	~DeltaVector() {
	}

	DeltaVector& operator=(const DeltaVector& v) {
		if (this == &v)
			return *this;

		vector = v.vector;
		updateCounter = v.updateCounter;

		if (mutex) {
			mutex = nullptr;
		}

		return *this;
	}

	bool readObjectMember(ObjectInputStream* stream, const String& name) {
		if (name == "vector") {
			TypeInfo<ArrayList<E> >::parseFromBinaryStream(&vector, stream);

			return true;
		} else if (name == "updateCounter") {
			TypeInfo<uint32>::parseFromBinaryStream(&updateCounter, stream);

			return true;
		}

		return false;
	}

	int writeObjectMembers(ObjectOutputStream* stream) {
		String _name;
		int _offset;
		uint32 _totalSize;

		_name = "vector";
		_name.toBinaryStream(stream);
		_offset = stream->getOffset();
		stream->writeInt(0);
		TypeInfo<ArrayList<E>>::toBinaryStream(&vector, stream);
		_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
		stream->writeInt(_offset, _totalSize);

		_name = "updateCounter";
		_name.toBinaryStream(stream);
		_offset = stream->getOffset();
		stream->writeInt(0);
		TypeInfo<uint32>::toBinaryStream(&updateCounter, stream);
		_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
		stream->writeInt(_offset, _totalSize);

		String emptyName; // making it serialize the same way as Serializable so bas doesnt have to update all the objects

		_name = "_className";
		_name.toBinaryStream(stream);
		_offset = stream->getOffset();
		stream->writeInt(0);
		TypeInfo<String>::toBinaryStream(&emptyName, stream);
		_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
		stream->writeInt(_offset, _totalSize);

		return 3;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		int _currentOffset = stream->getOffset();
		stream->writeShort(0);
		int _varCount = writeObjectMembers(stream);
		stream->writeShort(_currentOffset, _varCount);

		return true;
	}

	friend void to_json(nlohmann::json& j, const DeltaVector<E>& vec) {
		j["vector"] = vec.vector;
		j["updateCounter"] = vec.updateCounter;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		uint16 _varCount = stream->readShort();

		for (int i = 0; i < _varCount; ++i) {
			String _name;
			_name.parseFromBinaryStream(stream);

			uint32 _varSize = stream->readInt();

			int _currentOffset = stream->getOffset();

			if(readObjectMember(stream, _name)) {
			}

			stream->setOffset(_currentOffset + _varSize);
		}

		return true;
	}

	virtual E set(int idx, const E& newValue, DeltaMessage* message = nullptr, int updates = 1) {
		Locker locker(getLock());

		E object = vector.set(idx, newValue);

		updateCounter += updates;

		if (message != nullptr) {
			if (updates != 0)
				message->startList(updates, updateCounter);

			message->insertByte(2);
			message->insertShort(idx);

			E& nonconst = const_cast<E&>(newValue);
			insertItemToMessage(&nonconst, message);
		}

		return object;
	}

	virtual bool add(const E& element, DeltaMessage* message = nullptr, int updates = 1) {
		Locker locker(getLock());

		bool val = vector.add(element);

		updateCounter += updates;

		if (message != nullptr) {
			if (updates != 0)
				message->startList(updates, updateCounter);

			message->insertByte(1);
			message->insertShort(vector.size() - 1);

			E& nonconst = const_cast<E&>(element);
			insertItemToMessage(&nonconst, message);
		}

		return val;
	}

	E& get(int index) const {
		return vector.get(index);
	}

	E getSafe(int index) const {
		ReadLocker locker(getLock());

		E obj = vector.get(index);

		return obj;
	}

	virtual E remove(int index, DeltaMessage* message = nullptr, int updates = 1) {
		Locker locker(getLock());

		E object = vector.remove(index);

		updateCounter += updates;

		if (message != nullptr) {
			if (updates != 0)
				message->startList(updates, updateCounter);

			message->insertByte(0);
			message->insertShort((uint16)index);
		}

		return object;
	}

	void removeAll(DeltaMessage* message = nullptr) {
		Locker locker(getLock());

		vector.removeAll();

		if (message != nullptr) {
			message->startList(1, ++updateCounter);
			message->insertByte(4);
		}
	}

	virtual void insertToMessage(BaseMessage* msg) const {
		ReadLocker locker(getLock());

		msg->insertInt(size());
		msg->insertInt(updateCounter);

		for (int i = 0; i < size(); ++i) {
			E& value = get(i);
			insertItemToMessage(&value, msg);
		}
	}

	virtual void insertItemToMessage(E* item, BaseMessage* msg) const {
		TypeInfo<E>::toBinaryStream(item, msg);
	}

	virtual bool contains(const E& element) const {
		return find(element) != -1;
	}

	int find(const E& element) const {
		for (int i = 0; i < size(); ++i) {
			if (element == get(i))
				return i;
		}

		return -1;
	}

	inline uint32 getUpdateCounter() const {
		return updateCounter;
	}

	inline uint32 getNewUpdateCounter(int increment) {
		return updateCounter += increment;
	}

	inline void setUpdateCounter(int count) {
		updateCounter = count;
	}

	inline void resetUpdateCounter() {
		updateCounter = 0;
	}

	inline int size() const {
		return vector.size();
	}

	inline ReadWriteLock* getLock() const {
		if (mutex == nullptr) {
			mutex = new ReadWriteLock();
		}

		return mutex;
	}

};


}
}
}
}
}

using namespace server::zone::objects::scene::variables;


#endif /* DELTAVECTOR_H_ */
