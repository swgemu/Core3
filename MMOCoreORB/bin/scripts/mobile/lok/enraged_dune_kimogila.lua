enraged_dune_kimogila = Creature:new {
	objectName = "@mob/creature_names:enraged_dune_kimogila",
	socialGroup = "kimogila",
	pvpFaction = "",
	faction = "",
	level = 148,
	chanceHit = 6.25,
	damageMin = 940,
	damageMax = 1590,
	baseXp = 14030,
	baseHAM = 62000,
	baseHAMmax = 75000,
	armor = 2,
	resists = {80,90,80,100,80,80,100,80,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kimogila_hue.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "kimogila_common", chance = 10000000}
			},
			lootChance = 6500000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"creatureareaattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(enraged_dune_kimogila, "enraged_dune_kimogila")