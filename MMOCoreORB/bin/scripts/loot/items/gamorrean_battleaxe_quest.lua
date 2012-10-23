
gamorrean_battleaxe_quest = {
	minimumLevel = 0,
	maximumLevel = -1,
	customObjectName = "Gamorrean Battle Axe",
	directObjectTemplate = "object/weapon/melee/2h_sword/2h_sword_battleaxe.iff",
	craftingValues = {
		{"mindamage",53,98,0},
		{"maxdamage",123,228,0},
		{"attackspeed",6.5,4.5,1},
		{"woundchance",6,14,0},
		{"hitpoints",750,1500,0},
		{"zerorangemod",-26,-14,0},
		{"maxrangemod",-26,-14,0},
		{"midrange",3,3,0},
		{"midrangemod",-26,-14,0},
		{"maxrange",7,7,0},
		{"attackhealthcost",33,33,0},
		{"attackactioncost",11,11,0},
		{"attackmindcost",6,6,0},
	},
	customizationStringNames = {},
	customizationValues = {},
	skillMods = {{"block", 5}}
}
-- needs DOT added, disease mind str 50, dur 400s, pot 60% 9999 uses
addLootItemTemplate("gamorrean_battleaxe_quest", gamorrean_battleaxe_quest)