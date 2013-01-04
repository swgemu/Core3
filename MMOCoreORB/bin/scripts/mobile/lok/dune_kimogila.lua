dune_kimogila = Creature:new {
	objectName = "@mob/creature_names:dune_kimogila",
	socialGroup = "kimogila",
	pvpFaction = "",
	faction = "",
	level = 123,
	chanceHit = 40,
	damageMin = 785,
	damageMax = 1280,
	baseXp = 11671,
	baseHAM = 53000,
	baseHAMmax = 65000,
	armor = 2,
	resists = {40,65,15,100,-1,15,100,-1,-1},
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
		{"creatureareacombo",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dune_kimogila, "dune_kimogila")