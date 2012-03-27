enraged_kimogila = Creature:new {
	objectName = "@mob/creature_names:enraged_kimogila",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 135,
	chanceHit = 4.75,
	damageMin = 920,
	damageMax = 1550,
	baseXp = 12801,
	baseHAM = 50000,
	baseHAMmax = 61000,
	armor = 2,
	resists = {45,70,45,70,45,40,100,45,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kimogila.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "kimogila_common", chance = 3300000}
			},
			lootChance = 6500000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enraged_kimogila, "enraged_kimogila")