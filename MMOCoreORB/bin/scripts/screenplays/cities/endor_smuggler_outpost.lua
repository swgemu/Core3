EndorSmugglerOutpostScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "EndorSmugglerOutpostScreenPlay"
}

registerScreenPlay("EndorSmugglerOutpostScreenPlay", true)

function EndorSmugglerOutpostScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
	end
end

function EndorSmugglerOutpostScreenPlay:spawnMobiles()

	--tavern
	local pNpc = spawnMobile("endor", "commoner_old",60,1.0,0.7,-4.4,0,6645605)
	self:setMoodString(pNpc, "npc_sitting_chair")
	spawnMobile("endor", "businessman", 60, 3175.37, 24, -3490.78, 156.98, 0)
	spawnMobile("endor", "businessman", 60, 3190.35, 24, -3434.93, 256.64, 0)
	spawnMobile("endor", "businessman", 60, 3239.41, 24, -3432.75, 321.916, 0)
	spawnMobile("endor", "businessman", 60, 3270.48, 24, -3452.45, 289.69, 0)
	spawnMobile("endor", "businessman", 60, 3246.59, 24, -3500.57, 28.4927, 0)
	spawnMobile("endor", "businessman", 60, 3209.65, 24, -3493.64, 217.211, 0)
	spawnMobile("endor", "cll8_binary_load_lifter", 60,3250.85, 24, -3463.83, 330.752, 0)
	spawnMobile("endor", "commando", 300, 3196.77, 24, -3483.16, 359.892, 0)
	spawnMobile("endor", "commando", 300, 3166, 24, -3454, 130, 0)
	spawnMobile("endor", "commoner", 60, 3176.73, 24, -3512.02, 187.645, 0)
	spawnMobile("endor", "commoner", 60, 3188.73, 24, -3482.54, 277.835, 0)
	spawnMobile("endor", "commoner", 60, 3186.49, 24, -3459.94, 189.74, 0)
	spawnMobile("endor", "commoner", 60, 3171.1, 24,- 3504.6, 196.748, 0)
	spawnMobile("endor", "commoner", 60, 3246.28, 24, -3492.11, 322.758, 0)
	spawnMobile("endor", "commoner", 60, 3272.55, 24, -3438.99, 185.321, 0)
	spawnMobile("endor", "commoner", 60, 3255.57, 24, -3483.66, 195.741, 0)
	spawnMobile("endor", "commoner", 60, 3271.4, 24, -3502.14, 322.22, 0)
	spawnMobile("endor", "commoner", 60, 3201.34, 24, -3509.29, 348.067, 0)
	spawnMobile("endor", "commoner", 60, 3221.86, 24, -3473.87, 251.839, 0)
	spawnMobile("endor", "mercenary", 60, 3277, 24, -3484, -80, 0)
	spawnMobile("endor", "mercenary", 60, 3233, 24, -3451, 170, 0)
	spawnMobile("endor", "mercenary", 60, 3201, 24, -3463, 170, 0)
	spawnMobile("endor", "noble", 60, 3228.48, 24, -3510.48, 15.5858, 0)
	pNpc = spawnMobile("endor", "r3",60,3250.85,24,-3464.83,263.893,0)
	self:setMoodString(pNpc, "calm")
	pNpc = spawnMobile("endor", "r5",60,3249.85,24,-3464.83,180.771,0)
	self:setMoodString(pNpc, "calm")

end
