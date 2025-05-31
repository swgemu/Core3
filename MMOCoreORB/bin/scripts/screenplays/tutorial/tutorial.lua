--[[

TODO:
- Rewrite function Tutorial:getPlayerProfession(pPlayer) to pull from readStringData(playerID .. ":profession:", playerProfession)
	readStringData for playerProfession is returning nil --> marksman trainer is spawned.
		TODO: This happens when player logs in w/o novice box --> need to handle this to prevent spawning a marksman trainer

- Transfers to/from containers are not updating in the client, despite the moves taking place
	This includes inventory, drum, bank, equipping/deequipping items, combat animations, npc movement
	EXCEPTION: when officer in r10 grants travel documents, they instantly appear in inventory but custom name is not applied

- Get waypoints working inside terminal (to planets and JTL trainers)
	datatables/creation/starting_locations.iff

- After tutorial completion, move any items in player bank to inventory and reset bank location
	TODO: currently challenging due to lack of inventory updates (see line 18)
		Seems like items are being added in multiple places (on character cretion, throughout the screenplay)

- Any additional 'flair' stuff that may still be missing
	Seems we have everything now

	TODO Need to get correct items into inventory and drum when tutorial is enabled, when skippedTutorial & EnableHelperDroid, and when disable both
		getStartingItems(): remove professionSpecificItems from PlayerCreationManager::loadLuaStartingItems if doTutorial = true
		For both addStartingItemsInto and addStartingWeaponsInto
		Not understanding how to stop from adding into player inventory but allow tutorial to add commonStartingItems to drum

	TODO: adjust curStep timings to a better flow, so there aren't long delays or sound files stepping over each other

]]

local ObjectManager = require("managers.object.object_manager")

Tutorial = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("Tutorial", false);

-- Function triggered by StartTutorialTask when player zones in to unique tutorial instance
function Tutorial:start(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return
	end

	local ghost = LuaPlayerObject(pGhost)

	--Ensure that player is actually inside
	if CreatureObject(pPlayer):getParentID() == 0 then
		return
	end

	local pBuilding = self:getTutorialBuilding(pPlayer)

	if (pBuilding == nil or BuildingObject(pBuilding):getServerObjectCRC() ~= 3369536646) then
		return
	end

	createObserver(EXITEDBUILDING, "Tutorial", "onExitTutorial", pBuilding)
	writeData(SceneObject(pBuilding):getObjectID() .. ":ownerID", playerID)

	-- Monitor player cell changes
	createObserver(PARENTCHANGED, "Tutorial", "changedRoomEvent", pPlayer, 1)
	createObserver(LOGGEDOUT, "Tutorial", "onLoggedOut", pPlayer)

	if (self:isInRoom(pPlayer, "r1") and not self:isRoomComplete(pPlayer, "r1")) then
		self:initializeHudElements(pPlayer)

		-- Remove their novice skill so that they can use the skill trainer in r9 and re-learn it
		local playerProfession = self:getPlayerProfession(pPlayer)
		writeStringData(playerID .. ":profession:", playerProfession)

		if (playerProfession ~= "") then
			CreatureObject(pPlayer):surrenderSkill(playerProfession .. "_novice")
		end

		writeData(playerID .. ":tutorialStarted", 1)
		createEvent(2000, "Tutorial", "handleRoomOne", pPlayer, "")
	end

	self:spawnObjects(pPlayer)
end

function Tutorial:onLoggedOut(pPlayer)
	local pBuilding = self:getTutorialBuilding(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()

	if pBuilding == nil or playerID == nil then
		return 0
	end

	-- Store player zoneName, cellID and in-building coordinates to allow subsequent placement in building
	writeStringData(playerID .. ":savedZoneName:", CreatureObject(pPlayer):getZoneName())
	writeData(playerID .. ":savedParentID:", CreatureObject(pPlayer):getParentID())
	writeVector3Data(playerID .. ":Tutorial:position:", CreatureObject(pPlayer):getPositionX(), CreatureObject(pPlayer):getPositionZ(), CreatureObject(pPlayer):getPositionY())

	dropObserver(PARENTCHANGED, "Tutorial", "changedRoomEvent", pPlayer)
	dropObserver(LOGGEDOUT, "Tutorial", "onLoggedOut", pPlayer)

	return 1
end

function Tutorial:onExitTutorial(pBuilding, pPlayer)
	if pBuilding == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local ownerID = readData(SceneObject(pBuilding):getObjectID() .. ":ownerID")

	if (SceneObject(pPlayer):getObjectID() ~= ownerID) then
		return 0
	end

	createEvent(10000, "Tutorial", "clearPlayers", pBuilding, "")
	createEvent(20000, "Tutorial", "destroyTutorial", pBuilding, "")
	dropObserver(EXITEDBUILDING, "Tutorial", "onExitTutorial", pPlayer)

	return 1
end

-- In case any admins had teleported in, as any players in the building when it is destroyed will get a client crash
function Tutorial:clearPlayers(pBuilding)
	if (pBuilding == nil) then
		return
	end

	local ownerID = readData(SceneObject(pBuilding):getObjectID() .. ":ownerID")

	for i = 1, BuildingObject(pBuilding):getTotalCellNumber(), 1 do
		local pCell = BuildingObject(pBuilding):getCell(i)

		if (pCell ~= nil) then
			for j = SceneObject(pCell):getContainerObjectsSize(), 1, -1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)

				if (pObject == nil) then
					return
				end

				local mobileOid = SceneObject(pObject):getObjectID()

				if (mobileOid == nil) then
					return
				end

				if SceneObject(pObject):isPlayerCreature() and mobileOid ~= ownerID then
					SceneObject(pObject):switchZone("tatooine", 3387, 0, -4333, 0)
				elseif not SceneObject(pObject):isPlayerCreature() then
					SceneObject(pObject):destroyObjectFromWorld()
					SceneObject(pObject):destroyObjectFromDatabase()
				end
			end
		end
	end
end

function Tutorial:destroyTutorial(pBuilding)
	if (pBuilding == nil) then
		return
	end

	deleteData(SceneObject(pBuilding):getObjectID() .. ":ownerID")
	SceneObject(pBuilding):destroyObjectFromWorld()
	SceneObject(pBuilding):destroyObjectFromDatabase()
end

-- Spawn all tutorial mobiles and sceneobjects
function Tutorial:spawnObjects(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local pBuilding = self:getTutorialBuilding(pPlayer)

	if (pBuilding == nil) then
		return
	end

	local pCell, cellID, pMobile

	-- *** ROOM ONE ***
	pCell = BuildingObject(pBuilding):getNamedCell("r1")

	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()

		-- Greeter
		pMobile = spawnMobile("tutorial", "tutorial_room1_greeter", 0, 9.5, 0.7, -3, -90, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(playerID .. ":tutorial:roomOneGreeterID:", SceneObject(pMobile):getObjectID())
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)
		end

		-- Stormtroopers standing guard at door
		spawnMobile("tutorial", "tutorial_stormtrooper_filler", 0, 1.9, 0, -16.5, 0, cellID)
		spawnMobile("tutorial", "tutorial_stormtrooper_filler", 0, -1.9, 0, -16.5, 0, cellID)
	end

	-- ** ROOM TWO **
	pCell = BuildingObject(pBuilding):getNamedCell("r2")

	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()

		-- Greeter
		pMobile = spawnMobile("tutorial", "tutorial_room2_greeter", 0, 34.9, 0, -31.8, -90, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(playerID .. ":tutorial:roomTwoGreeterID", SceneObject(pMobile):getObjectID())
		end

		-- Commoner (conversable, animated)
		pMobile = spawnMobile("tutorial", "tutorial_commoner", 0, 19.7, 0, -23.1, 53, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(SceneObject(pMobile):getObjectID() .. ":tutorial:commonerNum", 1)
			CreatureObject(pMobile):setMoodString("npc_consoling")
		end

		-- Item drum, no permission to remove items until player speaks to greeter
		local pDrum = spawnSceneObject("tutorial", "object/tangible/container/drum/tatt_drum_1.iff", 34.8, 0, -33.1, cellID, 0.71, 0, -0.71, 0)

		if (pDrum ~= nil) then
			SceneObject(pDrum):clearContainerDefaultAllowPermission(OPEN + MOVEOUT);
			SceneObject(pDrum):setContainerAllowPermission("RoomTwoItemDrum", OPEN + MOVEOUT);
			SceneObject(pDrum):setContainerInheritPermissionsFromParent(false)
			SceneObject(pDrum):setContainerComponent("tutorialItemDrumContainerComponent")

			writeData(playerID .. ":tutorial:roomTwoDrum", SceneObject(pDrum):getObjectID())
			writeData(SceneObject(pDrum):getObjectID() .. ":playerOwnerID", playerID)

			if not (self:isRoomComplete(pPlayer, "r2")) then
				addStartingItemsInto(pPlayer, pDrum)
				print("\n\nTutorial:addStartingItemsInto(pPlayer, pDrum) executed...\n\n")
			end
		end
	end

	-- ** ROOM THREE **

	pCell = BuildingObject(pBuilding):getNamedCell("r3")

	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()

		local pNewbTerminal = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_newbie_clothing.iff", 54.95, -0.5, -0.68, cellID, 0.7071067811865476, 0, -0.7071067811865476, 0)

		if (pNewbTerminal ~= nil) then
			writeData(playerID .. ":tutorial:roomThreeBazaarID", SceneObject(pNewbTerminal):getObjectID())
		end

		local pBank = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_bank.iff", 50.83, -0.5, -3.63, cellID, 0.7071067811865476, 0, -0.7071067811865476, 0)

		if (pBank ~= nil) then
			writeData(playerID .. ":tutorial:roomThreeBankID", SceneObject(pBank):getObjectID())
		end

		-- Bank users
		pMobile = spawnMobile("tutorial", "tutorial_commoner_noconverse", 0, 41.65, 0, 6.35, 0, cellID)

		-- Animate them to look like they are operating terminal
		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			createEvent(getRandomNumber(10, 30) * 1000, "Tutorial", "doBankUserAnimation", pMobile, "")
		end

		pMobile = spawnMobile("tutorial", "tutorial_commoner_noconverse", 0, 46.07, 0, 6.55, 0, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			createEvent(getRandomNumber(10, 30) * 1000, "Tutorial", "doBankUserAnimation", pMobile, "")
		end

		-- Banker, conversable, explains bank and item dispenser/bazaar
		pMobile = spawnMobile("tutorial", "tutorial_banker", 0, 48.27, -0.5, 1.12, -90, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(playerID .. ":tutorial:roomThreeBankerID", SceneObject(pMobile):getObjectID())
		end
	end

	-- ** ROOM FOUR **
	pCell = BuildingObject(pBuilding):getNamedCell("r4")

	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()

		-- Droid, explains cloning and insurance, bark triggered on entering area
		pMobile = spawnMobile("tutorial", "tutorial_clone_droid", 0, 24.5, -7, -55.8, 102, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(playerID .. ":tutorial:roomFourCloneDroidID", SceneObject(pMobile):getObjectID())

			local pActiveArea = spawnActiveArea("tutorial", "object/active_area.iff", SceneObject(pMobile):getWorldPositionX(), -7, SceneObject(pMobile):getWorldPositionY(), 10, cellID)
			if pActiveArea ~= nil then
				createObserver(ENTEREDAREA, "Tutorial", "notifyEnteredCloneDroidArea", pActiveArea)
			end
		end
	end

	-- ** ROOM FIVE **
	pCell = BuildingObject(pBuilding):getNamedCell("r5")

	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()

		-- Cloning terminal, not actually usable, just sends system message when using radial
		local pCloneTerminal = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_cloning.iff", 2.9, -7, -56.55, cellID, 0.7071067811865476, 0, 0.7071067811865476, 0)

		if (pCloneTerminal ~= nil) then
			SceneObject(pCloneTerminal):setObjectMenuComponent("tutorialCloningTerminal")
			writeData(playerID .. ":tutorial:roomFiveCloneTerminalID", SceneObject(pCloneTerminal):getObjectID())
		end

		-- Insurance terminal, not actually usable, just sends system message when using radial
		local pInsurance = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_insurance.iff", -0.5, -7, -66.5, cellID, 0, 0, 0, 0)

		if (pInsurance ~= nil) then
			SceneObject(pInsurance):setObjectMenuComponent("tutorialInsuranceTerminal")
			writeData(playerID .. ":tutorial:roomFiveInsuranceTerminalID", SceneObject(pInsurance):getObjectID())
		end
	end

	-- ** ROOM SIX **
	pCell = BuildingObject(pBuilding):getNamedCell("r6")

	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()

		-- No converse commoner, panics when explosion goes off and runs to different cell while yelling
		pMobile = spawnMobile("tutorial", "tutorial_commoner_noconverse", 0, 18.25, -4, -76.9, 102, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			CreatureObject(pMobile):setMoodString("unhappy")
			writeData(playerID .. ":tutorial:roomSixPanicCommoner", SceneObject(pMobile):getObjectID())
		end
	end

	-- ** ROOM SEVEN **
	pCell = BuildingObject(pBuilding):getNamedCell("r7")

	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()

		-- Officer that gives player a weapon
		pMobile = spawnMobile("tutorial", "tutorial_scared_soldier", 0, 43.75, -7, -75.2, -88, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			CreatureObject(pMobile):setMoodString("nervous")
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)
			writeData(playerID .. ":tutorial:roomSevenScaredSoldier", SceneObject(pMobile):getObjectID())
		end

		-- Three nervous mood npcs, send random spatial strings regarding upcoming pirate
		pMobile = spawnMobile("tutorial", "tutorial_nervous_guy", 0, 43.1, -7, -70.4, -163, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			CreatureObject(pMobile):setMoodString("nervous")
			writeData(playerID .. ":tutorial:roomSevenNervousGuy1", SceneObject(pMobile):getObjectID())
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)
		end

		pMobile = spawnMobile("tutorial", "tutorial_nervous_guy", 0, 37.5, -7, -70, -108, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			CreatureObject(pMobile):setMoodString("nervous")
			writeData(playerID .. ":tutorial:roomSevenNervousGuy2", SceneObject(pMobile):getObjectID())
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)
		end

		pMobile = spawnMobile("tutorial", "tutorial_nervous_guy", 0, 39, -7, -79.6, 15, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			CreatureObject(pMobile):setMoodString("nervous")
			writeData(playerID .. ":tutorial:roomSevenNervousGuy3", SceneObject(pMobile):getObjectID())
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)
		end
	end

	-- ** ROOM FOURTEEN (BETWEEN SEVEN AND EIGHT) **

	if (not self:isRoomComplete(pPlayer, "r14")) then
		pCell = BuildingObject(pBuilding):getNamedCell("r14")

		if (pCell ~= nil) then
			cellID = SceneObject(pCell):getObjectID()

			-- Destroyable debris blocking hallway
			local pDebris = spawnSceneObject("tutorial", "object/tangible/newbie_tutorial/debris.iff", 77, -4, -109, cellID, 0, 0, 0, 0)

			if (pDebris ~= nil) then
				createObserver(OBJECTDESTRUCTION, "Tutorial", "debrisDestroyed", pDebris)
				TangibleObject(pDebris):setMaxCondition(100)
			end
		end
	end

	-- ** ROOM EIGHT **
	pCell = BuildingObject(pBuilding):getNamedCell("r8")

	if (pCell ~= nil and not self:isRoomComplete(pPlayer, "r8")) then
		cellID = SceneObject(pCell):getObjectID()

		-- Pirate, initates combat at 12m, blows himself up with grenade after 10-15 secs, lootable
		pMobile = spawnMobile("tutorial", "tutorial_bandit", 0, 39, -5.94, -113.6, 90, cellID)

		if (pMobile ~= nil) then
			writeData(playerID .. ":tutorial:roomEightPirate", SceneObject(pMobile):getObjectID())
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)

			createObserver(DEFENDERADDED, "Tutorial", "pirateDefenderAdded", pMobile)
			createObserver(OBJECTDESTRUCTION, "Tutorial", "pirateKilled", pMobile)

			local pActiveArea = spawnActiveArea("tutorial", "object/active_area.iff", SceneObject(pMobile):getWorldPositionX(), -7, SceneObject(pMobile):getWorldPositionY(), 20, cellID)
			if pActiveArea ~= nil then
				createObserver(ENTEREDAREA, "Tutorial", "notifyEnteredPirateArea", pActiveArea)
			end
		end
	end

	-- ** ROOM NINE **
	pCell = BuildingObject(pBuilding):getNamedCell("r9")

	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()

		-- Trainer based on player's initial chosen profession, teaches player novice
		print("PlayerTrainer = " .. tostring(self:getPlayerTrainer(pPlayer)))
		pMobile = spawnMobile("tutorial", self:getPlayerTrainer(pPlayer), 0, 3.7, -4.2, -127.7, 90, cellID)

		if (pMobile ~= nil) then
			createObserver(STOPCONVERSATION, "Tutorial", "finishedTrainerConvo", pMobile)
			writeData(playerID .. ":tutorial:roomNineTrainer", SceneObject(pMobile):getObjectID())
		end

		-- Training officer, tells player to speak to trainer
		pMobile = spawnMobile("tutorial", "tutorial_training_room_officer", 0, .65, -4.2, -113.3, 90, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(playerID .. ":tutorial:roomNineOfficer", SceneObject(pMobile):getObjectID())
			createObserver(STOPCONVERSATION, "Tutorial", "finishedTrainingRoomOfficerConvo", pMobile)
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)
		end

		-- Celebrity npcs, conversable, random strings sent in spatial
		pMobile = spawnMobile("tutorial", "tutorial_celebrity", 0, 7.6, -4.2, -105.5, -173, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(playerID .. ":tutorial:roomNineCeleb1", SceneObject(pMobile):getObjectID())
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)
		end

		pMobile = spawnMobile("tutorial", "tutorial_celebrity", 0, 1.75, -4.2, -108.2, 134, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(playerID .. ":tutorial:roomNineCeleb2", SceneObject(pMobile):getObjectID())
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)
		end
	end

	-- ** ROOM TEN **
	pCell = BuildingObject(pBuilding):getNamedCell("r10")

	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()

		-- Mission terminal, not actually usable, mission giver yells at player when radial is used
		local pMissionTerm = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_mission_newbie.iff", 19.6, -4.2, -138, cellID, 0, 0, 1, 0)

		if (pMissionTerm ~= nil) then
			SceneObject(pMissionTerm):setObjectMenuComponent("tutorialMissionTerminal")
		end

		-- Mission giver, gives player release documents, sends player to next room
		pMobile = spawnMobile("tutorial", "tutorial_mission_giver", 0, 19.5, -4.2, -145.35, 0, cellID)

		if (pMobile ~= nil) then
			if (self:isRoomComplete(pPlayer, "r10")) then
				CreatureObject(pMobile):clearOptionBit(CONVERSABLE)
			end
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(playerID .. ":tutorial:roomTenMissionGiver", SceneObject(pMobile):getObjectID())
		end

		-- Trapped guy commoner, sends random spatials
		pMobile = spawnMobile("tutorial", "tutorial_commoner_noconverse", 0, 17.75, -4.2, -144.65, 0, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)
			createEvent(30000, "Tutorial", "doTrappedGuySpam", pMobile, "")
			writeData(playerID .. ":tutorial:roomTenTrappedGuy", SceneObject(pMobile):getObjectID())
		end
	end

	-- ** ROOM ELEVEN **
	pCell = BuildingObject(pBuilding):getNamedCell("r11")

	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()

		-- Warp terminal, gives player ability to choose starting city, only accessable after speaking to quartermaster with release documents
		local pTravelTerm = spawnSceneObject("tutorial", "object/tangible/terminal/terminal_travel_tutorial.iff", 27.55, -3.5, -167.8, cellID, 0, 0, 0, 0)

		if (pTravelTerm ~= nil) then
			if (not self:isRoomComplete(pPlayer, "r11")) then
				setAuthorizationState(pTravelTerm, false)
			end
			writeData(playerID .. ":tutorial:travelTerminal", SceneObject(pTravelTerm):getObjectID())
		end

		-- Quartermaster, conversable, gives player access to warp terminal if they have release documents
		pMobile = spawnMobile("tutorial", "tutorial_quartermaster", 0, 25.4, -4.2, -158.3, 92, cellID)

		if (pMobile ~= nil) then
			if (self:isRoomComplete(pPlayer, "r11")) then
				CreatureObject(pMobile):clearOptionBit(CONVERSABLE)
			end
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(playerID .. ":tutorial:roomElevenQuartermaster", SceneObject(pMobile):getObjectID())
		end

		-- TODO: Add PILOT convo about pilot tracks
		spawnMobile("tutorial", "pilot", 0, 25.3, -4.2, -160.4, 55, cellID)

		-- Commoners sitting on ground, send random spatials
		pMobile = spawnMobile("tutorial", "tutorial_commoner_noconverse", 0, 38.8, -4.2, -166.1, -50, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setMoodString("npc_sitting_ground")
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)
			createEvent(30000, "Tutorial", "doRefugeeSpam", pMobile, "")
		end

		pMobile = spawnMobile("tutorial", "tutorial_commoner_noconverse", 0, 40.8, -4.2, -164.1, -50, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setMoodString("npc_sitting_ground")
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)
			createEvent(30000, "Tutorial", "doRefugeeSpam", pMobile, "")
		end

		pMobile = spawnMobile("tutorial", "tutorial_commoner_noconverse", 0, 36.8, -4.2, -164.1, -50, cellID)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setMoodString("npc_sitting_ground")
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			writeData(SceneObject(pMobile):getObjectID() .. ":playerID", playerID)
			createEvent(30000, "Tutorial", "doRefugeeSpam", pMobile, "")
		end

		-- Stormtroopers, conversable
		spawnMobile("tutorial", "tutorial_stormtrooper_filler", 0, 32, -4.2, -163.2, 111, cellID)
		spawnMobile("tutorial", "tutorial_stormtrooper_filler", 0, 19.25, -4.2, -160.3, 0, cellID)
	end
end

-- Triggered any time a player changes between cells, sets previous room complete as they move to a new one
function Tutorial:changedRoomEvent(pPlayer, pNewParent)
	if (pPlayer == nil or pNewParent == nil or SceneObject(pNewParent):getObjectID() == 0) then
		return 1
	end

	if (self:isInRoom(pPlayer, "r2") and not self:isRoomComplete(pPlayer, "r2")) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:part_2")
		createEvent(3000, "Tutorial", "handleRoomTwo", pPlayer, "")

		if (not self:isRoomComplete(pPlayer, "r1")) then
			self:markRoomComplete(pPlayer, "r1")
		end
	elseif (self:isInRoom(pPlayer, "r3") and not self:isRoomComplete(pPlayer, "r3")) then
		self:givePermission(pPlayer, "RoomTwoItemDrum")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:part_3")
		createEvent(1000, "Tutorial", "handleRoomThree", pPlayer, "")

		if (not self:isRoomComplete(pPlayer, "r2")) then
			self:markRoomComplete(pPlayer, "r2")
		end
	elseif (self:isInRoom(pPlayer, "r4") and not self:isRoomComplete(pPlayer, "r4")) then
		createEvent(500, "Tutorial", "handleRoomFour", pPlayer, "")
		self:markRoomComplete(pPlayer, "r3")
	elseif (self:isInRoom(pPlayer, "r5") and not self:isRoomComplete(pPlayer, "r5")) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:part_4")
		createEvent(500, "Tutorial", "handleRoomFive", pPlayer, "")
		self:markRoomComplete(pPlayer, "r4")
	elseif (self:isInRoom(pPlayer, "r6") and not self:isRoomComplete(pPlayer, "r6")) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:part_5")
		createEvent(100, "Tutorial", "handleRoomSix", pPlayer, "")
		self:markRoomComplete(pPlayer, "r5")
	elseif (self:isInRoom(pPlayer, "r7") and not self:isRoomComplete(pPlayer, "r7")) then
		createEvent(500, "Tutorial", "handleRoomSeven", pPlayer, "")
		self:markRoomComplete(pPlayer, "r6")
	elseif (self:isInRoom(pPlayer, "r14") and not self:isRoomComplete(pPlayer, "r14")) then
		if (readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:givenWeapon") == 1) then
			self:markRoomComplete(pPlayer, "r7")
		end
		createEvent(500, "Tutorial", "handleRoomFourteen", pPlayer, "")
	elseif (self:isInRoom(pPlayer, "r8") and not self:isRoomComplete(pPlayer, "r8")) then
		-- Lock door to room 9
		local pBuilding = self:getTutorialBuilding(pPlayer)

		if (pBuilding ~= nil) then
			local pCell = BuildingObject(pBuilding):getNamedCell("r9")

			if (pCell ~= nil) then
				updateCellPermission(pCell, false, pPlayer)
			end
		end
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:part_6")

		if (not self:isRoomComplete(pPlayer, "r14")) then
			self:markRoomComplete(pPlayer, "r14")
		end

		createEvent(500, "Tutorial", "handleRoomEight", pPlayer, "")
	elseif (self:isInRoom(pPlayer, "r9") and not self:isRoomComplete(pPlayer, "r9")) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:part_7")
		createEvent(500, "Tutorial", "handleRoomNine", pPlayer, "")

		if (not self:isRoomComplete(pPlayer, "r8")) then
			self:markRoomComplete(pPlayer, "r8")
		end

	elseif (self:isInRoom(pPlayer, "r10") and not self:isRoomComplete(pPlayer, "r10")) then
		self:markRoomComplete(pPlayer, "r9")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:part_8")
		createEvent(500, "Tutorial", "handleRoomTen", pPlayer, "")
	elseif (self:isInRoom(pPlayer, "r11") and not self:isRoomComplete(pPlayer, "r11")) then
		self:markRoomComplete(pPlayer, "r10")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:part_9")
		createEvent(500, "Tutorial", "handleRoomEleven", pPlayer, "")
	end

	return 0
end

-- Enable hud elements if player zones into tutorial partially completed
function Tutorial:initializeHudElements(pPlayer)
	if (pPlayer == nil or self:isRoomComplete(pPlayer, "r8")) then
		return
	end

	CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("all", 0, 0)
	CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("buttonbar", 1, 0)

	if (self:isRoomComplete(pPlayer, "r1")) then
		CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("chatbox", 1, 0)
	end

	if (self:isRoomComplete(pPlayer, "r2")) then
		CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("toolbar", 1, 0)
	end

	if (self:isRoomComplete(pPlayer, "r6")) then
		CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("radar", 1, 0)
	end
end

-- ROOM ONE
-- Welcome / Movement and Camera Controls / Chat / Holocron
function Tutorial:handleRoomOne(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r1") or self:isRoomComplete(pPlayer, "r1")) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local curStep = readData(playerID .. ":tutorial:currentStep:r1")

	if (curStep == 0) then -- Welcome
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:welcome")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_01_welcome.snd")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:part_1")

		createEvent(6000, "Tutorial", "handleRoomOne", pPlayer, "")

	elseif (curStep == 1) then -- Movement tutorial
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:movement_keyboard")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:movement_mouse")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:lookaround")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_02_movement.snd")

		createEvent(12000, "Tutorial", "handleRoomOne", pPlayer, "")

	elseif (curStep == 2) then -- Mouse wheel tutorial
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:mousewheel")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_00_camera.snd")
		CreatureObject(pPlayer):sendNewbieTutorialRequest("zoomCamera")

		createEvent(35000, "Tutorial", "handleRoomOne", pPlayer, "")

	elseif (curStep == 3) then -- Chat tutorial
		CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("chatbox", 1, 3)
		CreatureObject(pPlayer):playMusicMessage("sound/tut_04_chat.snd")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:chatwindow")

		writeData(playerID .. ":tutorial:waitingOnChat", 1)
		CreatureObject(pPlayer):sendNewbieTutorialRequest("chatbox")
		createObserver(CHAT, "Tutorial", "chatEvent", pPlayer)

		createEvent(20000, "Tutorial", "doChatReminder", pPlayer, "")

	elseif (curStep == 4) then -- Holocron tutorial
		CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG")
		CreatureObject(pPlayer):sendNewbieTutorialRequest("closeHolocron")

		CreatureObject(pPlayer):playMusicMessage("sound/tut_00_holocron.snd")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:holocube")
		writeData(playerID .. ":tutorial:waitingOnHolocron", 1)

		createObserver(NEWBIETUTORIALHOLOCRON, "Tutorial", "holocronEvent", pPlayer)

	elseif (curStep == 5) then -- Move to next room
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:move_to_item_room")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_06_excellent.snd")

		createEvent(15000, "Tutorial", "doMoveToItemRoomReminder", pPlayer, "")
		self:markRoomComplete(pPlayer, "r1")
	end

	writeData(playerID .. ":tutorial:currentStep:r1", curStep + 1)

	-- Generate spam for tutorial_room1_greeter
	local celebID = readData(playerID .. ":tutorial:roomOneGreeterID:")
	local pCeleb = getSceneObject(celebID)

	if (pCeleb ~= nil) then
		createEvent(getRandomNumber(5, 10) * 1000, "Tutorial", "doGreeterOneSpeak", pCeleb, "")
	end
end

-- Event random spatials for greeter in room
function Tutorial:doGreeterOneSpeak(pCeleb)
	if (pCeleb == nil) then
		return
	end

	local playerID = readData(SceneObject(pCeleb):getObjectID() .. ":playerID")
	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil or self:isRoomComplete(pPlayer, "r1")) then
		return
	end

	-- Throttle messages so they dont always occur every iteration
	if (self:isInRoom(pPlayer, "r1") and getRandomNumber(1,20) > 10) then
		spatialChat(pCeleb, "@newbie_tutorial/newbie_convo:greeter1_bark" .. getRandomNumber(1,3))
	end

	createEvent(getRandomNumber(20,30) * 1000, "Tutorial", "doGreeterOneSpeak", pCeleb, "")
end

-- Reminder to move to the next room if player is still in room one after timer
function Tutorial:doMoveToItemRoomReminder(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r1")) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:repeat_item_room_prompt")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_07_comeon.snd")
	createEvent(15000, "Tutorial", "doMoveToItemRoomReminder", pPlayer, "")

end

-- Event triggered when player sends chat, used when tutorial is explaining chatbox
function Tutorial:chatEvent(pPlayer, chatMessage)
	if (pPlayer == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if (readData(playerID .. ":tutorial:waitingOnChat") == 1) then
		deleteData(playerID .. ":tutorial:waitingOnChat")
		createEvent(2000, "Tutorial", "handleRoomOne", pPlayer, "")
	end

	return 1
end

-- Reminder to type in chat if player has not done so after timer expires
function Tutorial:doChatReminder(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r1")) then
		return
	end

	if (readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:waitingOnChat") == 1) then
		CreatureObject(pPlayer):sendNewbieTutorialRequest("chatbox")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:repeatchatprompt")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_05_remind_chat.snd")
		createEvent(15000, "Tutorial", "doChatReminder", pPlayer, "")
	end
end

-- Triggered when a player opens their holocron in room 1 when instructed to
function Tutorial:holocronEvent(pPlayer)
	if (pPlayer == nil) then
		return 1
	end

	if (not self:isInRoom(pPlayer, "r1")) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if (readData(playerID .. ":tutorial:waitingOnHolocron") == 1) then
		deleteData(playerID .. ":tutorial:waitingOnHolocron")
		createEvent(3000, "Tutorial", "handleRoomOne", pPlayer, "")
	end

	return 1
end


-- ROOM TWO
-- Conversing with NPC's, Inventory
function Tutorial:handleRoomTwo(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r2") or self:isRoomComplete(pPlayer, "r2")) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local curStep = readData(playerID .. ":tutorial:currentStep:r2")

	if (curStep == 0) then -- Welcome
		local greeterID = readData(playerID .. ":tutorial:roomTwoGreeterID")
		local pGreeter = getSceneObject(greeterID)

		if (pGreeter ~= nil) then
			CreatureObject(pGreeter):doAnimation("wave_hail")
			CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_08")
			CreatureObject(pPlayer):playMusicMessage("sound/tut_08_imperialofficer.snd")
			spatialChat(pGreeter, "@newbie_tutorial/newbie_convo:greeting")
			createObserver(OBJECTRADIALOPENED, "Tutorial", "greeterRadialEvent", pGreeter)
			createEvent(15000, "Tutorial", "doGreeterConvoReminder", pPlayer, "")
		end

	elseif (curStep == 1) then -- Open item drum
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:prompt_open_box")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_14_openbox.snd")

		local drumID = readData(playerID .. ":tutorial:roomTwoDrum")
		local pDrum = getSceneObject(drumID)

		if (pDrum ~= nil) then
			SceneObject(pDrum):showFlyText("newbie_tutorial/system_messages", "open_me", 255, 255, 0)
			self:givePermission(pPlayer, "RoomTwoItemDrum")
			createObserver(OBJECTRADIALOPENED, "Tutorial", "drumRadialEvent", pDrum)
			createObserver(OPENCONTAINER, "Tutorial", "drumOpenEvent", pDrum)
			createObserver(CLOSECONTAINER, "Tutorial", "drumCloseEvent", pDrum)
		end

		createEvent(15000, "Tutorial", "doDrumRadialReminder", pPlayer, "")
	elseif (curStep == 2) then -- Close inventory
		CreatureObject(pPlayer):sendNewbieTutorialRequest("closeInventory")
		createObserver(NEWBIECLOSEINVENTORY, "Tutorial", "closeInventoryEvent", pPlayer)
		CreatureObject(pPlayer):playMusicMessage("sound/tut_26_closeinventory.snd")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:close_inventory")
		createEvent(15000, "Tutorial", "doCloseInventoryReminder", pPlayer, "")
	elseif (curStep == 3) then -- Toolbar
		CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("toolbar", 1, 3)
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:show_toolbar")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_23_toolbar.snd")
		createEvent(5000, "Tutorial", "handleRoomTwo", pPlayer, "")
	elseif (curStep == 4) then -- Toolbar drag
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_00_toolbardrag")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_00_toolbardrag.snd")
		createEvent(15000, "Tutorial", "handleRoomTwo", pPlayer, "")
	elseif (curStep == 5) then -- Move to next room
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:visit_commerce_room")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_27_proceed.snd")
		createEvent(15000, "Tutorial", "doCommerceRoomReminder", pPlayer, "")
		self:markRoomComplete(pPlayer, "r2")
	end

	writeData(playerID .. ":tutorial:currentStep:r2", curStep + 1)
end

-- Reminder to move to commerce room if player has not changed room after timer ends
function Tutorial:doCommerceRoomReminder(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r2") or self:isRoomComplete(pPlayer, "r2")) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:repeat_visit_commerce")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_27_proceed.snd")
end

-- Triggered when player opens the item drum, explains taking items from drum using radial
function Tutorial:drumOpenEvent(pDrum, pPlayer)
	if (pPlayer == nil or pDrum == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if(readData(playerID .. ":tutorial:hasOpenedDrum") == 1) then
		return 1
	end

	if (not self:isInRoom(pPlayer, "r2") or self:isRoomComplete(pPlayer, "r2")) then
		return 1
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:prompt_take_items")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_16_a_youcantake.snd")
	writeData(playerID .. ":tutorial:hasOpenedDrum", 1)

	for i = 0, SceneObject(pDrum):getContainerObjectsSize() - 1, 1 do
		local pItem = SceneObject(pDrum):getContainerObject(i)

		if pItem ~= nil then
			createObserver(OBJECTRADIALOPENED, "Tutorial", "drumItemRadialEvent", pItem)
		end
	end

	return 1
end

-- Triggered when player closes the drum, explains opening inventory and triggering free mouse
function Tutorial:drumCloseEvent(pDrum, pPlayer)
	if (pPlayer == nil or pDrum == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if(readData(playerID .. ":tutorial:hasClosedDrum") == 1) then
		return 1
	end

	if (not self:isInRoom(pPlayer, "r2") or self:isRoomComplete(pPlayer, "r2")) then
		return 1
	end

	writeData(playerID .. ":tutorial:hasClosedDrum", 1)

	CreatureObject(pPlayer):playMusicMessage("sound/tut_19_inventory.snd")
	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:explain_freemouse")
	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:explain_freemouse_toggle")
	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:explain_inventory")

	CreatureObject(pPlayer):sendNewbieTutorialRequest("openInventory")
	createObserver(NEWBIEOPENINVENTORY, "Tutorial", "openInventoryEvent", pPlayer)
	createEvent(20000, "Tutorial", "doOpenInventoryReminder", pPlayer, "")

	return 1
end

-- Reminds player to open inventory if they have not done so after timer expires
function Tutorial:doOpenInventoryReminder(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r2")) then
		return
	end

	if(readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:hasOpenedInventory") == 1) then
		return
	end

	CreatureObject(pPlayer):playMusicMessage("sound/tut_25_openinventory.snd")
	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:repeat_open_inventory")
end

-- Triggered when player opens inventory, prompts them to find food item and use it.
function Tutorial:openInventoryEvent(pPlayer)
	if (pPlayer == nil) then
		return 1
	end

	if (not self:isInRoom(pPlayer, "r2") or self:isRoomComplete(pPlayer, "r2")) then
		return 1
	end

	CreatureObject(pPlayer):playMusicMessage("sound/tut_20_selectfooditem.snd")
	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:prompt_find_food")

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return 1
	end

	for i = 0, SceneObject(pInventory):getContainerObjectsSize() - 1, 1 do
		local pItem = SceneObject(pInventory):getContainerObject(i)

		-- Sets radial observer if item is food
		if pItem ~= nil and SceneObject(pItem):getGameObjectType() == 8202 then
			createObserver(OBJECTRADIALOPENED, "Tutorial", "melonRadialEvent", pItem)
		end
	end

	writeData(SceneObject(pPlayer):getObjectID() .. ":tutorial:hasOpenedInventory", 1)

	return 1
end

-- Reminds player to close inventory if they have not done so after timer expires
function Tutorial:doCloseInventoryReminder(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r2")) then
		return
	end

	if(readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:hasClosedInventory") == 1) then
		return
	end

	CreatureObject(pPlayer):playMusicMessage("sound/tut_26_closeinventory.snd")
	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:close_inventory")
end

-- Triggered when player closes inventory
function Tutorial:closeInventoryEvent(pPlayer)
	if (pPlayer == nil) then
		return 1
	end

	if (not self:isInRoom(pPlayer, "r2") or self:isRoomComplete(pPlayer, "r2")) then
		return 1
	end

	writeData(SceneObject(pPlayer):getObjectID() .. ":tutorial:hasClosedInventory", 1)

	createEvent(5000, "Tutorial", "handleRoomTwo", pPlayer, "")

	return 1
end

-- Triggered when player opens radial on food item, prompts to use item
function Tutorial:melonRadialEvent(pItem, pPlayer)
	if (pPlayer == nil or pItem == nil) then
		return 1
	end

	if (not self:isInRoom(pPlayer, "r2") or self:isRoomComplete(pPlayer, "r2")) then
		return 1
	end

	CreatureObject(pPlayer):playMusicMessage("sound/tut_21_usefood.snd")
	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:prompt_use_item")
	createObserver(OBJECTRADIALUSED, "Tutorial", "melonRadialUsedEvent", pItem)

	return 1
end

-- Triggered when player uses food item, explains attributes from food
function Tutorial:melonRadialUsedEvent(pItem, pPlayer, radialID)
	if (pPlayer == nil or pItem == nil) then
		return 1
	end

	if (not self:isInRoom(pPlayer, "r2") or self:isRoomComplete(pPlayer, "r2")) then
		return 1
	end

	if (radialID ~= 20) then
		return 0
	end

	CreatureObject(pPlayer):playMusicMessage("sound/tut_22_attributes.snd")
	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:explain_item_used")
	createEvent(10000, "Tutorial", "handleRoomTwo", pPlayer, "")
	return 1
end

-- Triggered when an item is removed from the drum, explains inventory
function Tutorial:drumItemLootEvent(pDrum, pPlayer)
	if (pPlayer == nil or pDrum == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if(readData(playerID .. ":tutorial:hasLootedDrumItem") == 1) then
		return
	end

	if (not self:isInRoom(pPlayer, "r2") or self:isRoomComplete(pPlayer, "r2")) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:pickup_complete")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_18_inventory.snd")
	writeData(playerID .. ":tutorial:hasLootedDrumItem", 1)
end

-- Triggered when radial is opened on any item in the drum, prompts to pickup item, only triggers on one item
function Tutorial:drumItemRadialEvent(pDrum, pPlayer)
	if (pPlayer == nil or pDrum == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if(readData(playerID .. ":tutorial:hasOpenedDrumItemRadial") == 1) then
		return 1
	end

	if (not self:isInRoom(pPlayer, "r2") or self:isRoomComplete(pPlayer, "r2")) then
		return 1
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:prompt_select_pickup")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_17_pickup.snd")
	writeData(playerID .. ":tutorial:hasOpenedDrumItemRadial", 1)

	return 1
end

-- Triggered when radial is opened on item drum, prompts to choose open
function Tutorial:drumRadialEvent(pDrum, pPlayer)
	if (pPlayer == nil or pDrum == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if(readData(playerID .. ":tutorial:hasOpenedDrumRadial") == 1) then
		return 1
	end

	if (not self:isInRoom(pPlayer, "r2") or self:isRoomComplete(pPlayer, "r2")) then
		return 1
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:prompt_choose_open")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_15_opencontainer.snd")
	writeData(playerID .. ":tutorial:hasOpenedDrumRadial", 1)

	return 1
end

-- Triggered when player opens radial on room 2 greeter, prompts to converse
function Tutorial:greeterRadialEvent(pGreeter, pPlayer)
	if (pPlayer == nil or pGreeter == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if(readData(playerID .. ":tutorial:isHandlingGreeterConvo") == 1) then
		return 1
	end

	if (not self:isInRoom(pPlayer, "r2") or self:isRoomComplete(pPlayer, "r2")) then
		return 1
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_11")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_11_converse.snd")
	spatialChat(pGreeter, "@newbie_tutorial/newbie_convo:explain_lookat")
	CreatureObject(pGreeter):doAnimation("point_to_self")
	writeData(playerID .. ":tutorial:isHandlingGreeterConvo", 1)

	return 1
end

-- Reminds player to use radial on drum if they have not done so after timer expires
function Tutorial:doDrumRadialReminder(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r2")) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if(readData(playerID .. ":tutorial:hasOpenedDrumRadial") == 1 or readData(playerID .. ":tutorial:hasLootedDrumItem") == 1) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:repeat_open_box")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_16_intheboxyouneed.snd")
end

-- Prompts player to converse with greeter if they have not done so after timer expires
function Tutorial:doGreeterConvoReminder(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r2")) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if(readData(playerID .. ":tutorial:isHandlingGreeterConvo") == 1) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_10")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_10_radialmenu.snd")
	createEvent(15000, "Tutorial", "doGreeterConvoReminder", pPlayer, "")
end

-- ROOM THREE
-- Banking, Shopping
function Tutorial:handleRoomThree(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r3") or self:isRoomComplete(pPlayer, "r3")) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local greeterID = readData(playerID .. ":tutorial:roomThreeBankerID")
	local pGreeter = getSceneObject(greeterID)

	if (pGreeter ~= nil) then
		spatialChat(pGreeter, "@newbie_tutorial/newbie_convo:banker_greeting")
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_28")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_28_converse.snd")

	-- Shows flytext over both bank and bazaar and sets radial observers on both
	local bankID = readData(playerID .. ":tutorial:roomThreeBankID")
	local pBank = getSceneObject(bankID)

	if (pBank ~= nil) then
		createObserver(OBJECTRADIALOPENED, "Tutorial", "bankRadialEvent", pBank)
		SceneObject(pBank):showFlyText("newbie_tutorial/system_messages", "bank_flytext", 255, 255, 0)
	end

	local bazaarID = readData(playerID .. ":tutorial:roomThreeBazaarID")
	local pNewbTerminal = getSceneObject(bazaarID)

	if (pNewbTerminal ~= nil) then
		createObserver(OBJECTRADIALOPENED, "Tutorial", "bazaarRadialEvent", pNewbTerminal)
		SceneObject(pNewbTerminal):showFlyText("newbie_tutorial/system_messages", "bazaar_flytext", 255, 255, 0)
	end
end

-- Triggered when radial is opened on bazaar
function Tutorial:bazaarRadialEvent(pNewbTerminal, pPlayer)
	if (pPlayer == nil or pNewbTerminal == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if(readData(playerID .. ":tutorial:hasOpenedBazaarRadial") == 1) then
		return 1
	end

	if (not self:isInRoom(pPlayer, "r3") or self:isRoomComplete(pPlayer, "r3")) then
		return 1
	end

	createEvent(1000, "Tutorial", "bazaarExplanation", pPlayer, "")

	writeData(playerID .. ":tutorial:hasOpenedBazaarRadial", 1)

	return 1
end

-- Explains item dispenser/bazaar use, reschedules if player is receiving bank explanation
function Tutorial:bazaarExplanation(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if (not self:isInRoom(pPlayer, "r3") or self:isRoomComplete(pPlayer, "r3")) then
		return 1
	end

	-- Reschedule if player is receiving bank explanation
	if (readData(playerID .. ":tutorial:bankExplanationStep") ~= 0) then
		createEvent(5000, "Tutorial", "bazaarExplanation", pPlayer, "")
		return
	end

	local curBazaarStep = readData(playerID .. ":tutorial:bazaarExplanationStep")

	if (curBazaarStep == 0) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:bazaar_info_1")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_29_itemdispenser.snd")
		writeData(playerID .. ":tutorial:bazaarExplanationStep", 1)
		createEvent(6000, "Tutorial", "bazaarExplanation", pPlayer, "")
	elseif (curBazaarStep == 1) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:bazaar_info_2")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_00_bazaar_tease.snd")
		writeData(playerID .. ":tutorial:bazaarExplanationStep", 2)
		createEvent(7000, "Tutorial", "bazaarExplanation", pPlayer, "")
	elseif (curBazaarStep == 2) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:bazaar_info_3")
		deleteData(playerID .. ":tutorial:bazaarExplanationStep")
	end
end

-- Triggered when player opens radial on bank
function Tutorial:bankRadialEvent(pBank, pPlayer)
	if (pPlayer == nil or pBank == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if(readData(playerID .. ":tutorial:hasOpenedBankRadial") == 1) then
		return 1
	end

	if (not self:isInRoom(pPlayer, "r3") or self:isRoomComplete(pPlayer, "r3")) then
		return 1
	end

	createEvent(1000, "Tutorial", "bankExplanation", pPlayer, "")

	writeData(playerID .. ":tutorial:hasOpenedBankRadial", 1)

	return 1
end

-- Explains bank, reschedules explanation if player is getting bazaar explanation
function Tutorial:bankExplanation(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if (not self:isInRoom(pPlayer, "r3") or self:isRoomComplete(pPlayer, "r3")) then
		return 1
	end

	-- Reschedule if player is receiving bazaar explanation
	if (readData(playerID .. ":tutorial:bazaarExplanationStep") ~= 0) then
		createEvent(5000, "Tutorial", "bankExplanation", pPlayer, "")
		return
	end

	local curBankStep = readData(playerID .. ":tutorial:bankExplanationStep")

	if (curBankStep == 0) then
		CreatureObject(pPlayer):playMusicMessage("sound/tut_32_bank.snd")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:bank_info_1")
		writeData(playerID .. ":tutorial:bankExplanationStep", 1)
		createEvent(7000, "Tutorial", "bankExplanation", pPlayer, "")
	elseif (curBankStep == 1) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:bank_info_2")
		writeData(playerID .. ":tutorial:bankExplanationStep", 2)
		createEvent(7000, "Tutorial", "bankExplanation", pPlayer, "")
	elseif (curBankStep == 2) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:bank_info_3")
		writeData(playerID .. ":tutorial:bankExplanationStep", 3)
		createEvent(7000, "Tutorial", "bankExplanation", pPlayer, "")
	elseif (curBankStep == 3) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:bank_info_4")
		writeData(playerID .. ":tutorial:bankExplanationStep", 4)
		createEvent(5000, "Tutorial", "bankExplanation", pPlayer, "")
	elseif (curBankStep == 4) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:bank_info_5")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_33_cash.snd")
		writeData(playerID .. ":tutorial:bankExplanationStep", 5)
		createEvent(3000, "Tutorial", "bankExplanation", pPlayer, "")
	elseif (curBankStep == 5) then
		deleteData(playerID .. ":tutorial:bankExplanationStep")
	end
end

-- Triggers animation on commoners in front of bazaar terms every 10-30 secs
function Tutorial:doBankUserAnimation(pBanker)
	if (pBanker == nil) then
		return
	end

	CreatureObject(pBanker):doAnimation("manipulate_medium")

	createEvent(getRandomNumber(10, 30) * 1000, "Tutorial", "doBankUserAnimation", pBanker, "")
end

-- ROOM FOUR
-- Advises player to move down hall
function Tutorial:handleRoomFour(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r4") or self:isRoomComplete(pPlayer, "r4")) then
		return
	end

	CreatureObject(pPlayer):playMusicMessage("sound/tut_36_movedownhall.snd")
	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_36")
end

-- Triggered when player enters area near clone droid, droid greets player
function Tutorial:notifyEnteredCloneDroidArea(pArea, pPlayer)

	if (pPlayer == nil) then
		return 0
	end

	local cloneDroidID = readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:roomFourCloneDroidID")
	local pDroid = getSceneObject(cloneDroidID)

	if (pDroid ~= nil) then
		CreatureObject(pDroid):doAnimation("wave_greeting")
		spatialChat(pDroid, "@newbie_tutorial/newbie_convo:clone_greeting")
	end

	return 1
end

-- ROOM FIVE
-- Cloning/Insurance
function Tutorial:handleRoomFive(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r5") or self:isRoomComplete(pPlayer, "r5")) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local curStep = readData(playerID .. ":tutorial:currentStep:r5")

	if (curStep == 0) then -- Welcome

		local cloningID = readData(playerID .. ":tutorial:roomFiveCloneTerminalID")
		local pCloning = getSceneObject(cloningID)

		if (pCloning ~= nil) then
			SceneObject(pCloning):showFlyText("newbie_tutorial/system_messages", "clone_here", 255, 255, 0)
		end

		local insuranceID = readData(playerID .. ":tutorial:roomFiveInsuranceTerminalID")
		local pInsurance = getSceneObject(insuranceID)

		if (pInsurance ~= nil) then
			SceneObject(pInsurance):showFlyText("newbie_tutorial/system_messages", "insure_here", 255, 255, 0)
		end

		CreatureObject(pPlayer):playMusicMessage("sound/tut_37_cloning.snd")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_37")

	elseif (curStep == 1) then
		CreatureObject(pPlayer):playMusicMessage("sound/tut_38_insurance.snd")
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_38")
	end
	writeData(playerID .. ":tutorial:currentStep:r5", curStep + 1)
end

-- ROOM SIX
-- Hallway triggers explosion, commoner panics and runs away screaming
-- Radar/Combat actions
function Tutorial:handleRoomSix(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r6") or self:isRoomComplete(pPlayer, "r6")) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local curStep = readData(playerID .. ":tutorial:currentStep:r6")

	if (curStep == 0) then -- Welcome
		local panicID = readData(playerID .. ":tutorial:roomSixPanicCommoner")
		local pPanicNpc = getSceneObject(panicID)

		if (pPanicNpc == nil) then
			return
		end

		CreatureObject(pPanicNpc):playEffect("clienteffect/combat_explosion_lair_large.cef", "")
		createEvent(1000, "Tutorial", "doStartPanic", pPanicNpc, "")
		createEvent(2500, "Tutorial", "handleRoomSix", pPlayer, "")
	elseif (curStep == 1) then -- Radar
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:radar")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_41_advancewarning.snd")
		CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("radar", 1, 3)
		createEvent(8000, "Tutorial", "handleRoomSix", pPlayer, "")
	elseif (curStep == 2) then -- Radar again
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:radar_more")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_42_map.snd")
		createEvent(15000, "Tutorial", "handleRoomSix", pPlayer, "")
	elseif (curStep == 3) then -- overlay
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_43")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_43_zoommap.snd")
	end
	writeData(playerID .. ":tutorial:currentStep:r6", curStep + 1)
end

-- Starts panic action on commoner after explosion, commoner runs to room 4 while yelling
function Tutorial:doStartPanic(pPanicNpc)
	if (pPanicNpc == nil) then
		return
	end

	local pBuilding = self:getTutorialBuilding(pPanicNpc)

	if (pBuilding == nil) then
		return
	end

	local pCell = BuildingObject(pBuilding):getNamedCell("r4")
	local cellID = SceneObject(pCell):getObjectID()

	self:doPanicYelling(pPanicNpc)

	AiAgent(pPanicNpc):addObjectFlag(AI_NOAIAGGRO)
	AiAgent(pPanicNpc):addObjectFlag(AI_ESCORT)
	AiAgent(pPanicNpc):addObjectFlag(AI_STATIONARY) -- Don't move unless patrol point is added to list, walking speed
	AiAgent(pPanicNpc):setMovementState(AI_PATROLLING)
	AiAgent(pPanicNpc):stopWaiting()
	AiAgent(pPanicNpc):setNextPosition(47.1, -7, -51.5, cellID)
	AiAgent(pPanicNpc):executeBehavior()
end

-- Triggers yelling on panic commoner, 10 second intervals, 3 messages
function Tutorial:doPanicYelling(pNpc)
	if (pNpc == nil) then
		return
	end

	local panicYell = readData(SceneObject(pNpc):getObjectID() .. ":panicYell")
	if (panicYell == 0) then
		panicYell = 1
	end

	spatialMoodChat(pNpc, "@newbie_tutorial/newbie_convo:shout_panic" .. panicYell, 0, 80)

	if (panicYell < 3) then
		writeData(SceneObject(pNpc):getObjectID() .. ":panicYell", panicYell + 1)
		createEvent(10000, "Tutorial", "doPanicYelling", pNpc, "")
	end
end

-- ROOM SEVEN
-- Combat explain
function Tutorial:handleRoomSeven(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r7") or self:isRoomComplete(pPlayer, "r7")) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	for i = 1, 3, 1 do
		local celebID = readData(playerID .. ":tutorial:roomSevenNervousGuy" .. i)
		local pCeleb = getSceneObject(celebID)

		if (pCeleb ~= nil) then
			createEvent(getRandomNumber(5, 10) * 1000, "Tutorial", "doNervousGuySpeak", pCeleb, "")
		end
	end

	local soldierID = readData(playerID .. ":tutorial:roomSevenScaredSoldier")
	local pSoldier = getSceneObject(soldierID)

	if (pSoldier ~= nil) then
		CreatureObject(pSoldier):doAnimation("slow_down")
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_40")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_40_converse.snd")
end

-- Random spatial event for nervous commoners in room
function Tutorial:doNervousGuySpeak(pGuy)
	if (pGuy == nil) then
		return
	end

	local playerID = readData(SceneObject(pGuy):getObjectID() .. ":playerID")
	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil or self:isRoomComplete(pPlayer, "r7")) then
		return
	end

	-- Throttle messages so they dont always occur every iteration
	if (self:isInRoom(pPlayer, "r7") and getRandomNumber(1, 20) > 10) then
		spatialChat(pGuy, "@newbie_tutorial/newbie_convo:nervous_guy" .. getRandomNumber(1,5))
	end

	createEvent(getRandomNumber(20, 30) * 1000, "Tutorial", "doNervousGuySpeak", pGuy, "")
end

-- Hallway with debris blocking path, must be destroyed
function Tutorial:handleRoomFourteen(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r14") or self:isRoomComplete(pPlayer, "r14")) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_45")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_45_proceed.snd")
end

-- Triggered when debris is destroyed, schedules event to remove debris from world
function Tutorial:debrisDestroyed(pDebris, pPlayer)
	if (pPlayer == nil) then
		return 1
	end

	self:markRoomComplete(pPlayer, "r14")

	if (pDebris == nil) then
		return 1
	end

	createEvent(1000, "Tutorial", "removeDebris", pDebris, "")

	return 1
end

-- Removes debris from world
function Tutorial:removeDebris(pDebris)
	if (pDebris == nil) then
		return
	end

	SceneObject(pDebris):destroyObjectFromWorld()
end

-- ROOM EIGHT
-- Combat, player fights pirate
function Tutorial:handleRoomEight(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r8") or self:isRoomComplete(pPlayer, "r8")) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local pirateID = readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:roomEightPirate")
	local pPirate = getSceneObject(pirateID)

	local curStep = readData(playerID .. ":tutorial:currentStep:r8")

	if (curStep == 0) then
		-- Explain combat message 1, pirate taunts
		if (pPirate ~= nil and not CreatureObject(pPirate):isDead() and not AiAgent(pPirate):isInCombat()) then
			spatialMoodChat(pPirate, "@newbie_tutorial/newbie_convo:pirate_taunt1", 4, 0)
		end
		CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("all", 1, 0)
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:explain_combat_1")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_47_defaultattack.snd")
		createEvent(5000, "Tutorial", "handleRoomEight", pPlayer, "")
	elseif (curStep == 1) then -- Explain combat message 2, pirate taunts again
		spatialMoodChat(pPirate, "@newbie_tutorial/newbie_convo:pirate_taunt2", 4, 0)
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:explain_combat_2")
		createEvent(5000, "Tutorial", "handleRoomEight", pPlayer, "")
	elseif (curStep == 2) then -- Explain combat message 3
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:explain_combat_3")
	end
	writeData(playerID .. ":tutorial:currentStep:r8", curStep + 1)
end

-- Triggered by pirate during combat
function Tutorial:handlePirateGrenade(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pirateID = readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:roomEightPirate")
	local pPirate = getSceneObject(pirateID)

	if (pPirate == nil or CreatureObject(pPirate):isDead()) then
		return
	end

	local grenadeStep = readData(SceneObject(pPirate):getObjectID() .. ":grenadeStep")

	if (grenadeStep == 0) then -- Pirate taunts that he has grenade
		spatialMoodChat(pPirate, "@newbie_tutorial/newbie_convo:pirate_taunt3", 4, 0)
		writeData(SceneObject(pPirate):getObjectID() .. ":grenadeStep", 1)
		createEvent(3000, "Tutorial", "handlePirateGrenade", pPlayer, "")
	elseif (grenadeStep == 1) then -- Faulty grenade, schedules explosion
		spatialMoodChat(pPirate, "@newbie_tutorial/newbie_convo:pirate_taunt4", 4, 0)
		createEvent(2000, "Tutorial", "doGrenadeExplode", pPirate, "")
	end
end

-- Blows up pirate after timer
function Tutorial:doGrenadeExplode(pPirate)
	if (pPirate == nil) then
		return
	end

	local playerID = readData(SceneObject(pPirate):getObjectID() .. ":playerID")
	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		pPlayer = pPirate
	end

	CreatureObject(pPirate):playEffect("clienteffect/combat_explosion_lair_large.cef", "")
	CreatureObject(pPirate):inflictDamage(pPlayer, 0, 1000000, 1)
end

-- Triggers combat with pirate when player enters area near pirate, schedules grenade explosion
function Tutorial:notifyEnteredPirateArea(pArea, pPlayer)
	if (pPlayer == nil) then
		return 1
	end

	local pirateID = readData(SceneObject(pPlayer):getObjectID() .. ":tutorial:roomEightPirate")
	local pPirate = getSceneObject(pirateID)

	if (pPirate == nil) then
		return 1
	end

	AiAgent(pPirate):addDefender(pPlayer)
	return 1
end

-- Triggered when pirate adds a defender, either by player initiating combat or entering area near pirate
function Tutorial:pirateDefenderAdded(pPirate, pPlayer)
	if (pPlayer == nil or pPirate == nil) then
		return 1
	end

	createEvent(10000, "Tutorial", "handlePirateGrenade", pPlayer, "")
	spatialMoodChat(pPirate, "@newbie_tutorial/newbie_convo:pirate_attack", 4, 0)

	return 1
end

-- Triggered when pirate is killed, calls congrats function
function Tutorial:pirateKilled(pPirate, pPlayer)
	if (pPlayer == nil) then
		print("***** pirateKilled: pPlayer == nil *****")
		return 1
	end

	self:markRoomComplete(pPlayer, "r8")

	self:pirateCongrats(pPlayer)

	return 1
end

-- Congratulates player, explains looting pirate, unlocks room 9 to player
function Tutorial:pirateCongrats(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:loot_pirate")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_00_congratulations.snd")

	local pBuilding = self:getTutorialBuilding(pPlayer)

	if (pBuilding == nil) then
		return 1
	end

	local pCell = BuildingObject(pBuilding):getNamedCell("r9")

	if (pCell ~= nil) then
		updateCellPermission(pCell, true, pPlayer)
	end

	return 1
end

-- ROOM NINE
-- Skill training
function Tutorial:handleRoomNine(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r9")) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	local curStep = readData(playerID .. ":tutorial:currentStep:r9")

	if (curStep == 0) then
		local playerID = SceneObject(pPlayer):getObjectID()

		for i = 1, 2, 1 do
			local celebID = readData(playerID .. ":tutorial:roomNineCeleb" .. i)
			local pCeleb = getSceneObject(celebID)
			if (pCeleb ~= nil) then
				createEvent(getRandomNumber(2,4) * 1000, "Tutorial", "doCelebAnimation", pCeleb, "")
				createEvent(getRandomNumber(5,10) * 1000, "Tutorial", "doCelebSpeak", pCeleb, "")
			end
		end

	elseif (curStep == 1) then -- Explains character sheet
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_51")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_51_charactersheet.snd")
		createEvent(10000, "Tutorial", "handleRoomNine", pPlayer, "")
	elseif (curStep == 2) then -- Advises to move to next room
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:visit_commerce_room") -- Not actually commerce room, but only string that matches sound
		CreatureObject(pPlayer):playMusicMessage("sound/tut_52_walkdown.snd")
	end
	writeData(playerID .. ":tutorial:currentStep:r9", curStep + 1)
end

-- Event random spatials for celebs in room
function Tutorial:doCelebSpeak(pCeleb)
	if (pCeleb == nil) then
		return
	end

	local playerID = readData(SceneObject(pCeleb):getObjectID() .. ":playerID")
	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil or self:isRoomComplete(pPlayer, "r9")) then
		return
	end

	-- Throttle messages so they dont always occur every iteration
	if (self:isInRoom(pPlayer, "r9") and getRandomNumber(1,20) > 10) then
		spatialChat(pCeleb, "@newbie_tutorial/newbie_convo:celeb_guy" .. getRandomNumber(1,5))
	end

	createEvent(getRandomNumber(20,30) * 1000, "Tutorial", "doCelebSpeak", pCeleb, "")
end

-- Random animated cheering event for celebs in room
function Tutorial:doCelebAnimation(pCeleb)
	if (pCeleb == nil) then
		return
	end

	local playerID = readData(SceneObject(pCeleb):getObjectID() .. ":playerID")
	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil or self:isRoomComplete(pPlayer, "r9")) then
		return
	end

	CreatureObject(pCeleb):doAnimation("celebrate")
	createEvent(getRandomNumber(5,10) * 1000, "Tutorial", "doCelebAnimation", pCeleb, "")
end

-- Triggered when ending conversation with training room officer, explains skill trainer
function Tutorial:finishedTrainingRoomOfficerConvo(pOfficer, pPlayer)
	if (pPlayer == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if (readData(playerID .. ":tutorial:spokeToTrainingRoomOfficer") == 1) then
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_49")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_49_skilltrainer.snd")

		local trainerID = readData(playerID .. ":tutorial:roomNineTrainer")
		local pTrainer = getSceneObject(trainerID)

		if (pTrainer ~= nil) then
			spatialChat(pTrainer, "@newbie_tutorial/newbie_convo:trainer_grunt")
		end

		return 1
	end

	return 0
end

-- Triggered by ending convo with trainer, checks to see if player has trained a skill
function Tutorial:finishedTrainerConvo(pOfficer, pPlayer)
	if (pPlayer == nil) then
		return 1
	end

	-- Player did not pick up a skillbox
	if (self:getPlayerProfession(pPlayer) == "") then
		return 0
	end

	CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_50")
	CreatureObject(pPlayer):playMusicMessage("sound/tut_50_skillbrowser.snd")
	createEvent(25000, "Tutorial", "handleRoomNine", pPlayer, "")
	return 1
end

-- ROOM TEN
-- Missions/Waypoints
-- TODO: Need trapped_guy use doTrappedGuySpam
function Tutorial:handleRoomTen(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r10")) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local curStep = readData(playerID .. ":tutorial:currentStep:r10")

	if (curStep == 0) then -- Explain Missions
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_53")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_53_missions.snd")
		createEvent(12000, "Tutorial", "handleRoomTen", pPlayer, "")
	elseif (curStep == 1) then -- Explain npc missions
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_54")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_54_npcmission.snd")
	elseif (curStep == 2) then -- Advise player to move to quartermaster
		CreatureObject(pPlayer):sendSystemMessage("@newbie_tutorial/system_messages:tut_56")
		CreatureObject(pPlayer):playMusicMessage("sound/tut_56_quartermaster.snd")
	end
	writeData(playerID .. ":tutorial:currentStep:r10", curStep + 1)
end

-- Random spatial event for guy trapped by training officer
function Tutorial:doTrappedGuySpam(pMobile)
	if (pMobile == nil) then
		return
	end

	local playerID = readData(SceneObject(pMobile):getObjectID() .. ":playerID")
	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil or self:isRoomComplete(pPlayer, "r10")) then
		return
	end

	if (getRandomNumber(1,10) > 5 and self:isInRoom(pPlayer, "r10")) then
		spatialChat(pMobile, "@newbie_tutorial/newbie_convo:trapped_guy" .. getRandomNumber(1,5))
	end

	createEvent(getRandomNumber(20,30) * 1000, "Tutorial", "doTrappedGuySpam", pMobile, "")
end

-- ROOM ELEVEN
-- Travel
function Tutorial:handleRoomEleven(pPlayer)
	if (pPlayer == nil) then
		return
	end

	if (not self:isInRoom(pPlayer, "r11")) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local qmID = readData(playerID .. ":tutorial:roomElevenQuartermaster")
	local pQuartermaster = getSceneObject(qmID)

	if (pQuartermaster ~= nil and readData(qmID .. ":barked") ~= 1) then
		spatialChat(pQuartermaster, "@newbie_tutorial/newbie_convo:quarter_greeting")
		writeData(qmID .. ":barked", 1)
	end
end

-- Random spatial event for refugees in room 11
function Tutorial:doRefugeeSpam(pMobile)
	if (pMobile == nil) then
		return
	end

	local playerID = readData(SceneObject(pMobile):getObjectID() .. ":playerID")
	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil or self:isRoomComplete(pPlayer, "r11")) then
		return
	end

	if (getRandomNumber(1,10) > 5 and self:isInRoom(pPlayer, "r11")) then
		spatialChat(pMobile, "@newbie_tutorial/newbie_convo:refugee" .. getRandomNumber(1,5))
	end

	createEvent(getRandomNumber(20,30) * 1000, "Tutorial", "doRefugeeSpam", pMobile, "")
end

-- **** General Functions ****

-- Gets player trainer based on player's profession
function Tutorial:getPlayerTrainer(pPlayer)
	if (pPlayer == nil) then
		print("pPlayer == nil, returning marksman...")
		return "trainer_marksman"
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if (playerID == nil) then
		print("playerID == nil, returning nil...")
		return ""
	end

	local playerProfession = readStringData(playerID .. ":profession:") -- self:getPlayerProfession(pPlayer)
	print("playerProfession == " .. playerProfession)

	if (playerProfession == "") then
		print("playerProfession == nil, returning marksman...")
		return "trainer_marksman"
	end

	local tokenizer = {}
	for word in playerProfession:gmatch("%w+") do table.insert(tokenizer, word) end

	return "trainer_" .. tokenizer[2]
end

-- Gets player's profession based on novice skill
function Tutorial:getPlayerProfession(pPlayer)
	if (pPlayer == nil) then
		return ""
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if (playerID == nil) then
		return ""
	end

	local playerProfession = readStringData(playerID .. ":profession:")

	if (playerProfession == nil) then
		return ""
	end

	print("getPlayerProfession .. playerProfession == " .. tostring(playerProfession))

	if (CreatureObject(pPlayer):hasSkill("combat_brawler_novice")) then
		return "combat_brawler"
	elseif (CreatureObject(pPlayer):hasSkill("combat_marksman_novice")) then
		return "combat_marksman"
	elseif (CreatureObject(pPlayer):hasSkill("outdoors_scout_novice")) then
		return "outdoors_scout"
	elseif (CreatureObject(pPlayer):hasSkill("science_medic_novice")) then
		return "science_medic"
	elseif (CreatureObject(pPlayer):hasSkill("social_entertainer_novice")) then
		return "social_entertainer"
	elseif (CreatureObject(pPlayer):hasSkill("crafting_artisan_novice")) then
		return "crafting_artisan"
	else
		return ""
	end
end

-- Gets the tutorial building the player is in
function Tutorial:getTutorialBuilding(pPlayer)
	if (pPlayer == nil) then
		return nil
	end

	return SceneObject(pPlayer):getRootParent()
end

-- Marks a room complete, if hud elements were enabled in that room, ensures they are enabled
function Tutorial:markRoomComplete(pPlayer, roomName)
	if (pPlayer == nil) then
		print("***** markRoomComplete: pPlayer == nil *****")
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	local firstName = CreatureObject(pPlayer):getFirstName()

	if (firstName == nil) then
		return
	end

	if (roomName == "r1") then
		CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("chatbox", 1, 0)
	elseif (roomName == "r2") then
		CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("toolbar", 1, 0)
	elseif (roomName == "r6") then
		CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("radar", 1, 0)
	elseif (roomName == "r8") then
		CreatureObject(pPlayer):sendNewbieTutorialEnableHudElement("all", 1, 0)
	end

	print("Tutorial:markRoomComplete: " .. tostring(firstName) .. ", " .. roomName)
	writeScreenPlayData(pPlayer, "tutorial", roomName .. "Complete", 1)
end

-- Checks if room is complete
function Tutorial:isRoomComplete(pPlayer, roomName)
	if (pPlayer == nil or roomName == nil or roomName == "") then
		return false
	end

	return tonumber(readScreenPlayData(pPlayer, "tutorial", roomName .. "Complete")) == 1
end

-- Checks if player is in a room
function Tutorial:isInRoom(pPlayer, roomName)
	if (pPlayer == nil or roomName == nil or roomName == "") then
		return false
	end

	local playerCellID = CreatureObject(pPlayer):getParentID()

	if (playerCellID == 0) then
		return false
	end

	local pBuilding = self:getTutorialBuilding(pPlayer)

	if (pBuilding == nil or not SceneObject(pBuilding):isBuildingObject()) then
		return false
	end

	local pCell = BuildingObject(pBuilding):getNamedCell(roomName)

	if (pCell == nil or not SceneObject(pCell):isCellObject()) then
		return false
	end

	return (SceneObject(pCell):getObjectID() == playerCellID)
end

-- Gives a player permission to a group
function Tutorial:givePermission(pPlayer, permissionGroup)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		PlayerObject(pGhost):addPermissionGroup(permissionGroup, true)
	end
end

-- Removes player permission to a group
function Tutorial:removePermission(pPlayer, permissionGroup)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):hasPermissionGroup(permissionGroup)) then
		PlayerObject(pGhost):removePermissionGroup(permissionGroup, true)
	end

end

-- Checks if player has permission to a group
function Tutorial:hasPermission(pPlayer, permissionGroup)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	return pGhost ~= nil and PlayerObject(pGhost):hasPermissionGroup(permissionGroup)
end
