--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
NabooStaticSpawnsScreenPlay = ScreenPlay:new 
{
	numberOfActs = 1,

	screenplayName = "NabooStaticSpawnsScreenPlay",
}

registerScreenPlay("NabooStaticSpawnsScreenPlay", true)

function NabooStaticSpawnsScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
	end
end

function NabooStaticSpawnsScreenPlay:spawnMobiles()

	--Need to add the rest of static spawns (Incomplete).

	--Imperial Outpost Guard House (-4769 -3981) Rebel Outpost needs to be populated

end
