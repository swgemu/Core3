UniverseSpawnMap = {
	planets = {}
}

PlanetSpawnMap = {
	name = "",
	cities = {},
	npcs = {}
}

CitySpawnMap = {
	citycenter = {0, 0}
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
--NOSPAWN = 1;
--NEUTRALSPAWN = 2;
--IMPERIALSPAWN = 4;
--REBELSPAWN = 8;

universe = UniverseSpawnMap:new {
	planets = {	}
}

planet_tatooine = PlanetSpawnMap:new {
	name = "tatooine",
	cities = { },
	npcs = {
		{ 3511.0, -4859.0, 0.0, 2},
		{ 3501.0, -4856.0, 0.0, 2}
	}
}

planet_corellia = PlanetSpawnMap:new {
	name = "corellia",
	cities = { },
	npcs = {
		{ -498.0, -4667.0, 0.0, 2},
		{ -498.0, -4657.0, 0.0, 2},
		{ -498.0, -4677.0, 0.0, 2},
		{ -356.0, -4635.0, 0.0, 2},
		{ -295.0, -4558.0, 0.0, 2},
		{ -306.0, -4436.0, 0.0, 2},
		{ -189.0, -4409.0, 0.0, 2},
		{  -93.0, -4413.0, 0.0, 2},
		{    4.0, -4425.0, 0.0, 2},
		{    4.0, -4435.0, 2.0, 2},
		{    4.0, -4445.0, 1.0, 2},
		{ -3774.0, 3214.0, 0.0, 2},
		{ -3779.0, 3189.0, 0.0, 2},
		{ -3669.0, 3138.0, 0.0, 2},
		{ -3608.0, 3144.0, 0.0, 2},
		{ -3500.0, 3158.0, 0.0, 2},
		{ -3369.0, 3144.0, 0.0, 2},
		{ -3285.0, 3085.0, 0.0, 2}
	}
}

city_mos_eisley = CitySpawnMap:new {
	citycenter = {0, 0}
}

city_coronet = CitySpawnMap:new {
	citycenter = {0, -4500}
}

city_kor_vella = CitySpawnMap:new {
	citycenter = {-3500, 3150}
}

planet_tatooine:addCity(city_mos_eisley);
planet_corellia:addCity(city_coronet);
planet_corellia:addCity(city_kor_vella);

universe:addPlanet(planet_tatooine);
universe:addPlanet(planet_corellia);
