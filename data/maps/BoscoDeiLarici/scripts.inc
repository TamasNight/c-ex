BoscoDeiLarici_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BoscoDeiLarici_OnFrame
    	.byte 0

BoscoDeiLarici_OnFrame:
    map_script_2 VAR_BOSCODEILARICI_STATE, 1, BoscoDeiLarici_EventScript_ResetPopup
    .2byte 0

BoscoDeiLarici_EventScript_ResetPopup::
    clearflag FLAG_HIDE_MAP_NAME_POPUP
    msgbox BoscoDeiLarici_Text_SoClose, MSGBOX_DEFAULT
    closemessage
    setvar VAR_BOSCODEILARICI_STATE, 0
    end

BoscoDeiLarici_EventScript_Dangerous::
    lockall
    msgbox BoscoDeiLarici_Text_ItsDangerous, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, Common_Movement_WalkUp
    waitmovement 0
    releaseall
    end

BoscoDeiLarici_EventScript_DangerousLower::
    lockall
    msgbox BoscoDeiLarici_Text_ItsDangerous, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, Common_Movement_WalkLeft
    waitmovement 0
    releaseall
    end

BoscoDeiLarici_EventScript_Spotted::
    lockall
    playmoncry SPECIES_HOUNDOUR, CRY_MODE_NORMAL
    msgbox BoscoDeiLarici_Text_SpottedByHoundour, MSGBOX_DEFAULT
    closemessage
    waitmoncry
    setflag FLAG_HIDE_MAP_NAME_POPUP
    setvar VAR_BOSCODEILARICI_STATE, 1
    fadescreen FADE_TO_BLACK
    delay 8
    warp MAP_ROUTE101, 23, 11
    waitstate
    releaseall
    end

BoscoDeiLarici_EventScript_FundTauros::
    lockall
    applymovement LOCALID_PLAYER, Common_Movement_WalkLeft6Fast
    turnobject LOCALID_TAUROS_WOOD, DIR_EAST
    waitmovement
    msgbox BoscoDeiLarici_Text_FinallyTauros, MSGBOX_DEFAULT
    closemessage
    clearflag FLAG_HIDE_SCENE_HOUNDOUR_FROM_WOOD
    addobject LOCALID_FIRST_HOUNDOUR
    addobject LOCALID_SECOND_HOUNDOUR
    applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
    applymovement LOCALID_PLAYER, Common_Movement_FaceRight
    waitmovement 0
    applymovement LOCALID_FIRST_HOUNDOUR, Common_Movement_WalkLeft6Fast
    applymovement LOCALID_SECOND_HOUNDOUR, Common_Movement_WalkLeft6Fast
    applymovement LOCALID_PLAYER, BoscoDeiLarici_Movement_PlayerSurprised
    waitmovement 0
    applymovement LOCALID_SECOND_HOUNDOUR, BoscoDeiLarici_Movement_HoundourPositioning
    waitmovement 0
    playmoncry SPECIES_HOUNDOUR, CRY_MODE_NORMAL
    msgbox BoscoDeiLarici_Text_SpottedByHoundour, MSGBOX_DEFAULT
    closemessage
    waitmoncry
    delay 16
    msgbox BoscoDeiLarici_Text_Screwed, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_TAUROS_WOOD, BoscoDeiLarici_Movement_TaurosPositioning
    waitmovement 0
    msgbox PascoliDelLago_Text_Tauros, MSGBOX_DEFAULT
    playmoncry SPECIES_TAUROS, CRY_MODE_NORMAL
    msgbox BoscoDeiLarici_Text_LetsFight, MSGBOX_DEFAULT
    closemessage
    waitmoncry
    setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TAUROS
    givemon SPECIES_TAUROS, 5, ITEM_ORAN_BERRY, ITEM_POKE_BALL, NATURE_ADAMANT, 0, 0, 0, 0, 0, 0, 0, 0, 31, 31 31, 31, 31, 31, MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_WORK_UP, MOVE_ROCK_SMASH, FALSE, FALSE, TYPE_NONE, 0, 1
    setwildbattle SPECIES_HOUNDOUR, 5, ITEM_NONE, SPECIES_HOUNDOUR, 5, ITEM_NONE
    dowildbattle
    playmoncry SPECIES_HOUNDOUR, CRY_MODE_FAINT
    msgbox PascoliDelLago_Text_HoundoursRunAway, MSGBOX_DEFAULT
    closemessage
    waitmoncry
    applymovement LOCALID_SECOND_HOUNDOUR, BoscoDeiLarici_Movement_HoundourRunning
    waitmovement 0
    applymovement LOCALID_SECOND_HOUNDOUR, Common_Movement_WalkRight6Fast
    applymovement LOCALID_FIRST_HOUNDOUR, Common_Movement_WalkRight6Fast
    waitmovement 0
    removeobject LOCALID_FIRST_HOUNDOUR
    removeobject LOCALID_SECOND_HOUNDOUR
    setflag FLAG_HIDE_HOUNDOUR_FROM_WOOD
    setflag FLAG_HIDE_DAD_FROM_STABLE
    clearflag FLAG_HIDE_TAUROS_FROM_STABLE
    setvar VAR_PASCOLI_DEL_LAGO_INTRO_STATE, 5
    applymovement LOCALID_TAUROS_WOOD, Common_Movement_FaceLeft
    waitmovement 0
    msgbox BoscoDeiLarici_Text_Victory, MSGBOX_DEFAULT
    closemessage
    delay 16
    applymovement LOCALID_PLAYER, Common_Movement_WalkUp
    applymovement LOCALID_TAUROS_WOOD, Common_Movement_WalkUp
    waitmovement 0
    applymovement LOCALID_TAUROS_WOOD, BoscoDeiLarici_Movement_TaurosSearching
    waitmovement 0
    applymovement LOCALID_PLAYER, Common_Movement_FaceRight
    waitmovement 0
    giveitem ITEM_BROKEN_COLLAR, 1
    delay 16
    applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
    waitmovement 0
    delay 16
    msgbox PascoliDelLago_Text_Suspicious, MSGBOX_DEFAULT
    closemessage
    delay 16
    msgbox PascoliDelLago_Text_VerySuspicious, MSGBOX_DEFAULT
    closemessage
    startquest QUEST_WOODS_SHADOWS
    delay 16
    fadescreen FADE_TO_BLACK
    warp MAP_PASCOLI_DEL_LAGO_BRENDANS_HOUSE_2F, 6, 6
    waitstate
    releaseall
    end

BoscoDeiLarici_Text_ItsDangerous:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: It's too dangerous to go\n"
    .string "into the high grass without Pokemon.$"

BoscoDeiLarici_Text_FinallyTauros:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: Here you are!\p"
    .string "Now let's go home, don't worry anymore.$"

BoscoDeiLarici_Text_LetsFight:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: All right, Tauros, let's show\n"
   	.string "them what we're capable of!$"

BoscoDeiLarici_Text_Screwed:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: Now what do I do? I'm\n"
    .string "screwed.$"

BoscoDeiLarici_Text_SpottedByHoundour:
    .string "Rrrr... Houndour!!$"

PascoliDelLago_Text_Suspicious:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: What is this...?\p"
    .string "No, it can't be, it's a collar...$"

PascoliDelLago_Text_VerySuspicious:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: It's impossible that they\n"
    .string "were trained...\p"
    .string "That would mean that someone attacked\n"
    .string "the farm intentionally...\p"
    .string "I need to get to the bottom of this, but\n"
    .string "for now it's best to go back.$"

PascoliDelLago_Text_HoundoursRunAway:
    .string "Houn... Houn...$"

BoscoDeiLarici_Text_SoClose:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: I was so close, I have to be\n"
    .string "more careful.$"

BoscoDeiLarici_Text_Victory:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: We did it, let's go home\n"
    .string "before they get too worried.$"

BoscoDeiLarici_Movement_HoundourPositioning::
    walk_fast_up
    walk_fast_left
    step_end

BoscoDeiLarici_Movement_HoundourRunning::
    walk_fast_right
    walk_fast_down
    step_end

BoscoDeiLarici_Movement_TaurosPositioning::
    walk_down
    walk_right
    walk_right
    walk_up
    face_right
    step_end

BoscoDeiLarici_Movement_TaurosSearching::
    emote_question_mark
    delay_16
    delay_16
    walk_in_place_faster_right
    delay_16
    delay_16
    delay_16
    face_left
    delay_16
    delay_16
    step_end

BoscoDeiLarici_Movement_PlayerSurprised::
    delay_16
    emote_question_mark
    face_left
    step_end


