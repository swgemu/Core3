local ObjectManager = require("managers.object.object_manager")

JediPadawanTrialArchitechScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "JediPadawanTrialArchitechScreenPlay",

	-- Regions/zones available for the trial.
	zones = {
		-- Corellia
		{planetName = "corellia",
			regions = {
				{"bela_vistal", "Bela Vistal"},
				{"tyrena", "Tyrena"},
				{"vreni_island", "Vreni Island"},
				{"kor_vella", "Kor Vella"},
				{"coronet", "Coronet"},
				{"doaba_guerfel", "Doaba Guerfel"}
			}
		}
	}

-- TODO: Fill these in.
--[[
	dantooine = {},
	dathomir = {},
	endor = {},
	lok = {},
	naboo = {},
	rori = {},
	talus = {},
	tatooine = {},
	yavin4 = {}]]

}

registerScreenPlay("JediPadawanTrialArchitechScreenPlay", false)

function JediPadawanTrialArchitechScreenPlay:start(pCreature)

	local zoneTables = self:getRandomZoneTable()
	local regionTables = zoneTables.regions

	local regionNum = getRandomNumber(1, table.getn(regionTables))

	local zoneName = zoneTables.planetName

	local region = regionTables[regionNum][1]
	local regionString = regionTables[regionNum][2]

	local suiManager = LuaSuiManager()

	-- For SUI.
	local msg1 = "@jedi_trials:architect_01 " .. "@jedi_trials:" .. tostring(zoneName)
	local msg2 = "@jedi_trials:architect_02 " .. tostring(regionString)
	local msgFinal = msg1 .. " " .. msg2

	suiManager:sendMessageBox(pCreature, pCreature, "@jedi_trials:padawan_trials_title", msgFinal, "@ok", "JediPadawanTrialArchitechScreenPlay", "notifyOkPressed")
	createObserver(ZONECHANGED, "JediPadawanTrialArchitechScreenPlay", "onArrivedToPlanet", pCreature)

	-- Trial started.
	CreatureObject(pCreature):setScreenPlayState(1, "JediPadawanTrials")

	writeStringData(CreatureObject(pCreature):getObjectID() .. ":trials:padawan:planet", zoneName)
	writeStringData(CreatureObject(pCreature):getObjectID() .. ":trials:padawan:region", region)
end

function JediPadawanTrialArchitechScreenPlay:notifyOkPressed()
-- Nothing.
end

function JediPadawanTrialArchitechScreenPlay:getRandomZoneTable()
	-- Lets get a random Zone.
	local randZone = getRandomNumber(1, table.getn(self.zones))

	randZone = 1 -- Corellia testing.

	local zoneTable = self.zones[randZone]
	local zoneString = zoneTable.planetName

	if (isZoneEnabled(zoneString)) then
		return zoneTable
	else self:getRandomZoneTable()
	end
end

function JediPadawanTrialArchitechScreenPlay:onArrivedToPlanet(pCreature, arg1, arg2)
	local zoneName = CreatureObject(pCreature):getZoneName()
	local destinationZoneName = readStringData(CreatureObject(pCreature):getObjectID() .. ":trials:padawan:planet")

	if (zoneName == destinationZoneName) then
		CreatureObject(pCreature):sendSystemMessage("More coming soon...")
		-- Start mission, give waypoint.
		return 0
	else return 1
	end

end
