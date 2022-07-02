SafetyMeasures = ScreenPlay:new {
	numberOfActs = 1,
	screenplayName = "SafetyMeasures",

	safetyMeasuresCRC = 2511484011,

	questCRCs = {
		1663428765,
		193143818,
		4047447943,
		182193299,
		1137797918,
		--[[
		0x6325E89D,
		0xB83240A,
		0xF13F2787,
		0xADC0C93,
		0x43D16B1E,]]
	},

	KILLWORRTS = 1,
	KILLRILLS = 2,
	KLLBRIGANDS = 3,
	BRIGANDCAMP = 4,
	BRIGANDLEADER = 5,

	questGiver = "gerak_vurtimis",
	planet = "tatooine",
	location = {-1254, 12, -3617},
}

registerScreenPlay("SafetyMeasures", true)

function SafetyMeasures:start()
	if (not isZoneEnabled(self.planet)) then
		return
	end

	self:spawnMobiles()



	--[[for i = 1, #self.questCRCs, 1 do
		local crc = self.questCRCs[i]

		print(" CRC  #" .. i .. " = " .. crc)

	end]]
end

function SafetyMeasures:spawnMobiles()
	spawnMobile(self.planet, self.questGiver, -1, location[1], location[2], location[3], 0, 0)
end



--PlayerObject(pGhost):completeJournalQuestTask(questCrc, TASK_GOTOMOENIA, true);
--PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_TALKTOSELAN, true);