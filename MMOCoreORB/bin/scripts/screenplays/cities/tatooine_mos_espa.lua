TatooineMosEspaScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineMosEspaScreenPlay"
}

registerScreenPlay("TatooineMosEspaScreenPlay", true)

function TatooineMosEspaScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
	end
end

function TatooineMosEspaScreenPlay:spawnMobiles()

	--Atm adding the file to cites folder to get it out of the way.
end
