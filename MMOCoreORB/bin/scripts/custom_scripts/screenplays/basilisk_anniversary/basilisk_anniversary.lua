BasiliskAnniversary = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "BasiliskAnniversary",
}

registerScreenPlay("BasiliskAnniversary", true)

function BasiliskAnniversary:start()
	self:spawnMobiles()
    self:spawnDecorationObjects()
end

function BasiliskAnniversary:spawnMobiles()
	local mobileTable = anniversaryMobiles

	for i = 1, #mobileTable, 1 do
		local mobile = mobileTable[i]

		if isZoneEnabled(mobile[1]) then
			--{planet, template, timer, x, z, y, direction, cell}
			local pMobile = spawnMobile(mobile[1], mobile[2], -1, mobile[3], mobile[4], mobile[5], mobile[6], mobile[7])

			if (pMobile ~= nil) then
				CreatureObject(pMobile):setPvpStatusBitmask(0)
			end
		end
	end
end

function BasiliskAnniversary:spawnDecorationObjects()
	local decoTable = anniversaryDecorationObjects

	for i = 1, #decoTable, 1 do
		local sceneObject = decoTable[i]

		if isZoneEnabled(sceneObject[1]) then
			--{planet, template, x, z, y, cell, direction}
			spawnSceneObject(sceneObject[1], sceneObject[2], sceneObject[3], sceneObject[4], sceneObject[5], sceneObject[6], math.rad(sceneObject[7]))
		end
	end
end

function BasiliskAnniversary:hasCollectionItem(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return false
	end

	local templates = {
		"object/tangible/food/foraged/shared_edible_jar_berries.iff",
	}


	for i = 1, #templates, 1 do
		local pInvItem = getContainerObjectByTemplate(pInventory, templates[i], true)

		if pInvItem ~= nil then
			return true
		end
	end

	return false
end

function BasiliskAnniversary:setQuestStatus(pPlayer, quest, status)
	local playerID = SceneObject(pPlayer):getObjectID()
	local string = quest
	local questStatus = status

	if (playerID ~= nil) then
		setQuestStatus(playerID .. string, status)
	end
end

function BasiliskAnniversary:cleanUp(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	if (playerID ~= nil) then
		removeQuestStatus(playerID .. ":anniversaryWpID_1")
		removeQuestStatus(playerID .. ":anniversaryWpID_2")
		removeQuestSTatus(playerID .. ":anniversaryWPID_3")
	end
end

function BasiliskAnniversary:grantReward(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil or pInventory == nil then
		return
	end

	PlayerObject(pGhost):awardBadge(124) --Live Event Badge

	local pReward = giveItem(pInventory, "object/tangible/food/crafted/dessert_air_cake.iff", -1)

	if pReward ~= nil then
		SceneObject(pReward):setCustomObjectName("2021 - Spectacular Basilisk 9th Anniversary Cake")
	end
end