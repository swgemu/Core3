NabooMoeniaScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "NabooMoeniaScreenPlay"
}

registerScreenPlay("NabooMoeniaScreenPlay", true)

function NabooMoeniaScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
	end
end

function NabooMoeniaScreenPlay:spawnMobiles()

	--Atm adding the file to cites folder to get it out of the way.
end
