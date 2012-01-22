ThemeparkJabba = ScreenPlay:new {
	numberOfActs = 1
}

registerScreenPlay("ThemeparkJabba", true);

function ThemeparkJabba:start(creatureObject)	
	printf("Initiating Jabba's Themepark\n")
	
	local regionPointer = getRegion("tatooine","jabbas_palace") 
	if regionPointer == nil then
		printf("[Jabba's Themepark] Region zero. Zone not loaded?\n")
		return 0
	else
		createObserver(ENTEREDAREA, "ThemeparkJabba", "setCellPermissions", regionPointer)
	end
end

function ThemeparkJabba:setCellPermissions(regionObject, creatureObject)
	--printf("entered area\n")
	local cellObject = LuaSceneObject(getSceneObject(1177466))
	local creature = LuaCreatureObject(creatureObject)
	state = creature:hasScreenPlayState(2, "themepark_jabba")
	if state == 0 then 
		cellObject:updateCellPermission(0, creatureObject)
	end
 
	return 0
end