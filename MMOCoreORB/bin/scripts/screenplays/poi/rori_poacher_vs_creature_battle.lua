RoriPoacherVsCreatureBattleScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	planet = "rori",

	mobiles = {
		{"poacher", 770.1, 82.3, -2084.4, 0, 0},
		{"poacher", 770.1, 82.3, -2084.4, 0, 0},
		{"poacher", 770.1, 82.3, -2084.4, 0, 0},
		{"hunter", 748.8, 85.5 -2090.7, 0, 0},
		{"hunter", 748.8, 85.5 -2090.7, 0, 0},
		{"poacher", 752.1, 85.7, -2082.7, 0, 0},
		{"poacher", 752.1, 85.7, -2082.7, 0, 0},
		{"hunter", 765.9, 82.7, -2086.3, 0, 0},
		{"hunter", 765.9, 82.7, -2086.3, 0, 0},
		{"hunter", 765.9, 82.7, -2086.3, 0, 0},
		{"poacher", 781.5, 82.6, -2073.7, 0, 0},
		{"poacher", 781.5, 82.6, -2073.7, 0, 0},
		{"hunter", 772.2, 84.1, -2068.5, 0, 0},
		{"hunter", 772.2, 84.1, -2068.5, 0, 0},

		{"vrobal", 735.8, 89.2, -2074.9, 0, 0},
		{"vrobal", 735.8, 89.2, -2074.9, 0, 0},
		{"vrobal", 735.8, 89.2, -2074.9, 0, 0},
		{"vicious_squall", 785.7, 81.1, -2059.9, 0, 0},
		{"vicious_squall", 785.7, 81.1, -2059.9, 0, 0},
		{"vicious_squall", 785.7, 81.1, -2059.9, 0, 0},
		{"female_squall", 781.8, 81.4, -2048.4, 0, 0},
		{"female_squall", 781.8, 81.4, -2048.4, 0, 0},
		{"male_squall", 790.6, 78.9, -2036.8, 0, 0},
		{"male_squall", 790.6, 78.9, -2036.8, 0, 0},
		{"vrobal", 714.6, 93.6, -2063.5, 0, 0},
		{"vrobal", 714.6, 93.6, -2063.5, 0, 0},
		{"vrobal", 722.2, 91.2, -2076.5, 0, 0},
		{"vrobal", 722.2, 91.2, -2076.5, 0, 0},
	},
}

registerScreenPlay("RoriPoacherVsCreatureBattleScreenPlay", true)

function RoriPoacherVsCreatureBattleScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
	end
end

function RoriPoacherVsCreatureBattleScreenPlay:spawnMobiles()
	local mobileTable = self.mobiles

	for i = 1, #mobileTable, 1 do
		local mobile = mobileTable[i]
		local mobileName = mobile[1]

		spawnMobile(self.planet, mobileName, 300, mobile[2], mobile[3], mobile[4], mobile[5], mobile[6])

	end
end
