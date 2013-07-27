event_krayt_dragon_ancient = Creature:new {
	objectName = "@mob/creature_names:krayt_dragon_ancient",
	customName = "a krayt dragon ancient (event)",
	socialGroup = "Krayt",
	pvpFaction = "",
	faction = "",
	level = 336,
	chanceHit = 300,
	damageMin = 2270,
	damageMax = 4250,
	baseXp = 0,
	baseHAM = 410000,
	baseHAMmax = 501000,
	armor = 3,
	resists = {95,95,95,100,65,95,95,95,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_bristley",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 30,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/krayt_dragon.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareacombo",""},
		{"creatureareaknockdown","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(event_krayt_dragon_ancient, "event_krayt_dragon_ancient")
