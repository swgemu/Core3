local ObjectManager = require("managers.object.object_manager")

CorellianCorvetteScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	buildings = {
		{ faction = "neutral", buildingIds = { 1945494, 1945561, 1945628, 1945695, 1945762, 1945829, 1945896, 1945963, 1946030, 1946097, 1946164, 4335861, 4335928, 4335995, 4336062, 4336129 } },
		{ faction = "imperial", buildingIds = { 1946231, 1946298, 1946365, 1946432, 1946499, 1946566, 1946633, 1946700, 1946767, 1946834, 1946901, 4336196, 4336263, 4336330, 4336397, 4336464 } },
		{ faction = "rebel", buildingIds = { 1946968, 1947035, 1947102, 1947169, 1947236, 1947303, 1947370, 1947437, 1947504, 1947571, 1947638, 4336531, 4336598, 4336665, 4336732, 4336799 } }
	},

	escapePoints = {
		{ faction = "neutral", planet = "tatooine", x = -6150, y = -6350 }, -- TODO find correct coords
		{ faction = "imperial", planet = "naboo", x = 2430, y = -3415 }, -- TODO find correct coords
		{ faction = "rebel", planet = "corellia", x = -6460, y = 5972 },
	},
}

registerScreenPlay("CorellianCorvetteScreenPlay", true)

function CorellianCorvetteScreenPlay:start()
	if (isZoneEnabled("dungeon1")) then
		self:initialize()
	end
end

function CorellianCorvetteScreenPlay:initialize()
	local num = 0
	for i = 1, #self.buildings, 1 do
		local building = self.buildings[i]
		for j = 1, #building.buildingIds, 1 do
			local pCorvette = getSceneObject(building.buildingIds[j])
			if pCorvette ~= nil then
				ObjectManager.withSceneObject(pCorvette, function(corvette)
					if not corvette:isBuildingObject() then
						print("Corvette id isn't a building: " .. building.buildingIds[j])
					else
						writeData("corvetteActive:" .. corvette:getObjectID(), 0)
						self:ejectAllPlayers(pCorvette)
						writeData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID(), 0)
						createObserver(ENTEREDBUILDING, "CorellianCorvetteScreenPlay", "onEnterCorvette", pCorvette)
						createObserver(EXITEDBUILDING, "CorellianCorvetteScreenPlay", "onExitCorvette", pCorvette)
						num = num + 1
					end
				end)
			else
				print("Corvette id isn't valid: " .. building.buildingIds[j])
			end
		end
	end

	print(num .. " corvette buildings initialized.")
end

function CorellianCorvetteScreenPlay:activate(pPlayer, faction, questType)
	if (isZoneEnabled("dungeon1")) then
		local ids = nil
		for i = 1, #self.buildings, 1 do
			if self.buildings[i].faction == faction then
				ids = self.buildings[i].buildingIds
			end
		end

		if ids == nil then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:corellian_corvette_travel_fail") -- The Corellian corvette is currently out of transport range making transportation impossible.
			return 0
		end

		local active = 1
		local corvetteId = 0
		for i = 1, #ids, 1 do
			active = readData("corvetteActive:" .. ids[i])

			if active ~= 1 then
				corvetteId = ids[i]
				break
			end
		end

		if corvetteId ~= 0 then
			writeData(SceneObject(pPlayer):getObjectID() .. "corvetteId", corvetteId)
			writeStringData(SceneObject(pPlayer):getObjectID() .. "questType", questType)
			createEvent(1000, "CorellianCorvetteScreenPlay", "transportPlayer", pPlayer)
			--TODO prompt nearby group members for travel
			return 1

		else
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:corellian_corvette_travel_fail") -- The Corellian corvette is currently out of transport range making transportation impossible.
			return 0
		end
	else
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:unable_to_find_dungeon") -- That area is currently unavailable. Please try again later.
		return 0
	end
end

function CorellianCorvetteScreenPlay:transportPlayer(pPlayer)
	if pPlayer == nil then
		return
	end

	local questType = readStringData(SceneObject(pPlayer):getObjectID() .. "questType")
	local corvetteId = readData(SceneObject(pPlayer):getObjectID() .. "corvetteId")
	local pCorvette = getSceneObject(corvetteId)

	ObjectManager.withBuildingObject(pCorvette, function(corvette)
		self:startQuest(pCorvette, questType)
		local cellId = SceneObject(corvette:getCell(1)):getObjectID()
		SceneObject(pPlayer):switchZone("dungeon1", -42.9, 0, 0.1, cellId)
	end)
end

function CorellianCorvetteScreenPlay:startQuest(pCorvette, questType)
	writeData("corvetteActive:" .. SceneObject(pCorvette):getObjectID(), 1)
	createEvent(5 * 60 * 1000, "CorellianCorvetteScreenPlay", "handleQuestFailure", pCorvette)
	--TODO add timer countdowns
	--TODO spawn quest mobs, scene objects, and objectives
end

function CorellianCorvetteScreenPlay:getBuildingFaction(pCorvette)
	return ObjectManager.withSceneObject(pCorvette, function(corvette)
		if string.find(corvette:getTemplateObjectPath(), "imperial") ~= nil then
			return "imperial"
		elseif string.find(corvette:getTemplateObjectPath(), "rebel") ~= nil then
			return "rebel"
		else
			return "neutral"
		end
	end)
end

function CorellianCorvetteScreenPlay:onEnterCorvette(pCorvette, pPlayer)
	if SceneObject(pPlayer):isPlayerCreature() then
		local active = readData("corvetteActive:" .. SceneObject(pCorvette):getObjectID())
		if active ~= 1 then
			createEvent(10 * 1000, "CorellianCorvetteScreenPlay", "handleNotAuthorized", pPlayer)
			return 0
		end

		local playerCount = readData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID())

		writeData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID(), playerCount + 1)

		if playerCount > 10 then
			createEvent(10 * 1000, "CorellianCorvetteScreenPlay", "handleTooMany", pPlayer)
			return 0
		end
	end

	return 0
end

function CorellianCorvetteScreenPlay:onExitCorvette(pCorvette, pPlayer)
	if SceneObject(pPlayer):isPlayerCreature() then
		local playerCount = readData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID())

		writeData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID(), playerCount - 1)
	end

	return 0
end

function CorellianCorvetteScreenPlay:handleNotAuthorized(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:not_authorized") -- You do not have the proper authorization to be in this area.
	createEvent(2 * 1000, "CorellianCorvetteScreenPlay", "ejectPlayer", pPlayer)
end

function CorellianCorvetteScreenPlay:handleTooMany(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:no_room_remaining") -- There are too many people in this area. Return transportation initiated.
	createEvent(2 * 1000, "CorellianCorvetteScreenPlay", "ejectPlayer", pPlayer)
end

function CorellianCorvetteScreenPlay:handleQuestFailure(pCorvette)
	--TODO reset ticket giver quest
	self:ejectAllPlayers(pCorvette)
	writeData("corvetteActive:" .. SceneObject(pCorvette):getObjectID(), 0)
end

function CorellianCorvetteScreenPlay:ejectAllPlayers(pCorvette)
	ObjectManager.withBuildingObject(pCorvette, function(corvette)
		local playersToEject = {}
		for i = 1, 66, 1 do
			local pCell = corvette:getCell(i)
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)
				if SceneObject(pObject):isPlayerCreature() then
					table.insert(playersToEject, pObject)
				end
			end
		end

		for i = 1, #playersToEject, 1 do
			local pObject = playersToEject[i]
			createEvent(1000, "CorellianCorvetteScreenPlay", "ejectPlayer", pObject)
		end
	end)
end

function CorellianCorvetteScreenPlay:ejectPlayer(pPlayer)
	if pPlayer == nil then
		return 0
	end

	local point = nil

	local pCorvette = SceneObject(SceneObject(pPlayer):getParent()):getParent()

	if pCorvette == nil or not SceneObject(pCorvette):isBuildingObject() then
		print("Error: unable to get corvette in CorellianCorvetteScreenPlay:ejectPlayer")
		return 0
	end

	local faction = self:getBuildingFaction(pCorvette)

	for i = 1, #self.escapePoints, 1 do
		if self.escapePoints[i].faction == faction then
			point = self.escapePoints[i]
		end
	end

	if point == nil then
		print("Error: nil escape point for faction: " .. faction)
		return 0
	end

	if (isZoneEnabled(point.planet)) then
		SceneObject(pPlayer):switchZone(point.planet, point.x, 0, point.y, 0)
		print("Ejecting player " .. SceneObject(pPlayer):getCustomObjectName() .. " from corvette.")
	else
		print("Error: escape zone for corvette transfer is not enabled.")
	end
end
