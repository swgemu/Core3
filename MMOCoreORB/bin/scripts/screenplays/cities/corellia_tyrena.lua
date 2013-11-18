CorelliaTyrenaScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CorelliaTyrenaScreenPlay"
}

registerScreenPlay("CorelliaTyrenaScreenPlay", true)

function CorelliaTyrenaScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()
	end
end

function CorelliaTyrenaScreenPlay:spawnMobiles()

	--Atm adding the file to cites folder to get it out of the way.
end
