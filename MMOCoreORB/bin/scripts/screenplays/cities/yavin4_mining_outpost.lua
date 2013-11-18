Yavin4MiningOutpostScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "Yavin4MiningOutpostScreenPlay"
}

registerScreenPlay("Yavin4MiningOutpostScreenPlay", true)

function Yavin4MiningOutpostScreenPlay:start()
	if (isZoneEnabled("yavin4")) then
		self:spawnMobiles()
	end
end

function Yavin4MiningOutpostScreenPlay:spawnMobiles()

	--Atm adding the file to cites folder to get it out of the way.
end
