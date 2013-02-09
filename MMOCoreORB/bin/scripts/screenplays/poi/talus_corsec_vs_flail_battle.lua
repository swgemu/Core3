TalusCorsecVsFlailBattleScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("TalusCorsecVsFlailBattleScreenPlay", true)

function TalusCorsecVsFlailBattleScreenPlay:start()
	self:spawnMobiles()
end

function TalusCorsecVsFlailBattleScreenPlay:spawnMobiles()   
	spawnMobile("talus", "flail_boss", 300, 3085.8, 35.0, 6151.3, -148, 0)
	spawnMobile("talus", "flail_cutthroat", 300, 3073.9, 35.0, 6148.4, 48,  0)
	spawnMobile("talus", "flail_enforcer", 300, 3083.8, 35.0, 6144.0, 101, 0)
	spawnMobile("talus", "flail_killer", 300, 3079.8, 35.0, 6136.2, -142, 0)
	spawnMobile("talus", "flail_slayer", 300, 3077.0, 36.6, 6128.6, -135, 0)
	spawnMobile("talus", "flail_butcher", 300, 3066.3, 36.4, 6131.9, -139, 0)
	spawnMobile("talus", "corsec_chief", 300, 3023.3, 25.4, 6089.6, 50, 0)
	spawnMobile("talus", "corsec_captain", 300, 3040.6, 25.9, 6093.6, 37, 0)
	spawnMobile("talus", "corsec_trooper", 300, 3038.3, 30.6, 6104.7, 38, 0)
	spawnMobile("talus", "corsec_trooper", 300, 3045.9, 30.0, 6102.3, 30, 0)
	spawnMobile("talus", "corsec_trooper", 300, 3051.9, 29.8, 6099.3, 22, 0)
	spawnMobile("talus", "corsec_trooper", 300, 3053.1, 31.1, 6108.8, 38, 0)	
end
