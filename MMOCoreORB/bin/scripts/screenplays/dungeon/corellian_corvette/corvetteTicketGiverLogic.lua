require("screenplays.screenplay")
local ObjectManager = require("managers.object.object_manager")

SIT = 1
STAND = 0
local ticketTemplate = "object/tangible/travel/travel_ticket/dungeon_ticket.iff"

local intelLocationsMap = {
	{ 1, 2, 4 },
	{ 1, 4, 2 },
	{ 2, 1, 4 },
	{ 2, 4, 1 },
	{ 4, 2, 1 },
	{ 4, 1, 2 },
}

CorvetteTicketGiverLogic = ScreenPlay:new {
	numberOfActs = 1,
	npc = {},
	intelMap = {},
	ticketInfo = {},
	giverName = "corvetteTicketGiverLogic",
	faction = 0,
	compensation = {},
	badgeNumber = 0,
	menuComponent = "CorvetteIntelSearchMenuComponent",
}

function CorvetteTicketGiverLogic:start()
	self:spawnNpc()
end

function CorvetteTicketGiverLogic:spawnNpc()
	local npcSpawnData = self.npc
	if not isZoneEnabled(npcSpawnData.planetName) then
		return
	end

	local pNpc = spawnMobile(npcSpawnData.planetName, npcSpawnData.npcTemplate, 1, npcSpawnData.x, npcSpawnData.z, npcSpawnData.y, npcSpawnData.direction, npcSpawnData.cellID)
	if pNpc ~= nil then
		if (npcSpawnData.position == SIT) then
			CreatureObject(pNpc):setState(STATESITTINGONCHAIR)
		end
		if (npcSpawnData.mood ~= nil and npcSpawnData.mood ~= "") then
			CreatureObject(pNpc):setMoodString(npcSpawnData.mood)
		end
	end
end

CorvetteIntelSearchMenuComponent = Object:new {
	ticketGiver = nil
}

function CorvetteIntelSearchMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local activeQuest = getQuestStatus(playerID .. ":activeCorvetteQuest")
	local activeStep = getQuestStatus(playerID .. ":activeCorvetteStep")

	if activeQuest == self.ticketGiver.giverName and activeStep == "1" then
		local menuResponse = LuaObjectMenuResponse(pMenuResponse)

		menuResponse:addRadialMenuItem(20, 3, "@bestine:search_item") -- Search
	end
end

function CorvetteIntelSearchMenuComponent:handleObjectMenuSelect(pContainer, pPlayer, selectedID)
	local player = CreatureObject(pPlayer)
	local playerID = player:getObjectID()
	local activeQuest = getQuestStatus(playerID .. ":activeCorvetteQuest")
	local activeStep = getQuestStatus(playerID .. ":activeCorvetteStep")

	if activeQuest == self.ticketGiver.giverName and activeStep == "1" and selectedID == 20 then
		local intelNumber = self.ticketGiver:getContainersIntelNumber(pPlayer, pContainer)

		if intelNumber == 0 then
			return 0
		end

		local intelAcquired = tonumber(getQuestStatus(playerID .. ":corvetteIntelAcquired"))

		if intelAcquired == nil then
			intelAcquired = 0
		end

		if intelAcquired == 7 or (intelAcquired == 6 and intelNumber ~= 1) or (intelAcquired == 5 and intelNumber ~= 2) or (intelAcquired == 3 and intelNumber ~= 4) or (intelAcquired == 4 and intelNumber == 4) or (intelAcquired == 2 and intelNumber == 2) or (intelAcquired == 1 and intelNumber == 1) then
			player:sendSystemMessage("@bestine:already_searched") -- You've already searched here.
			return 0
		end

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if pInventory == nil then
			return 0
		end

		local intelItem = intelNumber

		if intelItem == 4 then
			intelItem = 3
		end

		local pItem = giveItem(pInventory, self.ticketGiver.intelMap.itemTemplates[intelItem], -1)

		if pItem ~= nil then
			SceneObject(pItem):sendTo(pPlayer)
			player:sendSystemMessage("@bestine:default_receive_msg") -- You search and find something then place it into your inventory.
			setQuestStatus(player:getObjectID() .. ":corvetteIntelAcquired", intelNumber + intelAcquired)
		else
			player:sendSystemMessage("@bestine:inventory_full") -- You find something but have no room in your inventory for it. Try again when you are carrying fewer things.
		end
	end

	return 0
end

function CorvetteTicketGiverLogic:getContainersIntelNumber(pPlayer, pContainer)
	local intelLocs = getQuestStatus(CreatureObject(pPlayer):getObjectID() .. ":corvetteIntelLocs")

	if intelLocs == nil then
		return 0
	end

	local templatePath = SceneObject(pContainer):getTemplateObjectPath()
	local containerNumber = tonumber(string.sub(templatePath, -5, -5))

	if containerNumber == nil or containerNumber == 0 then
		return 0
	end

	local layout = intelLocationsMap[tonumber(intelLocs)]
	return layout[containerNumber]
end

function CorvetteTicketGiverLogic:randomizeIntelLocs(pPlayer)
	local result = getRandomNumber(6)
	setQuestStatus(CreatureObject(pPlayer):getObjectID() .. ":corvetteIntelLocs", result)
end

function CorvetteTicketGiverLogic:hasIntel(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return false
	end

	local templates = self.intelMap.itemTemplates

	for i = 1, # templates do
		local pInvItem = getContainerObjectByTemplate(pInventory, templates[i], true)

		if pInvItem ~= nil then
			return true
		end
	end

	return false
end

function CorvetteTicketGiverLogic:removeDocuments(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return
	end

	local templates = self.intelMap.itemTemplates

	for i = 1, # templates do
		local pInvItem = getContainerObjectByTemplate(pInventory, templates[i], true)

		if pInvItem ~= nil then
			SceneObject(pInvItem):destroyObjectFromWorld()
			SceneObject(pInvItem):destroyObjectFromDatabase()
		end
	end

	local pInvItem = getContainerObjectByTemplate(pInventory, ticketTemplate, true)

	if pInvItem ~= nil then
		SceneObject(pInvItem):destroyObjectFromWorld()
		SceneObject(pInvItem):destroyObjectFromDatabase()
	end
end

function CorvetteTicketGiverLogic:removeIntel(pPlayer, intelNumber)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return
	end

	local templates = self.intelMap.itemTemplates
	local pInvItem = getContainerObjectByTemplate(pInventory, templates[intelNumber], true)

	if pInvItem ~= nil then
		SceneObject(pInvItem):destroyObjectFromWorld()
		SceneObject(pInvItem):destroyObjectFromDatabase()
	end
end

function CorvetteTicketGiverLogic:giveCompensation(pPlayer)
	if (pPlayer == nil) then
		return
	end

	for i = 1, #self.compensation do
		local comp = self.compensation[i]

		if comp.compType == "credits" then
			local amount = (comp.amount / 2) + getRandomNumber(comp.amount)
			ThemeParkLogic:giveCredits(pPlayer, amount)
			CreatureObject(pPlayer):sendSystemMessageWithDI("@new_player:credits_reward", amount)
		elseif comp.compType == "faction" then
			ThemeParkLogic:giveFaction(pPlayer, comp.faction, comp.amount)
		end
	end
end

function CorvetteTicketGiverLogic:giveTicket(pPlayer)
	local player = CreatureObject(pPlayer)
	local pInventory = player:getSlottedObject("inventory")

	if pInventory == nil then
		return
	end

	local pItem = giveItem(pInventory, ticketTemplate, -1)

	if pItem ~= nil then
		local ticket = LuaTicketObject(pItem)
		ticket:setDeparturePlanet(self.ticketInfo.depPlanet)
		ticket:setDeparturePoint(self.ticketInfo.faction)
		ticket:setArrivalPlanet(self.ticketInfo.missionType)
		ticket:setArrivalPoint(self.ticketInfo.faction)
		ticket:setOwnerID(SceneObject(pPlayer):getObjectID())
		SceneObject(pItem):sendTo(pPlayer)
		createObserver(OBJECTREMOVEDFROMZONE, "CorvetteTicketGiverLogic", "notifyTicketDestroyed", pItem, 1)
	end
end

function CorvetteTicketGiverLogic:notifyTicketDestroyed(pTicket)
	if (pTicket == nil) then
		return 1
	end

	local ticket = LuaTicketObject(pTicket)
	local ownerID = ticket:getOwnerID()

	removeQuestStatus(ownerID .. ":activeCorvetteQuest")
	removeQuestStatus(ownerID .. ":activeCorvetteStep")
	removeQuestStatus(ownerID .. ":activeCorvetteQuestType")

	return 1
end

function CorvetteTicketGiverLogic:hasTicket(pPlayer)
	local player = CreatureObject(pPlayer)
	local activeQuest = getQuestStatus(player:getObjectID() .. ":activeCorvetteQuest")
	local pInventory = player:getSlottedObject("inventory")

	if pInventory == nil then
		return false
	end

	local pItem = getContainerObjectByTemplate(pInventory, ticketTemplate, true)
	local ticket = LuaTicketObject(pItem)

	return pItem ~= nil and activeQuest == self.giverName
end

function CorvetteTicketGiverLogic:hasDocuments(pPlayer)
	local player = CreatureObject(pPlayer)
	local pInventory = player:getSlottedObject("inventory")

	if pInventory == nil then
		return false
	end

	local templates = self.intelMap.itemTemplates

	return getContainerObjectByTemplate(pInventory, templates[1], true) or getContainerObjectByTemplate(pInventory, templates[2], true) or getContainerObjectByTemplate(pInventory, templates[3], true)
end

function CorvetteTicketGiverLogic:giveReward(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return
	end

	local pItem = giveItem(pInventory, "object/tangible/loot/loot_schematic/corellian_corvette_landspeeder_av21_schematic.iff", -1)

	if pItem ~= nil then
		SceneObject(pItem):sendTo(pPlayer)
	end
end
