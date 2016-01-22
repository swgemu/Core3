function printf(...) io.write(string.format(table.unpack({...}))) end

local creature = LuaCreatureObject(nil)

function runScript(creatureObject)
	creature:_setObject(creatureObject)
  	
  	--creature:setHAM(0, getRandomNumber(99))
  	credits = creature:getBankCredits()  
end
