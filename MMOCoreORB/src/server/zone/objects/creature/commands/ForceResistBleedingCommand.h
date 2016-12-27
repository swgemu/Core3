/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCERESISTBLEEDINGCOMMAND_H_
#define FORCERESISTBLEEDINGCOMMAND_H_

class ForceResistBleedingCommand : public JediQueueCommand {
public:

	ForceResistBleedingCommand(const String& name, ZoneProcessServer* server)
		: JediQueueCommand(name, server) {

		buffCRC = BuffCRC::JEDI_RESIST_BLEEDING;

		skillMods.put("resistance_bleeding", 25);
		skillMods.put("absorption_bleeding", 25);

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		return doJediSelfBuffCommand(creature);
	}

};

#endif //FORCERESISTBLEEDINGCOMMAND_H_
