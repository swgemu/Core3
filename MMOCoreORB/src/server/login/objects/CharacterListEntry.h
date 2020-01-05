/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHARACTERLISTENTRY_H_
#define CHARACTERLISTENTRY_H_

#include "system/lang/Object.h"

class CharacterListEntry : public Object {
private:
	uint64 objectID = 0;
	uint32 accountID = 0;
	uint32 galaxyID = 0;
	String firstName;
	String surName;
	uint32 race = 0;
	uint32 gender = 0;
	Time creationDate;

	String galaxyName;
	String banReason;
	uint32 banAdmin = 0;
	Time banExpiration;

public:
	CharacterListEntry() = default;


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

	const Time& getCreationDate() const {
		return creationDate;
	}

	const String& getFirstName() const {
		return firstName;
	}

	uint32 getGalaxyID() const {
		return galaxyID;
	}

	const String& getGalaxyName() const {
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

	const String& getSurName() const {
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

	String getFullName() const {
		StringBuffer fullName;
		fullName << firstName;

		if(!surName.isEmpty())
			fullName << " " << surName;

		return fullName.toString();
	}


	bool isBanned() const {
		return !banExpiration.isPast();
	}

	void setBanReason(const String& banReason) {
		this->banReason = banReason;
	}

	const String& getBanReason() const {
		return banReason;
	}

	void setBanExpiration(Time banExpiration) {
		this->banExpiration = banExpiration;
	}

	uint32 getBanExpiration() const {
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
