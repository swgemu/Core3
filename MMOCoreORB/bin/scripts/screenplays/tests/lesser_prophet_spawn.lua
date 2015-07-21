lesser_prophet_spawn = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("lesser_prophet_spawn", true)

function lesser_prophet_spawn:start()
	self:spawnMobile()
end

function lesser_prophet_spawn:spawnMobile("naboo", "lesser_prophet", 10800, -3735.35, 81.5629, 277.791, 5, 0)
end
