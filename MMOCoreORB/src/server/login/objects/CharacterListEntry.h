/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

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
