GunganTempleScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "GunganTempleScreenPlay",
	
	lootContainers = {
		6336300,
		261337,
		261336
	},
	
	lootLevel = 17,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 3500000},
				{group = "junk", chance = 3500000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("GunganTempleScreenPlay", true)

function GunganTempleScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function GunganTempleScreenPlay:spawnMobiles()
	--Exterior of double Wall NW (4)
	spawnMobile("naboo", "gungan_scout",300,-313.1,10.1,2861.2,-24,0)
	spawnMobile("naboo", "gungan_scout",300,-309.3,10.4,2868.8,0,0)
	spawnMobile("naboo", "gungan_scout",300,-314.9,10.9,2860,-144,0)
	spawnMobile("naboo", "gungan_scout",300,-315.3,10.3,2861.1,-99,0)
	--Exterior of double Wall N W.Side (4)
	spawnMobile("naboo", "gungan_scout",300,-299.7,10.7,2864.1,-20,0)
	spawnMobile("naboo", "gungan_scout",300,-291.9,11.1,2864.4,-38,0)
	spawnMobile("naboo", "gungan_scout",300,-284.3,11.2,2866.4,-6,0)
	spawnMobile("naboo", "gungan_scout",300,-282.3,11.4,2865.2,21,0)
	--Exterior of double Wall Center Entrance (3)
	spawnMobile("naboo", "gungan_captain",300,-267.3,12.2,2858.4,0,0)
	spawnMobile("naboo", "gungan_guard",300,-269.1,11.9,2862.3,-3,0)
	spawnMobile("naboo", "gungan_guard",300,-263.8,12.0,2862.0,8,0)
	--Exterior of double Wall N E.Side (3)
	spawnMobile("naboo", "gungan_scout",300,-255.4,12.0,2862.9,-9,0)
	spawnMobile("naboo", "gungan_scout",300,-246.7,11.7,2867.9,-38,0)
	spawnMobile("naboo", "gungan_scout",300,-243.0,11.9,2864.1,12,0)
	--Exterior of double Wall NE (4)
	spawnMobile("naboo", "gungan_scout",300,-214.6,11.6,2864.2,-74,0)
	spawnMobile("naboo", "gungan_scout",300,-211.8,11.5,2866.5,10,0)
	spawnMobile("naboo", "gungan_scout",300,-206.7,11.7,2862.5,130,0)
	spawnMobile("naboo", "gungan_scout",300,-207.9,11.7,2859.1,162,0)
	--Exterior of Double Wall E Gaps (5)
	spawnMobile("naboo", "gungan_scout",300,-208.0,12.1,2844.0,110,0)
	spawnMobile("naboo", "gungan_scout",300,-206.9,15.1,2836.2,51,0)
	spawnMobile("naboo", "gungan_scout",300,-208.6,11.0,2808.4,56,0)
	spawnMobile("naboo", "gungan_scout",300,-205.4,7.1,2802.9,70,0)
	spawnMobile("naboo", "gungan_scout",300,-205.7,10.4,2792.2,121,0)
	--Exterior of double Wall SE (4)
	spawnMobile("naboo", "gungan_scout",300,-208.7,10.0,2763.1,32,0)
	spawnMobile("naboo", "gungan_scout",300,-205.4,9.9,2764.1,73,0)
	spawnMobile("naboo", "gungan_scout",300,-209.8,9.9,2757.9,-144,0)
	spawnMobile("naboo", "gungan_scout",300,-206.2,9.8,2757.4,102,0)
	--Exterior of double Wall SW (3)
	spawnMobile("naboo", "gungan_scout",300,-313.7,13.5,2768.3,-50,0)
	spawnMobile("naboo", "gungan_scout",300,-307.2,12.8,2758.5,120,0)
	spawnMobile("naboo", "gungan_scout",300,-314.4,13.2,2755.7,-113,0)
	-- Double Wall N (3)
	spawnMobile("naboo", "gungan_scout",300,-305.5,11.0,2857.3,90,0)
	spawnMobile("naboo", "gungan_scout",300,-281.8,12.0,2856.3,-91,0)
	spawnMobile("naboo", "gungan_scout",300,-230.1,12.3,2856.1,1,0)
	-- Double Wall E (3)
	spawnMobile("naboo", "gungan_scout",300,-216.4,12.4,2843.2,90,0)
	spawnMobile("naboo", "gungan_scout",300,-216.9,8.2,2792.7,31,0)
	spawnMobile("naboo", "gungan_scout",300,-216.8,10.4,2770.4,-8,0)
	-- Double Wall S (3)
	spawnMobile("naboo", "gungan_scout",300,-233.3,10.8,2768.0,157,0)
	spawnMobile("naboo", "gungan_scout",300,-259.5,11.3,2764.6,65,0)
	spawnMobile("naboo", "gungan_scout",300,-278.7,11.7,2766.6,175,0)
	-- Double Wall W (3)
	spawnMobile("naboo", "gungan_scout",300,-303.5,12.8,2767.6,49,0)
	spawnMobile("naboo", "gungan_scout",300,-305.2,12.9,2807.9,-95,0)
	spawnMobile("naboo", "gungan_scout",300,-303.5,11.9,2839.6,-179,0)
	-- Inside Double Wall NW (3)
	spawnMobile("naboo", "gungan_guard",300,-291.4,12.2,2844.8,-3,0)
	spawnMobile("naboo", "gungan_guard",300,-276.7,12.7,2840.3,32,0)
	spawnMobile("naboo", "gungan_guard",300,-281.4,12.8,2826.0,160,0)
	-- Inside Double Wall NE (3)
	spawnMobile("naboo", "gungan_guard",300,-229.5,12.6,2846.8,89,0)
	spawnMobile("naboo", "gungan_guard",300,-227.3,12.6,2833.3,170,0)
	spawnMobile("naboo", "gungan_guard",300,-249.2,12.9,2840.9,-34,0)
	-- Inside Double Wall SW (3)
	spawnMobile("naboo", "gungan_guard",300,-275.1,12.0,2778.9,-80,0)
	spawnMobile("naboo", "gungan_guard",300,-296.4,12.8,2779.6,-165,0)
	spawnMobile("naboo", "gungan_guard",300,-285.7,12.6,2789.3,172,0)
	-- Inside Double Wall SE (3)
	spawnMobile("naboo", "gungan_guard",300,-221.2,10.7,2777.6,126,0)
	spawnMobile("naboo", "gungan_guard",300,-235.9,7.8,2774.4,-143,0)
	spawnMobile("naboo", "gungan_guard",300,-245.8,11.5,2781.0,34,0)
	-- Top Of Temple (4)
	spawnMobile("naboo", "gungan_guard",300,-259.9,28.2,2800.9,-47,0)
	spawnMobile("naboo", "gungan_guard",300,-268.3,28.2,2800.8,39,0)
	spawnMobile("naboo", "gungan_priest",300,-264.4,28.2,2795.1,-46,0)
	spawnMobile("naboo", "gungan_captain",300,-264.1,28.2,2803.1,-4,0)
	-- Front of Temple Gungan Defenders TODO AI(Future Defenders)
	spawnMobile("naboo", "gungan_captain",300,-265.4,13.0,2833.1,1,0)
	spawnMobile("naboo", "gungan_boss",300,-262.5,13.0,2833.1,0,0)
	spawnMobile("naboo", "gungan_captain",300,-259.7,13.0,2833.1,-6,0)
	spawnMobile("naboo", "gungan_guard",300,-262.9,12.9,2840.3,-2,0)
	spawnMobile("naboo", "gungan_guard",300,-258.6,12.9,2844.1,-15,0)
	spawnMobile("naboo", "gungan_guard",300,-261.9,12.9,2843.9,-2,0)
	spawnMobile("naboo", "gungan_guard",300,-266.1,12.9,2843.1,4,0)
	spawnMobile("naboo", "gungan_guard",300,-269.3,12.6,2849.1,5,0)
	spawnMobile("naboo", "gungan_guard",300,-265.5,12.7,2848.8,8,0)
	spawnMobile("naboo", "gungan_guard",300,-260.8,12.8,2848.5,-12,0)
	--Imperial troops Outside Attackers TODO AI(future Attackers)
	spawnMobile("naboo", "imperial_corporal",300,-276.4,10.0,2881.3,170,0)
	spawnMobile("naboo", "imperial_corporal",300,-260.3,11.0,2875.2,-167,0)
	spawnMobile("naboo", "imperial_army_captain",300,-270.7,8.6,2892.6,172,0)
	spawnMobile("naboo", "imperial_trooper",300,-277.1,10.3,2878.8,171,0)
	spawnMobile("naboo", "imperial_trooper",300,-271.5,10.4,2879.3,168,0)
	spawnMobile("naboo", "imperial_trooper",300,-266.3,10.4,2874.4,-169,0)
	spawnMobile("naboo", "imperial_trooper",300,-261.9,10.4,2880.7,-169,0)
	spawnMobile("naboo", "imperial_trooper",300,-265.5,10.0,2883.7,-169,0)
	spawnMobile("naboo", "imperial_trooper",300,-270.7,9.9,2882.9,0,0)
	spawnMobile("naboo", "imperial_trooper",300,-273.9,10.0,2882.1,168,0)

end
