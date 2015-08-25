Yavin4LaborOutpostScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "Yavin4LaborOutpostScreenPlay"
}

registerScreenPlay("Yavin4LaborOutpostScreenPlay", true)

function Yavin4LaborOutpostScreenPlay:start()
	if (isZoneEnabled("yavin4")) then
		self:spawnMobiles()
	end
end

function Yavin4LaborOutpostScreenPlay:spawnMobiles()

	local pNpc = spawnMobile("yavin4", "devaronian_male",60,7.3,0.6,-6.7,-149,3035379)
	self:setMoodString(pNpc, "npc_standing_drinking")
	pNpc = spawnMobile("yavin4", "commoner_technician",60,5.8,0.6,-6.2,-141,3035379)
	self:setMoodString(pNpc, "npc_use_terminal_low")
	pNpc = spawnMobile("yavin4", "chiss_female",60,-6.8,0.6,6.3,179,3035377)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("yavin4", "chiss_male",60,-6.8,0.6,5.0,1,3035377)
	self:setMoodString(pNpc, "happy")
	pNpc = spawnMobile("yavin4", "medic",60,-6.1,0.6,-3.8,-102,3035374)
	self:setMoodString(pNpc, "sad")
	pNpc = spawnMobile("yavin4", "commoner_technician",60,-6.1,0.6,-4.8,-10,3035374)
	self:setMoodString(pNpc, "npc_consoling")

end
