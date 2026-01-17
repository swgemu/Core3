idleCitypatrol = {
	{id="2542740457",	name="Sequence",	pid="none"},
	{id="2903196510",	name="If",	pid="2542740457"},
	{id="2470654644",	name="CheckHasPatrol",	pid="2903196510"},
	{id="157619381",	name="If",	pid="2542740457"},
	{id="1407757091",	name="CheckDestination",	pid="157619381",	args={condition=0.0}},
	{id="853611168",	name="WriteBlackboard",	pid="2542740457",	args={key="moveMode", val=WALK}},
	{id="1110374020",	name="TreeSocket",	pid="2542740457",	args={slot=MOVE}}}
addAiTemplate("idleCitypatrol", idleCitypatrol)

rootCitypatrol = {
	{id="4144146773",	name="Selector",	pid="none"},
	{id="4217744519",	name="TreeSocket",	pid="4144146773",	args={slot=IDLE}}}
addAiTemplate("rootCitypatrol", rootCitypatrol)

