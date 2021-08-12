/*
 * FriendList.h
 *
 *  Created on: 05/02/2010
 *      Author: victor
 */

#ifndef FRIENDLIST_H_
#define FRIENDLIST_H_

#include "PlayerList.h"

class FriendList : public PlayerList<7> {
protected:
	Vector<String> reverseTable;

public:
	FriendList() {
	}

	FriendList(const FriendList& list) : PlayerList<7>(list) {
		reverseTable = list.reverseTable;
	}

	FriendList& operator=(const FriendList& list) {
		if (this == &list) {
			return *this;
		}

		PlayerList<7>::operator=(list);

		reverseTable = list.reverseTable;

		return *this;
	}

	bool readObjectMember(ObjectInputStream* stream, const String& name) {
		if (name == "reverseTable") {
			TypeInfo<Vector<String>>::parseFromBinaryStream(&reverseTable, stream);

			return true;
		}

		return PlayerList<7>::readObjectMember(stream, name);
	}

	int writeObjectMembers(ObjectOutputStream* stream) {
		static String _name = "reverseTable";
		int _offset;
		uint32 _totalSize;

		_name.toBinaryStream(stream);
		_offset = stream->getOffset();
		stream->writeInt(0);
		TypeInfo<Vector<String>>::toBinaryStream(&reverseTable, stream);
		_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
		stream->writeInt(_offset, _totalSize);

		return 1 + PlayerList<7>::writeObjectMembers(stream);
	}


	bool toBinaryStream(ObjectOutputStream* stream) {
		int _currentOffset = stream->getOffset();
		stream->writeShort(0);
		int _varCount = writeObjectMembers(stream);
		stream->writeShort(_currentOffset, _varCount);

		return true;
	}

	friend void to_json(nlohmann::json& j, const FriendList& l) {
		const DeltaVector<String>& dv = l;

		j["reverseTable"] = l.reverseTable;
		j["players"] = dv;
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





	void addReversePlayer(const String& name) {
		Locker locker(getLock());

		String low = name.toLowerCase();

		int idx = -1;

		for (int i = 0; i < reverseTable.size(); ++i) {
			if (low == reverseTable.get(i)) {
				idx = i;
				break;
			}
		}

		if (idx == -1)
			reverseTable.add(low);
	}

	void removeReversePlayer(const String& name) {
		Locker locker(getLock());

		String low = name.toLowerCase();

		int idx = -1;

		for (int i = 0; i < reverseTable.size(); ++i) {
			if (low == reverseTable.get(i)) {
				idx = i;
				break;
			}
		}

		if (idx != -1)
			reverseTable.remove(idx);
	}

	String getReversePlayer(int idx) {
		Locker locker(getLock());

		return reverseTable.get(idx);
	}

	int reversePlayerCount() {
		return reverseTable.size();
	}

};

#endif /* FRIENDLIST_H_ */
