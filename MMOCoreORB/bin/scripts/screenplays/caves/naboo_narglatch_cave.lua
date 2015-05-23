NarglatchCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	--location 5840 -4635
	screenplayName = "NarglatchCaveScreenPlay",

 	lootContainers = {
		6336292,
		6336293,
		6336295,
		6336297,
		6336298
	},

	lootLevel = 16,

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 160000},
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

registerScreenPlay("NarglatchCaveScreenPlay", true)

function NarglatchCaveScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function NarglatchCaveScreenPlay:spawnMobiles()
	spawnMobile("naboo", "narglatch_hunter", 300,  -0.5, -12.8, -6.2, 170, 5285895)
	spawnMobile("naboo", "narglatch_hunter", 300,  -1.6, -11.6, -11.9, 280, 5285895)
	spawnMobile("naboo", "narglatch_cub", 300,  19.2, -27, -10.1, 10, 5285895)
	spawnMobile("naboo", "narglatch_cub", 300,  19.8, -26, -5.9, 140, 5285895)
	spawnMobile("naboo", "narglatch_cub", 300,  25.2, -28, -10.0, 300, 5285895)
	spawnMobile("naboo", "narglatch_cub", 300,  23.6, -26, -5.7, 250, 5285895)

	spawnMobile("naboo", "narglatch_guardian", 300,  22.0, -39, -36.0, 10, 5285896)
	spawnMobile("naboo", "narglatch_guardian", 300,  26.9, -38, -34.3, 180, 5285896)
	spawnMobile("naboo", "narglatch_hunter", 300,  25.8, -41, -55.4, 160, 5285896)
	spawnMobile("naboo", "narglatch_cub", 300,  21.6, -42, -66.3, 0, 5285896)
	spawnMobile("naboo", "narglatch_cub", 300,  22.7, -42, -66.9, 0, 5285896)
	spawnMobile("naboo", "narglatch_cub", 300,  24.0, -42, -67.5, 0, 5285896)

	spawnMobile("naboo", "narglatch_guardian", 300,  45.8, -47, -26.2, 0, 5285896)
	spawnMobile("naboo", "narglatch_guardian", 300,  46.2, -47, -20.7, 170, 5285896)
	spawnMobile("naboo", "female_narglatch", 300,  51.1727, -67.489, -44.9174, 0, 5285896)
	spawnMobile("naboo", "narglatch_cub", 300,  51.1845, -67.6346, -47.5875, 0, 5285896)
	spawnMobile("naboo", "narglatch_cub", 300,  51.3974, -67.6616, -48.7445, 0, 5285896)
	spawnMobile("naboo", "narglatch_cub", 300,  51.6902, -67.6934, -48.6905, 0, 5285896)
	spawnMobile("naboo", "narglatch_cub", 300,  50.7219, -67.539, -47.8711, 0, 5285896)

	spawnMobile("naboo", "female_narglatch", 300,  81.1, -62, -14.2, 100, 5285897)
	spawnMobile("naboo", "narglatch_cub", 300,  93.5, -62, -7.5, 70, 5285897)
	spawnMobile("naboo", "narglatch_cub", 300,  87.7, -62, -6.3, 330, 5285897)
	spawnMobile("naboo", "narglatch_cub", 300,  87.9, -62, -8.8, 30, 5285897)
	spawnMobile("naboo", "narglatch_cub", 300,  89.1, -62, -12.8, 180, 5285897)

	spawnMobile("naboo", "narglatch", 300,  74.7, -77, -88.6, 0, 5285898)
	spawnMobile("naboo", "narglatch", 300,  73.9, -75, -54.8, 240, 5285898)
	spawnMobile("naboo", "narglatch", 300,  83.8, -76, -57.4, 100, 5285898)
	spawnMobile("naboo", "narglatch", 300,  78.7, -76, -60.8, 10, 5285898)
	spawnMobile("naboo", "female_narglatch", 300,  72.2, -77, -90.5, 10, 5285898)

	spawnMobile("naboo", "female_narglatch", 300,  85.2, -47, -107.4, 80, 5285899)
	spawnMobile("naboo", "female_narglatch", 300,  83.7, -47, -112.8, 320, 5285899)

	spawnMobile("naboo", "narglatch", 300,  54.5, -72, -114.0, 350, 5285900)
	spawnMobile("naboo", "narglatch", 300,  56.1, -71, -118.3, 300, 5285900)
	spawnMobile("naboo", "narglatch", 300,  58.6, -70.6, -120.8, 110, 5285900)

	spawnMobile("naboo", "female_narglatch", 300,  79.8, -66, -137.8, 70, 5285901)
	spawnMobile("naboo", "female_narglatch", 300,  78.3, -66, -142.7, 100, 5285901)
	spawnMobile("naboo", "narglatch_cub", 300,  90.0, -66, -140.8, 250, 5285901)
	spawnMobile("naboo", "narglatch_cub", 300,  92.5, -66, -135.8, 10, 5285901)
	spawnMobile("naboo", "narglatch_cub", 300,  90.5, -66, -137.3, 240, 5285901)
	spawnMobile("naboo", "narglatch_cub", 300,  87.7, -66, -134.7, 190, 5285901)

	spawnMobile("naboo", "narglatch", 300,  145.6, -66, -100.3, 260, 5285902)
	spawnMobile("naboo", "narglatch", 300,  146.0, -66, -93.3, 160, 5285902)
	spawnMobile("naboo", "narglatch", 300,  152.3, -66, -94.8, 270, 5285902)
	spawnMobile("naboo", "narglatch", 300,  155.0, -66, -100.4, 10, 5285902)
	spawnMobile("naboo", "narglatch", 300,  111.3, -66, -100.8, 200, 5285902)
	spawnMobile("naboo", "narglatch", 300,  111.5, -66, -111.5, 190, 5285902)
	spawnMobile("naboo", "narglatch", 300,  105.5, -66, -107.6, 210, 5285902)
	spawnMobile("naboo", "narglatch", 300,  111.1, -66, -106.8, 80, 5285902)
	spawnMobile("naboo", "female_narglatch", 300,  129.2, -66, -89.3, 230, 5285902)
	spawnMobile("naboo", "female_narglatch", 300,  119.4, -66, -86.9, 270, 5285902)
	spawnMobile("naboo", "female_narglatch", 300,  136.3, -66, -120.5, 20, 5285902)
	spawnMobile("naboo", "female_narglatch", 300,  128.8, -66, -106.3, 150, 5285902)

	spawnMobile("naboo", "narglatch_matriarch", 300,  190.2, -66, -101.4, 100, 5285903)
	spawnMobile("naboo", "narglatch", 300,  188.4, -66, -96.0, 50, 5285903)
	spawnMobile("naboo", "narglatch_cub", 300,  195.3, -66, -102.1, 120, 5285903)
	spawnMobile("naboo", "narglatch_cub", 300,  194.5, -66, -98.0, 340, 5285903)
	spawnMobile("naboo", "narglatch_cub", 300,  187.0, -66, -100.6, 230, 5285903)
	spawnMobile("naboo", "narglatch_cub", 300,  186.6, -66, -106.8, 80, 5285903)

	spawnMobile("naboo", "narglatch_cub", 300,  55.7, -48, -105.2, 160, 5285904)
	spawnMobile("naboo", "narglatch_cub", 300,  51.5, -48, -105.1, 110, 5285904)
	spawnMobile("naboo", "narglatch_cub", 300,  54.8, -48, -101.8, 150, 5285904)
	spawnMobile("naboo", "narglatch_cub", 300,  59.7, -48, -107.3, 40, 5285904)
	spawnMobile("naboo", "narglatch_guardian", 300,  47.4, -51, -84.6, 350, 5285904)
	spawnMobile("naboo", "narglatch_guardian", 300,  52.8, -51, -84.5, 0, 5285904)
	spawnMobile("naboo", "narglatch_guardian", 300,  48.7, -51, -86.5, 190, 5285904)

	spawnMobile("naboo", "narglatch_cub", 300,  78.8, -46, -140.8, 60, 5285905)
	spawnMobile("naboo", "narglatch_cub", 300,  76.2, -46, -136.6, 90, 5285905)
	spawnMobile("naboo", "female_narglatch", 300,  83.8, -46, -138.4, 40, 5285905)
	spawnMobile("naboo", "narglatch", 300,  92.2, -46, -142.0, 0, 5285905)
	spawnMobile("naboo", "narglatch", 300,  82.0, -46, -144.7, 0, 5285905)


end
