TatooineBestineScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineBestineScreenPlay"
}

registerScreenPlay("TatooineBestineScreenPlay", true)

function TatooineBestineScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
	end
end

function TatooineBestineScreenPlay:spawnMobiles()

	--Atm adding the file to cites folder to get it out of the way.
end
