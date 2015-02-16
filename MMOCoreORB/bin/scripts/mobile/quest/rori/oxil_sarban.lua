oxil_sarban = Creature:new {
  objectName = "",
  customName = "Oxil Sarban",
  socialGroup = "townsperson",
  faction = "townsperson",
  level = 100,
  chanceHit = 1,
  damageMin = 645,
  damageMax = 1000,
  baseXp = 9429,
  baseHAM = 24000,
  baseHAMmax = 30000,
  armor = 0,
  resists = {0,0,0,0,0,0,0,0,-1},
  meatType = "",
  meatAmount = 0,
  hideType = "",
  hideAmount = 0,
  boneType = "",
  boneAmount = 0,
  milk = 0,
  tamingChance = 0,
  ferocity = 0,
  pvpBitmask = NONE,
  creatureBitmask = NONE,
  optionsBitmask = 136,
  diet = HERBIVORE,

  templates = {"object/mobile/dressed_oxil_sarban.iff"},
  lootGroups = {},
  weapons = {},
  conversationTemplate = "oxil_sarban_mission_giver_convotemplate",
  attacks = {
  }
}

CreatureTemplates:addCreatureTemplate(oxil_sarban, "oxil_sarban")