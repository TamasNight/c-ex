Lungavalle_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Lungavalle_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Lungavalle_OnLoad
	.byte 0

Lungavalle_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	setflag FLAG_VISITED_LUNGAVALLE
	call_if_unset FLAG_ADVENTURE_STARTED, Lungavalle_EventScript_BlockWestEntrance
	call_if_unset FLAG_RECEIVED_POTION_OLDALE, Lungavalle_EventScript_MoveMartEmployee
	call_if_set FLAG_ADVENTURE_STARTED, Lungavalle_EventScript_SetOldaleState
	end

Lungavalle_OnLoad:
	call_if_unset FLAG_FOUND_VALLELUNGA_HUNTER, Vallelunga_ClosenHuntersHouse
	call_if_set FLAG_FOUND_VALLELUNGA_HUNTER, Vallelunga_OpenHuntersHouse
	end

Vallelunga_CloseHuntersHouse::
	setmetatile 21, 15, METATILE_Farm_HalfTimberedHouseDoor, TRUE
	return

Vallelunga_OpenHuntersHouse::
	setmetatile 21, 15, METATILE_Farm_HalfTimberedHouseDoor, FALSE
	return

@ This script seems pointless because nothing uses VAR_LUNGAVALLE_STATE
Lungavalle_EventScript_SetOldaleState::
	setvar VAR_LUNGAVALLE_STATE, 1
	return

Lungavalle_EventScript_BlockWestEntrance::
	setobjectxyperm LOCALID_FOOTPRINTS_MAN, 1, 11
	setobjectmovementtype LOCALID_FOOTPRINTS_MAN, MOVEMENT_TYPE_FACE_LEFT
	return

Lungavalle_EventScript_MoveMartEmployee::
	setobjectxyperm LOCALID_OLDALE_MART_EMPLOYEE, 13, 14
	setobjectmovementtype LOCALID_OLDALE_MART_EMPLOYEE, MOVEMENT_TYPE_FACE_DOWN
	return

Lungavalle_EventScript_TownSign::
	msgbox Lungavalle_Text_TownSign, MSGBOX_SIGN
	end

Lungavalle_EventScript_FarmerWorried::
	@ TODO missione alla ricerca del cacciatore
	msgbox Lungavalle_Text_WorriedForTheHunter, MSGBOX_NPC
	end

Lungavalle_EventScript_MartEmployee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POTION_OLDALE, Lungavalle_EventScript_ExplainPotion
	goto_if_set FLAG_TEMP_1, Lungavalle_EventScript_ExplainPotion
	setflag FLAG_TEMP_1
	playbgm MUS_FOLLOW_ME, FALSE
	msgbox Lungavalle_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, Lungavalle_EventScript_GoToMartSouth
	case DIR_NORTH, Lungavalle_EventScript_GoToMartNorth
	case DIR_EAST, Lungavalle_EventScript_GoToMartEast
	end

Lungavalle_EventScript_GoToMartSouth::
	applymovement LOCALID_OLDALE_MART_EMPLOYEE, Lungavalle_Movement_EmployeeSouth
	applymovement LOCALID_PLAYER, Lungavalle_Movement_PlayerSouth
	waitmovement 0
	goto Lungavalle_EventScript_ExplainPokemonMart
	end

Lungavalle_EventScript_GoToMartNorth::
	applymovement LOCALID_OLDALE_MART_EMPLOYEE, Lungavalle_Movement_EmployeeNorth
	applymovement LOCALID_PLAYER, Lungavalle_Movement_PlayerNorth
	waitmovement 0
	goto Lungavalle_EventScript_ExplainPokemonMart
	end

Lungavalle_EventScript_GoToMartEast::
	applymovement LOCALID_PLAYER, Lungavalle_Movement_PlayerEast
	applymovement LOCALID_OLDALE_MART_EMPLOYEE, Lungavalle_Movement_EmployeeEast
	waitmovement 0
	goto Lungavalle_EventScript_ExplainPokemonMart
	end

Lungavalle_EventScript_ExplainPokemonMart::
	msgbox Lungavalle_Text_ThisIsAPokemonMart, MSGBOX_DEFAULT
	giveitem ITEM_HEALING_HERBS
	goto_if_eq VAR_RESULT, FALSE, Lungavalle_EventScript_BagIsFull
	msgbox Lungavalle_Text_PotionExplanation, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_POTION_OLDALE
	fadedefaultbgm
	release
	end

Lungavalle_EventScript_ExplainPotion::
	msgbox Lungavalle_Text_PotionExplanation, MSGBOX_DEFAULT
	release
	end

Lungavalle_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	fadedefaultbgm
	release
	end

Lungavalle_Movement_EmployeeEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

Lungavalle_Movement_EmployeeSouth:
	walk_left
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

Lungavalle_Movement_EmployeeNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

Lungavalle_Movement_Unknown1:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	walk_in_place_faster_down
	step_end

Lungavalle_Movement_PlayerEast:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Lungavalle_Movement_PlayerSouth:
	delay_16
	delay_16
	delay_16
	delay_16
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Lungavalle_Movement_PlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Lungavalle_Movement_Unknown2:
	walk_left
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Lungavalle_EventScript_FootprintsMan::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Lungavalle_EventScript_NotBlockingPath
	msgbox Lungavalle_Text_DiscoveredFootprints, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Lungavalle_EventScript_ToTheInn::
	lockall
	msgbox Lungavalle_Text_ToTheInn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkRight
	waitmovement 0
	releaseall
	end

Lungavalle_EventScript_NotBlockingPath::
	msgbox Lungavalle_Text_FinishedSketchingFootprints, MSGBOX_DEFAULT
	release
	end

Lungavalle_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	step_end

Lungavalle_Movement_RivalApproachPlayer2:
	walk_left
	step_end

Lungavalle_Movement_RivalApproachPlayer3:
	face_left
	step_end

Lungavalle_Movement_RivalExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Lungavalle_Movement_WatchRivalExit:
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

Lungavalle_Movement_PlayerStepBack:
	delay_8
	walk_right
	step_end

Lungavalle_Movement_BackUp:
	walk_fast_up
	walk_in_place_faster_left
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

Lungavalle_Movement_ReturnToOriginalPosition:
	walk_down
	walk_left
	step_end

Lungavalle_Text_WorriedForTheHunter:
	.string "I want to take a rest, so I'm saving my\n"
	.string "progress.$"

Lungavalle_Text_IWorkAtPokemonMart:
	.string "Hi!\n"
	.string "I work at a POKéMON MART.\p"
	.string "Can I get you to come with me?$"

Lungavalle_Text_ThisIsAPokemonMart:
	.string "This is a POKéMON MART.\n"
	.string "Just look for our blue roof.\p"
	.string "We sell a variety of goods including\n"
	.string "POKé BALLS for catching POKéMON.\p"
	.string "Here, I'd like you to have this as\n"
	.string "a promotional item.$"

Lungavalle_Text_PotionExplanation:
	.string "A POTION can be used anytime, so it's\n"
	.string "even more useful than a POKéMON CENTER\l"
	.string "in certain situations.$"


Lungavalle_Text_DiscoveredFootprints:
	.string "I just discovered the footprints of\n"
	.string "a rare POKéMON!\p"
	.string "Wait until I finish sketching\n"
	.string "them, okay?$"

Lungavalle_Text_FinishedSketchingFootprints:
	.string "I finished sketching the footprints of\n"
	.string "a rare POKéMON.\p"
	.string "But it turns out they were only my\n"
	.string "own footprints…$"


Lungavalle_Text_ToTheInn:
	.string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: The Inn is not on this way.$"

Lungavalle_Text_TownSign:
	.string "Lungavalle\n"
	.string "“Gateway to the real Alps.”$"

