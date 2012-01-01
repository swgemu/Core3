singing_mountain_clan_initiate = Creature:new {
	objectName = "@mob/creature_names:Singing_Mountain_clan_initiate",
	socialGroup = "Mtn. Clan",
	pvpFaction = "Mtn. Clan",
	faction = "",
	level = 50,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4916,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 1,
	resists = {30,30,75,-1,75,-1,-1,35,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dathomir_sing_mt_clan_initiate.iff"},
	lootgroups = {},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(singing_mountain_clan_initiate, "singing_mountain_clan_initiate")