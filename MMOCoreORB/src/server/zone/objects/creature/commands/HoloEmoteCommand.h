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

#ifndef HOLOEMOTECOMMAND_H_
#define HOLOEMOTECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/packets/scene/PlayClientEventObjectMessage.h"

class HoloEmoteCommand : public QueueCommand {
public:

	HoloEmoteCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if( !creature->isPlayerCreature() )
			return GENERALERROR;

		StringTokenizer args(arguments.toString());
		if( !args.hasMoreTokens() ){
			creature->sendSystemMessage("@image_designer:holoemote_help"); // "Please type '/holoemote help' for valid Holo-Emote names."
			return INVALIDPARAMETERS;
		}

		String arg;
		args.getStringToken(arg);
		if( !isValidArgument( arg ) ){
			creature->sendSystemMessage("@image_designer:holoemote_help"); // "Please type '/holoemote help' for valid Holo-Emote names."
			return INVALIDPARAMETERS;
		}

		if( arg == "help" ){
			// Send help SUI
			handleHelp( creature );
		}
		else if( arg == "delete" ){
			// Delete installed emote
			handleDelete( creature );
		}
		else{
			// Execute emote
			handleEmote( creature, arg );
		}

		return SUCCESS;
	}

	void handleEmote( CreatureObject* player, String& arg ) const {

		PlayerObject* ghost = player->getPlayerObject();
		if( player == NULL )
			return;

		Locker gLocker( ghost, player );

		// "kitty" is an alias for "technokitty"
		if( arg == "kitty" )
			arg = "technokitty";

		// Emote string matches string saved during image design session and the client effect file name
		String emote = "holoemote_" + arg;

		// Check if player has an emote generator
		if( ghost->getInstalledHoloEmote().isEmpty() ){
			player->sendSystemMessage("@image_designer:no_holoemote"); // "You do not own a Holo-Emote generator. Please visit an Image Designer if you wish to purchase one."
			return;
		}

		// Check if player has an emote generator that supports the emote
		if( ghost->getInstalledHoloEmote() != emote && ghost->getInstalledHoloEmote() != "holoemote_all" ){
			player->sendSystemMessage( "Your installed Holo-Emote generator does not support that emote" );
			return;
		}

		// Check emote charges
		if( ghost->getHoloEmoteUseCount() < 1 ){
			player->sendSystemMessage("@image_designer:no_charges_holoemote"); // "You have no charges remaining in your Holo-Emote generator."
			return;
		}

		// Check cooldown
		if( player->getCooldownTimerMap() == NULL || !player->getCooldownTimerMap()->isPast("holoEmoteCooldown") ) {
			player->sendSystemMessage( "Your Holo-Emote generator is in use or recharging" );
			return;
		}

		// Execute client effect
		String emoteEffectPath = "clienteffect/" + emote + ".cef";
		player->playEffect( emoteEffectPath, "head" ); // "head" aux string plays effect on player's head.  Without it, effect would play on their feet

		// Decrement charge
		ghost->decreaseHoloEmoteUseCount();

		// Set cooldown
		player->getCooldownTimerMap()->updateToCurrentAndAddMili("holoEmoteCooldown", 30000); // 30 sec

	}

	void handleHelp( CreatureObject* player ) const {

		PlayerObject* ghost = player->getPlayerObject();
		if( ghost == NULL )
			return;

		Locker gLocker( ghost, player );

		// Check if player has an emote generator
		if( ghost->getInstalledHoloEmote().isEmpty() ){
			player->sendSystemMessage("@image_designer:no_holoemote"); // "You do not own a Holo-Emote generator. Please visit an Image Designer if you wish to purchase one."
			return;
		}

		StringBuffer body;
		String installedHoloEmote = ghost->getInstalledHoloEmote();
		if( installedHoloEmote == "holoemote_all" ){
			body << "Your Holo-Emote generator can play all Holo-Emotes available.\n";
		}
		else{
			body << "Your Holo-Emote generator can only play the " << installedHoloEmote.replaceAll("holoemote_", "") << " Holo-Emote.\n";
		}

		body << "You have " << String::valueOf( ghost->getHoloEmoteUseCount() ) << " charges remaining\n";
		body << "To play a Holo-Emote, type /holoemote <name>.\n";
		body << "To delete your Holo-Emote, type /holoemote delete.\n";
		body << "Purchasing a new Holo-Emote will automatically delete your current Holo-Emote.\n";

		body << "\nThe available Holo-Emote names are:\n\n";

		body << "beehive, blossom, brainstorm, bubblehead\n";
		body << "bullhorns, butterflies, champagne, haunted\n";
		body << "hearts, hologlitter, holonotes, imperial\n";
		body << "kitty, phonytail, rebel, sparky\n";

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::HOLO_EMOTE_HELP);
		box->setPromptTitle("HOLO-EMOTE HELP");
		box->setPromptText(body.toString());
		box->setUsingObject(player);
		box->setForceCloseDisabled();

		ghost->addSuiBox(box);
		player->sendMessage(box->generateMessage());
	}

	void handleDelete( CreatureObject* player ) const {

		PlayerObject* ghost = player->getPlayerObject();
		if( ghost == NULL )
			return;

		Locker gLocker( ghost, player );

		ghost->removeInstalledHoloEmote();
		player->sendSystemMessage("@image_designer:remove_holoemote"); // "You have successfully removed your Holo-Emote generator."

	}

	bool isValidArgument(const String& arg) const {

		if( arg == "help" ||
		    arg == "beehive" ||
		    arg == "blossom" ||
		    arg == "brainstorm" ||
		    arg == "bubblehead" ||
		    arg == "bullhorns" ||
		    arg == "butterflies" ||
		    arg == "champagne" ||
		    arg == "haunted" ||
		    arg == "hearts" ||
		    arg == "hologlitter" ||
		    arg == "holonotes" ||
		    arg == "imperial" ||
		    arg == "technokitty" ||
		    arg == "kitty" ||		// Alias for technokitty
		    arg == "phonytail" ||
		    arg == "rebel" ||
		    arg == "sparky" ||
		    arg == "delete" ){
			return true;
		}

		return false;

	}

};

#endif //HOLOEMOTECOMMAND_H_
