Coa3ContainerComponent = {}

function Coa3ContainerComponent:transferObject(pContainer, pObj, slot)
	if (pObj == nil) then
		return TRANSFERFAIL
	end

	local pPlayer = Coa3Screenplay:getObjOwner(pObj)

	if (pPlayer == nil) then
		return TRANSFERFAIL
	end

	local faction = CreatureObject(pContainer):getFaction()
	local stateKey = Coa3Screenplay:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)

	SceneObject(pObj):destroyObjectFromWorld()
	SceneObject(pObj):destroyObjectFromDatabase()

	local factionString = "imperial"

	if (faction == FACTIONREBEL) then
		factionString = "rebel"
	end

	ThemeParkLogic:giveFaction(pPlayer, factionString, 50)

	if (state < Coa3Screenplay.M3_COMPLETE) then
		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.M3_COMPLETE)
	end

	return 1
end

function Coa3ContainerComponent:canAddObject(pContainer, pObj, slot)
	if (pObj == nil) then
		return TRANSFERCANTADD
	end

	local pPlayer =  Coa3Screenplay:getObjOwner(pObj)

	if (pPlayer == nil) then
		return TRANSFERCANTADD
	end

	local containerName = SceneObject(pContainer):getObjectName()
	local faction = CreatureObject(pContainer):getFaction()
	local stateKey = Coa3Screenplay:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)
	local objectTemplate = SceneObject(pObj):getTemplateObjectPath()

	if (string.find(containerName, "coa3_tactical_") and state >= Coa3Screenplay.M3_WAREHOUSE_DESTROYED and string.find(objectTemplate, "alderaan/act3/alderaan_flora.iff")) then
		return TRANSFERCANADD
	end

	return TRANSFERCANTADD
end

function Coa3ContainerComponent:removeObject(pContainer, pObj, slot)
	return TRANSFERFAIL
end