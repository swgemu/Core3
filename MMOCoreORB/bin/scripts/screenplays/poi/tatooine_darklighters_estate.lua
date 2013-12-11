TatooineDarklightersEstateScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TatooineDarklightersEstateScreenPlay"
}

registerScreenPlay("TatooineDarklightersEstateScreenPlay", true)

function TatooineDarklightersEstateScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
	end
end

function TatooineDarklightersEstateScreenPlay:spawnMobiles()

	spawnMobile("tatooine", "informant_npc_lvl_2",0,-685,8,-6731,0,0)
	spawnMobile("tatooine", "informant_npc_lvl_2",0,-703,8,-6734,0,0)

end
