VeermokCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	--location 5703 -1557
	screenplayName = "VeermokCaveScreenPlay",

 	lootContainers = {
		261338,
		7955559,
		7955560,
		7955561,
		7955562,
		7955563
	},

	lootLevel = 20,

	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 8240000},
				{group = "rifles", chance = 500000},
				{group = "pistols", chance = 500000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000}
			},
			lootChance = 8000000
		}
	},

	lootContainerRespawn = 1800
}

registerScreenPlay("VeermokCaveScreenPlay", true)

function VeermokCaveScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function VeermokCaveScreenPlay:spawnMobiles()

	spawnMobile("naboo", "veermok_scout", 300, 5737.8, 298.7, -1529.7, 144, 0)
	spawnMobile("naboo", "veermok_scout", 300, 5776.7, 294.9, -1563.3, 51, 0)
	spawnMobile("naboo", "veermok_scout", 300, 5749.1, 295.5, -1579.1, 119, 0)
	spawnMobile("naboo", "veermok_sentry", 300, 5723.2, 284.4, -1555.9, -21, 0)
	spawnMobile("naboo", "veermok_sentry", 300, 5723.1, 291.7, -1537.8, -121, 0)

	spawnMobile("naboo", "veermok_sentry", 300, -17.7, -4.1, -6.1, -10, 4295394)
	spawnMobile("naboo", "veermok_sentry", 300, -3.2, -11.2, -10.5, -17, 4295394)
	spawnMobile("naboo", "veermok_sentry", 300, 24.7, -27.8, -8.8, -90, 4295394)
	spawnMobile("naboo", "veermok_sentry", 300, 22.4, -25.9, -5.3, -160, 4295394)

	spawnMobile("naboo", "veermok_sentry", 300, 23.6, -39.5, -40.7, 90, 4295395)
	spawnMobile("naboo", "veermok_sentry", 300, 25.7, -39.5, -40.9, 0, 4295395)
	spawnMobile("naboo", "veermok_ravager", 300, 24.1, -42.5, -67.9, 0, 4295395)
	spawnMobile("naboo", "veermok_ravager", 300, 52.2, -48.8, -63.6, -90, 4295395)
	spawnMobile("naboo", "veermok_scavenger", 300, 52.9, -48.6, -58.4, -90, 4295395)
	spawnMobile("naboo", "veermok_ravager", 300, 51.5, -48.8, -20.8, 90, 4295395)
	spawnMobile("naboo", "veermok_scavenger", 300, 51.5, -48.3, -16.3, 180, 4295395)

	spawnMobile("naboo", "veermok_ravager", 300, 48.9, -51.8, -83.4, -90, 4295403)
	spawnMobile("naboo", "veermok_ravager", 300, 52.0, -48.7, -104.1, 0, 4295403)

	spawnMobile("naboo", "veermok_ravager", 300, 94.9, -45.6, -99.6, -145, 4295398)
	spawnMobile("naboo", "veermok_sentry", 300, 85.7, -46.8, -109.0, -85, 4295398)

	spawnMobile("naboo", "veermok_guard", 300, 91.9, -46.9, -138.8, 11, 4295404)
	spawnMobile("naboo", "giant_cave_veermok", 480, 81.9, -46.7, -145.4, 35, 4295404)
	spawnMobile("naboo", "giant_cave_veermok", 480, 76.5, -46.6, -142.4, 88, 4295404)

	spawnMobile("naboo", "veermok_ravager", 300, 89.5, -60.5, -6.2, -110, 4295396)
	spawnMobile("naboo", "veermok_ravager", 300, 95.2, -61.6, -10.7, -175, 4295396)
	spawnMobile("naboo", "veermok_ravager", 300, 87.5, -63.0, -21.5, 10, 4295396)

	spawnMobile("naboo", "veermok_scavenger", 300, 53.1, -68.0, -36.5, 111, 4295395)

	spawnMobile("naboo", "veermok_scavenger", 300, 83.9, -76.6, -88.8, -90, 4295397)
	spawnMobile("naboo", "veermok_scavenger", 300, 74.9, -77.1, -88.8, 90, 4295397)

	spawnMobile("naboo", "veermok_scavenger", 300, 84.0, -66.2, -140.8, -60, 4295400)
	spawnMobile("naboo", "veermok_scavenger", 300, 89.3, -67.0, -137.1, 12, 4295400)
	spawnMobile("naboo", "veermok_scavenger", 300, 84.8, -66.5, -136.8, -100, 4295400)
	spawnMobile("naboo", "veermok_scout", 300, 80.1, -65.6, -140.0, -90, 4295400)

	spawnMobile("naboo", "veermok_scavenger", 300, 134.4, -66.2, -117.8, -6, 4295401)
	spawnMobile("naboo", "veermok_ravager", 300, 134.4, -66.2, -122.8, -6, 4295401)
	spawnMobile("naboo", "veermok_scavenger", 300, 148.2, -67.1, -124.2, -46, 4295401)
	spawnMobile("naboo", "veermok_scavenger", 300, 140.9, -67.2, -94.0, -136, 4295401)
	spawnMobile("naboo", "veermok_ravager", 300, 131.1, -66.8, -108.4, -96, 4295401)

	spawnMobile("naboo", "veermok_guard", 300, 173.4, -66.0, -98.1, -86, 4295402)
	spawnMobile("naboo", "veermok_guard", 300, 166.0, -66.7, -98.3, -88, 4295402)
	spawnMobile("naboo", "giant_cave_veermok", 480, 187.8, -65.5, -108.2, -16, 4295402)

end
