local ObjectManager = require("managers.object.object_manager")

HeroOfTatooineScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	courageSpawns = { { -861, 4557 }, { -159, 5040 }, { -1264, 5379 }, { -695, 4506 }, { 16, 4068 }, { -533, 4314 }, { -1023, 5214 }, { -318, 4477 }, { -443, 4970 },
		{ -1183, 4647 }, { -575, 4985 }, { -1618, 5272 }, { -97, 5025 }, { -471, 4715 }, { -991, 5887 }, { -998, 5240 }, { -500, 4600 }, { -1131, 6185 } },

	altruismSpawns = { { 2123, 1291 }, { 2470, 1394 }, { 2511, 1357 }, { 2439, 1294 }, { 3196, 1272 }, { 3303, 1107 }, { 2123, 1291 }, { 2494, 1714 }, { 2545, 1741 },
		{ 2778, 1507 }, { 5100, 800 }, { 2168, 1293 }, { 2488, 1676 }, { 3640, -44 }, { 1839, 966 }, { 2570, 1164 }, { 2478, 687 }, { 1003, 1240 }, { 2560, 1324 }, { 2437, 1421 } },

}

registerScreenPlay("HeroOfTatooineScreenPlay", true)

function HeroOfTatooineScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:initEvents()

		local pAltCave = getSceneObject(5995564)
		createObserver(ENTEREDBUILDING, "HeroOfTatooineScreenPlay", "onEnteredAltruismCave", pAltCave)
		createObserver(EXITEDBUILDING, "HeroOfTatooineScreenPlay", "onExitedAltruismCave", pAltCave)
	end
end

function HeroOfTatooineScreenPlay:spawnMobiles()
	local pHermit = spawnMobile("tatooine", "hero_of_tat_hermit",0,36.5,-69,-103.7,0,7125586)
	writeData("hero_of_tat:hermit_id", SceneObject(pHermit):getObjectID())
end

function HeroOfTatooineScreenPlay:getEventChangeTime()
	return getRandomNumber(20, 30) * 60 * 1000 -- 20-30 minutes
end

function HeroOfTatooineScreenPlay:spawnAltruismObjects()
	local pCrate = spawnSceneObject("tatooine", "object/tangible/item/quest/hero_of_tatooine/explosives_crate.iff", 76.87,-46.24,-136.9, 5995575, .985, 0, .1714, 0)

	if (pCrate ~= nil) then
		writeData("hero_of_tat:altruismCrate", SceneObject(pCrate):getObjectID())
		SceneObject(pCrate):setObjectMenuComponent("explosivesCrateMenuComponent")
	end

	local pWall = spawnSceneObject("tatooine", "object/static/structure/general/cave_wall_damprock_style_01.iff", 162.5,-66.8,-97.7, 5995573, 0, 0, 0, 0)

	if (pWall ~= nil) then
		writeData("hero_of_tat:altruismWall", SceneObject(pWall):getObjectID())
	end

	local pCrevice = spawnSceneObject("tatooine", "object/tangible/container/quest/hero_of_tatooine/rock_crevice.iff", 156.767,-66.46,-93.84, 5995572, 0.95, 0, 0, 0)

	if (pCrevice ~= nil) then
		writeData("hero_of_tat:altruismCrevice", SceneObject(pCrevice):getObjectID())
		SceneObject(pCrevice):setContainerComponent("heroOfTatooineRockCrevice")
	end

	local pWife = spawnMobile("tatooine", "hero_of_tat_farmers_wife", 0, 190.8, -66.6, -104.6, -70, 5995573)
	CreatureObject(pWife):setPvpStatusBitmask(0)
	writeData("hero_of_tat:farmerWifeId", SceneObject(pWife):getObjectID())
	local pDaughter = spawnMobile("tatooine", "hero_of_tat_farmers_child", 0, 192.1, -66.8, -105.9, -70, 5995573)
	CreatureObject(pDaughter):setPvpStatusBitmask(0)
	writeData("hero_of_tat:farmerChildId", SceneObject(pDaughter):getObjectID())
end

function HeroOfTatooineScreenPlay:initEvents()
	if (not hasServerEvent("HeroOfTatCourage")) then
		self:createCourageEvent()
	end
	if (not hasServerEvent("HeroOfTatAltruism")) then
		self:createAltruismEvent()
	end
end

function HeroOfTatooineScreenPlay:createCourageEvent()
	createServerEvent(self:getEventChangeTime(), "HeroOfTatooineScreenPlay", "doCourageChange", "HeroOfTatCourage")
end

function HeroOfTatooineScreenPlay:createAltruismEvent()
	createServerEvent(self:getEventChangeTime(), "HeroOfTatooineScreenPlay", "doAltruismChange", "HeroOfTatAltruism")
end

function HeroOfTatooineScreenPlay:doCourageChange()
	if (not isZoneEnabled("tatooine")) then
		return 0
	end

	local hermitId = readData("hero_of_tat:hermit_id")
	local pHermit = getSceneObject(hermitId)

	if (pHermit == nil) then
		printf("Error in HeroOfTatooineScreenPlay, unable to find hermit object.\n")
		return 0
	end

	local mobId = readData("hero_of_tat:courage_mob_id")
	local mobLoc = readData("hero_of_tat:courage_mob_loc")
	local pCourageMob

	if (mobId ~= 0) then
		pCourageMob = getSceneObject(mobId)
	end

	-- Reschedule respawn if boar is in combat or dead
	if (pCourageMob ~= nil and (AiAgent(pCourageMob):isInCombat() or CreatureObject(pCourageMob):isDead())) then
		self:createCourageEvent()
		return 0
	elseif (pCourageMob ~= nil) then
		SceneObject(pCourageMob):destroyObjectFromWorld()
	end

	local newLoc = getRandomNumber(1, table.getn(self.courageSpawns))

	if (newLoc == mobLoc) then
		if (newLoc == table.getn(self.courageSpawns)) then
			newLoc = newLoc - 1
		else
			newLoc = newLoc + 1
		end
	end

	writeData("hero_of_tat:courage_mob_loc", newLoc)

	local z = getTerrainHeight(pHermit, self.courageSpawns[newLoc][1], self.courageSpawns[newLoc][2])
	local pBoar = spawnMobile("tatooine", "wild_bladeback_boar", 0, self.courageSpawns[newLoc][1], z, self.courageSpawns[newLoc][2], getRandomNumber(360) - 180, 0)

	if (pBoar ~= nil) then
		createObserver(OBJECTDESTRUCTION, "HeroOfTatooineScreenPlay", "notifyDefeatedBoar", pBoar)
		writeData("hero_of_tat:courage_mob_id", SceneObject(pBoar):getObjectID())
	else
		printf("Error in HeroOfTatooineScreenPlay:doCourageChange, unable to spawn boar.\n")
	end

	self:createCourageEvent()
end

function HeroOfTatooineScreenPlay:notifyDefeatedBoar(pVictim, pAttacker)
	if (CreatureObject(pAttacker):hasScreenPlayState(2, "hero_of_tatooine") ~= 1 or CreatureObject(pAttacker):hasScreenPlayState(16, "hero_of_tatooine") == 1) then
		if (CreatureObject(pAttacker):hasScreenPlayState(16, "hero_of_tatooine") == 1) then
			CreatureObject(pAttacker):sendSystemMessage("@quest/hero_of_tatooine/system_messages:courage_already_have_mark")
		end
		self:clearInventory(pVictim)
		return 0
	end

	local pInventory = CreatureObject(pVictim):getSlottedObject("inventory")

	if pInventory == nil then
		return 0
	end

	if (SceneObject(pInventory):getContainerObjectsSize() > 0) then
		local pItem = SceneObject(pInventory):getContainerObject(0)

		if pItem ~= nil then
			local item = SceneObject(pItem)
			createObserver(ITEMLOOTED, "HeroOfTatooineScreenPlay", "notifyMarkOfCourageLooted", pItem)
		end
		CreatureObject(pAttacker):sendSystemMessage("@quest/hero_of_tatooine/system_messages:courage_notice_object")
	end
end

function HeroOfTatooineScreenPlay:clearInventory(pCreature)
	ObjectManager.withCreatureObject(pCreature, function(creature)
		local pInventory = creature:getSlottedObject("inventory")

		if pInventory == nil then
			return 0
		end
		ObjectManager.withSceneObject(pInventory, function(inventory)
			local numberOfItems = inventory:getContainerObjectsSize()
			for i = 0, numberOfItems - 1, 1 do
				local pItem = inventory:getContainerObject(0)
				SceneObject(pItem):destroyObjectFromWorld()
				SceneObject(pItem):destroyObjectFromDatabase()
			end
		end)
	end)
end

function HeroOfTatooineScreenPlay:notifyMarkOfCourageLooted(pItem, pLooter)
	if pItem == nil or pLooter == nil then
		return 0
	end

	ObjectManager.withCreatureAndPlayerObject(pLooter, function(player, playerObject)
		playerObject:awardBadge(7)
		player:setScreenPlayState(16, "hero_of_tatooine")
	end)
end

function HeroOfTatooineScreenPlay:doAltruismChange()
	if (not isZoneEnabled("tatooine")) then
		return 0
	end

	local hermitId = readData("hero_of_tat:hermit_id")
	local pHermit = getSceneObject(hermitId)

	if (pHermit == nil) then
		printf("Error in HeroOfTatooineScreenPlay, unable to find hermit object.\n")
		return 0
	end

	local mobId = readData("hero_of_tat:altruism_mob_id")
	local mobLoc = readData("hero_of_tat:altruism_mob_loc")
	local pFarmer

	if (mobId ~= 0) then
		pFarmer = getSceneObject(mobId)
	end

	if (pFarmer ~= nil) then
		SceneObject(pFarmer):destroyObjectFromWorld()
	end

	local newLoc = getRandomNumber(1, table.getn(self.altruismSpawns))

	if (newLoc == mobLoc) then
		if (newLoc == table.getn(self.altruismSpawns)) then
			newLoc = newLoc - 1
		else
			newLoc = newLoc + 1
		end
	end

	writeData("hero_of_tat:altruism_mob_loc", newLoc)

	local z = getTerrainHeight(pHermit, self.altruismSpawns[newLoc][1], self.altruismSpawns[newLoc][2])
	local pFarmer = spawnMobile("tatooine", "hero_of_tat_farmer", 0, self.altruismSpawns[newLoc][1], z, self.altruismSpawns[newLoc][2], getRandomNumber(360) - 180, 0)

	if (pFarmer ~= nil) then
		writeData("hero_of_tat:altruism_mob_id", SceneObject(pFarmer):getObjectID())
		CreatureObject(pFarmer):setPvpStatusBitmask(0)

		if (CreatureObject(pFarmer):isAiAgent()) then
			AiAgent(pFarmer):setAiTemplate("idlewait")
			AiAgent(pFarmer):setFollowState(4)
		end
	else
		printf("Error in HeroOfTatooineScreenPlay:doAltruismChange, unable to spawn farmer.\n")
	end

	self:createAltruismEvent()
end

function HeroOfTatooineScreenPlay:onEnteredAltruismCave(pCave, pCreature)
	if (pCreature == nil or not SceneObject(pCreature):isPlayerCreature() or SceneObject(pCreature):getParentID() == 5995573) then
		return
	end

	local count = self:getCavePlayerWithQuestCount()
	if (count == 1) then
		self:spawnAltruismObjects()
	end
end

function HeroOfTatooineScreenPlay:onExitedAltruismCave(pCave, pCreature)
	if (pCreature == nil or not SceneObject(pCreature):isPlayerCreature()) then
		return
	end

	local escorterID = readData("hero_of_tat:altruismEscorterID")

	if (SceneObject(pCreature):getObjectID() == escorterID) then
		self:completeEscort(pCreature)
		return
	end

	local count = self:getCavePlayerCount()
	if (count == 0) then
		self:despawnAltruismObjects()
	end
end

function HeroOfTatooineScreenPlay:despawnAltruismObjects()
	local objectIDs = { readData("hero_of_tat:altruismWall"), readData("hero_of_tat:altruismCrevice"),
		readData("hero_of_tat:farmerWifeId"), readData("hero_of_tat:farmerChildId"), readData("hero_of_tat:altruismCrate") }

	for i = 1, #objectIDs, 1 do
		local pObject = getSceneObject(objectIDs[i])

		if (pObject ~= nil) then
			SceneObject(pObject):destroyObjectFromWorld()
		end
	end
	deleteData("hero_of_tat:altruismWall")
	deleteData("hero_of_tat:altruismCrevice")
	deleteData("hero_of_tat:farmerWifeId")
	deleteData("hero_of_tat:farmerChildId")
	deleteData("hero_of_tat:altruismCrate")
	writeData("hero_of_tat:altruismEscorterID", 0) -- No escorter
	writeData("hero_of_tat:altruismEscortStatus", 0) -- No one doing escort
end

function HeroOfTatooineScreenPlay:getCavePlayerCount()
	local playerCount = 0
	for i = 5995565, 5995575, 1 do
		local pCell = getSceneObject(i)
		if pCell ~= nil then
			local cellSize = SceneObject(pCell):getContainerObjectsSize()
			for j = 0, cellSize - 1, 1 do
				local pObject = SceneObject(pCell):getContainerObject(j)

				if pObject ~= nil and SceneObject(pObject):isPlayerCreature() then
					playerCount = playerCount + 1
				end
			end
		end
	end
	return playerCount
end

function HeroOfTatooineScreenPlay:getCavePlayerWithQuestCount()
	local playerCount = 0
	for i = 5995565, 5995575, 1 do
		local pCell = getSceneObject(i)
		if pCell ~= nil then
			local cellSize = SceneObject(pCell):getContainerObjectsSize()
			for j = 0, cellSize - 1, 1 do
				local pObject = SceneObject(pCell):getContainerObject(j)

				-- If object exists, is a player, and has started but not completed Altruism quest
				if pObject ~= nil and SceneObject(pObject):isPlayerCreature() and CreatureObject(pObject):hasScreenPlayState(1, "hero_of_tatooine_altruism") == 1 and CreatureObject(pObject):hasScreenPlayState(2, "hero_of_tatooine_altruism") == 0 then
					playerCount = playerCount + 1
				end
			end
		end
	end
	return playerCount
end

function HeroOfTatooineScreenPlay:giveAltruismWaypoint(pPlayer)
	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local oldWaypointID = tonumber(getQuestStatus(player:getObjectID() .. ":altruismWaypointID"))
		if (oldWaypointID ~= 0) then
			playerObject:removeWaypoint(oldWaypointID, true)
			removeQuestStatus(player:getObjectID() .. ":altruismWaypointID")
		end
		local waypointID = playerObject:addWaypoint("tatooine", "Kidnapped Family", "", 6555, -1311, WAYPOINT_COLOR_PURPLE, true, true, 0, 0)
		setQuestStatus(player:getObjectID() .. ":altruismWaypointID", waypointID)
	end)
end

function HeroOfTatooineScreenPlay:removeAltruismWaypoint(pPlayer)
	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local oldWaypointID = tonumber(getQuestStatus(player:getObjectID() .. ":altruismWaypointID"))
		if (oldWaypointID ~= 0) then
			playerObject:removeWaypoint(oldWaypointID, true)
			removeQuestStatus(player:getObjectID() .. ":altruismWaypointID")
		end
	end)
end

function HeroOfTatooineScreenPlay:destroyCaveWall(pCrevice)
	local wallID = readData("hero_of_tat:altruismWall")
	local pWall = getSceneObject(wallID)

	if (pCrevice == nil or pWall == nil) then
		return
	end

	SceneObject(pCrevice):playEffect("clienteffect/combat_grenade_proton.cef", "")
	SceneObject(pCrevice):destroyObjectFromWorld()
	SceneObject(pWall):destroyObjectFromWorld()
end

function HeroOfTatooineScreenPlay:doFarmerDespawn(pFarmer)
	if (pFarmer == nil) then
		return
	end

	if (CreatureObject(pFarmer):isAiAgent()) then
		AiAgent(pFarmer):generatePatrol(1, 30)
		createObserver(DESTINATIONREACHED, "HeroOfTatooineScreenPlay", "farmerDespawnDestinationReached", pFarmer)
	else
		SceneObject(pFarmer):destroyObjectFromWorld()
	end
end

function HeroOfTatooineScreenPlay:farmerDespawnDestinationReached(pFarmer)
	createEvent(2000, "HeroOfTatooineScreenPlay", "destroyFarmer", pFarmer)
end

function HeroOfTatooineScreenPlay:destroyFarmer(pFarmer)
	if (pFarmer ~= nil) then
		deleteData(CreatureObject(pFarmer):getObjectID() .. ":gaveQuest")
		SceneObject(pFarmer):destroyObjectFromWorld()
	end
end

function HeroOfTatooineScreenPlay:failEscort(pPlayer)
	if (pPlayer ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/hero_of_tatooine/system_messages:altruism_quest_fail")
	end
	self:despawnAltruismObjects()
end

function HeroOfTatooineScreenPlay:isEscortInRangeOf(pPlayer)
	local wifeID = readData("hero_of_tat:farmerWifeId")
	local pWife = getSceneObject(wifeID)

	if (pPlayer == nil or pWife == nil) then
		return false
	end

	return CreatureObject(pPlayer):isInRangeWithObject(pWife, 32)
end

function HeroOfTatooineScreenPlay:escortRangeCheckEvent(pPlayer)
	local wifeID = readData("hero_of_tat:farmerWifeId")
	local pWife = getSceneObject(wifeID)

	if (pPlayer == nil or pWife == nil and readData("hero_of_tat:altruismEscortStatus") == 1) then
		self:failEscort(pPlayer)
		return
	end

	if (readData("hero_of_tat:altruismEscortStatus") == 0 or SceneObject(pPlayer):getParentID() == 0) then
		return
	end

	if (CreatureObject(pPlayer):isInRangeWithObject(pWife, 25)) then
		createEvent(1000, "HeroOfTatooineScreenPlay", "escortRangeCheckEvent", pPlayer)
	else
		self:failEscort(pPlayer)
	end
end

function HeroOfTatooineScreenPlay:completeEscort(pPlayer)
	if (pPlayer == nil) then
		return
	end
	local wifeID = readData("hero_of_tat:farmerWifeId")
	local pWife = getSceneObject(wifeID)

	if (pWife ~= nil and CreatureObject(pWife):isAiAgent()) then
		spatialChat(pWife, "@quest/hero_of_tatooine/system_messages:altruism_npc_farewell")
		AiAgent(pWife):setAiTemplate("idlewait")
	end

	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		writeData("hero_of_tat:altruismEscortStatus", 0)
		player:sendSystemMessage("@quest/hero_of_tatooine/system_messages:altruism_quest_success")

		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory == nil) then
			return 0
		end

		if (SceneObject(pInventory):hasFullContainerObjects()) then
			player:sendSystemMessage("@quest/hero_of_tatooine/system_messages:altruism_inv_full")
		else
			local pSkull = giveItem(pInventory, "object/tangible/loot/quest/hero_of_tatooine/mark_altruism.iff", -1)

			if (pSkull == nil) then
				player:sendSystemMessage("Error creating object. Please file a bug report.")
			end
		end

		playerObject:awardBadge(10)
		player:setScreenPlayState(4, "hero_of_tatooine")
		player:setScreenPlayState(2, "hero_of_tatooine_altruism")
		self:removeAltruismWaypoint(pPlayer)
		createEvent(3000, "HeroOfTatooineScreenPlay", "despawnAltruismObjects", pPlayer)
	end)
end