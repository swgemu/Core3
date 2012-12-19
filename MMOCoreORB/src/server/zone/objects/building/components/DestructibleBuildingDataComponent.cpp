/*
 * DestuctibleBuildingDataComponent.cpp
 *
 *  Created on: Oct 22, 2012
 *      Author: pete
 */
#include "DestructibleBuildingDataComponent.h"
#include "server/zone/managers/gcw/GCWManager.h"

void DestructibleBuildingDataComponent::setState(int state) {

	if ( state >= INVULNERABLE && state <= SHUTDOWNSEQUENCE )
	{	intCurrentState = state;

		if(state > INVULNERABLE)
			bIsVulnerable = true;
		else
			bIsVulnerable = false;

	}
}

void DestructibleBuildingDataComponent::initializeTransientMembers(){

}

bool DestructibleBuildingDataComponent::parseFromBinaryStream(ObjectInputStream* stream){

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

bool DestructibleBuildingDataComponent::toBinaryStream(ObjectOutputStream* stream){

			int _currentOffset = stream->getOffset();
			stream->writeShort(0);
			int _varCount = writeObjectMembers(stream);
			stream->writeShort(_currentOffset, _varCount);

	return true;
}

int DestructibleBuildingDataComponent::writeObjectMembers(ObjectOutputStream* stream){

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

	_name = "repairTime";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Time >::toBinaryStream(&repairTime, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "rebootFinishTime";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Time >::toBinaryStream(&rebootFinishTime, stream);
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

	_name = "sampleMatches";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<int >::toBinaryStream(&sampleMatches, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "switchesTurnedOn";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<int >::toBinaryStream(&switchesTurnedOn, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "powerSwitchesTester";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Vector<bool> >::toBinaryStream(&powerSwitchesTester, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "turretSlots";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Vector<uint64>  >::toBinaryStream(&turretSlots,stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "minefieldSlots";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Vector<uint64>  >::toBinaryStream(&minefieldSlots,stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "scannerSlots";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Vector<uint64>  >::toBinaryStream(&scannerSlots,stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "activeDefenses";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<bool >::toBinaryStream(&activeDefenses, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	_name = "exposed";
	_name.toBinaryStream(stream);
	_offset = stream->getOffset();
	stream->writeInt(0);
	TypeInfo<Vector<bool> >::toBinaryStream(&powerSwitchesTester, stream);
	_totalSize = (uint32) (stream->getOffset() - (_offset + 4));
	stream->writeInt(_offset, _totalSize);

	return 18;


}

bool DestructibleBuildingDataComponent::readObjectMember(ObjectInputStream* stream, const String& name){

	if (name == "placementTime") {
		TypeInfo<Time >::parseFromBinaryStream(&placementTime, stream);
		return true;
	}

	if (name == "nextVulnerableTime"){
		TypeInfo<Time >::parseFromBinaryStream(&nextVulnerableTime, stream);
		return true;
	}
	if (name == "lastResetTime"){
			TypeInfo<Time >::parseFromBinaryStream(&lastResetTime, stream);
			return true;
		}

	if(name == "lastVulnerableTime") {
		TypeInfo<Time >::parseFromBinaryStream(&lastVulnerableTime, stream);
		return true;
	}

	if(name == "vulnerabilityEndTime") {
		TypeInfo<Time >::parseFromBinaryStream(&vulnerabilityEndTime, stream);
		return true;
	}

	if(name == "repairTime") {
		TypeInfo<Time >::parseFromBinaryStream(&repairTime, stream);
		return true;
	}

	if(name == "rebootFinishTime") {
		TypeInfo<Time >::parseFromBinaryStream(&rebootFinishTime, stream);
		return true;
	}

	if (name == "inRepair") {
		TypeInfo<bool >::parseFromBinaryStream(&inRepair, stream);
		return true;
	}

	if (name == "terminalDamaged") {
		TypeInfo<bool >::parseFromBinaryStream(&terminalDamaged, stream);
		return true;
	}

	if (name == "intCurrentState") {
		TypeInfo<int >::parseFromBinaryStream(&intCurrentState, stream);
		return true;
	}

	if (name == "sampleMatches") {
		TypeInfo<int >::parseFromBinaryStream(&sampleMatches, stream);
		return true;
	}
	if (name == "switchesTurnedOn") {
		TypeInfo<int >::parseFromBinaryStream(&switchesTurnedOn, stream);
		return true;
	}

	if ( name == "powerSwitchesTester") {
		TypeInfo<Vector<bool> >::parseFromBinaryStream(&powerSwitchesTester, stream);
		return true;
	}

	if (name == "turretSlots"){
		TypeInfo<Vector<uint64> >::parseFromBinaryStream(&turretSlots, stream);
		return true;
	}

	if (name == "minefieldSlots"){
		TypeInfo<Vector<uint64> >::parseFromBinaryStream(&minefieldSlots, stream);
		return true;
	}

	if (name == "scannerSlots"){
		TypeInfo<Vector<uint64> >::parseFromBinaryStream(&scannerSlots, stream);
		return true;
	}
	if(name == "activeDefenses"){
		TypeInfo<bool>::parseFromBinaryStream(&activeDefenses, stream);
		return true;
	}
	if(name == "exposed"){
		TypeInfo<bool>::parseFromBinaryStream(&exposed, stream);
		return true;
	}


	return false;
}

