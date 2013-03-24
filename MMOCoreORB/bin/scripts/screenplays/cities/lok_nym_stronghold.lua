LokNymStrongholdScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "LokNymStrongholdScreenPlay"
}

registerScreenPlay("LokNymStrongholdScreenPlay", true)

function LokNymStrongholdScreenPlay:start()
	if (isZoneEnabled("lok")) then
		self:spawnMobiles()
	end
end

function LokNymStrongholdScreenPlay:spawnMobiles()
	--thugs
	spawnMobile("lok", "nym_surveyer",60,484.493,11.9154,5091.56,180.005,0)
	spawnMobile("lok", "nym_guard_weak",60,551.4,12,5169.8,200,0)
	spawnMobile("lok", "nym_guard_weak",60,535.7,11.9,5105.3,90,0)
	spawnMobile("lok", "nym_guard_weak",60,331.611,11.9777,4898.94,14.0896,0)
	spawnMobile("lok", "nym_guard_weak",60,322.8,12.1,5050,216,0)
	spawnMobile("lok", "nym_guard_weak",60,343.53,12.5909,4902.71,356.744,0)
	spawnMobile("lok", "nym_guard_weak",60,348.219,12.1248,4940.84,19.7209,0)
	spawnMobile("lok", "nym_guard_elite",60,381.62,12,5013.95,350,0)
	spawnMobile("lok", "nym_guard_elite",60,381.4,12,5015.13,170,0)
	spawnMobile("lok", "nym_guard_elite",60,384.094,11.9992,4996.7,286.256,0)
	spawnMobile("lok", "nym_guard_elite",60,550.517,11.7979,5167.25,10.2375,0)
	spawnMobile("lok", "nym_guard_elite",60,518.4,12,5100.5,300,0)
	spawnMobile("lok", "nym_guard_elite",60,405,12.5,5032,230,0)
	spawnMobile("lok", "nym_guard_elite",60,435.932,12.5279,5024.65,247.747,0)
	spawnMobile("lok", "nym_guard_elite",60,389.1,12,5034.2,260,0)
	spawnMobile("lok", "nym_guard_elite",60,441,12.5,5025,90,0)
	spawnMobile("lok", "nym_guard_strong",60,405.3,12.5,5030,349,0)
	spawnMobile("lok", "nym_guard_strong",60,537.325,11.9367,5112.7,290,0)
	spawnMobile("lok", "nym_guard_strong",60,540.129,12.073,5124.46,348.152,0)
	spawnMobile("lok", "nym_guard_strong",60,538.5,11.9,5102.6,45,0)
	spawnMobile("lok", "nym_guard_strong",60,406.311,11.8705,4991.53,286.282,0)
	spawnMobile("lok", "nym_guard_strong",60,334.572,11.9605,4892.89,349.707,0)
	spawnMobile("lok", "nym_guard_strong",60,350.446,12.0004,4975.94,216.027,0)
	spawnMobile("lok", "nym_guard_weak",60,400.5,12.5,5047.2,90,0)
	spawnMobile("lok", "nym_guard_weak",60,520.4,12,5128.8,180,0)

	spawnMobile("lok", "nym_guard_weak",60,18.98,2.29948,10.51,181.005,6595511)
	spawnMobile("lok", "nym_guard_weak",60,-20.26,2.29947,-18.62,3.00005,6595511)
	spawnMobile("lok", "nym_guard_strong",60,-18.91,2.29916,9.74,178.005,6595511)
	spawnMobile("lok", "nym_bodyguard",60,5.86,1.3,-5.04,283.008,6595511)
	spawnMobile("lok", "nym_bodyguard",60,-3.58,1.3,4.01,89.0026,6595511)
	spawnMobile("lok", "nym_brawler",60,-8.11,1.3,-1.06,177.005,6595511)
	spawnMobile("lok", "nym_brawler",60,4.17,1.3,-5.62,33.001,6595511)
	spawnMobile("lok", "nym_guard_elite",60,3.12,4.0782,-9.55,359.01,6595511)
	spawnMobile("lok", "nym_guard_elite",60,-3.1239,4.0782,-9.55698,359.01,6595511)
	spawnMobile("lok", "nym_guard_elite",60,1.98,8.9,-30.5,0,6595511)
	spawnMobile("lok", "nym_guard_elite",60,-1.91,8.9,-30.5,360.011,6595511)
	spawnMobile("lok", "nym_destroyer",60,-1.79,1.3,3.94,267.008,6595511)
	spawnMobile("lok", "nym_surveyer",60,-8.05,1.3,-2.3,7.00022,6595511)
	spawnMobile("lok", "nym_surveyer",60,4.39,1.3,-3.87,149.004,6595511)

	spawnMobile("lok", "nym_bodyguard",60,-29.1,2.3,1.5,200,6595515)

	spawnMobile("lok", "nym_pirate_elite",60,37.49,2.29422,-1.17,88.0026,6595518)
	spawnMobile("lok", "nym_pirate_elite",60,36.71,2.29422,-2.92,88.0026,6595518)

	spawnMobile("lok", "nym_surveyer",60,1.83273,-0.894992,-14.2461,180.009,8145381)
	spawnMobile("lok", "nym_surveyer",60,-2.13049,-0.894991,6.9956,360.011,8145378)

	--misc
	spawnMobile("lok", "informant_npc_lvl_3",60,369,0,5087,90,0)
	spawnMobile("lok", "informant_npc_lvl_3",60,540,0,5072,180,0)
	spawnMobile("lok", "junk_dealer",60,367,12,5202.8,-178,0)
	spawnMobile("lok", "reggi_tirver",60,443.925,12,4879.41,69.9891,0)

	--quest
	spawnMobile("lok", "jinkins",60,3.07003,3.29302,-21.31,0,6595511)
	spawnMobile("lok", "kole",60,-3,3.4,-19.6,0,6595511)
	spawnMobile("lok", "nym_fuel_tech",0,374.599,11.9876,4986.77,31.5798,0)
	spawnMobile("lok", "ramna",60,19.5548,-0.894995,-20.1381,20.176,8145379)
	spawnMobile("lok", "warvog_arkon",60,-12.1246,1.6,-16.3553,291.827,8145361)
	spawnMobile("lok", "viopa",60,-2.2483,4.0782,-10.4691,138.087,6595511)

	--trainer
	spawnMobile("lok", "trainer_doctor",60,22.1279,0.26,-6.11676,91,2745866)
	spawnMobile("lok", "trainer_doctor",60,-25.366,0.26,-4.25289,84,2745870)
	spawnMobile("lok", "trainer_medic",60,-16.0068,0.26,-2.42861,117,2745870)
end
