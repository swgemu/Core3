warren_agro_droid = Creature:new {
	objectName = "@mob/creature_names:warren_agro_droid_s01",
	socialGroup = "warren_imperial",
	pvpFaction = "",
	faction = "",
	level = 46,
	chanceHit = 0.36,
	damageMin = 400,
	damageMax = 600,
	baseXp = 4000,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {30,30,40,40,-1,40,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {	"object/mobile/warren_agro_droid_s01.iff", --droideka
					"object/mobile/warren_agro_droid_s02.iff", --probot
					"object/mobile/warren_agro_droid_s03.iff", --ig assassin
					"object/mobile/warren_agro_droid_s04.iff"  --dz70 fugitive tracker droid
				},
	lootGroups = {},
	conversationTemplate = "",
	defaultAttack = "creaturerangedattack",
	defaultWeapon = "object/weapon/ranged/droid/droid_droideka_ranged.iff"
}

CreatureTemplates:addCreatureTemplate(warren_agro_droid, "warren_agro_droid")
