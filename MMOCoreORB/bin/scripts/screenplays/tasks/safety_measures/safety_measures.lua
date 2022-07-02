SafetyMeasures = ScreenPlay:new {
	numberOfActs = 1,
	screenplayName = "SafetyMeasures",

	safetyMeasuresCRC = ,

	KILLWORRTS = 1,
	KILLRILLS = 2,
	KLLBRIGANDS = 3,
	BRIGANDCAMP = 4,
	BRIGANDLEADER = 5,

}

registerScreenPlay("SafetyMeasures", true)

function SafetyMeasures:start()
	--self:spawnMobiles()

end

function SafetyMeasures:spawnMobiles()


end



--PlayerObject(pGhost):completeJournalQuestTask(questCrc, TASK_GOTOMOENIA, true);
--PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_TALKTOSELAN, true);