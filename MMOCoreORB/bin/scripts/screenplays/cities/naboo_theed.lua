NabooTheedScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "NabooTheedScreenPlay"
}

registerScreenPlay("NabooTheedScreenPlay", true)

function NabooTheedScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
	end
end

function NabooTheedScreenPlay:spawnMobiles()

	--Atm adding the file to cites folder to get it out of the way.
end
