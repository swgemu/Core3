RemembranceMemorial = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "RemembranceMemorial",

	planet = "naboo",

	noBuildZone = {4138, 14, 3211},

	noBuildSize = 175,

	mobiles = {
	},

	sceneObjects = {
	},
}
registerScreenPlay("RemembranceMemorial", true)

function RemembranceMemorial:start()
	if isZoneEnabled(self.planet) then
		self:deployActiveArea()
		--self:spawnMobiles()
		--self:spawnSceneObjects()
	end
end

function RemembranceMemorial:deployActiveArea()
	local noBuildLoc = self.noBuildZone

	local pNoBuildZone = spawnActiveArea(self.planet, "object/active_area.iff", noBuildLoc[1], noBuildLoc[2], noBuildLoc[3], self.noBuildSize, 0)

	if pNoBuildZone ~= nil then
		ActiveArea(pNoBuildZone):setNoBuildArea(true)
		ActiveArea(pNoBuildZone):setNoSpawnArea(true)
	end
end

function RemembranceMemorial:spawnMobiles()
	local mobiles = self.mobiles

	for i = 1, #mobiles, 1 do
		local mobile = mobiles[i]

		local pMobile = spawnMobile(self.planet, mobile[1], -1, mobile[2], mobile[3], mobile[4], mobile[5], mobile[6])

		if pMobile ~= nil then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
		end
	end
end

function RemembranceMemorial:spawnSceneObjects()
	local decorations = self.sceneObjects

	for i = 1, #decorations, 1 do
		local decoration = decorations[i]

		--{planet, template, x, z, y, cell, direction}
		local pScno = spawnSceneObject(self.planet, decoration[1], decoration[2], decoration[3], decoration[4], decoration[5], math.rad(decoration[6]))

		if pScno ~= nil and decoration[7] ~= "" then
			SceneObject(pScno):setCustomObjectName(decoration[7])
		end
	end
end