VillageGmCommands = ScreenPlay:new {}

function VillageGmCommands:cmdGetCurrentPhase(pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return
	end

	local curPhase = VillageJediManagerTownship:getCurrentPhase()

	CreatureObject(pPlayer):sendSystemMessage("Current Village Phase: " .. curPhase)
end

function VillageGmCommands:cmdGetCurrentPhaseID(pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return
	end

	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()

	CreatureObject(pPlayer):sendSystemMessage("Current Village Phase ID: " .. phaseID)
end

function VillageGmCommands:cmdGetCurrentPhaseDuration(pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return
	end

	local eventID = getServerEventID("VillagePhaseChange")

	if (eventID == nil) then
		return
	end

	local timeLeft = getServerEventTimeLeft(eventID) / 1000
	local daysLeft = math.floor(timeLeft / (24 * 60 * 60))
	local hoursLeft = math.floor((timeLeft / 3600) % 24)
	local minutesLeft = math.floor((timeLeft / 60) % 60)
	local secondsLeft = math.floor(timeLeft % 60)

	local timeString = "Time left in current Village Phase: " .. daysLeft .. " days, " .. hoursLeft .. " hours, " .. minutesLeft .. " minutes, " .. secondsLeft .. " seconds."
	CreatureObject(pPlayer):sendSystemMessage(timeString)
end

function VillageGmCommands:cmdChangeCurrentPhase(pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("Changing to next village phase.")
	VillageJediManagerTownship:switchToNextPhase()
end

return VillageGmCommands
