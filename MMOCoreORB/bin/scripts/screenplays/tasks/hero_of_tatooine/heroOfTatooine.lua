local ObjectManager = require("managers.object.object_manager")

HeroOfTatooineScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	courageSpawns = { { -861, 4557 }, { -159, 5040 }, { -1264, 5379 }, { -695, 4506 }, { 16, 4068 }, { -533, 4314 }, { -1023, 5214 }, { -318, 4477 }, { -443, 4970 },
		{ -1183, 4647 }, { -575, 4985 }, { -1618, 5272 }, { -97, 5025 }, { -471, 4715 }, { -991, 5887 }, { -998, 5240 }, { -500, 4600 }, { -1131, 6185 } },

	altruismSpawns = { { 2123, 1291 }, { 2470, 1394 }, { 2511, 1357 }, { 2439, 1294 }, { 3196, 1272 }, { 3303, 1107 }, { 2123, 1291 }, { 2494, 1714 }, { 2545, 1741 },
		{ 2778, 1507 }, { 5100, 800 }, { 2168, 1293 }, { 2488, 1676 }, { 3640, -44 }, { 1839, 966 }, { 2570, 1164 }, { 2478, 687 }, { 1003, 1240 }, { 2560, 1324 }, { 2437, 1421 } },

	intellectSpawns = {
		{ x1 = 59.5, z1 = 52, y1 = -5372.23, x2 = 57.56, z2 = 52, y2 = -5366.43, bhX = 59.4, bhZ = 52, bhY = -5368.9, bhAngle = 84 },
		{ x1 = -1370.11, z1 = 12, y1 = -3639.83, x2 = -1363.3, z2 = 12, y2 = -3642.07, bhX = -1367, bhZ = 12, bhY = -3642.2, bhAngle = -168 },
		{ x1 = 3481.75, z1 = 5, y1 = -4641.05, x2 = 3486.69, z2 = 5, y2 = -4645.42, bhX = 3483.8, bhZ = 5, bhY = -4644.1, bhAngle = -145 },
		{ x1 = 1541.44, z1 = 7, y1 = 3126.77, x2 = 1551.83, z2 = 7, y2 = 3124.25, bhX = 1546.2, bhZ = 7, bhY = 3124.3, bhAngle = -165 },
		{ x1 = -2890.04, z1 = 5, y1 = 2198.77, x2 = -2893.69, z2 = 5, y2 = 2204.23, bhX = -2890.9, bhZ = 5, bhY = 2201.9, bhAngle = 57 },
		{ x1 = 3793.97, z1 = 11.62, y1 = 2389.19, x2 = 3794.33, z2 = 11.66, y2 = 2396.27, bhX = 3795.4, bhZ = 11.9, bhY = 2392.4, bhAngle = 91 },
		{ x1 = -5166.3, z1 = 75, y1 = -6620.24, x2 = -5171.38, z2 = 75, y2 = -6624.75, bhX = -5169.4, bhZ = 75, bhY = -6621.8, bhAngle = -42 }
	}

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
	if (not hasServerEvent("HeroOfTatIntellect")) then
		self:createIntellectEvent()
	end
end

function HeroOfTatooineScreenPlay:createCourageEvent()
	createServerEvent(self:getEventChangeTime(), "HeroOfTatooineScreenPlay", "doCourageChange", "HeroOfTatCourage")
end

function HeroOfTatooineScreenPlay:createAltruismEvent()
	createServerEvent(self:getEventChangeTime(), "HeroOfTatooineScreenPlay", "doAltruismChange", "HeroOfTatAltruism")
end

function HeroOfTatooineScreenPlay:createIntellectEvent()
	createServerEvent(self:getEventChangeTime(), "HeroOfTatooineScreenPlay", "doIntellectSpawn", "HeroOfTatIntellect")
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
		return 1
	end

	local pInventory = CreatureObject(pVictim):getSlottedObject("inventory")

	if pInventory == nil then
		return 1
	end

	if (SceneObject(pInventory):getContainerObjectsSize() > 0) then
		local pItem = SceneObject(pInventory):getContainerObject(0)

		if pItem ~= nil then
			local item = SceneObject(pItem)
			createObserver(ITEMLOOTED, "HeroOfTatooineScreenPlay", "notifyMarkOfCourageLooted", pItem)
		end
		CreatureObject(pAttacker):sendSystemMessage("@quest/hero_of_tatooine/system_messages:courage_notice_object")
	end
	return 1
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
		return 1
	end

	ObjectManager.withCreatureAndPlayerObject(pLooter, function(player, playerObject)
		playerObject:awardBadge(7)
		player:setScreenPlayState(16, "hero_of_tatooine")
	end)

	return 1
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

function HeroOfTatooineScreenPlay:doIntellectSpawn()
	if (not isZoneEnabled("tatooine")) then
		return 0
	end

	local hermitId = readData("hero_of_tat:hermit_id")
	local pHermit = getSceneObject(hermitId)

	if (pHermit == nil) then
		printf("Error in HeroOfTatooineScreenPlay, unable to find hermit object.\n")
		return 0
	end


	local mobLoc = readData("hero_of_tat:intellect_mob_loc")

	self:destroyIntellectMobs()

	local newLoc = getRandomNumber(1, table.getn(self.intellectSpawns))

	if (newLoc == mobLoc) then
		if (newLoc == table.getn(self.intellectSpawns)) then
			newLoc = newLoc - 1
		else
			newLoc = newLoc + 1
		end
	end

	writeData("hero_of_tat:intellect_mob_loc", newLoc)

	local pBountyHunter = spawnMobile("tatooine", "hero_of_tat_bh", 0, self.intellectSpawns[newLoc]["bhX"], self.intellectSpawns[newLoc]["bhZ"], self.intellectSpawns[newLoc]["bhY"], self.intellectSpawns[newLoc]["bhAngle"], 0)

	if (pBountyHunter == nil) then
		printf("Error in HeroOfTatooineScreenPlay, unable to spawn bounty hunter.\n")
		return
	end

	writeData("hero_of_tat:intellect_mob_id", SceneObject(pBountyHunter):getObjectID())
	CreatureObject(pBountyHunter):setPvpStatusBitmask(0)

	self:spawnIntellectLiars(pBountyHunter)
end

function HeroOfTatooineScreenPlay:getIntellectLiarName(liarNum)
	local liarId = readData("hero_of_tat:liar_" .. liarNum)
	local pLiar = getSceneObject(liarId)

	if (pLiar == nil) then
		return "unknown"
	end

	return string.match(SceneObject(pLiar):getCustomObjectName(), "%a+")
end

function HeroOfTatooineScreenPlay:sendImplicateSui(pPlayer, pNpc)
	local liarTable = { }

	for i = 1, 6, 1 do
		local liarId = readData("hero_of_tat:liar_" .. i)
		local pLiar = getSceneObject(liarId)

		if (pLiar ~= nil) then
			table.insert(liarTable, self:getIntellectLiarName(i))
		end
	end

	local suiManager = LuaSuiManager()
	suiManager:sendListBox(pNpc, pPlayer, "@quest/hero_of_tatooine/intellect_liar:sui_title", "@quest/hero_of_tatooine/intellect_liar:sui_prompt", 2, "@quest/hero_of_tatooine/intellect_liar:sui_btn_cancel", "", "@quest/hero_of_tatooine/intellect_liar:sui_btn_ok", "HeroOfTatooineScreenPlay", "handleSuiImplication", liarTable)
end

function HeroOfTatooineScreenPlay:handleSuiImplication(pPlayer, pSui, cancelPressed, arg0)
	if (pPlayer == nil) then
		return
	end

	if (cancelPressed) then
		return
	end

	local mobId = readData("hero_of_tat:intellect_mob_id")

	if (mobId == 0) then
		return
	end

	local pBountyHunter = getSceneObject(mobId)

	if (pBountyHunter == nil) then
		return
	end


	local liarNum = arg0 + 1
	return ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		if (liarNum == 4) then
			local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

			if (pInventory == nil) then
				return
			end

			if (SceneObject(pInventory):hasFullContainerObjects()) then
				player:sendSystemMessage("@quest/hero_of_tatooine/system_messages:intellect_inv_full")
			else
				local pMark = giveItem(pInventory, "object/tangible/loot/quest/hero_of_tatooine/mark_intellect.iff", -1)

				if (pMark == nil) then
					player:sendSystemMessage("Error creating object. Please file a bug report.")
				end
			end

			player:setScreenPlayState(8, "hero_of_tatooine")
			player:setScreenPlayState(2, "hero_of_tatooine_intellect")
			playerObject:awardBadge(POI_TWOLIARS)
			spatialChat(pBountyHunter, "@quest/hero_of_tatooine/intellect_liar:bh_win")
			createEvent(10 * 1000, "HeroOfTatooineScreenPlay", "doIntellectSpawn", pBountyHunter)
		else
			spatialChat(pBountyHunter, "@quest/hero_of_tatooine/intellect_liar:bh_lose")
			writeData(player:getObjectID() .. ":hero_of_tat:failedIntellect", mobId)
		end
	end)
end

function HeroOfTatooineScreenPlay:destroyIntellectMobs()
	local mobId = readData("hero_of_tat:intellect_mob_id")
	local mobLoc = readData("hero_of_tat:intellect_mob_loc")
	local pBountyHunter

	if (mobId ~= 0) then
		pBountyHunter = getSceneObject(mobId)
	end

	if (pBountyHunter ~= nil) then
		SceneObject(pBountyHunter):destroyObjectFromWorld()
	end

	for i = 1, 6, 1 do
		local liarId = readData("hero_of_tat:liar_" .. i)
		local pLiar = getSceneObject(liarId)

		if (pLiar ~= nil) then
			deleteData(SceneObject(pLiar):getObjectID() .. ":liarId")
			SceneObject(pLiar):destroyObjectFromWorld()
		end

		deleteData("hero_of_tat:liar_" .. i)
	end
end

function HeroOfTatooineScreenPlay:spawnIntellectLiars(pBountyHunter)
	local mobLoc = readData("hero_of_tat:intellect_mob_loc")
	local mobId = readData("hero_of_tat:intellect_mob_id")

	for i = 1, 6, 1 do
		local x, y, z

		if (i < 4) then
			x = self.intellectSpawns[mobLoc]["x1"]
			z = self.intellectSpawns[mobLoc]["z1"]
			y = self.intellectSpawns[mobLoc]["y1"]
		else
			x = self.intellectSpawns[mobLoc]["x2"]
			z = self.intellectSpawns[mobLoc]["z2"]
			y = self.intellectSpawns[mobLoc]["y2"]
		end

		if (i == 1 or i == 4) then x = x - .75; y = y + 1.3
		elseif (i == 2 or i == 5) then x = x - .75; y = y - 1.3
		elseif (i == 3 or i == 6) then x = x + 1.5 end

		local pLiar

		if (i == 1) then
			pLiar = spawnMobile("tatooine", "hero_of_tat_smuggler_captain", 0, x, z, y, getRandomNumber(360) - 180, 0)
		else
			pLiar = spawnMobile("tatooine", "hero_of_tat_smuggler", 0, x, z, y, getRandomNumber(360) - 180, 0)
		end

		if (pLiar == nil) then
			printf("Error in HeroOfTatooineScreenPlay, unable to spawn Mark of Intellect smugglers.\n")
			self:destroyIntellectMobs() -- If not all were able to spawn, destroy them all until next spawn attempt
			return
		end
		CreatureObject(pLiar):setPvpStatusBitmask(0)
		writeData("hero_of_tat:liar_" .. i, SceneObject(pLiar):getObjectID())
		writeData(SceneObject(pLiar):getObjectID() .. ":liarId", i)
	end
end

function HeroOfTatooineScreenPlay:onEnteredAltruismCave(pCave, pCreature)
	if (pCreature == nil or not SceneObject(pCreature):isPlayerCreature() or SceneObject(pCreature):getParentID() == 5995573) then
		return 0
	end

	local count = self:getCavePlayerWithQuestCount()

	if (count == 1) then
		self:spawnAltruismObjects()
	end

	return 0
end

function HeroOfTatooineScreenPlay:onExitedAltruismCave(pCave, pCreature)
	if (pCreature == nil or not SceneObject(pCreature):isPlayerCreature()) then
		return 0
	end

	local escorterID = readData("hero_of_tat:altruismEscorterID")

	if (SceneObject(pCreature):getObjectID() == escorterID) then
		self:completeEscort(pCreature)
		return 0
	end

	local count = self:getCavePlayerCount()
	if (count == 0) then
		self:despawnAltruismObjects()
	end

	return 0
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

	local planterId = readData("hero_of_tat:explosivePlanterID")

	if (planterId ~= 0 and getSceneObject(planterId) ~= nil) then
		playClientEffectLoc(planterId, "clienteffect/lair_damage_heavy_shake.cef", "tatooine", 162.5, -66.8, -97.7, 5995573)
		playClientEffectLoc(planterId, "clienteffect/lair_damage_heavy_shake.cef", "tatooine", 150.96, -65.83, -97.66, 5995573)
		writeData("hero_of_tat:explosivePlanterID", 0)
	end

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
	return 1
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
			local pMark = giveItem(pInventory, "object/tangible/loot/quest/hero_of_tatooine/mark_altruism.iff", -1)

			if (pMark == nil) then
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