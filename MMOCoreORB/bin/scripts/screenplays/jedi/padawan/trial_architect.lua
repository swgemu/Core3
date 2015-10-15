local ObjectManager = require("managers.object.object_manager")

JediPadawanTrialArchitechScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "JediPadawanTrialArchitechScreenPlay",

	-- Zones available for this trial.
	zones = {
		"corellia", "dantooine", "dathomir", "endor", "lok", "naboo", "rori", "talus", "tatooine", "yavin4"
	},


	-- Regions available for this trial.
	regions = {
		corellia = {
			{"bela_vistal", "Bela Vistal"},
			{"tyrena", "Tyrena"},
			{"vreni_island", "Vreni Island"},
			{"kor_vella", "Kor Vella"},
			{"coronet", "Coronet"},
			{"doaba_guerfel", "Doaba Guerfel"}
		},

		-- TODO: Fill these.
		dantooine = {},
		dathomir = {},
		endor = {},
		lok = {},
		naboo = {},
		rori = {},
		talus = {},
		tatooine = {},
		yavin4 = {}
	}

}

registerScreenPlay("JediPadawanTrialArchitechScreenPlay", false)

function JediPadawanTrialArchitechScreenPlay:start(pCreature)

	local zoneName = self:getRandomZone()

	local regionNum = getRandomNumber(1, table.getn(regions.zoneName))

	local region = self.regions.zoneName[regionNum][1]
	local regionString = self.regions.zoneName[regionNum][2]

	local suiManager = LuaSuiManager()

	local msg1 = "@jedi_trials:architect_01"
	local msg2 = "@jedi_trials:architect_02"

	local msgFinal = msg1 .. zoneName .. msg2 .. regionString

	suiManager:sendMessageBox(pCreature, pCreature, "@jedi_trials:padawan_trials_title", msgFinal, "@ok", "JediPadawanTrialArchitechScreenPlay", NULL)
	createObserver(ZONECHANGED, "JediPadawanTrialArchitechScreenPlay", "onArrivedToPlanet", pCreature)

	-- Trial started.
	CreatureObject(pCreature):setScreenPlayState(1, "JediPadawanTrials")
	writeStringData(CreatureObject(pCreature):getObjectID() .. ":trials:padawan:planet", zoneName)

end

function JediPadawanTrialArchitechScreenPlay:getRandomZone()
	-- Lets get a random Zone.
	local randZone = self.zones[getRandomNumber(1, 10)]

	if (isZoneEnabled(randZone)) then
		return randZone
	else self:getRandomZone()
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
