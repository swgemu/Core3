require("screenplays.screenplay")
local ObjectManager = require("managers.object.object_manager")

RecordKeeper =ScreenPlay:new {
	quests = { "dummy"},
	keeperName = "dummy",
	faction = 0
}
function RecordKeeper:start()
	-- no op
end
function RecordKeeper:wipeQuests(pObject)
	ObjectManager.withCreatureObject(pObject, function(player)
		for k,v in pairs(self.quests) do
			-- we wipe out all screen play data for this theme park/quest
			park = _G[v]
			park:resetThemePark(pObject)
		end
		writeScreenPlayData(player, self.keeperName, "completed", 1)
	end)
end

function RecordKeeper:resetQuests(pObject)
	for k,v in pairs(self.quests) do
		park = _G[v]
		park:resetCurrentMission(pObject)
	end
	ObjectManager.withCreatureObject(pObject, function(player)
		writeScreenPlayData(player, self.keeperName, "completed", 1)
	end)
end
function RecordKeeper:available(pObject)
	return ObjectManager.withCreatureObject(pObject, function(player)
		-- read the variable
		local val = readScreenPlayData(player, self.keeperName, "completed")
		if val == 1 then
			return false
		else
			return true
		end
	end)
end

function RecordKeeper:hasStartedPark(pObject)
	local count = 0
	for k,v in pairs(self.quests) do
		park = _G[v]
		count = park:getCurrentMissionNumber(1,pObject)
	end	
	return count > 0
end

function RecordKeeper:needsFaction()
	if self.faction == 0 then
		return false
	else
		return true
	end
end

function RecordKeeper:hasFaction(faction, pCreature)
	if pCreature == nil then
		return false
	end

	local creature = CreatureObject(pCreature)

	if creature:getFaction() == faction then
		return true
	else
		return false
	end
end

