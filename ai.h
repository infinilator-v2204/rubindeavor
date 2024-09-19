#pragma once

#include "battlesystem.h"

bool Fighter_AI_TurnStart(Fighter* fighter);
void Fighter_AI_TurnEnd(Fighter* fighter);
void Fighter_AI_ChooseAction(Fighter* fighter);
int Fighter_AI_Attack(Fighter* fighter, Fighter* target);
int Fighter_AI_Block(Fighter* fighter, Fighter* attacker);
