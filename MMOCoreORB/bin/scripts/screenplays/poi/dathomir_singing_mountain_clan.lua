SingingMountainClanScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SingingMountainClanScreenPlay",

}

registerScreenPlay("SingingMountainClanScreenPlay", true)

function SingingMountainClanScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
	end
end

function SingingMountainClanScreenPlay:spawnMobiles()

	--Structure Entrance. 154, 4573

	spawnMobile("dathomir", "singing_mountain_clan_sentry", 900, -1.5, 2.0, 5.6, 78, 2665879)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 900, -1.4, 2.0, 10.1, 81, 2665879)
	spawnMobile("dathomir", "singing_mountain_clan_huntress", 900, 4.7, 2.0, 13.3, -21, 2665879)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 900, 0.6, 2.0, 23.4, -108, 2665879)

	spawnMobile("dathomir", "singing_mountain_clan_guardian", 900, -12.0, 2.0, 14.7, 150, 2665880)
	spawnMobile("dathomir", "singing_mountain_clan_slave", 900, -12.78, 2.3, 4.47, 0, 2665880)
	spawnMobile("dathomir", "singing_mountain_clan_slave", 900, -11.3, 2.3, 5.38, 0, 2665880)
	spawnMobile("dathomir", "singing_mountain_clan_slave", 900, -12.7, 2.3, 6.3, 0, 2665880)

	spawnMobile("dathomir", "singing_mountain_clan_huntress", 900, -28.1, 2.0, 4.9, 63, 2665881)
	spawnMobile("dathomir", "singing_mountain_clan_huntress", 900, -27.3, 2.0, 9.0, 66, 2665881)

	spawnMobile("dathomir", "singing_mountain_clan_rancor_tamer", 900, -17.8, 2.0, -6.1, -97, 2665882)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 900, -25.9, 2.0, -7.4, -153, 2665882)

	spawnMobile("dathomir", "singing_mountain_clan_councilwoman", 1800, -1.7, 3.0, -5.2, 140, 2665884)
	spawnMobile("dathomir", "singing_mountain_clan_guardian", 900, 3.0, 2.0, -16.5, -138, 2665884)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 900, 8.5, 2.0, -26.4, -45, 2665884)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 900, 8.6, 2.0, -21.2, -150, 2665884)

	spawnMobile("dathomir", "singing_mountain_clan_sentry", 900, 16.4, 2.01, -10.8, -174, 2665885)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 900, 16.5, 2.0, -24.4, -82, 2665885)

	spawnMobile("dathomir", "singing_mountain_clan_slave", 900, 24.9, 2.0, -20.2, 49, 2665886)

	spawnMobile("dathomir", "singing_mountain_clan_slave", 900, 27.0, 2.0, -12.4, 89, 2665887)

	spawnMobile("dathomir", "singing_mountain_clan_slave", 900, 26.2, 2.0, -3.6, 86, 2665888)

	spawnMobile("dathomir", "singing_mountain_clan_slave", 900, 16.4, 2.0, 7.4, 0, 2665889)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 900, 16.8, 2.0, 9.7, -6, 2665889)

	spawnMobile("dathomir", "singing_mountain_clan_rancor_tamer", 600, 153.0, 430.0, 4544.3, 0, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor", 600, 147.5, 430.0, 4537.5, 0, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor", 600, 158.5, 430.0, 4537.5, 0, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 600, 141.0, 430.0, 4549.3, 90, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 600, 164.6, 430.0, 4554.5, -90, 0)
	spawnMobile("dathomir", "singing_mountain_clan_huntress", 600, 150.1, 430.0, 4525.8, 23, 0)
	spawnMobile("dathomir", "singing_mountain_clan_dragoon", 600, 162.3, 430.0, 4528.2, -70, 0)

	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 600, 195.3, 430.0, 4593.2, -145, 0)
	spawnMobile("dathomir", "singing_mountain_clan_huntress", 600, 199.9, 430.0, 4580.8, -83, 0)
	spawnMobile("dathomir", "singing_mountain_clan_scout", 600, 185.8, 430.0, 4571.3, -45, 0)

	spawnMobile("dathomir", "singing_mountain_clan_dragoon", 600, 162.2, 390.7, 4637.8, 10, 0)
	spawnMobile("dathomir", "singing_mountain_clan_dragoon", 600, 151.8, 429.2, 4581.1, 10, 0)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 600, 176.7, 375.6, 4668.3, 47, 0)
	spawnMobile("dathomir", "singing_mountain_clan_outcast", 450, 87.3, 312.1, 4684.6, -176, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor_tamer", 600, 210.6, 369.9, 4686.2, -11, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor", 600, 209.1, 371.6, 4691.2, 38, 0)

	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 900, 253.9, 256.2, 4842.8, -66, 0)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 900, 270.3, 275.9, 4813.3, -125, 0)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 600, 307.7, 334.1, 4753.5, 13, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 600, 388.2, 345.6, 4751.6, -112, 0)

	spawnMobile("dathomir", "singing_mountain_clan_rancor", 600, 513.8, 275.1, 4739.1, 105, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor_tamer", 600, 512.4, 275.0, 4733.3, 105, 0)
	spawnMobile("dathomir", "singing_mountain_clan_guardian", 600, 502.6, 274.9, 4697.2, 33, 0)
	spawnMobile("dathomir", "singing_mountain_clan_councilwoman", 1800, 530.7, 275.0, 4690.4, -15, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 600, 521.2, 275.0, 4714.3, -16, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 600, 517.7, 275.0, 4718.5, 114, 0)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 600, 524.6, 275.0, 4720.3, -129, 0)
	spawnMobile("dathomir", "singing_mountain_clan_huntress", 600, 534.2, 274.4, 4737.5, -147, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 450, 546.8, 275.0, 4702.1, 75, 0)

	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 900, 677.5, 214.2, 4622.4, 64, 0)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 900, 693.3, 214.1, 4590.3, -160, 0)
	spawnMobile("dathomir", "singing_mountain_clan_huntress", 600, 601.4, 247.5, 4612.1, 152, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 600, 626.7, 257.3, 4560.4, -20, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 600, 635.5, 256.1, 4485.3, -170, 0)

	spawnMobile("dathomir", "singing_mountain_clan_guardian", 1800, 614.8, 260.0, 4520.2, -90, 0)
	spawnMobile("dathomir", "singing_mountain_clan_dragoon", 900, 599.3, 260.0, 4521.5, 172, 0)
	spawnMobile("dathomir", "singing_mountain_clan_scout", 900, 591.5, 260.0, 4512.8, 51, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 600, 571.2, 260.0, 4520.3, 93, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 600, 571.4, 260.0, 4536.8, 117, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 450, 581.5, 260.0, 4550.6, 149, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 450, 601.4, 260.0, 4542.8, 84, 0)

	spawnMobile("dathomir", "singing_mountain_clan_scout", 300, 833.8, 190.3, 4328.9, -75, 0)
	spawnMobile("dathomir", "singing_mountain_clan_scout", 300, 797.7, 190.3, 4208.2, 175, 0)
	spawnMobile("dathomir", "singing_mountain_clan_scout", 300, 696.0, 186.7, 4070.5, 160, 0)
	spawnMobile("dathomir", "singing_mountain_clan_scout", 300, 528.1, 190.0, 4029.3, -75, 0)
	spawnMobile("dathomir", "singing_mountain_clan_scout", 300, 374.3, 176.1, 3979.4, -155, 0)

	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 600, 608.0, 272.3, 4325.7, -165, 0)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 600, 629.1, 251.6, 4281.8, 65, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor", 600, 625.6, 240.3, 4238.4, 135, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor_tamer", 600, 634.3, 238.9, 4240.2, 145, 0)

	spawnMobile("dathomir", "singing_mountain_clan_initiate", 900, 602.4, 257.7, 4246.7, 137, 0)
	spawnMobile("dathomir", "singing_mountain_clan_councilwoman", 1800, 546.3, 229.5, 4244.3, 170, 0)
	spawnMobile("dathomir", "singing_mountain_clan_councilwoman", 1800, 513.3, 229.5, 4168.1, -3, 0)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 600, 566.1, 229.5, 4225.9, -105, 0)
	spawnMobile("dathomir", "singing_mountain_clan_guardian", 900, 543.7, 229.5, 4214.4, -7, 0)
	spawnMobile("dathomir", "singing_mountain_clan_dragoon", 600, 551.8, 229.5, 4204.4, -110, 0)
	spawnMobile("dathomir", "singing_mountain_clan_scout", 600, 538.3, 229.5, 4176.0, -175, 0)
	spawnMobile("dathomir", "singing_mountain_clan_scout", 600, 547.3, 229.5, 4178.5, -175, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 600, 537.9, 229.5, 4230.9, 107, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor", 600, 535.2, 229.5, 4207.8, 145, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor_tamer", 600, 529.6, 229.5, 4202.9, 145, 0)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 600, 500.0, 229.5, 4219.1, 145, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor", 600, 505.5, 229.5, 4202.6, 105, 0)
	spawnMobile("dathomir", "singing_mountain_clan_huntress", 600, 502.1, 229.5, 4187.4, 2, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 450, 573.4, 229.5, 4162.6, -109, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 450, 536.4, 229.5, 4146.8, 164, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 450, 476.7, 230.2, 4125.6, -104, 0)

	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 600, 363.9, 220.5, 4109.9, -157, 0)
	spawnMobile("dathomir", "singing_mountain_clan_guardian", 900, 175.7, 149.7, 4032.9, -117, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 450, 173.0, 150.0, 4041.6, -117, 0)

	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 600, 250.7, 385.2, 4338.3, 147, 0)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 600, 375.0, 367.0, 4321.0, -4, 0)
	spawnMobile("dathomir", "singing_mountain_clan_scout", 600, 432.6, 317.6, 4275.9, 135, 0)
	spawnMobile("dathomir", "singing_mountain_clan_outcast", 600, 268.7, 226.6, 4154.1, -151, 0)

	spawnMobile("dathomir", "aujante_klee", 1800, 3.0, 3.0, -5.2 ,180, 2665884)
	spawnMobile("dathomir", "herald_dathomir_azzenaj", 900, 533.7, 228, 4238.5, 130, 0)
	spawnMobile("dathomir", "izaryx", 900, -12, 2.0, -4, 240, 2665882)
	spawnMobile("dathomir", "vhaunda", 900, -22.3, 2.0, 5.05, 0, 2665881)
	spawnMobile("dathomir", "vurlene", 900, -12, 3.0, 9.5, 60, 2665880)
	spawnMobile("dathomir", "zideera", 900, -14.2, 1.9, -21.0, 0, 2665883)
end
