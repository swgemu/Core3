/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.caught in ChracterList query" << endl;
		}

		if (characters == NULL)
			return;

		while(characters->next()) {

			CharacterListEntry newEntry;
			newEntry.setObjectID(characters->getUnsignedLong(0));
			newEntry.setAccountID(characters->getUnsignedInt(1));
			newEntry.setGalaxyID(characters->getInt(2));
			newEntry.setFirstName(characters->getString(3));
			newEntry.setSurName(characters->getString(4));

			String race = characters->getString(7);
			newEntry.setRace(race.hashCode());
			Time createdTime(characters->getUnsignedInt(8));
			newEntry.setCreationDate(createdTime);
			newEntry.setGalaxyName(characters->getString(9));

			newEntry.setBanReason(characters->getString(10));
			Time expireTime(characters->getUnsignedInt(11));
			newEntry.setBanExpiration(expireTime);
			newEntry.setBanAdmin(characters->getUnsignedInt(12));

			add(newEntry);
		}
	}
};

#endif /*CHARACTERLIST_H_*/
