enraged_wood_mite_king = Creature:new {
	objectName = "@mob/creature_names:enraged_wood_mite_king",
	socialGroup = "mite",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 200,
	damageMax = 210,
	baseXp = 1803,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {115,125,-1,5,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/enraged_wood_mite_king.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 1.2,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(enraged_wood_mite_king, "enraged_wood_mite_king")
