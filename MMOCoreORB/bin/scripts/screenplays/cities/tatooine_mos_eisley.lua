TatooineMosEisleyScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineMosEisleyScreenPlay"
}

registerScreenPlay("TatooineMosEisleyScreenPlay", true)

function TatooineMosEisleyScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
	end
end

function TatooineMosEisleyScreenPlay:spawnMobiles()

	--Atm adding the file to cites folder to get it out of the way.
end
