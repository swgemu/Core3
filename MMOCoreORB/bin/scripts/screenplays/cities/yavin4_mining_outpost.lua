Yavin4MiningOutpostScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "Yavin4MiningOutpostScreenPlay"
}

registerScreenPlay("Yavin4MiningOutpostScreenPlay", true)

function Yavin4MiningOutpostScreenPlay:start()
	if (isZoneEnabled("yavin4")) then
		self:spawnMobiles()
	end
end

function Yavin4MiningOutpostScreenPlay:spawnMobiles()
	--tavern a
	local pNpc = spawnMobile("yavin4", "sullustan_male",60,3.1,0.7,2.4,0,7925478)
	self:setMoodString(pNpc, "npc_sitting_chair")

	pNpc = spawnMobile("yavin4", "medic",60,2.3,0.7,6.5,-5,7925478)
	self:setMoodString(pNpc, "sad")

	pNpc = spawnMobile("yavin4", "surgical_droid_21b",60,-1.9,0.7,2.5,175,7925478)
	self:setMoodString(pNpc, "neutral")

	--tavern b
	pNpc = spawnMobile("yavin4", "shadowy_figure",60,0.4,0.6,-0.7,-179,7925451)
	self:setMoodString(pNpc, "npc_sitting_chair")

	pNpc = spawnMobile("yavin4", "bartender",60,3.4,0.6,5.6,173,7925449)
	self:setMoodString(pNpc, "conversation")

	pNpc = spawnMobile("yavin4", "commoner_fat",60,3.5,0.6,4.2,-5,7925449)
	self:setMoodString(pNpc, "npc_standing_drinking")

	--building empty
	pNpc = spawnMobile("yavin4", "ithorian_male",60,3.6,0.1,-0.5,0,1713372)
	self:setMoodString(pNpc, "npc_sitting_chair")

	--outside tavern area
	spawnMobile("yavin4", "rebel_commando", 460, -255.5, 35.0, 4859.2, 81, 0)
	spawnMobile("yavin4", "rebel_commando", 460, -250.5, 35.0, 4854.2, 86, 0)
	spawnMobile("yavin4", "rebel_commando", 460, -260.5, 35.0, 4864.2, 76, 0)
	
end
