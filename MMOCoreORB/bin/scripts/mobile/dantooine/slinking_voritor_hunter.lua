slinking_voritor_hunter = Creature:new {
	objectName = "@mob/creature_names:slinking_voritor_hunter",
	socialGroup = "voritor",
	pvpFaction = "",
	faction = "",
	level = 57,
	chanceHit = 0.55,
	damageMin = 420,
	damageMax = 550,
	baseXp = 5555,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {45,45,10,10,10,-1,10,10,-1},
	meatType = "meat_carnivore",
	meatAmount = 90,
	hideType = "hide_leathery",
	hideAmount = 65,
	boneType = "bone_avian",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/slinking_voritor_hunter.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "voritor_lizard_common", chance = 3300000}
			},
			lootChance = 7000000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(slinking_voritor_hunter, "slinking_voritor_hunter")