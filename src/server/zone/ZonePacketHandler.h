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

#ifndef ZONEPACKETHANDLER_H_
#define ZONEPACKETHANDLER_H_

#include "engine/engine.h"



namespace server {
namespace zone {

class ZoneProcessServerImplementation;
class ZoneServer;

	class ZonePacketHandler : public Logger {
		ZoneProcessServerImplementation* processServer;

		ZoneServer* server;

	public:
		ZonePacketHandler() : Logger() {
			server = NULL;
		}

		ZonePacketHandler(const String& s, ZoneProcessServerImplementation* serv);

		~ZonePacketHandler() {
		}

		void handleMessage(Message* pack);

		/*void handleClientPermissionsMessage(Message* pack);
		void handleSelectCharacter(Message* pack);
		void handleCmdSceneReady(Message* packet);

		void handleObjectControllerMessage(Message* pack);
		void handleTellMessage(Message* pack);

		void handleClientRandomNameRequest(Message* pack);
		void handleClientCreateCharacter(Message* pack);

		void handleSendMail(Message* pack);
		void handleRequestPersistentMsg(Message* pack);
		void handleDeletePersistentMsg(Message* pack);

		void handleFactionRequestMessage(Message* pack);
		void handleGetMapLocationsRequestMessage(Message* pack);
		void handleStomachRequestMessage(Message* pack);
		void handleGuildRequestMessage(Message* pack);
		void handlePlayerMoneyRequest(Message* pack);

		void handleTravelListRequest(Message* pack);
		void handleRadialSelect(Message* pack);

		void handleChatRoomMessage(Message* pack);
		void handleChatRequestRoomList(Message* pack);

		void handleChatCreateRoom(Message* pack);
		void handleChatEnterRoomById(Message* pack);
		void handleChatDestroyRoom(Message* pack);
		void handleChatRemoveAvatarFromRoom(Message* pack);

		void handleSuiEventNotification(Message* pack);

		void handleAbortTradeMessage(Message* pack);
		void handleAddItemMessage(Message* pack);
		void handleGiveMoneyMessage(Message* pack);
		void handleAcceptTransactionMessage(Message* pack);
		void handleUnAcceptTransactionMessage(Message* pack);
		void handleVerifyTradeMessage(Message* pack);

		void handleBazaarAddItem(Message* pack, bool auction);
		void handleBazaarScreens(Message* pack);
		void handleBazaarBuy(Message* pack);
		void handleRetrieveAuctionItem(Message* pack);
		void handleGetAuctionItemAttributes(Message* pack);

		void handleVerifyPlayerNameMessage(Message* pack);
		void handleConnectPlayerMessage(Message* pack);
		void handleNewbieTutorialResponse(Message* pack);

		void handleGetArticleMessage(Message* pack);
		void handleSearchKnowledgebaseMessage(Message* pack);

		void handleAppendCommentMessage(Message* pack);
		void handleGetCommentsMessage(Message* pack);

		void handleCreateTicketMessage(Message* pack);
		void handleGetTicketsMessage(Message* pack);
		void handleNewTicketActivityMessage(Message* pack);
		void handleRequestCategoriesMessage(Message* pack);

		void handleClientInactivityMessage(Message* pack);

		void handleCommoditiesItemTypeListRequest(Message* pack);*/


	};

	}
}

using namespace server::zone;

#endif /*ZONEPACKETHANDLER_H_*/
