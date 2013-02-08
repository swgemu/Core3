Lair = {
	mobiles = {}, -- mobile, level?
	
	spawnLimit = 0,
	
	buildingsVeryEasy = {},
	buildingsEasy = {},
	buildingsMedium = {},
	buildingsHard = {},
	buildingsVeryHard = {},
	faction = "neutral",
	lairType = "creature"
}

function Lair:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end
