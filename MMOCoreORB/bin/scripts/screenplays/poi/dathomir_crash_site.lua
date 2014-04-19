DathomirCrashSiteScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DathomirCrashSiteScreenPlay",

	lootContainers = {
		7105572,	--magseal
		9815358,	--loose debris
		9815357,	--loose debris

	},

	lootLevel = 39,

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 700000},
				{group = "junk", chance = 6300000},
				{group = "heavy_weapons_consumable", chance = 600000},
				{group = "rifles", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000}
			},
			lootChance = 8000000
		}
	},

	lootContainerRespawn = 1200 -- 20 minutes
}

registerScreenPlay("DathomirCrashSiteScreenPlay", true)

function DathomirCrashSiteScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function DathomirCrashSiteScreenPlay:spawnMobiles()

	spawnMobile("dathomir", "injured_purbole", 300, 5614.3, 125.0, 1863.5, 10, 0)
	spawnMobile("dathomir", "purbole_scout", 300, 5616.9, 125.0, 1865.4, 120, 0)
	spawnMobile("dathomir", "injured_purbole", 300, 5612.2, 125.0, 1869.2, -80, 0)
	spawnMobile("dathomir", "purbole", 300, 5632.3, 125.0, 1923.9, 34, 0)
	spawnMobile("dathomir", "injured_purbole", 300, 5636.6, 125.0, 1921.7, -80, 0)
	spawnMobile("dathomir", "injured_purbole", 300, 5633.4, 125.0, 1927.1, 180, 0)
	spawnMobile("dathomir", "purbole", 300, 5656.7, 125.0, 1948.5, 20, 0)
	spawnMobile("dathomir", "purbole_youth", 300, 5652.3, 125.0, 1944.6, 80, 0)
	spawnMobile("dathomir", "injured_purbole", 300, 5658.3, 125.0, 1949.5, 0, 0)
	spawnMobile("dathomir", "injured_purbole", 300, 5697.2, 125.0, 1977.1, 60, 0)
	spawnMobile("dathomir", "purbole", 300, 5701.3, 125.0, 1975.5, -80, 0)
	spawnMobile("dathomir", "purbole_scout", 300, 5696.3, 125.0, 1980.5, 0, 0)
	spawnMobile("dathomir", "injured_purbole", 300, 5692.3, 125.0, 1988.1, -80, 0)
	spawnMobile("dathomir", "purbole_youth", 300, 5746.1, 125.0, 1992.2, 130, 0)
	spawnMobile("dathomir", "injured_purbole", 300, 5749.3, 125.0, 1998.1, -10, 0)
	spawnMobile("dathomir", "purbole_youth", 300, 5744.3, 125.0, 1988.4, -80, 0)
	spawnMobile("dathomir", "injured_purbole", 300, 5741.4, 125.0, 1991.1, 180, 0)
	spawnMobile("dathomir", "purbole_scout", 300, 5748.3, 125.0, 1941.6, -80, 0)
	spawnMobile("dathomir", "injured_purbole", 300, 5748.7, 125.0, 1945.7, 20, 0)
	spawnMobile("dathomir", "purbole", 300, 5744.2, 125.0, 1939.1, 0, 0)
	spawnMobile("dathomir", "injured_purbole", 300, 5742.3, 125.0, 1885.9, -50, 0)
	spawnMobile("dathomir", "injured_purbole", 300, 5746.3, 125.0, 1881.4, -150, 0)
	spawnMobile("dathomir", "purbole_scout", 300, 5740.3, 125.0, 1888.9, -70, 0)
	spawnMobile("dathomir", "purbole_youth", 300, 5742.3, 125.0, 1892.4, 150, 0)
	spawnMobile("dathomir", "injured_purbole", 300, 5686.9, 125.0, 1859.9, 0, 0)
	spawnMobile("dathomir", "purbole_scout", 300, 5682.3, 125.0, 1854.9, 50, 0)

	spawnMobile("dathomir", "purbole_elder", 300, 5647.3, 122.0, 1864.1, -94, 0)
	spawnMobile("dathomir", "purbole_youth", 300, 5641.9, 122.0, 1860.5, 174, 0)
	spawnMobile("dathomir", "purbole_elder", 300, 5639.9, 122.0, 1864.5, 54, 0)

	spawnMobile("dathomir", "purbole_hunter", 300, 5657.9, 122.0, 1892.1, 34, 0)
	spawnMobile("dathomir", "purbole_hunter", 300, 5665.3, 122.0, 1888.1, 54, 0)
	spawnMobile("dathomir", "purbole_hunter", 300, 5675.5, 122.0, 1898.6, -54, 0)
	spawnMobile("dathomir", "purbole_hunter", 300, 5667.3, 122.0, 1903.7, 54, 0)
	spawnMobile("dathomir", "purbole_hunter", 300, 5686.3, 122.0, 1903.8, 34, 0)

	spawnMobile("dathomir", "purbole_elder", 300, 5714.5, 125.0, 1912.3, -4, 0)
	spawnMobile("dathomir", "purbole_elder", 300, 5722.6, 125.0, 1921.6, -91, 0)

	spawnMobile("dathomir", "purbole_stalker", 300, 5704.3, 122.0, 1932.3, -91, 0)
	spawnMobile("dathomir", "purbole_stalker", 300, 5702.1, 122.0, 1934.9, -137, 0)
	spawnMobile("dathomir", "purbole_stalker", 300, 5699.0, 122.0, 1938.9, 155, 0)
	spawnMobile("dathomir", "purbole_stalker", 300, 5693.6, 122.0, 1937.1, 131, 0)
	spawnMobile("dathomir", "purbole_stalker", 300, 5693.5, 122.0, 1932.5, 71, 0)
	spawnMobile("dathomir", "purbole_stalker", 300, 5695.4, 122.0, 1928.5, 31, 0)

	spawnMobile("dathomir", "purbole", 300, 5708.5, 122.0, 1947.8, 33, 0)
	spawnMobile("dathomir", "purbole", 300, 5704.1, 122.0, 1951.8, 33, 0)
	spawnMobile("dathomir", "purbole", 300, 5714.4, 122.0, 1943.1, 33, 0)

end
