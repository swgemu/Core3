SpaceStationScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceStationScreenPlay",

	travelPoints = {
		coronet = {"corellia", -66, 28, -4705},
		kor_vella = {"corellia", -3155, 31, 2880},
		doaba_guerfel = {"corellia", 3349, 308, 5598},
		tyrena = {"corellia", -5001, 21, -2228},
		dantooine_mining = {"dantooine", -640, 3, 2505},
		agro = {"dantooine", 1575, 4, -6420},
		dantooine_imperial = {"dantooine", -4205, 3, -2350},
		abandoned_rebel = {"dantooine", -6792, 46, 5575},
		trade = {"dathomir", 620, 7, 3090},
		science = {"dathomir", -50, 18, -1580},
		research = {"endor", 3200, 24, -3470},
		smuggler = {"endor", -950, 73, 1550},
		nym = {"lok", 480, 9, 5510},
		theed = {"naboo", -4860, 6, 4165},
		kaadara = {"naboo", 5280, -192, 6688},
		keren = {"naboo", 1370, 13, 2750},
		moenia = {"naboo", 4730, 4.2, -4678},
		narmle = {"rori", -5372, 80, -2191},
		restuss = {"rori", 5341, 80, 5735},
		dearic = {"talus", 265, 6, -2950},
		nashal = {"talus", 4452, 2, 5355},
		talus_imperial = {"talus", -2215, 20, 2305},
		bestine = {"tatooine", -1360, 12, -3600},
		eisley = {"tatooine", 3600, 5, -4785},
		espa = {"tatooine", -2835, 5, 2105},
		entha = {"tatooine", 1265, 7, 3065},
		yavin4_mining = {"yavin4", -267, 35, 4896},
		labor = {"yavin4", -6921, 73, -5726},
		yavin4_imperial = {"yavin4", 4054, 37, -6216},
	},
}

function SpaceStationScreenPlay:landShip(pPlayer, destination)
	if (pPlayer == nil or destination == nil) then
		return
	end

	local pShip = SceneObject(pPlayer):getParent()
	if (pShip == nil or not SceneObject(pShip):isShipObject()) then
		return
	end

	local destinationTable = self.travelPoints
	local destinationInfo = destinationTable[destination]
	SceneObject(pPlayer):switchZone(destinationInfo[1], destinationInfo[2], destinationInfo[3], destinationInfo[4], 0)
	LuaShipObject(pShip):storeShip(pPlayer)
end
