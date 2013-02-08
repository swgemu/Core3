fambaa = Creature:new {
	objectName = "@mob/creature_names:fambaa",
	socialGroup = "fambaa",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.41,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3370,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {30,30,30,30,80,80,-1,30,-1},
	meatType = "meat_reptilian",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 750,
	boneType = "bone_mammal",
	boneAmount = 675,
	milk = 1,
	tamingChance = 0.25,
	ferocity = 7,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/fambaa.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "fambaa_common", chance = 3300000}
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

CreatureTemplates:addCreatureTemplate(fambaa, "fambaa")