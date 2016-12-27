/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCERESISTPOISONCOMMAND_H_
#define FORCERESISTPOISONCOMMAND_H_

class ForceResistPoisonCommand : public JediQueueCommand {
public:

	ForceResistPoisonCommand(const String& name, ZoneProcessServer* server)
		: JediQueueCommand(name, server) {

		buffCRC = BuffCRC::JEDI_RESIST_POISON;

		skillMods.put("resistance_poison", 25);
		skillMods.put("absorption_poison", 25);

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		return doJediSelfBuffCommand(creature);
	}

};

#endif //FORCERESISTPOISONCOMMAND_H_
