CorelliaCoronetScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CorelliaCoronetScreenPlay"
}

registerScreenPlay("CorelliaCoronetScreenPlay", true)

function CorelliaCoronetScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()
	end
end

function CorelliaCoronetScreenPlay:spawnMobiles()

	--Atm adding the file to cites folder to get it out of the way.
end
