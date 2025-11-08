PascoliDelLago_Stable_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PascoliDelLago_Stable_OnFrame
	.byte 0

PascoliDelLago_Stable_OnFrame::
    map_script_2 VAR_PASCOLI_DEL_LAGO_INTRO_STATE, 1, PascoliDelLago_Stable_EventScript_Finally
    map_script_2 VAR_PASCOLI_DEL_LAGO_INTRO_STATE, 5, PascoliDelLago_Stable_EventScript_End
    .2byte 0

PascoliDelLago_Stable_EventScript_Finally::
    lockall
    delay 16
    applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
    waitmovement 0
    delay 8
    applymovement LOCALID_FATHER, Common_Movement_FaceDown
    waitmovement 0
    msgbox PascoliDelLago_Stable_Text_Finally, MSGBOX_DEFAULT
    applymovement LOCALID_PLAYER, Common_Movement_WalkUp2
    msgbox PascoliDelLago_Stable_Text_Sorry, MSGBOX_DEFAULT
    waitmovement 0
    msgbox PascoliDelLago_Stable_Text_AtYourAge, MSGBOX_DEFAULT
    closemessage
    setvar VAR_PASCOLI_DEL_LAGO_INTRO_STATE 2
    subquestmenu QUEST_MENU_COMPLETE_QUEST QUEST_START_JOURNEY SUB_QUEST_START_JOURNEY_2
    updatequestmsg QUEST_START_JOURNEY
    releaseall
    end

PascoliDelLago_Stable_EventScript_End::
    lockall
    turnobject LOCALID_TAUROS_STABLE, DIR_SOUTH
    applymovement LOCALID_PLAYER, Common_Movement_FaceUp
    waitmovement 0
    msgbox PascoliDelLago_Stable_Text_JustRest, MSGBOX_DEFAULT
    closemessage
    completequest QUEST_START_JOURNEY
    setvar VAR_PASCOLI_DEL_LAGO_INTRO_STATE 6
    removemon 0
    clearflag FLAG_HIDE_KNIGHT_FROM_FIELD
    clearflag FLAG_HIDE_PARENTS_INTRO_IN_HOUSE
    releaseall
    end


PascoliDelLago_Stable_EventScript_TakingBreath::
    msgbox PascoliDelLago_Stable_Text_TakingBreath, MSGBOX_NPC
    end

PascoliDelLago_Stable_Text_Finally:
    .string "{COLOR}{GREEN}Father{COLOR}{02}: Finally, you show up.\n"
    .string "Beasts don't feed themselves, you know.$"

PascoliDelLago_Stable_Text_Sorry:
	.string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: Yeah, sorry... I didn't sleep\n"
	.string "well.$"

PascoliDelLago_Stable_Text_JustRest:
	.string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: Now you're out of danger.\n"
    .string "Rest up, you deserve it.$"


PascoliDelLago_Stable_Text_AtYourAge:
    .string "{COLOR}{GREEN}Father{COLOR}{02}: Did you sleep poorly or too\n"
    .string "much?\p"
    .string "You know, at your age, I was already\n"
    .string "taking care of everything on the farm.\p"
    .string "(sighs)\p"
    .string "Oh well. We have a long day ahead of us\n"
    .string "today. I'll finish up here. Go help your\l"
    .string "mother with the hay.$"

PascoliDelLago_Stable_Text_TakingBreath:
	.string "{COLOR}{GREEN}Father{COLOR}{02}: Don't worry, I said I'd do it, I'm\n"
	.string "just catching my breath a little.$"

PascoliDelLago_Stable_Movement_BrendanEnters:
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

PascoliDelLago_Stable_Movement_BrendanApproachPlayerNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

PascoliDelLago_Stable_Movement_BrendanWalkToPCNorth:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

PascoliDelLago_Stable_Movement_PlayerWatchBrendanNorth:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

PascoliDelLago_Stable_Movement_BrendanApproachPlayerSouth:
	walk_left
	walk_left
	walk_left
	step_end

PascoliDelLago_Stable_Movement_BrendanWalkToPCSouth:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

PascoliDelLago_Stable_Movement_PlayerWatchBrendanSouth:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

PascoliDelLago_Stable_Movement_BrendanApproachPlayerWest:
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

PascoliDelLago_Stable_Movement_BrendanWalkToPCWest:
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

PascoliDelLago_Stable_Movement_PlayerWatchBrendanWest:
	delay_8
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

PascoliDelLago_Stable_Movement_BrendanApproachPlayerEast:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

PascoliDelLago_Stable_Movement_BrendanWalkToPCEast:
	walk_up
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

@ Unused, the player is already facing this direction so its unneeded
PascoliDelLago_Stable_Movement_PlayerWatchBrendanEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

PascoliDelLago_Stable_EventScript_PC::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, PascoliDelLago_Stable_EventScript_CheckPlayersPC
	goto_if_eq VAR_RESULT, FEMALE, PascoliDelLago_Stable_EventScript_CheckRivalsPC
	end

PascoliDelLago_Stable_EventScript_CheckPlayersPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special BedroomPC
	waitstate
	releaseall
	end

PascoliDelLago_Stable_EventScript_TurnOffPlayerPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

PascoliDelLago_Stable_EventScript_CheckRivalsPC::
	msgbox gText_PokemonTrainerSchoolEmail, MSGBOX_DEFAULT
	releaseall
	end

PlayersHouse_2F_EventScript_Notebook::
	msgbox PlayersHouse_2F_Text_Notebook, MSGBOX_SIGN
	end

PlayersHouse_2F_EventScript_GameCube::
	msgbox PlayersHouse_2F_Text_ItsAGameCube, MSGBOX_SIGN
	end

PlayersHouse_2F_Text_ClockIsStopped:
	.string "The clock is stopped…\p"
	.string "Better set it and start it!$"

PlayersHouse_2F_Text_HowDoYouLikeYourRoom:
	.string "MOM: {PLAYER}, how do you like your\n"
	.string "new room?\p"
	.string "Good! Everything's put away neatly!\p"
	.string "They finished moving everything in\n"
	.string "downstairs, too.\p"
	.string "POKéMON movers are so convenient!\p"
	.string "Oh, you should make sure that\n"
	.string "everything's all there on your desk.$"

PlayersHouse_2F_Text_Notebook:
	.string "{PLAYER} flipped open the notebook.\p"
	.string "ADVENTURE RULE NO. 1\n"
	.string "Open the MENU with START.\p"
	.string "ADVENTURE RULE NO. 2\n"
	.string "Record your progress with SAVE.\p"
	.string "The remaining pages are blank…$"

Common_Text_LookCloserAtMap:
	.string "{PLAYER} took a closer look at the\n"
	.string "HOENN region map.$"

PlayersHouse_2F_Text_ItsAGameCube:
	.string "It's a Nintendo GameCube.\p"
	.string "A Game Boy Advance is connected to\n"
	.string "serve as the Controller.$"
