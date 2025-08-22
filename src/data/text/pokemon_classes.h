#ifndef C_EX_POKEMON_CLASSES_H
#define C_EX_POKEMON_CLASSES_H

//#include "constants/pokemon_classes.h"

static const u8 sClassName_Artificer[] = _("Artificer");
static const u8 sClassName_Barbarian[] = _("Barbarian");
static const u8 sClassName_Bard[] = _("Bard");
static const u8 sClassName_Cleric[] = _("Cleric");
static const u8 sClassName_Fighter[] = _("Fighter");
static const u8 sClassName_Monk[] = _("Monk");
static const u8 sClassName_Ranger[] = _("Ranger");
static const u8 sClassName_Wizard[] = _("Wizard");
static const u8 sClassName_Warlock[] = _("Warlock");
static const u8 sClassName_Sorcerer[] = _("Sorcerer");
static const u8 sClassName_Paladin[] = _("Paladin");
static const u8 sClassName_Thief[] = _("Thief");
static const u8 sClassName_Druid[] = _("Druid");

static const u8 * const gClassNames[NUM_POKEMON_CLASSES] =
{
    [CLASS_ARTIFICER] = sClassName_Artificer,
    [CLASS_BARBARIAN] = sClassName_Barbarian,
    [CLASS_BARD] = sClassName_Bard,
    [CLASS_CLERIC] = sClassName_Cleric,
    [CLASS_FIGHTER] = sClassName_Fighter,
    [CLASS_MONK] = sClassName_Monk,
    [CLASS_RANGER] = sClassName_Ranger,
    [CLASS_WIZARD] = sClassName_Wizard,
    [CLASS_WARLOCK] = sClassName_Warlock,
    [CLASS_SORCERER] = sClassName_Sorcerer,
    [CLASS_PALADIN] = sClassName_Paladin,
    [CLASS_THIEF] = sClassName_Thief,
    [CLASS_DRUID] = sClassName_Druid,
};

#endif //C_EX_POKEMON_CLASSES_H
