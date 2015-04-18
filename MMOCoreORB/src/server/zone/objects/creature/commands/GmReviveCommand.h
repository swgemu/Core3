/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef GMREVIVECOMMAND_H_
#define GMREVIVECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GmReviveCommand : public QueueCommand {
public:

	GmReviveCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		try {
			StringTokenizer args(arguments.toString());
			ManagedReference<CreatureObject*> patient = NULL;

			ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(creature->getTargetID());

			PlayerManager* pm = server->getZoneServer()->getPlayerManager();

			if (!args.hasMoreTokens()) { // No arguments passed

				if (object != NULL && (object->isPlayerCreature() || object->isPet())) { // Target is a player or pet, rez target
					patient = cast<CreatureObject*>( object.get());
					revivePatient(creature, patient);

				} else if (object == NULL) { // No target, rez self
					patient = creature;
					revivePatient(creature, patient);

				} else { // Target is not a player or pet
					creature->sendSystemMessage("Syntax: /gmrevive [buff] [ [<name>] | [area [<range>] [imperial | rebel | neutral]] ]");
					return INVALIDTARGET;
				}

			} else { // Has arguments

				String firstArg;
				String firstName = "";
				bool buff = false;
				args.getStringToken(firstArg);

				if (firstArg.toLowerCase() == "buff") { // First argument is buff, get second argument
					buff = true;
					if (args.hasMoreTokens())
						args.getStringToken(firstName);

				} else { // First argument is not buff, must be a name or area
					firstName = firstArg;
				}

				if (firstName != "") { // There's an argument for a name or area

					if (firstName.toLowerCase() == "area") { // Area argument found, check for range argument
						int range = 32;
						String faction = "";

						if (args.hasMoreTokens()) { // Can be range or faction
							String token;
							args.getStringToken(token);

							if (Character::isDigit(token.charAt(0))) { // If the argument is an int, it's range
								for (int i = 0; i < token.length(); i++) {
									if (!Character::isDigit(token.charAt(i)))
										throw Exception();
								}
								range = Integer::valueOf(token);

							} else { // Otherwise it's faction
								faction = token;
							}
						}

						if (range > 50) // We don't want the range to get crazy, so hard caps of 5-50
							range = 50;
						else if (range < 5)
							range = 5;

						if (faction == "" && args.hasMoreTokens()) { // Last argument must be faction
							args.getStringToken(faction);
						}

						SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
						Zone* zone = creature->getZone();

						if (creature->getCloseObjects() == NULL) {
							creature->info("Null closeobjects vector in GmReviveCommand::doQueueCommand", true);
							zone->getInRangeObjects(creature->getPositionX(), creature->getPositionY(), range, &closeObjects, true);
						} else {
							CloseObjectsVector* closeVector = (CloseObjectsVector*) creature->getCloseObjects();
							closeVector->safeCopyTo(closeObjects);
						}

						for (int i = 0; i < closeObjects.size(); ++i) {
							SceneObject* sceneObject = cast<SceneObject*>(closeObjects.get(i).get());

							if ((sceneObject->isPlayerCreature() || sceneObject->isPet()) && creature->isInRange(sceneObject, range)) {
								ManagedReference<CreatureObject*> patientObject = cast<CreatureObject*>(sceneObject);

								if (patientObject != NULL) {
									if (faction == "" || faction.hashCode() == patientObject->getFaction() || (faction == "neutral" && patientObject->getFaction() == 0)) {
										if (buff) {
											Locker clocker(patientObject, creature);

											if (patientObject->isPlayerCreature()) {
												pm->enhanceCharacter(patientObject);
												creature->sendSystemMessage(patientObject->getFirstName() + " has been enhanced.");
											} else if (patientObject->isCreature()) {
												pm->enhanceCharacter(patientObject);
												creature->sendSystemMessage(patientObject->getDisplayedName() + " has been enhanced.");
											}

										} else {
											revivePatient(creature, patientObject);
										}
									}
								}
							}
						}

					} else { // Not area
						patient = server->getZoneServer()->getChatManager()->getPlayer(firstName);

						if (patient != NULL) {
							if (buff) {
								Locker clocker(patient, creature);
								pm->enhanceCharacter(patient);
								creature->sendSystemMessage(patient->getFirstName() + " has been enhanced.");

							} else {
								revivePatient(creature, patient);
							}
						}
					}

				} else if (buff) {  // Buff was the only argument

					if (object != NULL && (object->isPlayerCreature() || object->isPet())) { // Target is a player or pet, buff target
						patient = cast<CreatureObject*>( object.get());
						Locker clocker(patient, creature);

						if (patient->isPlayerCreature()) {
							pm->enhanceCharacter(patient);
							creature->sendSystemMessage(patient->getFirstName() + " has been enhanced.");
						} else if (patient->isCreature()) {
							pm->enhanceCharacter(patient);
							creature->sendSystemMessage(patient->getDisplayedName() + " has been enhanced.");
						}

					} else if (object == NULL) { // No target, buff self
						pm->enhanceCharacter(creature);

					} else { // Target is not a player or pet
						creature->sendSystemMessage("Syntax: /gmrevive [buff] [ [<name>] | [area [<range>] [imperial | rebel | neutral]] ]");
						return INVALIDTARGET;
					}

				} else { // Shouldn't ever end up here
					creature->sendSystemMessage("Syntax: /gmrevive [buff] [ [<name>] | [area [<range>] [imperial | rebel | neutral]] ]");
					return INVALIDTARGET;
				}
			}

		} catch (Exception& e) {
			creature->sendSystemMessage("Syntax: /gmrevive [buff] [ [<name>] | [area [<range>] [imperial | rebel | neutral]] ]");
		}

		return SUCCESS;
	}

	void revivePatient(CreatureObject* creature, CreatureObject* patient) const {
		Locker clocker(patient, creature);

		patient->healDamage(creature, CreatureAttribute::HEALTH, 5000);
		patient->healDamage(creature, CreatureAttribute::ACTION, 5000);
		patient->healDamage(creature, CreatureAttribute::MIND, 5000);

		for (int i = 0; i < 9; ++i) {
			patient->setWounds(i, 0);
		}

		patient->setShockWounds(0);

		patient->clearDots();

		patient->setPosture(CreaturePosture::UPRIGHT);

		patient->broadcastPvpStatusBitmask();
				
		ManagedReference<PlayerObject*> targetGhost = patient->getPlayerObject();

		if (targetGhost != NULL && targetGhost->getJediState() > 1){
			targetGhost->setForcePower(targetGhost->getForcePowerMax());			
		}		

		if (patient->isPlayerCreature()) {
			patient->sendSystemMessage("You have been restored.");
			creature->sendSystemMessage(patient->getFirstName() + " has been restored.");
		} else {
			creature->sendSystemMessage(patient->getDisplayedName() + " has been restored.");
		}
	}
};

#endif //GMREVIVECOMMAND_H_
