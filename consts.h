#pragma once

#ifndef CONSTS
#define CONSTS

enum class ScreenId {
    MAIN_MENU,
    CUTSCENE,
    GAME,
    SOUND,
    LOOT
};

enum class EnemyType
{
    BASIC,
    FAST,
    TANK,
    RANGED
};

const float scale = 1.5;

#endif