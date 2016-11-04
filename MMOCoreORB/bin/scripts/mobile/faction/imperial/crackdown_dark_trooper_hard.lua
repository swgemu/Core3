crackdown_dark_trooper_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_dark_trooper_hard",
	randomNameType = NAME_DARKTROOPER,
	randomNameTag = false,
	socialGroup = "imperial",
	faction = "imperial",
	level = 100,
	chanceHit = 1.0,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 10000,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 1,
	resists = {140,20,20,150,150,150,150,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + OVERT,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,
	scale = 1.5,

	templates = {"object/mobile/dark_trooper.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 6650000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000},
				{group = "wearables_common", chance = 1000000}
			}
		}
	},
	weapons = {"dark_trooper_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,fencermaster,brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_dark_trooper_hard, "crackdown_dark_trooper_hard")
