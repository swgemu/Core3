SafetyMeasures = ScreenPlay:new {
	numberOfActs = 1,
	screenplayName = "SafetyMeasures",

	safetyMeasuresCRC = 2511484011,

	KILLWORRTS = 1,
	KILLRILLS = 2,
	KLLBRIGANDS = 3,
	BRIGANDCAMP = 4,
	BRIGANDLEADER = 5,

}

registerScreenPlay("SafetyMeasures", true)

function SafetyMeasures:start()
	--self:spawnMobiles()
	--local crc = getHashCode(0xca1445a8)

end

function SafetyMeasures:spawnMobiles()


end



--PlayerObject(pGhost):completeJournalQuestTask(questCrc, TASK_GOTOMOENIA, true);
--PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_TALKTOSELAN, true);