/*
 * DroidMaintenanceSessionRunMenuSuiCallback.h
 *
 */

#ifndef DROIDMAINTSESSIONRUNMENUSUICALLBACK_H_
#define DROIDMAINTSESSIONRUNMENUSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/DroidMaintenanceSession.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sessions/DroidMaintenanceSession.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/structure/StructureObject.h"

class DroidMaintenanceSessionRunMenuSuiCallback : public SuiCallback {
public:
	DroidMaintenanceSessionRunMenuSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::DROIDMAINTENANCERUN);
		ManagedReference<DroidMaintenanceSession*> session = dynamic_cast<DroidMaintenanceSession*>(facade.get());

		if (session == NULL) {
			player->dropActiveSession(SessionFacadeType::DROIDMAINTENANCERUN);
			return;
		}

		if (!suiBox->isListBox() || args->size() < 2  || cancelPressed) {
			session->cancelSession();
			return;
		}

		if (args->size() < 2)
			return;

		bool otherPressed = !Bool::valueOf(args->get(0).toString());

		if (otherPressed) {
			session->performMaintenanceRun();
			return;
		} else {
			uint64 idx = Long::unsignedvalueOf(args->get(1).toString());
			SuiListBox* suiListBox = cast<SuiListBox*>( suiBox);
			if (idx == -1) {
				session->sendMaintenanceTransferBox();
				return;
			}
			uint64 itemId = suiListBox->getMenuObjectID(idx);
			// lookup structure
			StructureObject* stobject = NULL;
			ManagedReference<SceneObject*> structure = player->getZoneServer()->getObject(itemId);
			if( structure != NULL && structure->isStructureObject() ) {
				stobject = cast<StructureObject*>(structure.get());
				if (stobject != NULL) {
					session->setSelectedStructure(stobject);
					session->sendMaintenanceTransferBox();
				} else {
					player->sendSystemMessage("@pet/droid_modules:droid_maint_data_error");
					return;
				}
			} else {
				player->sendSystemMessage("@pet/droid_modules:droid_maint_data_error");
				return;
			}
		}

		//int idx = Integer::valueOf(args->get(0).toString());

		//SuiListBox* box = cast<SuiListBox*>( suiBox);

		//byte menuID = box->getMenuObjectID(idx);

		//session->handleMenuSelect(player, menuID, box);

	}
};

#endif /* DROIDMAINTSESSIONRUNMENUSUICALLBACK_H_ */
