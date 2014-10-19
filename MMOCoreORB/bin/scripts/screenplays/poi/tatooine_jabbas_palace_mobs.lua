TatooineJabbasPalaceMobsScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("TatooineJabbasPalaceMobsScreenPlay", true)

function TatooineJabbasPalaceMobsScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		
		spawnSceneObject("tatooine", "object/tangible/instrument/instrument_organ_max_rebo.iff", -11.1, 2, 36.2, 1177487, 0.9974847113288691, 0, -0.07088194879630508, 0)
	end
end

function TatooineJabbasPalaceMobsScreenPlay:spawnMobiles()
	
	spawnMobile("tatooine", "bomarr_monk", 60, 4.01, 5.8, 72.13, 180, 1177470)
	spawnMobile("tatooine", "bomarr_monk", 60, 4.21, 0.2, 104.69, 85, 1177467)
	spawnMobile("tatooine", "bomarr_monk", 60, -18.0, 5.8, 73.0, 196, 1177489)
	spawnMobile("tatooine", "bomarr_monk", 60, 20.44, 11.11, 2.09, 64, 1177500)
	spawnMobile("tatooine", "bomarr_monk", 60, 27.41, 0.2, 43.70, 356, 1177472)
	spawnMobile("tatooine", "bomarr_monk", 60, -18.0, 3.0, 9.0, 207, 1177501)
	spawnMobile("tatooine", "commoner_naboo", 60, -33.8, 0.1, 76.6, 329, 1177491)
	spawnMobile("tatooine", "commoner_tatooine", 60, -37.4, 0.1, 76.9, 242, 1177492)
	spawnMobile("tatooine", "commoner_tatooine", 60, -34.5, 0.1, 88.2, 228, 1177493)
	spawnMobile("tatooine", "commoner_tatooine", 60, -38.7, 0.1, 88.2, 230, 1177494)
	spawnMobile("tatooine", "commoner_tatooine", 60, -10.1, 0.1, 77.5, 332, 1177495)
	spawnMobile("tatooine", "commoner_tatooine", 60, -13.6, 0.1, 77.5, 111, 1177496)
	spawnMobile("tatooine", "commoner_tatooine", 60, -10.9, 0.1, 87.5, 204, 1177497)
	spawnMobile("tatooine", "commoner_tatooine", 60, -15.4, 0.1, 87.7, 42, 1177498)
	spawnMobile("tatooine", "eg6_power_droid", 60, 15.8, 0.2, 82.6, 129, 1177479)
	spawnMobile("tatooine", "eg6_power_droid", 60, 39.6, 0.2, -1.7, 22, 1177499)
	spawnMobile("tatooine", "fringer", 300, -8.7, 2.0, 49.6, 347, 1177487)
	spawnMobile("tatooine", "jawa", 300, -23.0, 3.0, 59.0, 157, 1177474)
	spawnMobile("tatooine", "jawa", 300, -38.0, 3.0, 53.0, 46, 1177481)
	spawnMobile("tatooine", "jawa", 300, -1.0, 3.0, 25.0, 64, 1177487)
	spawnMobile("tatooine", "jawa", 300, -8.0, 3.0, 20.0, 176, 1177501)
	spawnMobile("tatooine", "jawa", 300, -18.0, 3.0, 13.0, 116, 1177501)
	spawnMobile("tatooine", "jawa", 300, -23.0, 3.0, 61.0, 180, 1177474)
	spawnMobile("tatooine", "jawa", 300, 8.7, 2.0, 23.6, 16, 1177487)
	spawnMobile("tatooine", "jawa", 300, 9.2, 2.0, 25.2, 196, 1177487)
	spawnMobile("tatooine", "jawa", 300, 29.4, 0.2, 46.6, 179, 1177472)
	spawnMobile("tatooine", "jawa", 300, 29.4, 0.2, 45.4, 359, 1177472)
	spawnMobile("tatooine", "outlaw", 300, 9.0, 5.8, 73.0, 153, 1177470)
	spawnMobile("tatooine", "roughneck", 300, -9.8, 3.0, 59.7, 274, 1177474)
	spawnMobile("tatooine", "roughneck", 300, -5.88, 2.0, 43.1, 8, 1177487)
	spawnMobile("tatooine", "roughneck", 300, -5.72, 2.0, 44.1, 188, 1177487)
	spawnMobile("tatooine", "scoundrel", 300, 5.0, 2.0, 44.0, 0, 1177487)
	spawnMobile("tatooine", "scoundrel", 300, -14.3, 2.0, 52.1, 264, 1177487)
	spawnMobile("tatooine", "slicer", 60, -9.0, 2.0, 51.0, 167, 1177487)
	spawnMobile("tatooine", "spacer", 300, -9.0, 3.0, 25.0, 303, 1177487)
	spawnMobile("tatooine", "thug", 300, -1.6, 3.0, 26.2, 151, 1177487)
	spawnMobile("tatooine", "thug", 300, -8.4, 3.0, 21.2, 160, 1177487)
	spawnMobile("tatooine", "thug", 300, 1.1, 2.0, 36.7, 180, 1177487)
	spawnMobile("tatooine", "thug", 300, -15.8, 2.0, 51.9, 84, 1177487)
	spawnMobile("tatooine", "thug", 300, -9.9, 3.0, 25.6, 123, 1177487)
	spawnMobile("tatooine", "thug", 300, 1.1, 2.0, 35.1, 0, 1177487)
	spawnMobile("tatooine", "wastrel", 300, 5.1, 2.0, 45.5, 180, 1177487)
		
end
