theme_park_singing_mountain_clan_dragoon = Creature:new {
  objectName = "@mob/creature_names:singing_mtn_clan_dragoon",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
  socialGroup = "mtn_clan",
  faction = "mtn_clan",
  level = 94,
  chanceHit = 0.95,
  damageMin = 620,
  damageMax = 950,
  baseXp = 8964,
  baseHAM = 20000,
  baseHAMmax = 25000,
  armor = 2,
  resists = {45,45,75,35,75,35,35,35,-1},
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
  creatureBitmask = PACK,
  optionsBitmask = AIENABLED + CONVERSABLE,
  diet = HERBIVORE,

  templates = {"object/mobile/dressed_dathomir_sing_mt_clan_dragoon.iff"},
  lootGroups = {},
  weapons = {"melee_weapons"},
  conversationTemplate = "theme_park_smc_vurlene_aujante_mission_target_convotemplate",
  attacks = merge(brawlermaster)

}

CreatureTemplates:addCreatureTemplate(theme_park_singing_mountain_clan_dragoon, "theme_park_singing_mountain_clan_dragoon")
