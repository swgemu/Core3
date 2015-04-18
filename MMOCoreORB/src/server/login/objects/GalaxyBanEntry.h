/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef GALAXYBANENTRY_H_
#define GALAXYBANENTRY_H_

class GalaxyBanEntry : public Object {
private:
	uint32 accountID;
	Time creationDate;
	int galaxyID;
	String banReason;
	uint32 banAdmin;
	Time banExpiration;

public:
	GalaxyBanEntry() {
		galaxyID = 0;
		accountID = banAdmin = 0;
	}

	GalaxyBanEntry(const GalaxyBanEntry& e) : Object() {
		accountID = e.accountID;
		creationDate = e.creationDate;
		galaxyID = e.galaxyID;
		banReason = e.banReason;
		banAdmin = e.banAdmin;
		banExpiration = e.banExpiration;
	}

	GalaxyBanEntry& operator=(const GalaxyBanEntry& e) {
		if (this == &e)
			return *this;

		accountID = e.accountID;
		creationDate = e.creationDate;
		galaxyID = e.galaxyID;
		banReason = e.banReason;
		banAdmin = e.banAdmin;
		banExpiration = e.banExpiration;

		return *this;
	}

	~GalaxyBanEntry() {

	}

	uint32 getAccountID() const {
		return accountID;
	}

	Time getCreationDate() const {
		return creationDate;
	}

	uint32 getGalaxyID() const {
		return galaxyID;
	}

	void setAccountID(uint32 accountID) {
		this->accountID = accountID;
	}

	void setCreationDate(Time creationDate) {
		this->creationDate = creationDate;
	}

	void setGalaxyID(uint32 galaxyID) {
		this->galaxyID = galaxyID;
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


#endif /*GALAXYBANENTRY_H_*/
