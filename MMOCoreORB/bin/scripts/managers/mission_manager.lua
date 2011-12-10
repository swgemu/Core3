UniverseSpawnMap = {
	planets = {}
}

PlanetSpawnMap = {
	name = "",
	cities = {}
}

CitySpawnMap = {
	citycenter = {0, 0},
	npcs = {}
}

function UniverseSpawnMap:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

function UniverseSpawnMap:addPlanet(planet)
	table.insert(self.planets, planet)
end

function PlanetSpawnMap:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

function PlanetSpawnMap:addCity(city)
	table.insert(self.cities, city)
end

function CitySpawnMap:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

-- Spawn points defined as x, y, spawn type, x and y are floats and spawn type is an int. 
-- z coordinate is taken from terrain height at the x, y coordinate.
-- Spawn types can be ored to have multiple definitions.
-- Spawn types:
--   1 = no spawn
--   2 = neutral spawn
--   4 = imperial spawn
--   8 = rebel spawn

universe = UniverseSpawnMap:new {
	planets = {	}
}

planet_tatooine = PlanetSpawnMap:new {
	name = "tatooine",
	cities = { }
} 

city_mos_eisley = CitySpawnMap:new {
	citycenter = {0, 0},
	npcs = {
		{ 3511.0, -4859.0, 2 },
		{ 3501.0, -4856.0, 2 }
	}
}

planet_tatooine:addCity(city_mos_eisley);

universe:addPlanet(planet_tatooine);