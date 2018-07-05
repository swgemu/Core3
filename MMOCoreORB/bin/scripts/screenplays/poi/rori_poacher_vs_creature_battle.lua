RoriPoacherVsCreatureBattleScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("RoriPoacherVsCreatureBattleScreenPlay", true)

function RoriPoacherVsCreatureBattleScreenPlay:start()
	if (isZoneEnabled("rori")) then
		self:spawnMobiles()
	end
end

function RoriPoacherVsCreatureBattleScreenPlay:spawnMobiles()

	spawnMobile("rori", "poacher", 300, 773.7, 82.0, -2091.8, -45, 0)
	spawnMobile("rori", "poacher", 300, 776.3, 81.7, -2086.6, -99, 0)
	spawnMobile("rori", "poacher", 300, 768.3, 82.2, -2091.5, 50, 0)
	spawnMobile("rori", "poacher", 300, 773.5, 81.9, -2086.1, 155, 0)
	spawnMobile("rori", "poacher", 300, 772.3, 81.8, -2090.0, 42, 0)
	spawnMobile("rori", "hunter", 300, 751.3, 84.9, -2092.7, -24, 0)
	spawnMobile("rori", "hunter", 300, 752.9, 84.7, -2089.8, -24, 0)
	spawnMobile("rori", "hunter", 300, 753.4, 89.5, -2061.8, -90, 0)
	spawnMobile("rori", "hunter", 300, 752.9, 89.8, -2059.2, -90, 0)
	spawnMobile("rori", "poacher", 300, 764.8, 85.7, -2044.5, 65, 0)
	spawnMobile("rori", "poacher", 300, 764.2, 85.4, -2041.5, 72, 0)
	spawnMobile("rori", "poacher", 300, 805.9, 85.4, -2065.8, -45, 0)
	spawnMobile("rori", "poacher", 300, 809.5, 84.6, -2061.6, -55, 0)

	spawnMobile("rori", "potbellied_vrobal", 300, 779.7, 83.1, -2055.5, -160, 0)
	spawnMobile("rori", "potbellied_vrobal", 300, 779.9, 82.3, -2061.2, -160, 0)
	spawnMobile("rori", "potbellied_vrobal", 300, 783.9, 81.8, -2058.1, -160, 0)
	spawnMobile("rori", "potbellied_vrobal", 300, 785.5, 81.3, -2063.0, -160, 0)

	spawnMobile("rori", "vrobal_bull", 300, 745.8, 89.1, -2037.6, 140, 0)
	spawnMobile("rori", "vrobal_sow", 300, 743.5, 89.6, -2040.4, 140, 0)
	spawnMobile("rori", "vrobal_sow", 300, 738.5, 90.6, -2040.8, 140, 0)
	spawnMobile("rori", "vrobal_bull", 300, 739.1, 89.7, -2065.2, 130, 0)
	spawnMobile("rori", "vrobal_bull", 300, 738.4, 89.0, -2073.2, 130, 0)
	spawnMobile("rori", "vrobal_bull", 300, 756.6, 86.9, -2073.0, 117, 0)
	spawnMobile("rori", "vrobal_bull", 300, 757.1, 85.5, -2078.0, 117, 0)

	spawnMobile("rori", "leviasquall", 300, 796.9, 78.3, -2031.4, 173, 0)
	spawnMobile("rori", "leviasquall", 300, 792.2, 78.5, -2031.3, -168, 0)
	spawnMobile("rori", "leviasquall", 300, 741.1, 87.0, -2092.2, 68, 0)
	spawnMobile("rori", "leviasquall", 300, 744.5, 86.7, -2085.3, 68, 0)


	local pHunter = spawnMobile("rori", "hunter", 300, 768.3, 82.5, -2085.6, -44, 0)
	createObserver(OBJECTDESTRUCTION, "RoriPoacherVsCreatureBattleScreenPlay", "notifyHunterDead", pHunter)

	local pLeviasquall = spawnMobile("rori", "leviasquall", 300, 794.5, 78.5, -2033.9, -177, 0)
	createObserver(OBJECTDESTRUCTION, "RoriPoacherVsCreatureBattleScreenPlay", "notifyLeviasquallDead", pLeviasquall)

	local pProwler = spawnMobile("rori", "kai_tok_prowler", 300, 801.5, 86.4, -2080.0, -49, 0)
	createObserver(OBJECTDESTRUCTION, "RoriPoacherVsCreatureBattleScreenPlay", "notifyProwlerDead", pProwler)

	local pBull = spawnMobile("rori", "vrobal_bull", 300, 779.5, 82.2, -2066.0, -160, 0)
	createObserver(OBJECTDESTRUCTION, "RoriPoacherVsCreatureBattleScreenPlay", "notifyBullDead", pBull)

end

--hunter

function RoriPoacherVsCreatureBattleScreenPlay:notifyHunterDead(pHunter, pKiller)
	local val = getRandomNumber(100)
	if (val > 66) then
		if (readData("RoriPoacherVsCreatureBattle:savage_pugoriss") == 0) then
			local pSavage = spawnMobile("rori", "savage_pugoriss", 0, 698.8, 95.4, -2071.2, 100, 0)
			spawnMobile("rori", "pugoriss", 0, 695.1, 95.7, -2075.9, 98, 0)
			spawnMobile("rori", "ikopi", 0, 706.9, 94.1, -2083.1, 98, 0)
			spawnMobile("rori", "ikopi", 0, 713.1, 92.9, -2075.6, 98, 0)
			spawnMobile("rori", "vrobal", 0, 743.4, 88.0, -2076.4, 112, 0)
			spawnMobile("rori", "vrobal", 0, 741.1, 87.8, -2081.0, 112, 0)
			spawnMobile("rori", "vrobal", 0, 738.6, 87.8, -2086.4, 112, 0)

			createObserver(OBJECTDESTRUCTION, "RoriPoacherVsCreatureBattleScreenPlay", "notifySavageDead", pSavage)
			writeData("RoriPoacherVsCreatureBattle:savage_pugoriss",1)
		end

	elseif (val < 33) then

		if (readData("RoriPoacherVsCreatureBattle:savage_pugoriss") == 0) then
			local pSavage = spawnMobile("rori", "savage_pugoriss", 0, 777.9, 87.6, -2108.9, -15, 0)
			spawnMobile("rori", "pugoriss", 0, 773.8, 87.4, -2115.6, -15, 0)
			spawnMobile("rori", "pugoriss", 0, 750.7, 87.2, -2103.5, 38, 0)
			spawnMobile("rori", "pugoriss", 0, 734.5, 88.5, -2091.3, 71, 0)
			spawnMobile("rori", "pugoriss", 0, 736.9, 88.3, -2084.4, 111, 0)

			createObserver(OBJECTDESTRUCTION, "RoriPoacherVsCreatureBattleScreenPlay", "notifySavageDead", pSavage)
			writeData("RoriPoacherVsCreatureBattle:savage_pugoriss",1)
		end

	else

		if (readData("RoriPoacherVsCreatureBattle:savage_pugoriss") == 0) then
			local pSavage = spawnMobile("rori", "savage_pugoriss", 0, 735.4, 89.3, -2073.9, 111, 0)
			spawnMobile("rori", "hunter", 0, 793.3, 86.4, -2090.9, -65, 0)
			spawnMobile("rori", "hunter", 0, 790.4, 86.3, -2097.1, -55, 0)
			spawnMobile("rori", "hunter", 0, 783.5, 86.6, -2103.4, -45, 0)
			spawnMobile("rori", "hunter", 0, 771.3, 85.3, -2057.3, 111, 0)
			spawnMobile("rori", "hunter", 0, 772.5, 84.8, -2054.9, 61, 0)

			createObserver(OBJECTDESTRUCTION, "RoriPoacherVsCreatureBattleScreenPlay", "notifySavageDead", pSavage)
			writeData("RoriPoacherVsCreatureBattle:savage_pugoriss",1)
		end

	end

	return 0

end

function RoriPoacherVsCreatureBattleScreenPlay:notifySavageDead(pSavage, pKiller)
	deleteData("RoriPoacherVsCreatureBattle:savage_pugoriss")

	return 1
end

--leviasquall

function RoriPoacherVsCreatureBattleScreenPlay:notifyLeviasquallDead(pLeviasquall, pKiller)
	if (readData("RoriPoacherVsCreatureBattle:female_squall") == 0) then
		local pFemale = spawnMobile("rori", "female_squall", 0, 767.8, 83.2, -2025.9, 131, 0)
		spawnMobile("rori", "male_squall", 0, 765.3, 84.0, -2028.0, 131, 0)
		spawnMobile("rori", "male_squall", 0, 777.6, 81.0, -2031.7, 145, 0)
		spawnMobile("rori", "male_squall", 0, 781.1, 80.1, -2030.0, 141, 0)
		spawnMobile("rori", "deranged_squall", 0, 783.1, 79.9, -2032.9, 145, 0)
		spawnMobile("rori", "deranged_squall", 0, 778.9, 81.9, -2045.2, 170, 0)
		spawnMobile("rori", "deranged_squall", 0, 770.3, 84.4, -2046.0, -114, 0)

		createObserver(OBJECTDESTRUCTION, "RoriPoacherVsCreatureBattleScreenPlay", "notifyFemaleDead", pFemale)
		writeData("RoriPoacherVsCreatureBattle:female_squall",1)
	end

	return 0
end

function RoriPoacherVsCreatureBattleScreenPlay:notifyFemaleDead(pFemale, pKiller)
	deleteData("RoriPoacherVsCreatureBattle:female_squall")

	return 1
end

--Prowler

function RoriPoacherVsCreatureBattleScreenPlay:notifyProwlerDead(pProwler, pKiller)
	if (readData("RoriPoacherVsCreatureBattle:screaming_kai_tok") == 0) then
		local pScreaming = spawnMobile("rori", "screaming_kai_tok", 0, 811.0, 85.4, -2091.4, -71, 0)
		spawnMobile("rori", "female_kai_tok", 0, 809.4, 85.3, -2096.7, -71, 0)
		spawnMobile("rori", "female_kai_tok", 0, 767.0, 88.2, -2116.1, -11, 0)
		spawnMobile("rori", "female_kai_tok", 0, 759.4, 88.5, -2113.5, -1, 0)
		spawnMobile("rori", "female_kai_tok", 0, 749.0, 89.2, -2109.7, 11, 0)

		createObserver(OBJECTDESTRUCTION, "RoriPoacherVsCreatureBattleScreenPlay", "notifyScreamingDead", pScreaming)
		writeData("RoriPoacherVsCreatureBattle:screaming_kai_tok",1)
	end

	return 0
end

function RoriPoacherVsCreatureBattleScreenPlay:notifyScreamingDead(pScreaming, pKiller)
	deleteData("RoriPoacherVsCreatureBattle:screaming_kai_tok")

	return 1
end

--Bull

function RoriPoacherVsCreatureBattleScreenPlay:notifyBullDead(pBull, pKiller)
	if (readData("RoriPoacherVsCreatureBattle:vrobalet") == 0) then
		local pVrobalet = spawnMobile("rori", "vrobalet", 0, 793.4, 79.2, -2052.3, -151, 0)
		spawnMobile("rori", "vrobal", 0, 788.2, 79.7, -2045.7, -158, 0)
		spawnMobile("rori", "vrobal", 0, 783.3, 80.4, -2040.8, -158, 0)
		spawnMobile("rori", "vrobal", 0, 781.4, 80.4, -2035.3, -158, 0)
		spawnMobile("rori", "vrobal", 0, 781.2, 80.1, -2030.9, -158, 0)

		createObserver(OBJECTDESTRUCTION, "RoriPoacherVsCreatureBattleScreenPlay", "notifyVrobaletDead", pVrobalet)
		writeData("RoriPoacherVsCreatureBattle:vrobalet",1)
	end

	return 0
end

function RoriPoacherVsCreatureBattleScreenPlay:notifyVrobaletDead(pVrobalet, pKiller)
	deleteData("RoriPoacherVsCreatureBattle:vrobalet")

	return 1
end

