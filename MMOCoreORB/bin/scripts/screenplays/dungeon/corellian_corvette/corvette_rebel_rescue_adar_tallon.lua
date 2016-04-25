
tallonIntel = {
      containerIds = { 4465363, 4105801, 4355510 }, -- yavin4 -6332 -476 ,tatooine -3978 6259, corellia 1353 -329
      itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/rebel_rescue_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_rescue_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_rescue_intel.iff" },
    }

tallonTicketInfo = { depPlanet = "corellia", faction = "rebel", missionType = "rescue" }

tallonCompensation = { { compType = "credits", amount = 500 } }

tallon = { planetName = "corellia", npcTemplate = "adar", x = -5448.03, z = 21, y = -2674.92, direction = 163, cellID = 0, position = STAND }

ticketGiverTallon = CorvetteTicketGiverLogic:new {
  numberOfActs = 1,
  npc = tallon,
  intelMap = tallonIntel,
  ticketInfo = tallonTicketInfo,
  giverName = "ticketGiverTallon",
  faction = 0,
  compensation = tallonCompensation,
  badgeNumber = 119,
  menuComponent = "TallonIntelSearchMenuComponent",
}

registerScreenPlay("ticketGiverTallon", true)

ticketGiverTallonConvoHandler = CorvetteTicketGiverConvoHandler:new {
  ticketGiver = ticketGiverTallon
}

TallonIntelSearchMenuComponent = IntelSearchMenuComponent:new {
  ticketGiver = ticketGiverTallon
}
