/*
 * DestuctibleBuildingDataComponent.cpp
 *
 *  Created on: Oct 22, 2012
 *      Author: pete
 */
#include "DestructibleBuildingDataComponent.h"

void DestructibleBuildingDataComponent::setState(int state) {
	if (state >= INVULNERABLE && state <= REBOOTSEQUENCE)
		intCurrentState = state;
}

void DestructibleBuildingDataComponent::initializeTransientMembers() {
	uplinkBand = System::random(0x9);
}

bool DestructibleBuildingDataComponent::parseFromBinaryStream(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();

	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);
		uint32 _varSize = stream->readInt();

		int _currentOffset = stream->getOffset();

		if (readObjectMember(stream, _name)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	return true;
}

bool DestructibleBuildingDataComponent::toBinaryStream(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);

	return true;
}

int DestructibleBuildingDataComponent::writeObjectMembers(ObjectOutputStream* stream) {

	String _name;
	int _offset;
	uint32 _totalSize;

	_name = "placementTime";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Time >::toBinaryStream(&placementTime, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "nextVulnerableTime";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Time >::toBinaryStream(&nextVulnerableTime, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "lastResetTime";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Time >::toBinaryStream(&lastResetTime, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "lastVulnerableTime";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Time >::toBinaryStream(&lastVulnerableTime, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "vulnerabilityEndTime";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Time >::toBinaryStream(&vulnerabilityEndTime, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "intCurrentState";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<int >::toBinaryStream(&intCurrentState, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "inRepair";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<bool >::toBinaryStream(&inRepair, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "terminalDamaged";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<bool >::toBinaryStream(&terminalDamaged, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "turretSlots";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Vector<uint64>  >::toBinaryStream(&turretSlots, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "minefieldSlots";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Vector<uint64>  >::toBinaryStream(&minefieldSlots, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "scannerSlots";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Vector<uint64>  >::toBinaryStream(&scannerSlots, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "activeDefenses";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<bool >::toBinaryStream(&activeDefenses, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "defenseAddedThisVuln";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<bool >::toBinaryStream(&defenseAddedThisVuln, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	return 13;
}

bool DestructibleBuildingDataComponent::readObjectMember(ObjectInputStream* stream, const String& name) {
	if (name == "placementTime") {
		TypeInfo<Time >::parseFromBinaryStream(&placementTime, stream);
		return true;

	} else if (name == "nextVulnerableTime") {
		TypeInfo<Time >::parseFromBinaryStream(&nextVulnerableTime, stream);
		return true;

	} else if (name == "lastResetTime") {
		TypeInfo<Time >::parseFromBinaryStream(&lastResetTime, stream);
		return true;

	} else if (name == "lastVulnerableTime") {
		TypeInfo<Time >::parseFromBinaryStream(&lastVulnerableTime, stream);
		return true;

	} else if (name == "vulnerabilityEndTime") {
		TypeInfo<Time >::parseFromBinaryStream(&vulnerabilityEndTime, stream);
		return true;

	} else if (name == "inRepair") {
		TypeInfo<bool >::parseFromBinaryStream(&inRepair, stream);
		return true;

	} else if (name == "terminalDamaged") {
		TypeInfo<bool >::parseFromBinaryStream(&terminalDamaged, stream);
		return true;

	} else if (name == "intCurrentState") {
		TypeInfo<int >::parseFromBinaryStream(&intCurrentState, stream);
		return true;

	} else if (name == "turretSlots") {
		TypeInfo<Vector<uint64> >::parseFromBinaryStream(&turretSlots, stream);
		return true;

	} else if (name == "minefieldSlots") {
		TypeInfo<Vector<uint64> >::parseFromBinaryStream(&minefieldSlots, stream);
		return true;

	} else if (name == "scannerSlots") {
		TypeInfo<Vector<uint64> >::parseFromBinaryStream(&scannerSlots, stream);
		return true;

	} else if (name == "activeDefenses") {
		TypeInfo<bool >::parseFromBinaryStream(&activeDefenses, stream);
		return true;

	} else if (name == "defenseAddedThisVuln") {
		TypeInfo<bool >::parseFromBinaryStream(&defenseAddedThisVuln, stream);
		return true;
	}

	return false;
}

