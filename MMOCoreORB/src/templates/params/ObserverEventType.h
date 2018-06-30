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
	enum {
		POSITIONCHANGED,			// ManagedObject arg1 = null, long arg2 = 0
		CLOSECONTAINER,				// ManagedObject arg1 = player that closes the container, long arg2 = 0
		POSTURECHANGED,				// ManagedObject arg1 = NULL, long arg2 = new posture
		OBJECTDESTRUCTION,			// ManagedObject arg1 = attacker, long arg2 = condition used when a certain object is destroyed
		OBJECTDISABLED,				// ManagedObject arg1 = attacker, long arg2 = 0
		SAMPLE,						// ManagedObject arg1 = ResourceSpawn, long arg2 = density
		CONVERSE,					// ManagedObject arg1 = converser, long arg2 = 0
		KILLEDCREATURE,				// ManagedObject arg1 = destructedObject, long arg2 = 0 used when a player kills any creature
		OBJECTREMOVEDFROMZONE,		// ManagedObject arg1 = null, long arg2 = 0
		ENTEREDAREA,				// ManagedObject arg1 = obj that entered, long arg2 = 0
		EXITEDAREA,					// ManagedObject arg1 = obj that quit, long arg2 = parentid from which player was removed
		DESTINATIONREACHED,			// ManagedObject arg1 = null, long arg2 = 0
		SPECIALATTACK,				// never notified?
		CALLFORHELP,
		NEWBIETUTORIALZOOMCAMERA, 	// ManagedObject arg1 = null, long arg2 = 0
		CHAT, 						// ManagedObject arg1 = ChatMessage, long arg2 = 0
		NEWBIETUTORIALHOLOCRON,		// ManagedObject arg1 = null, long arg2 = 0
		OBJECTINRANGEMOVED,			// ManagedObject arg1 = MovedObject, long arg2 = 0
		PLAYERCHANGEDTARGET,		// ManagedObject arg1 = newTarget, long arg2 = 0
		STARTCONVERSATION,			// ManagedObject arg1 = playerThatStartedConvo , long arg2 = 0
		SELECTCONVERSATION,			// ManagedObject arg1 = playerThatSelectedConvo , long arg2 = option
		STOPCONVERSATION,			// ManagedObject arg1 = playerThatStoppedConvo , long arg2 = 0
		OPENCONTAINER,				// ManagedObject arg1 = creature that opened container , long arg2 = 0
		NEWBIEOPENINVENTORY,		// ManagedObject arg1 = null, long arg2 = 0
		NEWBIECLOSEINVENTORY,		// ManagedObject arg1 = null, long arg2 = 0
		OBJECTRADIALUSED,			// ManagedObject arg1 = player that used the radial, long arg2 = radial selected id
		DAMAGERECEIVED,				// ManagedObject arg1 = object that is doing the damage, long arg2 = damage did
		OBJECTNAMECHANGED,			// ManagedObject arg1 = object whose name changed, long arg2 = 0
		SURVEY,						// ManagedObject arg1 = ResourceSpawn, long arg2 = density
		GETATTRIBUTESBATCHCOMMAND,	// ManagedObject arg1 = target object arg2 = batch or single
		HEALINGRECEIVED,			// ManagedObject arg1 = object doing healing, long arg2 = amount healed
		STARTCOMBAT,				// ManagedObject arg1 = null, long arg2 = 0
		DEFENDERADDED,				// ManagedObject arg1 = defender, long arg2 = 0
		DEFENDERDROPPED,			// ManagedObject arg1 = defender, long arg2 = 0
		OBJECTRADIALOPENED,			// ManagedObject arg1 = player who opened the radial
		ENTEREDBUILDING,			// ManagedObject arg1 = player who entered the building, long arg2 = 1 if condemned or not allowed in
		EXITEDBUILDING,				// ManagedObject arg1 = player who left building
		PLAYERKILLED,				// ManagedObject arg1 = killer, long arg2 = 0
		PLAYERCLONED,				// ManagedObject arg1 = player, long arg2 = 0
		CRAFTINGASSEMBLY,			// ManagedObject arg1 = player, long arg2 = 0
		CRAFTINGEXPERIMENTATION,	// ManagedObject arg1 = player, long arg2 = 0
		PROTOTYPECREATED,			// ManagedObject arg1 = prototype, long arg2 = 0
		ENHANCINGPERFORMED,			// ManagedObject arg1 = player, long arg2 = enhance amount
		WOUNDHEALINGRECEIVED,		// ManagedObject arg1 = player, long arg2 = wound heal amount
		XPAWARDED,					// ManagedObject arg1 = player, long arg2 = xp amount
		SPICEDOWNERACTIVATED,		// ManagedObject arg1 = player, long arg2 = 0
		FORCEARMOR,					// ManagedObject arg1 = player, long arg2 = damage amount absorbed.
		FORCESHIELD,				// ManagedObject arg1 = player, long arg2 = damage amount absorbed.
		FORCEFEEDBACK,				// ManagedObject arg1 = player, long arg2 = damage amount absorbed.
		FORCEABSORB,				// ManagedObject arg1 = player, long arg2 = force cost of attack
		SPATIALCHATSENT,			// ManagedObject arg1 = ChatMessage containing string text, long arg2 = 0
		OBJECTINSERTED,				// ManagedObject arg1 = inserted object, long arg2 = 0
		OBJECTDISAPPEARED,			// ManagedObject arg1 = disappeared object, long arg2 = 0
		ITEMLOOTED,					// ManagedObject arg1 = looting player, long arg2 = 0
		MEDPACKUSED,				// ManagedObject arg1 = null, long arg2 = 0
		BADGEAWARDED,				// ManagedObject arg1 = player, long arg2 = badge number awarded
		FACTIONBASEFLIPPED,			// ManagedObject arg1 = null, long arg2 = 0
		LOOTCREATURE,				// ManagedObject arg1 = player who is looting, long arg2 = 0, event occurs before looting starts, i.e. it is possible to change loot with this event.
		SCREENPLAYSTATECHANGED,		// ManagedObject arg1 = null, long arg2 = 0
		CREATUREDESPAWNED,			// ManagedObject arg1 = AiAgent that despawned, long arg2 = 0
		AIMESSAGE,					// ManagedObject arg1 = sender of the message (can be any SCNO), long arg2 = message
		STARTENTERTAIN,				// ManagedObject arg1 = player that started entertaining, long arg2 = 0
		CHANGEENTERTAIN,			// ManagedObject arg1 = player that changed entertaining, long arg2 = 0
		STOPENTERTAIN,				// ManagedObject arg1 = player that stopped entertaining, long arg2 = 0
		FLOURISH,					// ManagedObject arg1 = player that performed flourish, long arg2 = flourish id
		CONTAINERCONTENTSCHANGED,	// ManagedObject arg1 = looting player, long arg2 = 0
		WASLISTENEDTO,				// ManagedObject arg1 = player listening, long arg2 = 0
		WASWATCHED,					// ManagedObject arg1 = player watching, long arg2 = 0
		FLEEING,					// ManagedObject arg1 = creature, long arg2 = 0
		PEACE,						// ManagedObject arg1 = null, long arg2 = 0
		PARENTCHANGED,				// ManagedObject arg1 = newParent, long arg2 = 0
		LOGGEDIN,					// ManagedObject arg1 = player, long arg2 = 0
		LOGGEDOUT,					// ManagedObject arg1 = player, long arg2 = 0
		CREATUREREVIVED,			// ManagedObject arg1 = healer (optional), long arg2 = 0
		ZONESWITCHED,				// ManagedObject arg1 = null, long arg2 = 0
		TUNEDCRYSTAL,				// ManagedObject arg1 = crystal, long arg2 = 0
		BHTEFCHANGED,				// ManagedObject arg1 = null, long arg2 = 0
		FACTIONCHANGED,				// ManagedObject arg1 = null, long arg2 = 0
	};
};

#endif /* OBSERVEREVENTTYPES_H_ */
