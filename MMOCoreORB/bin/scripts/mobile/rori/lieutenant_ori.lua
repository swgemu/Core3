lieutenant_ori = Creature:new {
	objectName = "@mob/creature_names:lieutenant_ori",
	socialGroup = "rorgungan",
	faction = "rorgungan",
	level = 33,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3370,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {45,45,-1,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
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
	diet = HERBIVORE,

	templates = {"object/mobile/lieutenant_ori.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5000000},
				{group = "tailor_components", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "wearables_common", chance = 1000000}
			}
		}
	},
	weapons = {"lt_ori_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster,fencermaster,riflemanmaster)
}

CreatureTemplates:addCreatureTemplate(lieutenant_ori, "lieutenant_ori")
