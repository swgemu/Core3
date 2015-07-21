lesser_prophet_spawn = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("lesser_prophet_spawn", true)

function lesser_prophet_spawn:start()
	self:spawnMobiles()
end

function lesser_prophet_spawn:spawnMobiles()

-- Buried Ruins -3739, 252

spawnMobile("naboo", "lesser_prophet", 10800, -3739.35, 81.5629, 252.791, 5, 0)
end
