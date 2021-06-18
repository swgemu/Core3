EmpireDay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "EmpireDay",
}
registerScreenPlay("EmpireDay", true)

function EmpireDay:start()
	self:spawnMobiles()
	self:spawnDecorationObjects()

	-- Despawn function called in 10 days from start
	createEvent(10 * 24 * 60 * 60 * 1000, "EmpireDay", "despawnEvent", nil, "")
end

function EmpireDay:spawnMobiles()
	local mobileTable = empiredayMobiles

	for i = 1, #mobileTable, 1 do
		local mobile = mobileTable[i]

		if isZoneEnabled(mobile[1]) then
			--{planet, template, timer, x, z, y, direction, cell}
			local pMobile = spawnMobile(mobile[1], mobile[2], -1, mobile[3], mobile[4], mobile[5], mobile[6], mobile[7])

			if (pMobile ~= nil) then
				local pOid = SceneObject(pMobile):getObjectID()

				if mobile[2] == "empireday_peetyjoe" or "empireday_puprus" then
					createObserver(CREATUREDESPAWNED, "EmpireDay", "onDespawn", pMobile)
					CreatureObject(pMobile):setPvpStatusBitmask(0)
				end

				writeData(i .. ":EmpireDayMob", pOid)
			end
		end
	end
end

function EmpireDay:spawnDecorationObjects()
	local decoTable = empiredayDecorationObjects

	for i = 1, #decoTable, 1 do
		local deco = decoTable[i]

		if isZoneEnabled(deco[1]) then
            printf(" Spawning Decoration line #" .. i)
			--{planet, template, x, z, y, cell, direction}
			local pScno = spawndeco(deco[1], deco[2], deco[3], deco[4], deco[5], deco[6], math.rad(deco[7]))

			if pScno ~= nil then
				local pScnoOid = SceneObject(pScno):getObjectID()

				writeData(i .. ":empiredayDeco", pScnoOid)
			end
		end
	end
end

function EmpireDay:onDespawn(pMobile)
	if pMobile == nil or not SceneObject(pMobile):isAiAgent() then
		return
	end

	createEvent(60 * 1000, "EmpireDay", "respawn", nil, 3)
	deleteData(3 .. ":empiredayMob")

	return 1
end

function EmpireDay:respawn(pMobile, spawnNumber)
	local mobiles = self.empiredayMobiles
	local npc = mobiles[3]

	local pMob = spawnMobile(npc[1], npc[2], -1, npc[3], npc[4], npc[5], npc[6], npc[7])

	if (pMob ~= nil) then
		local pOid = SceneObject(pMob):getObjectID()

		createObserver(CREATUREDESPAWNED, "EmpireDay", "onDespawn", pMob)
		CreatureObject(pMob):setPvpStatusBitmask(0)
		writeData(3 .. ":empiredayMob", pOid)
	end
end

function EmpireDay:setQuestStatus(pPlayer, quest, status)
	if pPlayer == nil then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local string = quest
	local questStatus = status

	if (playerID ~= nil) then
		setQuestStatus(playerID .. string, status)
	end
end

function EmpireDay:cleanUp(pPlayer)
	if pPlayer == nil then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if (playerID ~= nil) then
		removeQuestStatus(playerID .. ":empiredayImpWPID_3")
		removeQuestStatus(playerID .. ":empiredayRebellWPID_3")
	end
end

function EmpireDay:grantReward(pPlayer)
	if pPlayer == nil then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pInventory == nil then
		return
	end

	PlayerObject(pGhost):awardBadge(124) --Live Event Badge

	local pReward = giveItem(pInventory, "object/tangible/item/lytus_family_artefact.iff", -1)

	if pReward == nil then
        if playerFaction == FACTIONIMPERIAL then
		    SceneObject(pReward):setCustomObjectName("2021 - Empire Day Minature Hologram")
        else
            SceneObject(pReward):setCustomObjectName("2021 - Rememberance Day Minature Hologram")
        end
	end

end

function EmpireDay:despawnEvent(pMobile, args)
	local mobiles = self.empiredayMobiles

	for  i = 1, #mobiles, 1 do
		local pMobID = readData(i .. ":empiredayMob")
		local despawnMob = getSceneObject(pMobID)

		if despawnMob ~= nil then
			if i == 3 then
				dropObserver(CREATUREDESPAWNED, "EmpireDay", "onDespawn", despawnMob)
			end

			SceneObject(despawnMob):destroyObjectFromWorld()
			deleteData(i .. ":empiredayMob")
		end
	end

	local decor = self.empiredayDecorationObjects

	for j = 1, #decor, 1 do
		local pObID = readData(j .. ":empiredayDeco")
		local pObject = getSceneObject(pObID)

		if pObject ~= nil then
			SceneObject(pObject):destroyObjectFromWorld()
			deleteData(j .. ":empiredayDeco")
		end
	end

	printf("Empire Day Event -- Despawn Complete \n")
end