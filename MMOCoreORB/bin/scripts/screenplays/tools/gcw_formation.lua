GCWFormation = {
	formations = {
		"rebel_small_1", "rebel_large_1", "rebel_small_2", "rebel_large_2",
		"rebel_small_3",  "rebel_large_3", "rebel_small_4",  "rebel_large_4",

		"imperial_small_1", "imperial_large_1", "imperial_small_2", "imperial_large_2",
		"imperial_small_3", "imperial_large_3", "imperial_small_4", "imperial_large_4",
		"stormtrooper_easy", "stormtrooper_extreme", "novatrooper",
	},
}

function GCWFormation:cleanUp(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	deleteData(playerID .. "GCWFormation:currentStep:")
	deleteData(playerID .. "GCWFormation:formation:")
end

function  GCWFormation:showMainUI(pPlayer)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed or pPlayer == nil) then
		return
	end

	writeData(SceneObject(pPlayer):getObjectID() .. "GCWFormation:currentStep:", 1)

	local sui = SuiListBox.new("GCWFormation", "suiSquadMainCallback")

	sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())

	sui.setTitle("GCW Formation Spawn")
	sui.setPrompt("Which GCW Formation would you like to spawn at your location and direction?")

	local squads = self.formations

	for i = 1, #squads, 1 do
		sui.add(squads[i], "")
	end

	sui.sendTo(pPlayer)
end

function GCWFormation:suiSquadMainCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed or pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local currentStep = readData(playerID .. "GCWFormation:currentStep:")
	local attackable = true

	if (currentStep <= 1) then
		writeData(playerID .. "GCWFormation:formation:", args + 1)

		self:showStationarySUI(pPlayer)
		return
	elseif (currentStep == 2) then
		writeData(playerID .. "GCWFormation:stationary:", tonumber(args))
		self:showAttackableSUI(pPlayer)

		return
	elseif (currentStep > 2 and tonumber(args) == 1) then
		attackable = false
	end

	local squadNum = readData(playerID .. "GCWFormation:formation:")
	local squad =  self.formations[squadNum]
	local stationary = readData(playerID .. "GCWFormation:stationary:")
	local parentID = SceneObject(pPlayer):getParentID()

	CreatureObject(pPlayer):sendSystemMessage("GCW Formation Spawning for the Squad: " .. squad)

	spawnSecurityPatrol(pPlayer, squad, parentID, stationary, attackable)

	createEvent(5 * 1000, "GCWFormation", "cleanUp", "pPlayer", "")
end

function  GCWFormation:showStationarySUI(pPlayer)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed or pPlayer == nil) then
		return
	end

	writeData(SceneObject(pPlayer):getObjectID() .. "GCWFormation:currentStep:", 2)

	local sui = SuiListBox.new("GCWFormation", "suiSquadMainCallback")

	sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())

	sui.setTitle("GCW Formation Spawn")
	sui.setPrompt("Would you like the squad to be stationary?")

	sui.add("Yes", "")
	sui.add("No", "")

	sui.sendTo(pPlayer)
end

function  GCWFormation:showAttackableSUI(pPlayer)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed or pPlayer == nil) then
		return
	end

	writeData(SceneObject(pPlayer):getObjectID() .. "GCWFormation:currentStep:", 3)

	local sui = SuiListBox.new("GCWFormation", "suiSquadMainCallback")

	sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())

	sui.setTitle("GCW Formation Spawn")
	sui.setPrompt("Would you like the squad to be attackable?")

	sui.add("Yes", "")
	sui.add("No", "")

	sui.sendTo(pPlayer)
end

