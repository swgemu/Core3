require("screenplays.screenplay")
local ObjectManager = require("managers.object.object_manager")

FACTIONIMPERIAL = 0xDB4ACC54
FACTIONREBEL = 0x16148850
SIT = 1
STAND = 0
local ticketTemplate = "object/tangible/travel/travel_ticket/dungeon_ticket.iff"
local rewardSchematic = "object/tangible/loot/loot_schematic/corellian_corvette_landspeeder_av21_schematic.iff"

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
	menuComponent = "IntelSearchMenuComponent",
}

function CorvetteTicketGiverLogic:start()
	self:spawnNpc()
	self:setupComponents()
end

function CorvetteTicketGiverLogic:spawnNpc()
	local npcSpawnData = self.npc
	if isZoneEnabled(npcSpawnData.planetName) then
		local pNpc = spawnMobile(npcSpawnData.planetName, npcSpawnData.npcTemplate, 1, npcSpawnData.x, npcSpawnData.z, npcSpawnData.y, npcSpawnData.direction, npcSpawnData.cellID)
		if pNpc ~= nil and npcSpawnData.position == SIT then
			CreatureObject(pNpc):setState(STATESITTINGONCHAIR)
		end
		if (npcSpawnData.mood ~= nil and npcSpawnData.mood ~= "") then
			CreatureObject(pNpc):setMoodString(npcSpawnData.mood)
		end
	end
end

IntelSearchMenuComponent = Object:new {
	ticketGiver = nil
}

function IntelSearchMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local player = CreatureObject(pPlayer)
	local activeQuest = getQuestStatus(player:getObjectID() .. ":activeCorvetteQuest")
	local activeStep = getQuestStatus(player:getObjectID() .. ":activeCorvetteStep")

	if activeQuest == self.ticketGiver.giverName and activeStep == "1" then
		local menuResponse = LuaObjectMenuResponse(pMenuResponse)

		menuResponse:addRadialMenuItem(20, 3, "@bestine:search_item") -- Search
	end
end

function IntelSearchMenuComponent:handleObjectMenuSelect(pContainer, pPlayer, selectedID)
	local player = CreatureObject(pPlayer)
	local activeQuest = getQuestStatus(player:getObjectID() .. ":activeCorvetteQuest")
	local activeStep = getQuestStatus(player:getObjectID() .. ":activeCorvetteStep")

	if activeQuest == self.ticketGiver.giverName and activeStep == "1" and selectedID == 20 then
		local intelNumber = self.ticketGiver:getContainersIntelNumber(pPlayer, pContainer)
		if intelNumber == 0 then
			return 0
		end

		local intelAcquired = tonumber(getQuestStatus(player:getObjectID() .. ":corvetteIntelAcquired"))
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

function CorvetteTicketGiverLogic:setupComponents()
	local containers = self.intelMap.containerIds

	for i = 1, # containers do
		local pContainer = getSceneObject(containers[i])
		if pContainer ~= nil then
			SceneObject(pContainer):setObjectMenuComponent(self.menuComponent)
		end
	end
end

function CorvetteTicketGiverLogic:getContainersIntelNumber(pPlayer, pContainer)
	local intelLocs = getQuestStatus(CreatureObject(pPlayer):getObjectID() .. ":corvetteIntelLocs")

	if intelLocs == nil then
		return 0
	end

	local containers = self.intelMap.containerIds
	local containerNumber = 0

	for i = 1, # containers do
		if containers[i] == SceneObject(pContainer):getObjectID() then
			containerNumber = i
		end
	end

	if containerNumber == 0 then
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
	for i = 1, # self.compensation do
		local comp = self.compensation[i]
		ObjectManager.withCreatureAndPlayerObject(pPlayer, function(creature, player)
			if comp.compType == "credits" then
				local amount = (comp.amount / 2) + getRandomNumber(comp.amount)
				creature:addCashCredits(amount, true)
				creature:sendSystemMessageWithDI("@new_player:credits_reward", amount)
			elseif comp.compType == "faction" then
				player:increaseFactionStanding(faction, comp.amount)
			end
		end)
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
		SceneObject(pItem):sendTo(pPlayer)
		setQuestStatus(player:getObjectID() .. ":activeCorvetteQuestType", self.ticketInfo.missionType)
	end
end

function CorvetteTicketGiverLogic:giveReward(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory == nil then
		return
	end

	local pItem = giveItem(pInventory, rewardSchematic, -1)
	if pItem ~= nil then
		SceneObject(pItem):sendTo(pPlayer)
	end
end
