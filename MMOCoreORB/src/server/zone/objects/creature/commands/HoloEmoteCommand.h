/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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
