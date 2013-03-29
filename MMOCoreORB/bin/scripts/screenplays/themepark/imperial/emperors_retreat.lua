EmperorsRetreatScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "EmperorsRetreatScreenPlay",
}

registerScreenPlay("EmperorsRetreatScreenPlay", true)

function EmperorsRetreatScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnSceneObjects()
	end
end

function EmperorsRetreatScreenPlay:spawnSceneObjects()
	spawnSceneObject("naboo", "object/tangible/terminal/terminal_elevator_up.iff", 13, 1, -36, 1418877, 1, 0, 0, 0)
	spawnSceneObject("naboo", "object/tangible/terminal/terminal_elevator_down.iff", 13, 21, -36, 1418877, 1, 0, 0, 0)
end
