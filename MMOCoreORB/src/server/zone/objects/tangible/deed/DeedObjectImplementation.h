#ifndef DEEDOBJECTIMPLEMENTATION_H_
#define DEEDOBJECTIMPLEMENTATION_H_

#include "../../player/Player.h"
#include "../../../packets.h"
#include "DeedObject.h"

class DeedObjectImplementation : public DeedObjectServant {
protected:
	string targetFile;
	string targetTemplate;
	string targetTempFile;
	unicode targetName;

public:
	// Sub Types


	// Installation
	static const int HARVESTER = 1;
	static const int FACTORY = 2;
	static const int GENERATOR = 3;

	// Not Implemented
	static const int TURRET = 4;
	static const int MINEFIELD = 5;

	// Player City Building Types
	static const int THEATER = 6;
	static const int SHUTTLEPORT = 7;
	static const int HOSPITAL = 8;
	static const int GARDEN = 9;
	static const int BANK = 10;
	static const int CANTINA = 11;
	static const int CITYHALL = 12;
	static const int GARAGE = 13;
	static const int CLONING = 14;


	DeedObjectImplementation(uint64 oid, uint32 tempCRC, const unicode& name, const string& tempname);
	DeedObjectImplementation(CreatureObject* creature, uint32 tempCRC, const unicode& name, const string& tempname);
	DeedObjectImplementation(uint64 oid, uint32 tempCRC, const unicode& name, const string& tempname, int type);
	DeedObjectImplementation(CreatureObject* creature, uint32 tempCRC, const unicode& name, const string& tempname, int type);

	~DeedObjectImplementation();

	void init();

	int useObject(Player * player);

	static int getSubType(uint32 objCRC);

	//inline DeedObject* deploy() {
	//	return (DeedObject*) SceneObjectImplementation::deploy();
	//}

	inline unicode& getTargetName() {
		return targetName;
	}
	inline string& getTargetFile() {
		return targetFile;
	}
	inline string& getTargetTemplate() {
		return targetTemplate;
	}
	inline string& getTargetTempFile() {
		return targetTempFile;
	}
	inline void setTargetFile(string path) {
		targetFile = path;
	}
	inline void setTargetTemplate(string temp) {
		targetTemplate = temp;
	}
private:

};

#endif /*DEEDOBJECTIMPLEMENTATION_H_*/
