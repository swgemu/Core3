/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef APPLYDISEASECOMMAND_H_
#define APPLYDISEASECOMMAND_H_

#include "DotPackCommand.h"

class ApplyDiseaseCommand : public DotPackCommand {
public:

	ApplyDiseaseCommand(const String& name, ZoneProcessServer* server)
		: DotPackCommand(name, server) {
		skillName = "applydisease";
	}

};

#endif //APPLYDISEASECOMMAND_H_
