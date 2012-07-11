/*
 * ObserverEventTypes.h
 *
 *  Created on: 20/06/2010
 *      Author: victor
 */

#ifndef OBSERVEREVENTTYPES_H_
#define OBSERVEREVENTTYPES_H_

class ObserverEventType {
public:
	const static int POSITIONCHANGED = 1; //ManagedObject arg1 = null, long arg2 = 0
	const static int CLOSECONTAINER = 2; //ManagedObject arg1 = player that closes the container, long arg2 = 0
	const static int POSTURECHANGED = 3; //ManagedObject arg1 = NULL, long arg2 = new posture
	const static int OBJECTDESTRUCTION = 4; //ManagedObject arg1 = attacker, long arg2 = condition used when a certain object is destroyed
	const static int SAMPLE = 5; //ManagedObject arg1 = ResourceSpawn, long arg2 = density
	const static int CONVERSE = 6; //ManagedObject arg1 = converser, long arg2 = 0
	const static int KILLEDCREATURE = 7; //ManagedObject arg1 = destructedObject, long arg2 = 0 used when a player kills any creature
	const static int OBJECTREMOVEDFROMZONE = 8; //ManagedObject arg1 = null, long arg2 = 0
	const static int ENTEREDAREA = 9; //ManagedObject arg1 = obj that entered, long arg2 = 0
	const static int EXITEDAREA = 10; //ManagedObject arg1 = obj that quit, long arg2 = parentid from which player was removed
	const static int DESTINATIONREACHED = 11; //ManagedObject arg1 = null, long arg2 = 0
	const static int SPECIALATTACK = 12; // never notified?
	const static int CALLFORHELP = 13;
	const static int NEWBIETUTORIALZOOMCAMERA = 14; //ManagedObject arg1 = null, long arg2 = 0
	const static int CHAT = 15; //ManagedObject arg1 = ChatMessage, long arg2 = 0
	const static int NEWBIETUTORIALHOLOCRON = 16; //ManagedObject arg1 = null, long arg2 = 0
	const static int OBJECTINRANGEMOVED = 17; //ManagedObject arg1 = MovedObject, long arg2 = 0
	const static int PLAYERCHANGEDTARGET = 18; //ManagedObject arg1 = newTarget, long arg2 = 0
	const static int STARTCONVERSATION = 19; //ManagedObject arg1 = playerThatStartedConvo , long arg2 = 0
	const static int SELECTCONVERSATION = 20; //ManagedObject arg1 = playerThatSelectedConvo , long arg2 = option
	const static int STOPCONVERSATION = 21; //ManagedObject arg1 = playerThatStoppedConvo , long arg2 = 0
	const static int OPENCONTAINER = 22; //ManagedObject arg1 = creature that opened container , long arg2 = 0
	const static int NEWBIEOPENINVENTORY = 23; //ManagedObject arg1 = null, long arg2 = 0
	const static int NEWBIECLOSEINVENTORY = 24; //ManagedObject arg1 = null, long arg2 = 0
	const static int OBJECTRADIALUSED = 25; //ManagedObject arg1 = player that used the radial, long arg2 = radial selected id
	const static int DAMAGERECEIVED = 26; //ManagedObject arg1 = object that is doing the damage, long arg2 = damage did
	const static int OBJECTNAMECHANGED = 27; //ManagedObject arg1 = object whose name changed, long arg2 = 0
	const static int SURVEY = 28; //ManagedObject arg1 = ResourceSpawn, long arg2 = density
	const static int GETATTRIBUTESBATCHCOMMAND = 29; //ManagedObject arg1 = target object arg2 = batch or single
	const static int HEALINGPERFORMED = 30; //ManagedObject arg1 = object doing healing, long arg2 = 0
	const static int STARTCOMBAT = 31; //ManagedObject arg1 = null, long arg2 = 0
	const static int DEFENDERADDED = 32; //ManagedObject arg1 = defender, long arg2 = 0
	const static int DEFENDERDROPPED = 33; //ManagedObject arg1 = defender, long arg2 = 0
	const static int OBJECTRADIALOPENED = 34; // ManagedObject arg1 = player who opened the radial
	const static int ENTEREDBUILDING = 35; // ManagedObject arg1 = player who entered the building, long arg2 = 1 if condemned or not allowed in
	const static int EXITEDBUILDING = 36; // ManagedObject arg1 = player who left building
	const static int PLAYERKILLED = 37; // ManagedObject arg1 = killer, long arg2 = 0
	const static int PLAYERCLONED = 38; // ManagedObject arg1 = player, long arg2 = 0
	const static int CRAFTINGASSEMBLY = 39; // ManagedObject arg1 = player, long arg2 = 0
	const static int CRAFTINGEXPERIMENTATION = 40; // ManagedObject arg1 = player, long arg2 = 0
	const static int ENHANCINGPERFORMED = 41; // ManagedObject arg1 = player, long arg2 = enhance amount
	const static int WOUNDHEALINGPERFORMED = 42; // ManagedObject arg1 = player, long arg2 = wound heal amount
	const static int XPAWARDED = 43; // ManagedObject arg1 = player, long arg2 = xp amount
	const static int SPICEDOWNERACTIVATED = 44; // ManagedObject arg1 = player, long arg2 = 0
	const static int FORCEBUFFHIT = 45; // ManagedObject arg1 = player, long arg2 = damage amount absorbed.
	const static int SPATIALCHATRECEIVED = 46; // ManagedObject arg1 = ChatMessage containing string text, long arg2 = 0
};

#endif /* OBSERVEREVENTTYPES_H_ */
