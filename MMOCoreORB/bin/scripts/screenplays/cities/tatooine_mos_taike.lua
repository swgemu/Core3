TatooineMosTaikeScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineMosTaikeScreenPlay"
}

registerScreenPlay("TatooineMosTaikeScreenPlay", true)

function TatooineMosTaikeScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:spawnSceneObjects()
	end
end

function TatooineMosTaikeScreenPlay:spawnSceneObjects()

	--Tavern
	spawnSceneObject("tatooine", "object/static/structure/general/droid_r2_powerdown.iff", 5.5, 1.0, 10.3, 1154121, math.rad(180) )
	spawnSceneObject("tatooine", "object/static/structure/general/all_foodcart_s01.iff", -7.1, -4.0, -6.1, 1154126, math.rad(180) )

end

function TatooineMosTaikeScreenPlay:spawnMobiles()

	local pNpc = spawnMobile("tatooine", "vendor",60,4.6,1.0,6.3,-107,1154121)
	self:setMoodString(pNpc, "npc_use_terminal_high")
	pNpc = spawnMobile("tatooine", "patron_ithorian",60,10.4,0.4,0.6,-150,1154122)
	self:setMoodString(pNpc, "npc_standing_drinking")
	pNpc = spawnMobile("tatooine", "patron_ithorian",60,9.6,0.4,-0.6,23,1154122)
	self:setMoodString(pNpc, "conversation")
	pNpc = spawnMobile("tatooine", "sullustan_male",60,9.0,0.4,-9.8,172,1154122)
	self:setMoodString(pNpc, "npc_use_terminal_low")
	pNpc = spawnMobile("tatooine", "entertainer",60,1.0,0.4,-4.7,173,1154122)
	self:setMoodString(pNpc, "npc_use_terminal_low")
	pNpc = spawnMobile("tatooine", "contractor",60,2.9,0.4,1.9,90,1154122)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("tatooine", "businessman",60,5.9,0.4,1.8,-90,1154122)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("tatooine", "mercenary",60,4.5,0.4,0.6,0,1154122)
	self:setMoodString(pNpc, "npc_sitting_table_eating")
	pNpc = spawnMobile("tatooine", "commoner_tatooine",60,9.1,0.4,-5.1,127,1154122)
	self:setMoodString(pNpc, "entertained")
	pNpc = spawnMobile("tatooine", "noble",60,10.4,0.4,5.6,-158,1154122)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("tatooine", "shadowy_figure",60,-8.9,1.0,7.5,89,1154123)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("tatooine", "twilek_slave",60,-8.9,1.0,6.6,89,1154123)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("tatooine", "scientist",60,5.0,-4.0,-7.6,46,1154128)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("tatooine", "r3",60,4.9,-4.0,-5.6,171,1154128)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("tatooine", "chiss_female",60,-3.8,-4.0,9.0,-45,1154127)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("tatooine", "medic",60,-4.3,-4.0,8.7,58,1154127)
	self:setMoodString(pNpc, "npc_use_terminal_low")
	pNpc = spawnMobile("tatooine", "entertainer",120,-6.0,1.0,7.2,-96,1154123)
	self:setMoodString(pNpc, "themepark_music_2")
	pNpc = spawnMobile("tatooine", "commoner_naboo",60,1.7,1.0,4.8,-85,1154123)
	self:setMoodString(pNpc, "entertained")

		--misc
	--spawnMobile("tatooine", "junk_dealer", 1, 3905.3, 33, 2362.9, -90, 0)
	--spawnMobile("tatooine", "junk_nathan", 1, 3817.7, 16.2, 2340.5, 0, 0)
	spawnMobile("tatooine", "informant_npc_lvl_1", 1, 3775, 8.7, 2371, 180, 0)
	spawnMobile("tatooine", "informant_npc_lvl_2", 1, 0.93374, 1.00421, 9.03511, 180, 1154123)
	spawnMobile("tatooine", "informant_npc_lvl_3", 1, -1.97807, -9.54192, 9.62469, -45, 1154131)
		--commoners
	spawnMobile("tatooine", "commoner_tatooine", 1, 3860.7, 28.0, 2361.1, 180, 0)
	spawnMobile("tatooine", "commoner_tatooine", 1, 3775.0, 8.6, 2369.7, 0, 0)
	spawnMobile("tatooine", "commoner_tatooine", 1, 4.9, -0.4, -3.8, -150, 1400866)
	spawnMobile("tatooine", "commoner_tatooine", 1, 3.1, -0.4, -5.8, -45, 1400866)
		--thugs
	spawnMobile("tatooine", "scoundrel", 300, 3867.0, 27.5, 2307.5, -90, 0)
	spawnMobile("tatooine", "spice_fiend", 300, 3865.0, 27.5, 2307.5, 90, 0)
	spawnMobile("tatooine", "dune_stalker", 300, getRandomNumber(13) + 3734.0, 6.2, getRandomNumber(13) + 2466.5, getRandomNumber(360), 0)
	spawnMobile("tatooine", "dune_stalker", 300, getRandomNumber(13) + 3734.0, 6.2, getRandomNumber(13) + 2466.5, getRandomNumber(360), 0)
	spawnMobile("tatooine", "dune_stalker", 300, getRandomNumber(13) + 3734.0, 6.2, getRandomNumber(13) + 2466.5, getRandomNumber(360), 0)
	spawnMobile("tatooine", "dune_stalker_scavenger", 300, getRandomNumber(13) + 3734.0, 6.2, getRandomNumber(13) + 2466.5, getRandomNumber(360), 0)
	spawnMobile("tatooine", "dune_stalker_scavenger", 300, getRandomNumber(13) + 3734.0, 6.2, getRandomNumber(13) + 2466.5, getRandomNumber(360), 0)
	spawnMobile("tatooine", "dune_stalker_scavenger", 300, getRandomNumber(13) + 3734.0, 6.2, getRandomNumber(13) + 2466.5, getRandomNumber(360), 0)
	spawnMobile("tatooine", "swooper", 300, getRandomNumber(13) + 3781, 6.9, getRandomNumber(13) + 2220, getRandomNumber(360), 0)
	spawnMobile("tatooine", "swooper", 300, getRandomNumber(13) + 3781, 6.9, getRandomNumber(13) + 2220, getRandomNumber(360), 0)
	spawnMobile("tatooine", "swooper", 300, getRandomNumber(13) + 3781, 6.9, getRandomNumber(13) + 2220, getRandomNumber(360), 0)
	spawnMobile("tatooine", "swooper", 300, getRandomNumber(13) + 3781, 6.9, getRandomNumber(13) + 2220, getRandomNumber(360), 0)
	spawnMobile("tatooine", "swooper", 300, getRandomNumber(13) + 3781, 6.9, getRandomNumber(13) + 2220, getRandomNumber(360), 0)
	spawnMobile("tatooine", "swooper", 300, getRandomNumber(13) + 3781, 6.9, getRandomNumber(13) + 2220, getRandomNumber(360), 0)
		--jawas
	spawnMobile("tatooine", "jawa_engineer", 300, 3971.5, 8.9, 2496.9, -97, 0)
	spawnMobile("tatooine", "jawa_engineer", 300, 3966.1, 9.1, 2502.9, 40, 0)
	spawnMobile("tatooine", "jawa_smuggler", 300, 3967.6, 9.0, 2503.3, -90, 0)
	spawnMobile("tatooine", "jawa_smuggler", 300, 3966.9, 9.1, 2504.5, -155, 0)
	spawnMobile("tatooine", "jawa_engineer", 300, 3974.4, 7.3, 2517.1, -161, 0)
	spawnMobile("tatooine", "jawa_smuggler", 300, 3980.9, 7.7, 2507.0, 25, 0)

		--creatures
	spawnMobile("tatooine", "rockmite", 300, getRandomNumber(13) + 3992, 7.4, getRandomNumber(13) + 2576, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rockmite", 300, getRandomNumber(13) + 3992, 7.4, getRandomNumber(13) + 2576, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rockmite", 300, getRandomNumber(13) + 3992, 7.4, getRandomNumber(13) + 2576, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rockmite", 300, getRandomNumber(13) + 3992, 7.4, getRandomNumber(13) + 2576, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rockmite", 300, getRandomNumber(13) + 3992, 7.4, getRandomNumber(13) + 2576, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rockmite", 300, getRandomNumber(13) + 3992, 7.4, getRandomNumber(13) + 2576, getRandomNumber(360), 0)

	spawnMobile("tatooine", "tatooine_mynock", 300, getRandomNumber(13) + 3660, 7.6, getRandomNumber(13) + 2407, getRandomNumber(360), 0)
	spawnMobile("tatooine", "tatooine_mynock", 300, getRandomNumber(13) + 3660, 7.6, getRandomNumber(13) + 2407, getRandomNumber(360), 0)
	spawnMobile("tatooine", "tatooine_mynock", 300, getRandomNumber(13) + 3660, 7.6, getRandomNumber(13) + 2407, getRandomNumber(360), 0)
	spawnMobile("tatooine", "tatooine_mynock", 300, getRandomNumber(13) + 3660, 7.6, getRandomNumber(13) + 2407, getRandomNumber(360), 0)
	spawnMobile("tatooine", "tatooine_mynock", 300, getRandomNumber(13) + 3660, 7.6, getRandomNumber(13) + 2407, getRandomNumber(360), 0)
	spawnMobile("tatooine", "tatooine_mynock", 300, getRandomNumber(13) + 3660, 7.6, getRandomNumber(13) + 2407, getRandomNumber(360), 0)

	spawnMobile("tatooine", "rockmite", 300, getRandomNumber(13) + 3660, 8.1, getRandomNumber(13) + 2258, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rockmite", 300, getRandomNumber(13) + 3660, 8.1, getRandomNumber(13) + 2258, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rockmite", 300, getRandomNumber(13) + 3660, 8.1, getRandomNumber(13) + 2258, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rockmite", 300, getRandomNumber(13) + 3660, 8.1, getRandomNumber(13) + 2258, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rockmite", 300, getRandomNumber(13) + 3660, 8.1, getRandomNumber(13) + 2258, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rockmite", 300, getRandomNumber(13) + 3660, 8.1, getRandomNumber(13) + 2258, getRandomNumber(360), 0)

	spawnMobile("tatooine", "rill", 300, getRandomNumber(13) + 3889, 6.6, getRandomNumber(13) + 2139, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rill", 300, getRandomNumber(13) + 3889, 6.6, getRandomNumber(13) + 2139, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rill", 300, getRandomNumber(13) + 3889, 6.6, getRandomNumber(13) + 2139, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rill", 300, getRandomNumber(13) + 3889, 6.6, getRandomNumber(13) + 2139, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rill", 300, getRandomNumber(13) + 3889, 6.6, getRandomNumber(13) + 2139, getRandomNumber(360), 0)
	spawnMobile("tatooine", "rill", 300, getRandomNumber(13) + 3889, 6.6, getRandomNumber(13) + 2139, getRandomNumber(360), 0)

	spawnMobile("tatooine", "minor_worrt", 300, getRandomNumber(13) + 4102, 12.3, getRandomNumber(13) + 2199, getRandomNumber(360), 0)
	spawnMobile("tatooine", "minor_worrt", 300, getRandomNumber(13) + 4102, 12.3, getRandomNumber(13) + 2199, getRandomNumber(360), 0)
	spawnMobile("tatooine", "minor_worrt", 300, getRandomNumber(13) + 4102, 12.3, getRandomNumber(13) + 2199, getRandomNumber(360), 0)
	spawnMobile("tatooine", "minor_worrt", 300, getRandomNumber(13) + 4102, 12.3, getRandomNumber(13) + 2199, getRandomNumber(360), 0)
	spawnMobile("tatooine", "minor_worrt", 300, getRandomNumber(13) + 4102, 12.3, getRandomNumber(13) + 2199, getRandomNumber(360), 0)
	spawnMobile("tatooine", "minor_worrt", 300, getRandomNumber(13) + 4102, 12.3, getRandomNumber(13) + 2199, getRandomNumber(360), 0)

end
