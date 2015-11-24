VillageGmCommands = Object:new {}

function VillageGmCommands:cmdGetCurrentPhase(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local curPhase = VillageJediManagerTownship:getCurrentPhase()

	CreatureObject(pPlayer):sendSystemMessage("Current Village Phase: " .. curPhase)
end

function VillageGmCommands:cmdGetCurrentPhaseID(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()

	CreatureObject(pPlayer):sendSystemMessage("Current Village Phase ID: " .. phaseID)
end

function VillageGmCommands:cmdGetCurrentPhaseDuration(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local eventID = getServerEventID("VillagePhaseChange")

	if (eventID == nil) then
		return
	end

	local timeLeft = getServerEventTimeLeft(eventID) / 1000
	local daysLeft = math.floor(timeLeft / (24 * 60 * 60))
	local secondsLeft = timeLeft - (daysLeft * (24 * 60 * 60))
	local hoursLeft = math.floor(secondsLeft / (60 * 60))
	local secondsLeft = secondsLeft - (hoursLeft * (60 * 60))
	local minutesLeft = math.floor(secondsLeft / 60)
	local secondsLeft = math.floor(secondsLeft - (minutesLeft * 60))
	
	local timeString = daysLeft .. " days, " .. hoursLeft .. " hours, " .. minutesLeft .. " minutes, " .. secondsLeft .. " seconds."
	CreatureObject(pPlayer):sendSystemMessage("Time left in current Village Phase: " .. timeString)
end

return VillageGmCommands
