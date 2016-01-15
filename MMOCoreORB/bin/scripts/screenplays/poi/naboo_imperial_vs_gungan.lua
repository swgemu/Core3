local ObjectManager = require("managers.object.object_manager")

ImperialVsGunganScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "ImperialVsGunganScreenPlay",

	gunganMobiles = {
		{ "rebel_gungan_priest", 420, 4760.9, 13.7, -3894.2, 11 },
		{ "rebel_gungan_boss", 300, 4763.8, 28.2, -3929.1, 0 },
		{ "rebel_gungan_captain", 300, 4764.3, 28.2, -3922.5, -90 },
		{ "rebel_gungan_general", 300, 4755.2, 28.2, -3925.0, 0 },
		{ "rebel_gungan_captain", 300, 4757.7, 28.2, -3929.1, 0 },
		{ "rebel_gungan_war_chief", 300, 4755.2, 28.2, -3922.5, 180 },
		{ "rebel_gungan_guard", 300, 4767.2, 13.9, -3898.5, -90 },
		{ "rebel_gungan_guard", 300, 4751.1, 13.9, -3898.5, 90 },
		{ "rebel_gungan_war_chief", 300, 4750.8, 13.9, -3906.6, 0 },
		{ "rebel_gungan_war_chief", 300, 4767.1, 14.0, -3903.5, 0 },
		{ "rebel_gungan_kaadu_rider", 300, 4786.8, 14.7, -3924.9, 0 },
		{ "rebel_gungan_kaadu_rider", 300, 4789.3, 14.4, -3937.6, 0 },
		{ "gungan_kaadu", 300, 4784.3, 14.7, -3924.9, 0 },
		{ "gungan_kaadu", 300, 4786.8, 14.4, -3937.6, 0 },
		{ "gungan_falumpaset", 300, 4752.1, 13.1, -3948.2, -60 },
		{ "gungan_falumpaset", 300, 4736.4, 13.1, -3938.9, -15 },
		{ "rebel_gungan_bomber", 300, 4729.9, 13.2, -3914.7, 0 },
		{ "gungan_falumpaset", 300, 4727.5, 13.2, -3917.2, 0 },

		{ "rebel_gungan_priest", 300, 4730.8, 12.8, -3897.9, 20 },
		{ "rebel_gungan_priest", 300, 4751.0, 12.8, -3887.1, 2 },
		{ "rebel_gungan_grand_army_soldier", 300, 4766.8, 13.6, -3886.4, 0 },
		{ "rebel_gungan_grand_army_soldier", 300, 4753.0, 12.5, -3874.9, 10 },
		{ "rebel_gungan_grand_army_soldier", 300, 4780.4, 13.5, -3876.3, 0 },
		{ "rebel_gungan_grand_army_soldier", 300, 4791.8, 13.6, -3876.4, 0 },

		{ "rebel_gungan_scout", 300, 4727.9, 10.4, -3852.1, 44 },
		{ "rebel_gungan_scout", 300, 4811.4, 13.2, -3867.5, -34 },
		{ "rebel_gungan_scout", 300, 4802.3, 14.5, -3893.8, -24 },
		{ "rebel_gungan_bomber", 300, 4743.6, 12.2, -3876.0, 10 },
		{ "rebel_gungan_bomber", 300, 4761.9, 12.7, -3873.5, 15 },
		{ "rebel_gungan_guard", 300, 4772.4, 13.1, -3875.1, 13 }
	},

	imperialMobiles = {
		{ "imperial_exterminator", 420, 4761.4, 10.7, -3823.9, -175 },
		{ "plasma_thieving_swamp_trooper", 300, 4742.5, 10.2, -3836.4, -165 },
		{ "plasma_thieving_swamp_trooper_captain", 300, 4791.3, 11.4, -3821.6, -167 },
		{ "imperial_exterminator", 300, 4759.2, 10.7, -3830.4, 72 },
		{ "plasma_thieving_swamp_trooper", 300, 4757.2, 10.7, -3826.7, 72 },
		{ "plasma_thieving_swamp_trooper_captain", 300, 4784.7, 11.3, -3820.7, 95 },
		{ "plasma_thieving_swamp_trooper", 300, 4768.4, 10.9, -3825.0, 35 },

		{ "plasma_thieving_swamp_trooper", 300, 4781.3, 12.0, -3847.1, 161 },
		{ "plasma_thieving_swamp_trooper", 300, 4740.9, 10.7, -3851.5, -90 },
		{ "plasma_thieving_swamp_trooper", 300, 4784.3, 12.0, -3845.9, 160 },
		{ "plasma_thieving_swamp_trooper", 300, 4778.3, 12.0, -3849.5, 170 },
		{ "plasma_thieving_swamp_trooper_captain", 300, 4768.7, 11.8, -3854.9, 175 },
		{ "plasma_thieving_swamp_trooper", 300, 4761.2, 11.8, -3856.0, 175 },
		{ "plasma_thieving_swamp_trooper", 300, 4754.7, 11.7, -3858.0, 175 },
		{ "plasma_thieving_swamp_trooper", 300, 4747.7, 11.6, -3859.1, 175 },

		{ "plasma_thieving_swamp_trooper", 300, 4726.2, 9.6, -3825.6, 175 },
		{ "plasma_thieving_swamp_trooper", 300, 4712.3, 11.2, -3871.0, 15 },
		{ "plasma_thieving_swamp_trooper", 300, 4808.3, 11.7, -3836.6, 166 }
	}

}

registerScreenPlay("ImperialVsGunganScreenPlay", true)

function ImperialVsGunganScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
	end
end

function ImperialVsGunganScreenPlay:spawnMobiles()
	local mobileTable = self.gunganMobiles
	for i = 1, #mobileTable, 1 do
		local pMobile = spawnMobile("naboo", mobileTable[i][1], mobileTable[i][2], mobileTable[i][3], mobileTable[i][4], mobileTable[i][5], mobileTable[i][6], 0)
		if (pMobile ~= nil and CreatureObject(pMobile):isAiAgent()) then
			AiAgent(pMobile):setAiTemplate("")
		end
	end
	
	mobileTable = self.imperialMobiles
	for i = 1, #mobileTable, 1 do
		local pMobile = spawnMobile("naboo", mobileTable[i][1], mobileTable[i][2], mobileTable[i][3], mobileTable[i][4], mobileTable[i][5], mobileTable[i][6], 0)
		if (pMobile ~= nil and CreatureObject(pMobile):isAiAgent()) then
			AiAgent(pMobile):setAiTemplate("")
		end
	end
end
