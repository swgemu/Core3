TatooineMosEnthaScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineMosEnthaScreenPlay"
}

registerScreenPlay("TatooineMosEnthaScreenPlay", true)

function TatooineMosEnthaScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
	end
end

function TatooineMosEnthaScreenPlay:spawnMobiles()

	--Atm adding the file to cites folder to get it out of the way.
end
