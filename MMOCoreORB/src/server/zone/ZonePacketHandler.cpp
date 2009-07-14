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

/*#include "objects.h"
#include "packets.h"*/

#include "ZonePacketHandler.h"

#include "ZoneServer.h"

#include "ZoneClientSession.h"

#include "ZoneProcessServerImplementation.h"

/*#include "Zone.h"

#include "managers/player/PlayerManager.h"
#include "managers/name/NameManager.h"
#include "managers/item/ItemManager.h"
#include "managers/radial/RadialManager.h"
#include "managers/planet/PlanetManager.h"
#include "managers/bazaar/BazaarManager.h"
#include "managers/bazaar/BazaarPlanetManager.h"
#include "managers/sui/SuiManager.h"

#include "objects/terrain/PlanetNames.h"
#include "objects/tangible/terminal/bazaar/RegionBazaar.h"

#include "managers/planet/events/tutorial/TutorialAudioStatMigrationEvent.h"
#include "managers/planet/events/tutorial/TutorialAudioWelcomeEvent.h"

#include "../login/packets/ErrorMessage.h"

#include "../chat/ChatManager.h"
*/


ZonePacketHandler::ZonePacketHandler(const String& s, ZoneProcessServerImplementation* serv) : Logger(s) {
		processServer = serv;

		server = processServer->getZoneServer();
}

void ZonePacketHandler::handleMessage(Message* pack) {
	//info("parsing " + pack->toString());

	/*uint16 opcount = pack->parseShort();
	uint32 opcode = pack->parseInt();

	//System::out << "handleMessage: opcount: " << hex << opcount << dec << " opcode: " << hex << opcode << endl;

	switch (opcount) {
	case 1:
		switch (opcode) {
		case 0x43FD1C22: //CmdSceneReady Zone done loading.
			handleCmdSceneReady(pack);
			break;
		case 0xC1B03B81: //FactionRequestMessage
			handleFactionRequestMessage(pack);
			break;
		case 0xB75DD5D7: //StomachRequestMessage
		    handleStomachRequestMessage(pack);
		    break;
		case 0x9D105AA1: //PlayerMoneyRequest
		    handlePlayerMoneyRequest(pack);
		    break;
		case 0x4C3D2CFA: //ChatRequestRoomList
			handleChatRequestRoomList(pack);
			break;
		case 0x9CA80F98: // AbortTradeMsg
			handleAbortTradeMessage(pack);
			break;
		case 0xB131CA17: // AcceptTransactionMessage
			handleAcceptTransactionMessage(pack);
			break;
		case 0xE81E4382: // UnAcceptTransactionMessage
			handleUnAcceptTransactionMessage(pack);
			break;
		case 0x9AE247EE: // VerifyTradeMessage
			handleVerifyTradeMessage(pack);
			break;
		}

		break;
	case 2:
		switch (opcode) {
		case 0xB5098D76: //SelectCharacter Request/zone insert.
			handleSelectCharacter(pack);
			break;
		case 0x8F251641: //ChatDeletePersistentMessage
			handleDeletePersistentMsg(pack);
			break;
		case 0x81EB4EF7: //GuildRequestMessage
		    handleGuildRequestMessage(pack);
		    break;
		case 0x1E8D1356: // AddItemMessage
			handleAddItemMessage(pack);
			break;
		case 0xD1527EE8: // GiveMoneyMessage
			handleGiveMoneyMessage(pack);
			break;
		case 0xD36EFAE4: //GetAuctionDetails
			handleGetAuctionItemAttributes(pack);
			break;
		case 0xD6D1B6D1: //ClientRandomNameRequest
			handleClientRandomNameRequest(pack);
			break;
		case 0x2E365218: //ConnectPlayerMessage
			handleConnectPlayerMessage(pack);
			break;
		case 0x274F4E78: //NewTicketActivityMessage
			handleNewTicketActivityMessage(pack);
			break;
		case 0xF898E25F: //RequestCategoriesMessage
			handleRequestCategoriesMessage(pack);
			break;
		case 0x0F5D5325: //ClientInactivityMessage
			handleClientInactivityMessage(pack);
			break;
		case 0x48F493C5: //CommoditiesItemTypeListRequest
			handleCommoditiesItemTypeListRequest(pack);
			break;
		}

		break;
	case 3:
		switch (opcode) {
		case 0xD5899226: //	ClientIdMsg
			handleClientPermissionsMessage(pack);
			break;
		case 0x07E3559F: //ChatRequestPersistentMessage
			handleRequestPersistentMsg(pack);
			break;
		case 0x7CA18726:
			handleRadialSelect(pack);
		    break;
		case 0x96405D4D: //Travel Points list
		    handleTravelListRequest(pack);
		    break;
		case 0xBC6BDDF2: // ChatEnterRoomById
			handleChatEnterRoomById(pack);
			break;
		case 0x94B2A77: // ChatDestroyRoom
			handleChatDestroyRoom(pack);
			break;
		case 0x493E3FFA: //  ChatRemoveAvatarFromRoom
			handleChatRemoveAvatarFromRoom(pack);
			break;
		case 0x12B0D449: //RetrieveAuctionItemMessage
			handleRetrieveAuctionItem(pack);
			break;
		case 0xBB8CAD45: // VerifyPlayerNameMessage
			handleVerifyPlayerNameMessage(pack);
			break;
		case 0x5E7B4846: // GetArticleMessage
			handleGetArticleMessage(pack);
			break;
		case 0x962E8B9B: //SearchKnowledgebaseMessage
			handleSearchKnowledgebaseMessage(pack);
			break;
		}

		break;
	case 04:
		switch (opcode) {
		case 0xD5899226:
			handleClientPermissionsMessage(pack);
			break;
		case 0x092D3564: //SuiEventNotification
			handleSuiEventNotification(pack);
			break;
		case 0x91125453: //BidAuctionMessage
			handleBazaarBuy(pack);
			break;
		case 0xC9A5F98D: // GetTicketsMessage
			handleGetTicketsMessage(pack);
			break;
		}
		break;
	case 05:
		switch (opcode) {
		case 0x80CE5E46:
			handleObjectControllerMessage(pack);
			break;
		case 0x84BB21F7: //ChatInstantMessageToCharacter
			handleTellMessage(pack);
			break;
		case 0xD6D1B6D1: //ClientRandomNameRequest
			handleClientRandomNameRequest(pack);
			break;
		case 0x1A7AB839: //GetMapLocationsRequestMessage
			handleGetMapLocationsRequestMessage(pack);
			break;
		case 0x20E4DBE3: //ChatSendToRoom
			handleChatRoomMessage(pack);
			break;
		}

		break;
	case 6:
		switch(opcode) {
		case 0x25A29FA6: //	ChatPersistentMessageToServer
			handleSendMail(pack);
			break;
		}
		break;
	case 7:
		switch (opcode) {
		case 0x35366BED: //ChatCreateRoom
			handleChatCreateRoom(pack);
			break;
		case 0xAD47021D: //CreateAuctionMessage
			handleBazaarAddItem(pack, true);
			break;
		}

		break;
	case 8:
		switch (opcode) {
		case 0x1E9CE308: //CreateImmediateAuctionMessage
			handleBazaarAddItem(pack, false);
			break;
		}
		break;
	case 10:
		switch (opcode) {
		case 0x40E64DAC: //CreateTicketMessage
			handleCreateTicketMessage(pack);
			break;
		}
		break;
	case 12:
		switch (opcode) {
		case 0xB97F3074: //ClientCreateCharacter
			handleClientCreateCharacter(pack);
			break;
		}
		break;
	case 14:
		switch (opcode) {
		case 0x679E0D00: //AuctionQueryHeadersMessage
			handleBazaarScreens(pack);
			break;
		}
		break;
	default:
		//error("unhandled operand count" + pack->toString());
		break;
	}*/
}

