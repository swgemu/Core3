crackdown_rebel_elite_sand_rat_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_rebel_elite_sand_rat_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 141,
	chanceHit = 5.6,
	damageMin = 840,
	damageMax = 1450,
	baseXp = 7045,
	baseHAM = 63200,
	baseHAMmax = 88800,
	armor = 1,
	resists = {0,0,140,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_rebel_trooper_sullustan_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 4700000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000},
				{group = "wearables_common", chance = 1000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(commandomid,pistoleermid,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_rebel_elite_sand_rat_hard, "crackdown_rebel_elite_sand_rat_hard")