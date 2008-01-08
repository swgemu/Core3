#ifndef RESOURCEIMPLEMENTATION_H_
#define RESOURCEIMPLEMENTATION_H_

#include "../../ZoneServer.h"
#include "ResourceManager.h"
#include "ResourceManagerImplementation.h"

class ResourceImplementation {
	string resname, restype, class1, class2, class3, class4, class5, class6,
			class7, container, att1, att2, att3, att4, att5, att6, att7, att8,
			att9, att10, att11;
	
	int att1stat, att2stat, att3stat, att4stat, att5stat, att6stat, att7stat,
			att8stat, att9stat, att10stat, att11stat, maxtype, mintype,
			minpool, maxpool;
	
	uint32 containerCRC;

public:
	ResourceImplementation(const string& inType) {
		restype = inType;
	}

	// setters
	inline void setName(const string& instring) {
		resname = instring;
	}
	
	inline void setClass1(const string& inString) {
		class1 = inString;
	}
	
	inline void setClass2(const string& inString) {
		class2 = inString;
	}
	
	inline void setClass3(const string& inString) {
		class3 = inString;
	}
	
	inline void setClass4(const string& inString) {
		class4 = inString;
	}
	
	inline void setClass5(const string& inString) {
		class5 = inString;
	}
	
	inline void setClass6(const string& inString) {
		class6 = inString;
	}
	
	inline void setClass7(const string& inString) {
		class7 = inString;
	}
	
	inline void setAtt1(const string& inString) {
		att1 = inString;
	}
	
	inline void setAtt2(const string& inString) {
		att2 = inString;
	}
	
	inline void setAtt3(const string& inString) {
		att3 = inString;
	}
	
	inline void setAtt4(const string& inString) {
		att4 = inString;
	}
	
	inline void setAtt5(const string& inString) {
		att5 = inString;
	}
	
	inline void setAtt6(const string& inString) {
		att6 = inString;
	}
	
	inline void setAtt7(const string& inString) {
		att7 = inString;
	}
	
	inline void setAtt8(const string& inString) {
		att8 = inString;
	}
	
	inline void setAtt9(const string& inString) {
		att9 = inString;
	}
	
	inline void setAtt10(const string& inString) {
		att10 = inString;
	}
	
	inline void setAtt11(const string& inString) {
		att11 = inString;
	}
	
	inline void setAtt1Stat(int inInt) {
		att1stat = inInt;
	}
	
	inline void setAtt2Stat(int inInt) {
		att2stat = inInt;
	}
	
	inline void setAtt3Stat(int inInt) {
		att3stat = inInt;
	}
	
	inline void setAtt4Stat(int inInt) {
		att4stat = inInt;
	}
	
	inline void setAtt5Stat(int inInt) {
		att5stat = inInt;
	}
	
	inline void setAtt6Stat(int inInt) {
		att6stat = inInt;
	}
	
	inline void setAtt7Stat(int inInt) {
		att7stat = inInt;
	}
	
	inline void setAtt8Stat(int inInt) {
		att8stat = inInt;
	}
	
	inline void setAtt9Stat(int inInt) {
		att9stat = inInt;
	}
	
	inline void setAtt10Stat(int inInt) {
		att10stat = inInt;
	}
	
	inline void setAtt11Stat(int inInt) {
		att11stat = inInt;
	}
	
	inline void setMaxType(int inInt) {
		maxtype = inInt;
	}
	
	inline void setMinType(int inInt) {
		mintype = inInt;
	}
	
	inline void setMaxPool(int inInt) {
		maxpool = inInt;
	}
	
	inline void setMinPool(int inInt) {
		minpool = inInt;
	}
	
	inline void setContainer(const string& inString) {
		container  = inString;
	}
	
	inline void setContainerCRC(uint32 inCRC) {
		containerCRC = inCRC;
	}

	// getters
	inline const string& getName() {
		return resname;
	}
	
	inline const string& getType() {
		return restype;
	}
	
	inline const string& getClass1() {
		return class1;
	}
	
	inline const string& getClass2() {
		return class2;
	}
	
	inline const string& getClass3() {
		return class3;
	}
	
	inline const string& getClass4() {
		return class4;
	}
	
	inline const string& getClass5() {
		return class5;
	}
	
	inline const string& getClass6() {
		return class6;
	}
	
	inline const string& getClass7() {
		return class7;
	}
	
	inline const string& getAtt1() {
		return att1;
	}
	
	inline const string& getAtt2() {
		return att2;
	}
	
	inline const string& getAtt3() {
		return att3;
	}
	
	inline const string& getAtt4() {
		return att4;
	}
	
	inline const string& getAtt5() {
		return att5;
	}
	
	inline const string& getAtt6() {
		return att6;
	}
	
	inline const string& getAtt7() {
		return att7;
	}
	
	inline const string& getAtt8() {
		return att8;
	}
	
	inline const string& getAtt9() {
		return att9;
	}
	
	inline const string& getAtt10() {
		return att10;
	}
	
	inline const string& getAtt11() {
		return att11;
	}
	
	inline int getAtt1Stat() {
		return att1stat;
	}
	
	inline int getAtt2Stat() {
		return att2stat;
	}
	
	inline int getAtt3Stat() {
		return att3stat;
	}
	
	inline int getAtt4Stat() {
		return att4stat;
	}
	
	inline int getAtt5Stat() {
		return att5stat;
	}
	
	inline int getAtt6Stat() {
		return att6stat;
	}
	
	inline int getAtt7Stat() {
		return att7stat;
	}
	
	inline int getAtt8Stat() {
		return att8stat;
	}
	
	inline int getAtt9Stat() {
		return att9stat;
	}
	
	inline int getAtt10Stat() {
		return att10stat;
	}
	
	inline int getAtt11Stat() {
		return att11stat;
	}
	
	inline int getMaxType() {
		return maxtype;
	}
	
	inline int getMinType() {
		return mintype;
	}
	
	inline int getMaxPool() {
		return maxpool;
	}
	
	inline int getMinPool() {
		return minpool;
	}
	
	inline const string& getContainer() {
		return container;
	}
	
	inline uint32 getContainerCRC() {
		return containerCRC;
	}

};

#endif /*RESOURCEIMPLEMENTATION_H_*/
