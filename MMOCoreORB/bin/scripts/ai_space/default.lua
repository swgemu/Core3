idleDefault = {
	{id="2434234854",	name="Selector",	pid="none"},
	{id="2195546559",	name="GeneratePatrol",	pid="2434234854",	args={distFromHome=0.0, numPoints=0}}}
addAiTemplate("idleDefault", idleDefault)

moveDefault = {
	{id="533619163",	name="Selector",	pid="none"}}
addAiTemplate("moveDefault", moveDefault)

rootDefault = {
	{id="714360210",	name="Selector",	pid="none"},
	{id="1646776990",	name="TreeSocket",	pid="714360210",	args={slot=MOVE}},
	{id="2514877899",	name="TreeSocket",	pid="714360210",	args={slot=IDLE}}}
addAiTemplate("rootDefault", rootDefault)

