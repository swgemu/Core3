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

#ifndef PACKETS_H_
#define PACKETS_H_

#include "packets/HeartBeat.h"
#include "packets/LinkDeadMessage.h"
#include "packets/BaseLineMessage.h"
#include "packets/DeltaMessage.h"

#include "../login/packets/ErrorMessage.h"

#include "packets/zone/SelectCharacter.h"
#include "packets/zone/ClientIDMessage.h"
#include "packets/zone/ClientLogout.h"
#include "packets/zone/ClientPermissionsMessage.h"
#include "packets/zone/unkByteFlag.h"
#include "packets/zone/ParametersMessage.h"
#include "packets/zone/CmdStartScene.h"
#include "packets/zone/CmdSceneReady.h"
#include "packets/zone/unkZone.h"
#include "packets/zone/unkZoneTwo.h"
#include "packets/zone/unkZoneThree.h"
#include "packets/zone/ConnectionServerTestMessage.h"
#include "packets/zone/ConnectPlayerResponseMessage.h"

#include "packets/object/ObjectControllerMessage.h"
#include "packets/object/CombatAction.h"
#include "packets/object/CombatSpam.h"
#include "packets/object/ShowFlyText.h"
#include "packets/object/CommandQueueEnqueue.h"
#include "packets/object/CommandQueueRemove.h"
#include "packets/object/SpatialChat.h"
#include "packets/object/PostureMessage.h"
#include "packets/object/PlayClientEffectObjectMessage.h"
#include "packets/object/Animation.h"
#include "packets/object/Buffs.h"
#include "packets/object/Emote.h"
#include "packets/object/ObjectMenuResponse.h"
#include "packets/object/StartNpcConversation.h"
#include "packets/object/StopNpcConversation.h"
#include "packets/object/NpcConversationMessage.h"
#include "packets/object/StringList.h"
#include "packets/object/Biography.h"
#include "packets/object/Flourish.h"
#include "packets/object/ImageDesignMessage.h"
#include "packets/object/GenericResponse.h"
#include "packets/object/SitOnObject.h"
#include "packets/object/PlayersNearYou.h"
#include "packets/object/DataTransform.h"
#include "packets/object/DataTransformWithParent.h"
#include "packets/object/StfParameter.h"
#include "packets/object/StartingLocationList.h"

#include "packets/scene/SceneObjectCreateMessage.h"
#include "packets/scene/SceneObjectCloseMessage.h"
#include "packets/scene/UpdateContainmentMessage.h"
#include "packets/scene/UpdateTransformMessage.h"
#include "packets/scene/UpdateTransformWithParentMessage.h"
#include "packets/scene/LightUpdateTransformMessage.h"
#include "packets/scene/LightUpdateTransformWithParentMessage.h"
#include "packets/scene/SceneObjectDestroyMessage.h"
#include "packets/scene/AttributeListMessage.h"
#include "packets/scene/ServerTimeMessage.h"
#include "packets/scene/ServerWeatherMessage.h"
#include "packets/scene/GameSceneChangedMessage.h"
#include "packets/scene/PlayClientEffectLocMessage.h"
#include "packets/scene/ClientOpenContainerMessage.h"
#include "packets/scene/DebugTransformMessage.h"
#include "packets/scene/IsFlattenedTheaterMessage.h"

#include "packets/ship/ShipObjectMessage1.h"
#include "packets/ship/ShipObjectMessage3.h"
#include "packets/ship/ShipObjectMessage4.h"
#include "packets/ship/ShipObjectMessage6.h"

#include "packets/creature/CreatureObjectMessage1.h"
#include "packets/creature/CreatureObjectMessage3.h"
#include "packets/creature/CreatureObjectMessage4.h"
#include "packets/creature/CreatureObjectMessage6.h"
#include "packets/creature/CreatureObjectDeltaMessage1.h"
#include "packets/creature/CreatureObjectDeltaMessage3.h"
#include "packets/creature/CreatureObjectDeltaMessage4.h"
#include "packets/creature/CreatureObjectDeltaMessage6.h"
#include "packets/creature/UpdatePVPStatusMessage.h"

#include "packets/group/GroupObjectMessage3.h"
#include "packets/group/GroupObjectMessage6.h"
#include "packets/group/GroupObjectDeltaMessage6.h"

#include "packets/guild/GuildObjectMessage3.h"
#include "packets/guild/GuildObjectMessage6.h"

#include "packets/player/FactionResponseMessage.h"
#include "packets/player/GetMapLocationsResponseMessage.h"
#include "packets/player/StatMigrationTargetsMessage.h"
#include "packets/player/BadgesResponseMessage.h"
#include "packets/player/CharacterSheetResponseMessage.h"
#include "packets/player/GuildResponseMessage.h"
#include "packets/player/PlayerMoneyResponseMessage.h"
#include "packets/player/EnterTicketPurchaseModeMessage.h"
#include "packets/player/TravelListResponseMessage.h"
#include "packets/player/PlayMusicMessage.h"
#include "packets/player/PlayerObjectMessage3.h"
#include "packets/player/PlayerObjectMessage6.h"
#include "packets/player/PlayerObjectMessage8.h"
#include "packets/player/PlayerObjectMessage9.h"
#include "packets/player/PlayerObjectDeltaMessage3.h"
#include "packets/player/PlayerObjectDeltaMessage6.h"
#include "packets/player/PlayerObjectDeltaMessage8.h"
#include "packets/player/PlayerObjectDeltaMessage9.h"

#include "packets/player/AddFriendInitiateMessage.h"
#include "packets/player/AddFriendMessage.h"
#include "packets/player/FriendStatusChangeMessage.h"
#include "packets/player/FriendListMessage.h"

#include "packets/player/AddIgnoreMessage.h"
#include "packets/player/IgnoreListMessage.h"

#include "packets/player/LogoutMessage.h"
#include "packets/player/NewbieTutorialRequest.h"

#include "packets/tangible/TangibleObjectMessage3.h"
#include "packets/tangible/TangibleObjectMessage6.h"
#include "packets/tangible/TangibleObjectMessage7.h"
#include "packets/tangible/TangibleObjectMessage8.h"
#include "packets/tangible/TangibleObjectMessage9.h"
#include "packets/tangible/TangibleObjectDeltaMessage3.h"
#include "packets/tangible/TangibleObjectDeltaMessage6.h"

#include "packets/tangible/WeaponObjectMessage3.h"

#include "packets/intangible/IntangibleObjectMessage3.h"
#include "packets/intangible/IntangibleObjectMessage6.h"
#include "packets/intangible/IntangibleObjectDeltaMessage3.h"

#include "packets/chat/ChatSystemMessage.h"
#include "packets/chat/ChatInstantMessageToCharacter.h"
#include "packets/chat/ChatInstantMessageToClient.h"
#include "packets/chat/ChatOnSendInstantMessage.h"
#include "packets/chat/ChatOnConnectAvatar.h"
#include "packets/chat/ChatOnSendPersistentMessage.h"
#include "packets/chat/ChatPersistentMessageToClient.h"
#include "packets/chat/ChatRoomList.h"
#include "packets/chat/ChatOnEnteredRoom.h"
#include "packets/chat/ChatOnReceiveRoomInvitation.h"
#include "packets/chat/ChatRoomMessage.h"
#include "packets/chat/ChatOnSendRoomMessage.h"
#include "packets/chat/ChatOnDestroyRoom.h"
#include "packets/chat/ChatOnCreateRoom.h"
#include "packets/chat/ChatOnLeaveRoom.h"
#include "packets/chat/ChatServerStatus.h"

#include "packets/ui/SuiCreatePageMessage.h"
#include "packets/ui/SuiForceClosePage.h"
#include "packets/ui/SearchKnowledgebaseResponseMessage.h"
#include "packets/ui/GetArticleResponseMessage.h"
#include "packets/ui/GetTicketsResponseMessage.h"
#include "packets/ui/AppendCommentsResponseMessage.h"
#include "packets/ui/CancelTicketResponseMessage.h"
#include "packets/ui/CloseHolocronMessage.h"
#include "packets/ui/ConGenericMessage.h"
#include "packets/ui/CreateClientPathMessage.h"
#include "packets/ui/DestroyClientPathMessage.h"
#include "packets/ui/ExecuteConsoleCommand.h"
#include "packets/ui/LaunchBrowserMessage.h"
#include "packets/ui/OpenHolocronToPageMessage.h"
#include "packets/ui/PermissionListCreateMessage.h"
#include "packets/ui/NewbieTutorialEnableHudElement.h"
#include "packets/ui/CreateTicketResponseMessage.h"
#include "packets/ui/ClientMfdStatusUpdateMessage.h"
#include "packets/ui/RequestCategoriesResponseMessage.h"
#include "packets/ui/NewTicketActivityResponseMessage.h"
#include "packets/ui/VerifyPlayerNameResponseMessage.h"
#include "packets/ui/CommoditiesItemTypeListResponse.h"

#include "packets/building/BuildingObjectMessage3.h"
#include "packets/building/BuildingObjectMessage6.h"

#include "packets/cell/CellObjectMessage3.h"
#include "packets/cell/CellObjectMessage6.h"
#include "packets/cell/UpdateCellPermissionsMessage.h"
#include "packets/cell/CellObjectDeltaMessage3.h"

#include "packets/installation/InstallationObjectMessage3.h"
#include "packets/installation/InstallationObjectMessage6.h"
#include "packets/installation/InstallationObjectMessage7.h"
#include "packets/installation/InstallationObjectDeltaMessage3.h"
#include "packets/installation/InstallationObjectDeltaMessage6.h"
#include "packets/installation/InstallationObjectDeltaMessage7.h"
#include "packets/installation/ResourceHarvesterActivatePageMessage.h"
#include "packets/installation/HarvesterResourceDataMessage.h"

#include "packets/player/EnterStructurePlacementModeMessage.h"

//vendor/auction stuff:
//#include "packets/auction/AuctionQueryHeadersResponseMessage.h"
#include "packets/auction/BidAuctionResponseMessage.h"
#include "packets/auction/GetAuctionDetailsResponseMessage.h"
#include "packets/auction/IsVendorOwnerResponseMessage.h"
#include "packets/auction/RetrieveAuctionItemResponseMessage.h"
#include "packets/auction/ItemSoldMessage.h"
#include "packets/auction/BazaarDisplayUI.h"

//Char Creation:
#include "packets/charcreation/ClientCreateCharacter.h"
#include "packets/charcreation/ClientRandomNameResponse.h"
#include "packets/charcreation/ClientCreateCharacterSuccess.h"
#include "packets/charcreation/ClientCreateCharacterFailed.h"

//mission:
#include "packets/mission/MissionObjectMessage3.h"
#include "packets/mission/MissionObjectMessage6.h"
#include "packets/mission/MissionObjectDeltaMessage3.h"
#include "packets/mission/PopulateMissionBrowserMessage.h"

// trade
#include "packets/trade/AbortTradeMessage.h"
#include "packets/trade/AcceptTransactionMessage.h"
#include "packets/trade/UnAcceptTransactionMessage.h"
#include "packets/trade/AddItemMessage.h"
#include "packets/trade/BeginTradeMessage.h"
#include "packets/trade/DenyTradeMessage.h"
#include "packets/trade/TradeCompleteMessage.h"
#include "packets/trade/GiveMoneyMessage.h"

//Resources:
#include "packets/resource/ResourceListForSurveyMessage.h"
#include "packets/resource/SurveyMessage.h"
#include "packets/resource/ResourceContainerObjectMessage3.h"
#include "packets/resource/ResourceContainerObjectMessage6.h"
#include "packets/resource/ResourceContainerObjectMessage8.h"
#include "packets/resource/ResourceContainerObjectMessage9.h"
#include "packets/resource/ResourceContainerObjectDeltaMessage3.h"
#include "packets/resource/ResourceContainerObjectDeltaMessage6.h"

// Schematics - Commenting cause I HATE long compiles
/*#include "packets/manufactureschematic/ManufactureSchematicObjectMessage3.h"
#include "packets/manufactureschematic/ManufactureSchematicObjectMessage6.h"
#include "packets/manufactureschematic/ManufactureSchematicObjectMessage7.h"
#include "packets/manufactureschematic/ManufactureSchematicObjectMessage8.h"
#include "packets/manufactureschematic/ManufactureSchematicObjectMessage9.h"
#include "packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage3.h"
#include "packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage6.h"
#include "packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage7.h"*/

// static objects
#include "packets/static/StaticObjectMessage3.h"
#include "packets/static/StaticObjectMessage6.h"

// Factory Crates
#include "packets/factory/FactoryCrateObjectMessage3.h"
#include "packets/factory/FactoryCrateObjectMessage6.h"

// JTL
#include "packets/jtl/CreateMissileMessage.h"
#include "packets/jtl/CreateNebulaLightningMessage.h"
#include "packets/jtl/CreateProjectileMessage.h"
#include "packets/jtl/DogfightTauntPlayerMessage.h"
#endif /*PACKETS_H_*/
