CrackdownCantina = ScreenPlay:new {
	cantinaPlanets = { "corellia", "naboo", "tatooine" },

	cantinaOids = {
		corellia = { { 2625352, "tyrena" }, { 3005396, "kor_vella" }, { 3005694, "vreni_island" }, { 3075426, "doaba_guerfel" }, { 3375352, "bela_vistal" }, { 8105493, "coronet" } },
		naboo = { { 2, "keren" }, { 61, "kaadara" }, { 88, "theed" }, { 108, "moenia" } },
		tatooine = { { 1028644, "bestine" }, { 1082874, "mos_eisley" }, { 1134557, "wayfar" }, { 1256055, "mos_espa" } }
	},

	debugNotify = true -- Send system message when successfully triggered (for debugging)
}

registerScreenPlay("CrackdownCantina", true)

function CrackdownCantina:start()
	for i = 1, #self.cantinaPlanets, 1 do
		local planetName = self.cantinaPlanets[i]

		if (isZoneEnabled(planetName)) then
			local oidList = self.cantinaOids[planetName]

			for j = 1, #oidList, 1 do
				local pCantina = getSceneObject(oidList[j][1])

				if pCantina ~= nil then
					createObserver(ENTEREDBUILDING, "CrackdownCantina", "onEnteredCantina", pCantina)
				end
			end
		end
	end
end

function CrackdownCantina:doCleanup(pBuilding)
	if (pBuilding == nil) then
		return
	end

	local cantinaID = SceneObject(pBuilding):getObjectID()
	local mobileID = readData(cantinaID .. ":harasserID")

	deleteData(cantinaID .. ":harasserID")
	deleteData(cantinaID .. ":crackdownInProgress")
	deleteData(mobileID .. ":harassing")
	deleteData(mobileID .. ":lastHarass")
	deleteData(mobileID .. ":timesHarassed")
	deleteData(mobileID .. ":doneHarassing")
	deleteData(mobileID .. ":targetID")
	deleteStringData(mobileID .. ":nextPoint")
	deleteStringData(mobileID .. ":factionName")
end

function CrackdownCantina:onEnteredCantina(pCantina, pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	local cantinaID = SceneObject(pCantina):getObjectID()

	if (readData(cantinaID .. ":crackdownInProgress") == 1) then
		local mobileID = readData(cantinaID .. ":harasserID")
		local pMobile = getSceneObject(mobileID)

		if (pMobile == nil or CreatureObject(pMobile):isDead()) then
			createEvent(30000, "CrackdownCantina", "doCleanup", pCantina, "")
		end

		return 0
	end

	self:handlePotentialTrouble(pCantina, pPlayer)

	return 0
end

function CrackdownCantina:handlePotentialTrouble(pCantina, pPlayer)
	if (readData(SceneObject(pCantina):getObjectID() .. ":crackdownInProgress") == 1) then
		return
	end

	-- Only going to check for trouble 20% of the time
	if (getRandomNumber(100) > 20) then
		return
	end

	if (self.debugNotify) then
		CreatureObject(pPlayer):sendSystemMessage("Debug: Cantina crackdown triggered")
	end
	createEvent(15000, "CrackdownCantina", "startTrouble", pCantina, "")
end

function CrackdownCantina:startTrouble(pCantina)
	if (pCantina == nil) then
		return
	end

	local cantinaID = SceneObject(pCantina):getObjectID()

	local pFoyer = BuildingObject(pCantina):getNamedCell("foyer1")

	if (pFoyer == nil) then
		return
	end

	local foyerID = SceneObject(pFoyer):getObjectID()

	writeData(cantinaID .. ":crackdownInProgress", 1)
	local zoneName = SceneObject(pCantina):getZoneName()
	local controllingFaction = getControllingFaction(zoneName)
	local cantinaCity = self:getCantinaCity(cantinaID, zoneName)

	-- Some cities are always controlled by a specific faction
	if cantinaCity == "bestine" or cantinaCity == "bela_vistal" or cantinaCity == "deeja_peak" then
		controllingFaction = FACTIONIMPERIAL
	elseif cantinaCity == "vreni_island" or cantinaCity == "moenia" then
		controllingFaction = FACTIONREBEL
	end

	local spawnTemplate
	local factionName

	if (controllingFaction == FACTIONIMPERIAL or controllingFaction == FACTIONNEUTRAL) then
		spawnTemplate = "crackdown_stormtrooper"
		factionName = "imperial"
	else
		spawnTemplate = "crackdown_rebel_command_security_guard"
		factionName = "rebel"
	end

	local pSpawn = spawnMobile(zoneName, spawnTemplate, 0, 48.13, .1, 2.47, 0, foyerID)

	if (pSpawn == nil) then
		deleteData(cantinaID .. ":crackdownInProgress")
		return
	end

	writeData(cantinaID .. ":harasserID", SceneObject(pSpawn):getObjectID())

	spatialChat(pSpawn, "@npc_reaction/imperial_crackdown_cantina:call_in_" .. factionName)
	createEvent(10, "CrackdownCantina", "setupHarasser", pSpawn, factionName)
end

function CrackdownCantina:setupHarasser(pMobile, factionName)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	local mobileID = SceneObject(pMobile):getObjectID()
	createObserver(DESTINATIONREACHED, "CrackdownCantina", "destinationReached", pMobile)
	createObserver(DEFENDERADDED, "CrackdownCantina", "onStartedCombat", pMobile)

	writeStringData(mobileID .. ":nextPoint", "cantina")
	writeStringData(mobileID .. ":factionName", factionName)
	AiAgent(pMobile):setAiTemplate("cantinacrackdown") -- Don't move unless patrol point is added to list, walking speed
	AiAgent(pMobile):setFollowState(4) -- Patrolling

	createEvent(2000, "CrackdownCantina", "moveToHarassPoint", pMobile, "")
end

function CrackdownCantina:onStartedCombat(pMobile, pPlayer)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return 1
	end

	local mobileID = SceneObject(pMobile):getObjectID()

	if (readData(mobileID .. ":doneHarassing") ~= 1) then
		writeData(mobileID .. ":doneHarassing", 1)
		createEvent(60000, "CrackdownCantina", "finishHarassing", pMobile, "")
	end

	if (readData(mobileID .. ":calledForBackup") ~= 1) then
		writeData(mobileID .. ":calledForBackup", 1)
		writeData(mobileID .. ":targetID", SceneObject(pPlayer):getObjectID())
		spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:back_up")
		local factionName = readStringData(mobileID .. ":factionName")
		createEvent(1000, "CrackdownCantina", "callForBackup", pMobile, factionName)
	end

	return 1
end

function CrackdownCantina:moveToHarassPoint(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	local pBuilding = self:getCantinaBuilding(pMobile)

	if (pBuilding == nil) then
		return
	end

	local pNewCell = BuildingObject(pBuilding):getNamedCell("cantina")
	local cellID = SceneObject(pNewCell):getObjectID()

	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)
	AiAgent(pMobile):setNextPosition(22.37, -0.9, 0.98, cellID)
	AiAgent(pMobile):setHomeLocation(22.37, -0.9, 0.98, pNewCell)
	AiAgent(pMobile):executeBehavior()
end

function CrackdownCantina:destinationReached(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return 1
	end

	local mobileID = SceneObject(pMobile):getObjectID()

	local pointName = readStringData(mobileID .. ":nextPoint")
	deleteStringData(mobileID .. ":nextPoint")

	local factionName = readStringData(mobileID .. ":factionName")

	if (pointName == "cantina") then
		spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:rebel_scum_" .. factionName)
		createEvent(7000, "CrackdownCantina", "startHarassing", pMobile, "")
	elseif (pointName == "harassPlayer") then
		spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:sudden_moves_" .. factionName)

		local playerID = readData(mobileID .. ":harassing")

		local pPlayer = getSceneObject(playerID)

		if (pPlayer ~= nil) then
			SceneObject(pPlayer):faceObject(pPlayer, true)
			createEvent(7000, "CrackdownCantina", "continueHarassingPlayer", pMobile, "")
		end
	elseif (pointName == "exit") then
		spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:back_home")
		createEvent(7000, "CrackdownCantina", "leaveCantina", pMobile, "")
	elseif (pointName == "backupLoc") then
		local targetID = readData(mobileID .. ":targetID")
		local pTarget = getSceneObject(targetID)

		if pTarget ~= nil then
			CreatureObject(pMobile):engageCombat(pTarget)
			deleteData(mobileID .. ":targetID")
		end
	end

	return 0
end

function CrackdownCantina:leaveCantina(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	if (AiAgent(pMobile):isInCombat()) then
		createEvent(60000, "CrackdownCantina", "leaveCantina", pMobile, "")
		return
	end

	local pBuilding = self:getCantinaBuilding(pMobile)

	if (pBuilding ~= nil) then
		createEvent(2000, "CrackdownCantina", "doCleanup", pBuilding, "")
	end

	SceneObject(pMobile):destroyObjectFromWorld()
end

function CrackdownCantina:destroyMobile(pMobile)
	if (pMobile == nil) then
		return
	end

	SceneObject(pMobile):destroyObjectFromWorld()
end

function CrackdownCantina:startHarassing(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	local pBuilding = self:getCantinaBuilding(pMobile)

	if (pBuilding == nil) then
		return
	end

	local mobileID = SceneObject(pMobile):getObjectID()
	local playerTable = self:getPlayersInCantina(pBuilding, pMobile, 20)

	local playerCount = #playerTable
	local factionName = readStringData(mobileID .. ":factionName")
	local harassingPlayer = 0
	local foundHarass = false

	if (playerCount <= 0) then
		spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:no_one_here_" .. factionName)
		createEvent(5000, "CrackdownCantina", "finishHarassing", pMobile, "")
	elseif (playerCount == 1) then
		local pPlayer = playerTable[1]
		spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:only_one_here_" .. factionName)

		if (pPlayer ~= nil) then
			SceneObject(pMobile):faceObject(pPlayer, true)
			harassingPlayer = SceneObject(pPlayer):getObjectID()
			writeData(mobileID .. ":harassing", harassingPlayer)
			foundHarass = true
			createEvent(12000, "CrackdownCantina", "harassPlayer", pMobile, "")
		end
	else
		local harassFaction

		if (factionName == "imperial") then
			harassFaction = FACTIONREBEL
		else
			harassFaction = FACTIONIMPERIAL
		end

		local pTarget

		for i = 1, playerCount, 1 do
			local pPlayer = playerTable[i]
			if (pPlayer ~= nil and CreatureObject(pPlayer):getFaction() == harassFaction) then
				pTarget = pPlayer
			end
		end

		if (pTarget ~= nil) then
			spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:harass_guy_" .. factionName)
			harassingPlayer = SceneObject(pTarget):getObjectID()
			writeData(mobileID .. ":harassing", harassingPlayer)
			foundHarass = true
			createEvent(10000, "CrackdownCantina", "harassPlayer", pMobile, "")
		end
	end

	if (not foundHarass) then
		local pPlayer = playerTable[1]
		spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:harass_guy_" .. factionName)

		if (pPlayer ~= nil) then
			harassingPlayer = SceneObject(pPlayer):getObjectID()
			writeData(mobileID .. ":harassing", harassingPlayer)
			createEvent(10000, "CrackdownCantina", "harassPlayer", pMobile, "")
		end
	end
end

function CrackdownCantina:harassPlayer(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	local mobileID = SceneObject(pMobile):getObjectID()
	local playerID = readData(mobileID .. ":harassing")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		createEvent(15000, "CrackdownCantina", "finishHarassing", pMobile, "")
		return
	end

	local factionName = readStringData(mobileID .. ":factionName")
	SceneObject(pMobile):faceObject(pPlayer, true)
	spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:looking_at_" .. factionName)

	createEvent(3000, "CrackdownCantina", "moveToPlayer", pMobile, "")
end

function CrackdownCantina:moveToPlayer(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	local mobileID = SceneObject(pMobile):getObjectID()
	local playerID = readData(mobileID .. ":harassing")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		createEvent(15000, "CrackdownCantina", "finishHarassing", pMobile, "")
		return
	end

	writeStringData(mobileID .. ":nextPoint", "harassPlayer")
	local factionName = readStringData(mobileID .. ":factionName")
	spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:checking_out_" .. factionName)

	AiAgent(pMobile):setHomeLocation(SceneObject(pPlayer):getPositionX() + 1, SceneObject(pPlayer):getPositionZ(), SceneObject(pPlayer):getPositionY(), SceneObject(pPlayer):getParent())
	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)
	AiAgent(pMobile):setNextPosition(SceneObject(pPlayer):getPositionX() + 1, SceneObject(pPlayer):getPositionZ(), SceneObject(pPlayer):getPositionY(), SceneObject(pPlayer):getParentID())
	AiAgent(pMobile):executeBehavior()
end

function CrackdownCantina:continueHarassingPlayer(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	local mobileID = SceneObject(pMobile):getObjectID()
	local playerID = readData(mobileID .. ":harassing")

	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		createEvent(15000, "CrackdownCantina", "finishHarassing", pMobile, "")
		return
	end

	local timesHarassed = readData(mobileID .. ":timesHarassed")
	local lastHarass = readData(mobileID .. ":lastHarass")
	local factionName = readStringData(mobileID .. ":factionName")

	if (timesHarassed > 6) then
		createEvent(15000, "CrackdownCantina", "finishHarassing", pMobile, "")
		return
	end

	SceneObject(pMobile):faceObject(pPlayer, true)
	local spatialString = ""
	local randSpatial = getRandomNumber(1,15)

	if (randSpatial == lastHarass) then
		if (randSpatial == 15) then
			randSpatial = 14
		else
			randSpatial = randSpatial + 1
		end
	end

	spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:harass_" .. tostring(randSpatial) .. "_" .. factionName)

	writeData(mobileID .. ":lastHarass", randSpatial)
	writeData(mobileID .. ":timesHarassed", timesHarassed + 1)
	createEvent(18000, "CrackdownCantina", "continueHarassingPlayer", pMobile, "")
end

function CrackdownCantina:finishHarassing(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	if (AiAgent(pMobile):isInCombat()) then
		createEvent(60000, "CrackdownCantina", "finishHarassing", pMobile, "")
		return
	end

	local mobileID = SceneObject(pMobile):getObjectID()

	if (readData(mobileID .. ":doneHarassing") ~= 1 and getRandomNumber(1,4) == 1) then
		if self:doFinalFight(pMobile) then
			writeData(mobileID .. ":doneHarassing", 1)
			createEvent(300000, "CrackdownCantina", "finishHarassing", pMobile, "")
			return
		end
	end

	local factionName = readStringData(mobileID .. ":factionName")
	spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:rebel_cowards_" .. factionName)

	local pBuilding = self:getCantinaBuilding(pMobile)

	if (pBuilding == nil) then
		return
	end

	local pNewCell = BuildingObject(pBuilding):getNamedCell("foyer1")
	local cellID = SceneObject(pNewCell):getObjectID()
	writeStringData(mobileID .. ":nextPoint", "exit")
	createEvent(60 * 1000, "CrackdownCantina", "doFailedExit", pMobile, "yes")

	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)
	AiAgent(pMobile):setNextPosition(47.02, .1, -2.93, cellID)
	AiAgent(pMobile):setHomeLocation(47.02, .1, -2.93, pNewCell)
	AiAgent(pMobile):executeBehavior()
end

function CrackdownCantina:doFinalFight(pMobile)
	local mobileID = SceneObject(pMobile):getObjectID()

	local pBuilding = self:getCantinaBuilding(pMobile)

	if (pBuilding == nil) then
		return false
	end

	local playerTable = self:getPlayersInCantina(pBuilding, pMobile, 20)

	if (playerTable == nil) then
		return false
	end

	local playerCount = #playerTable

	if (playerCount <= 0) then
		return false
	end

	local factionName = readStringData(mobileID .. ":factionName")
	local harassFaction

	if (factionName == "imperial") then
		harassFaction = FACTIONREBEL
	else
		harassFaction = FACTIONIMPERIAL
	end

	local pTarget = nil

	local harassID = readData(mobileID .. ":harassing")
	local pHarass = getSceneObject(harassID)

	if (pHarass ~= nil and self:isValidTarget(pHarass, harassFaction)) then
		pTarget = pHarass
	else
		for i = 1, playerCount, 1 do
			local pPlayer = playerTable[i]

			if (self:isValidTarget(pPlayer, harassFaction)) then
				pTarget = pPlayer
				break
			end
		end
	end

	if (pTarget == nil) then
		return false
	end

	if (CreatureObject(pTarget):isOnLeave()) then
		CreatureObject(pTarget):setFactionStatus(1)
	end

	if (readData(mobileID .. ":calledForBackup") ~= 1) then
		writeData(mobileID .. ":calledForBackup", 1)
		writeData(mobileID .. ":targetID", SceneObject(pTarget):getObjectID())
		spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:back_up")
		createEvent(2000, "CrackdownCantina", "callForBackup", pMobile, factionName)
	end

	CreatureObject(pMobile):engageCombat(pTarget)

	return true
end

function CrackdownCantina:callForBackup(pMobile, factionName)
	if (pMobile == nil) then
		return
	end

	local mobileID = SceneObject(pMobile):getObjectID()
	local targetID = readData(mobileID .. ":targetID")

	local pBuilding = self:getCantinaBuilding(pMobile)

	if (pBuilding == nil) then
		return
	end

	local spawnTemplate

	if (factionName == "imperial") then
		spawnTemplate = "crackdown_stormtrooper"
	else
		spawnTemplate = "crackdown_rebel_command_security_guard"
	end

	local pNewCell = BuildingObject(pBuilding):getNamedCell("foyer1")
	local zoneName = SceneObject(pMobile):getZoneName()

	if (pNewCell ~= nil) then
		local cellID = SceneObject(pNewCell):getObjectID()

		local pSpawn = spawnMobile(zoneName, spawnTemplate, 0, 48.13, .1, 2.47, 0, cellID)

		if (pSpawn ~= nil) then
			local spawnID = SceneObject(pSpawn):getObjectID()
			writeData(spawnID .. ":targetID", targetID)
			createEvent(200, "CrackdownCantina", "setupBackupMobile", pSpawn, "")
		end
	end

	pNewCell = BuildingObject(pBuilding):getNamedCell("cantina")

	if (pNewCell ~= nil) then
		local cellID = SceneObject(pNewCell):getObjectID()

		local pSpawn = spawnMobile(zoneName, spawnTemplate, 0, -14.38, 0, 14.29, 0, cellID)

		if (pSpawn ~= nil) then
			local spawnID = SceneObject(pSpawn):getObjectID()
			writeData(spawnID .. ":targetID", targetID)
			createEvent(200, "CrackdownCantina", "setupBackupMobile", pSpawn, "")
		end
	end

	pNewCell = BuildingObject(pBuilding):getNamedCell("back_hallway")

	if (pNewCell ~= nil) then
		local cellID = SceneObject(pNewCell):getObjectID()

		local pSpawn = spawnMobile(zoneName, spawnTemplate, 0, -17.8, 0, -11.53, 0, cellID)

		if (pSpawn ~= nil) then
			local spawnID = SceneObject(pSpawn):getObjectID()
			writeData(spawnID .. ":targetID", targetID)
			createEvent(200, "CrackdownCantina", "setupBackupMobile", pSpawn, "")
		end
	end
end

function CrackdownCantina:setupBackupMobile(pMobile)
	if (pMobile == nil) then
		return
	end

	local targetID = readData(SceneObject(pMobile):getObjectID() .. ":targetID")

	local pTarget = getSceneObject(targetID)

	if (pTarget ~= nil) then
		writeStringData(SceneObject(pMobile):getObjectID() .. ":nextPoint", "backupLoc")
		createObserver(DESTINATIONREACHED, "CrackdownCantina", "destinationReached", pMobile)
		AiAgent(pMobile):setAiTemplate("cantinacrackdown") -- Don't move unless patrol point is added to list, walking speed
		AiAgent(pMobile):setFollowState(4) -- Patrolling

		AiAgent(pMobile):stopWaiting()
		AiAgent(pMobile):setWait(0)

		local targetX = SceneObject(pTarget):getPositionX() - 5 + getRandomNumber(10)
		AiAgent(pMobile):setNextPosition(targetX, SceneObject(pTarget):getPositionZ(), SceneObject(pTarget):getPositionY(), SceneObject(pTarget):getParentID())
		AiAgent(pMobile):setHomeLocation(targetX, SceneObject(pTarget):getPositionZ(), SceneObject(pTarget):getPositionY(), SceneObject(pTarget):getParent())
		AiAgent(pMobile):executeBehavior()
	end

	createEvent(getRandomNumber(300, 360) * 1000, "CrackdownCantina", "doBackupExit", pMobile, "")
end

function CrackdownCantina:doBackupExit(pMobile)
	if (pMobile == nil) then
		return
	end

	createEvent(60 * 1000, "CrackdownCantina", "destroyMobile", pMobile, "")

	if (CreatureObject(pMobile):isDead()) then
		return
	end

	local pBuilding = self:getCantinaBuilding(pMobile)

	if (pBuilding == nil) then
		return
	end

	local pNewCell = BuildingObject(pBuilding):getNamedCell("foyer1")

	if (pNewCell ~= nil) then
		local cellID = SceneObject(pNewCell):getObjectID()
		writeStringData(SceneObject(pMobile):getObjectID() .. ":nextPoint", "exit")

		AiAgent(pMobile):stopWaiting()
		AiAgent(pMobile):setWait(0)
		AiAgent(pMobile):setNextPosition(47.02, .1, -2.93, cellID)
		AiAgent(pMobile):setHomeLocation(47.02, .1, -2.93, pNewCell)
		AiAgent(pMobile):executeBehavior()
	end
end

function CrackdownCantina:doFailedExit(pMobile, isMain)
	if (pMobile == nil) then
		return
	end

	deleteStringData(SceneObject(pMobile):getObjectID() .. ":nextPoint")

	if (isMain == "yes" and not CreatureObject(pMobile):isDead()) then
		spatialChat(pMobile, "@npc_reaction/imperial_crackdown_cantina:back_home")
	end

	if (isMain ~= "yes") then
		createEvent(7000, "CrackdownCantina", "destroyMobile", pMobile, "")
	else
		createEvent(7000, "CrackdownCantina", "leaveCantina", pMobile, "")
	end
end

function CrackdownCantina:isValidTarget(pPlayer, harassFaction)
	if (pPlayer == nil) then
		return false
	end

	-- Only attack opposite faction
	if CreatureObject(pPlayer):getFaction() ~= harassFaction then
		return false
	end

	-- Leave the weaklings alone, only attack players with elite professions
	if (CreatureObject(pPlayer):getLevel() < 6) then
		return false
	end

	-- TODO: Smuggler checks to avoid valid target detect

	return true
end

function CrackdownCantina:getCantinaBuilding(pMobile)
	local pCell = SceneObject(pMobile):getParent()

	if (pCell == nil) then
		return nil
	end

	return SceneObject(pCell):getParent()
end

function CrackdownCantina:getCantinaCity(cantinaID, zoneName)
	local planetData = self.cantinaOids[zoneName]

	if (planetData == nil) then
		return ""
	end

	for i = 1, #planetData, 1 do
		local cantinaData = planetData[i]

		if (cantinaData[1] == cantinaID) then
			return cantinaData[2]
		end
	end

	return ""
end

function CrackdownCantina:getPlayersInCantina(pCantina, pCenterObject, range)
	local playerTable = { }

	if (pCantina == nil) then
		return playerTable
	end

	for i = 1, BuildingObject(pCantina):getTotalCellNumber(), 1 do
		local pCell = BuildingObject(pCantina):getCell(i)

		if (pCell ~= nil) then
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)
				if pObject ~= nil and SceneObject(pObject):isPlayerCreature() and CreatureObject(pObject):isInRangeWithObject(pCenterObject, range) then
					table.insert(playerTable, pObject)
				end
			end
		end
	end

	return playerTable
end
