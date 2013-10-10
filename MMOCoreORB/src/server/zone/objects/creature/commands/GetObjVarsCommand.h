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

#ifndef GETOBJVARSCOMMAND_H_
#define GETOBJVARSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GetObjVarsCommand : public QueueCommand {
public:

	GetObjVarsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if ( creature != NULL  )
			{
				uint64 objectID = 0;
				UnicodeTokenizer tokenizer(arguments);
				tokenizer.setDelimeter(" ");

				// if we have an argument passed, use it
				if (tokenizer.hasMoreTokens())
				{	try {
						objectID = tokenizer.getLongToken();
					} catch ( Exception& err ) {
						creature->sendSystemMessage("INVALID OBJECT.  Please specify a valid object name or objectid");
						return INVALIDPARAMETERS;

					}
				} else {
					objectID = target;
				}

				if ( objectID == 0 ){
					creature->sendSystemMessage("You need to target an object or specify an object id: /getobjvars <objectID> ");
				}

				ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(objectID, false);

				if ( object == NULL){
					creature->sendSystemMessage("ERROR GETTIGN OBJECT - NULL" + String::valueOf(target));
				} else {

					String strClassName = object->getObjectNameStringIdName();
					String strDescription = object->getDetailedDescription();
					bool bMarkedForDelete = object->_isMarkedForDeletion();
					bool bIsUpdated = object->_isUpdated();
					int rCount = object.get()->getReferenceCount();
					uint64 parentID = object->getParentID();
					StringBuffer msg;
					msg << endl << "OBJECTID: " << String::valueOf(objectID) << endl;
					msg << "OBJECTTYPE: " << String::valueOf(object->getGameObjectType()) << endl;

					if(object->isCreatureObject()){
						msg << "Creature First Name: " << object.castTo<CreatureObject*>()->getFirstName() << endl;
					}

					msg << "CLASS: " << strClassName << endl;
					msg << "Marked for deletion: " << String::valueOf(bMarkedForDelete) << endl;
					msg << "IsUpdated: " <<  String::valueOf(bIsUpdated) << endl;
					msg << "REFERENCE COUNT " << String::valueOf(rCount) << endl;
					msg << "Path: " << object->getObjectTemplate()->getFullTemplateString() << endl;
					msg << "Children: " << String::valueOf(object->getChildObjects()->size()) << endl;
					msg << "PARENT OBJECTID: " << String::valueOf(parentID) << endl;
					if(object->getZone() != NULL)
						msg << "location: " << String::valueOf(object->getPositionX()) << " "  << String::valueOf(object->getPositionY()) << " " << object->getZone()->getZoneName();

					creature->sendSystemMessage(msg.toString());
				}
			}
		return SUCCESS;

	}

};

#endif //GETOBJVARSCOMMAND_H_
