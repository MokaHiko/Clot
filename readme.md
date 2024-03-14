## Clot Demo:

### General Notes 
	Setup:
	- UE v5.3

	General gameplay revolves around the UUnit Component;
	UUnit manages the taking damage and status effects via the StatusEffect flags.

	enum class StatusEffect 
	{
		Clean = 0, // No effect
		Dead = 1, // Queued for Death
		Bleeding = 1 << 1, // No Impl
		Burning = 1 << 2 // Takes 50 dmg per second
	};

	Even death itself is a status condition. This allows for abilities like being being revived or skills that can kill instantly. 
	UUnits can have multiple status effects at the same time. Individual status effects can be checked via the IsStatusEffect() and applied via the ApplyStatus() methods;

	General Recommendations: 
	- Consider a more component based approach, as not all weapons require a projectile. 
	- Abilities should have multiple termination methods aside from completion. Such as Abort, Fail, etc..
	- Abilities would ideally allow for nested processes that occur after the ability has succeeded.
	- Stacking of status effects was a feature I'd like to have implemented but I did not have the time

### Gravity Gun

	The gravity gun uses a physics handle to deal with moving objects. The crosshair will animate if an object is grabbable. 
	The conditions for being grabbable is being a movable body and blocking in the grabbable channel.

### Ability System

	Abilities are AActors managed by the AbilitySystem component. It's a form of cooperative multi tasking simmilair to Unity's coroutines. This allows abilities to have state for continuos buffs but crucially relinquish control over their lifespans and runtime updates.

	Ability creation is a two step process. First inherit from the Ability class then create a blue print class from that inherited class. 

	The two abilities in the demo is dash (Q) and a mortar strike (E)
	
	Notes:
		- Unreal has it's own Gameplay Ability System(GAS) that works with networking too, however this seemed a little overkill for this project. 

### Quest System

	Quests are AActors. Quests have a objectives that are defined via flags 

	enum class QuestType
	{
		Complete,
		Goto,
		KillX,
	};

	A quest are considered complete when each objective flag is satisfied. 

	Notes:
		- I decided not to go with an inheritence based approach as multiple quests may require simmilair functionality. Composition was considered but the current set up is generally better for serialization. 
		- Unreal has a Json library that would've been a clean choice for game saves, had I the time.

