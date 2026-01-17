idleHerd = {
	{id="3567301393",	name="Selector",	pid="none"},
	{id="3294417074",	name="Sequence",	pid="3567301393"},
	{id="2426014909",	name="Selector",	pid="3294417074"},
	{id="195163317",	name="If",	pid="2426014909"},
	{id="348206776",	name="CheckIsHerdLeader",	pid="195163317"},
	{id="1044560513",	name="Not",	pid="2426014909"},
	{id="2075598757",	name="If",	pid="1044560513"},
	{id="4122940892",	name="CheckHasHerdObserver",	pid="2075598757"},
	{id="2954366442",	name="WriteBlackboard",	pid="3294417074",	args={key="moveMode", val=WALK}},
	{id="2704711532",	name="AlwaysSucceed",	pid="3294417074"},
	{id="2826757068",	name="Sequence",	pid="2704711532"},
	{id="3626218478",	name="Not",	pid="2826757068"},
	{id="3006309375",	name="If",	pid="3626218478"},
	{id="1568150506",	name="CheckHasPatrol",	pid="3006309375"},
	{id="383327892",	name="GeneratePatrol",	pid="2826757068",	args={distFromHome=40.0, numPoints=5}},
	{id="505873291",	name="Sequence",	pid="3567301393"},
	{id="1558329068",	name="Not",	pid="505873291"},
	{id="2146384398",	name="If",	pid="1558329068"},
	{id="2963031111",	name="CheckFollowIsHerdLeader",	pid="2146384398"},
	{id="2256881794",	name="FollowHerd",	pid="505873291"},
	{id="244234023",	name="WriteBlackboard",	pid="505873291",	args={key="moveMode", val=WALK}}}
addAiTemplate("idleHerd", idleHerd)

