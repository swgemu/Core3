/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHARACTERLISTENTRY_H_
#define CHARACTERLISTENTRY_H_

class CharacterListEntry : public Object {
private:
	uint64 objectID;
	uint32 accountID;
	uint32 galaxyID;
	String firstName;
	String surName;
	uint32 race;
	uint32 gender;
	Time creationDate;

	String galaxyName;
	String banReason;
	uint32 banAdmin;
	Time banExpiration;

public:
	CharacterListEntry() {
		objectID = accountID = galaxyID = race = gender = banAdmin = 0;
	}

	CharacterListEntry(const CharacterListEntry& e) : Object() {
		objectID = e.objectID;
		accountID = e.accountID;
		galaxyID = e.galaxyID;
		firstName = e.firstName;
		surName = e.surName;
		race = e.race;
		gender = e.gender;
		creationDate = e.creationDate;

		galaxyName = e.galaxyName;
		banReason = e.banReason;
		banAdmin = e.banAdmin;
		banExpiration = e.banExpiration;
	}

	CharacterListEntry& operator=(const CharacterListEntry& e) {
		if (this == &e)
			return *this;

		objectID = e.objectID;
		accountID = e.accountID;
		galaxyID = e.galaxyID;
		firstName = e.firstName;
		surName = e.surName;
		race = e.race;
		gender = e.gender;
		creationDate = e.creationDate;

		galaxyName = e.galaxyName;
		banReason = e.banReason;
		banAdmin = e.banAdmin;
		banExpiration = e.banExpiration;

		return *this;
	}

	~CharacterListEntry() {

	}

	uint32 getAccountID() const {
		return accountID;
	}

	Time getCreationDate() const {
		return creationDate;
	}

	String getFirstName() const {
		return firstName;
	}

	uint32 getGalaxyID() const {
		return galaxyID;
	}

	String getGalaxyName() const {
		return galaxyName;
	}

	uint32 getGender() const {
		return gender;
	}

	uint64 getObjectID() const {
		return objectID;
	}

	uint32 getRace() const {
		return race;
	}

	String getSurName() const {
		return surName;
	}

	void setAccountID(uint32 accountID) {
		this->accountID = accountID;
	}

	void setCreationDate(Time creationDate) {
		this->creationDate = creationDate;
	}

	void setFirstName(String firstName) {
		this->firstName = firstName;
	}

	void setGalaxyName(String galaxyName) {
		this->galaxyName = galaxyName;
	}

	void setGalaxyID(uint32 galaxyID) {
		this->galaxyID = galaxyID;
	}

	void setGender(uint32 gender) {
		this->gender = gender;
	}

	void setObjectID(uint64 objectID) {
		this->objectID = objectID;
	}

	void setRace(uint32 race) {
		this->race = race;
	}

	void setSurName(String surName) {
		this->surName = surName;
	}

	String getFullName() {
		StringBuffer fullName;
		fullName << firstName;
		if(!surName.isEmpty())
			fullName << " " << surName;
		return fullName.toString();
	}


	bool isBanned() {
		return !banExpiration.isPast();
	}

	void setBanReason(String banReason) {
		this->banReason = banReason;
	}

	String getBanReason() const {
		return banReason;
	}

	void setBanExpiration(Time banExpiration) {
		this->banExpiration = banExpiration;
	}

	uint32 getBanExpiration() {
		return banExpiration.getTime();
	}

	void setBanAdmin(uint32 banAdmin) {
		this->banAdmin = banAdmin;
	}

	uint32 getBanAdmin() const {
		return banAdmin;
	}

};


#endif /*CHARACTERLISTENTRY_H_*/
