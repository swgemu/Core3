kliknik_hatchling = Creature:new {
	objectName = "@mob/creature_names:kliknik_hatchling",
	socialGroup = "kliknik",
	faction = "",
	level = 22,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 1,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik_hatchling.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 0.65,
	lootGroups = {
	 {
	        groups = {
				{group = "kliknik_common", chance = 10000000}
			},
			lootChance = 1440000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_hatchling, "kliknik_hatchling")
