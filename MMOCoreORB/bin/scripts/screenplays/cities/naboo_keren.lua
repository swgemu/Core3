NabooKerenScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "NabooKerenScreenPlay"
}

registerScreenPlay("NabooKerenScreenPlay", true)

function NabooKerenScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
	end
end

function NabooKerenScreenPlay:spawnMobiles()

	--Atm adding the file to cites folder to get it out of the way.
end
