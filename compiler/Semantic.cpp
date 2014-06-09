#include "Semantic.h"
#include "Constants.h"
#include "SemanticActions.h"

#include <iostream>

Semantic::Semantic(std::fstream& output) :
    code(output)
{
    actions[0] = action_01;
    actions[1] = action_02;
    actions[2] = action_03;
    actions[3] = action_04;
    actions[4] = action_05;
    actions[5] = action_06;
    actions[6] = action_07;
    actions[10] = action_11;
    actions[11] = action_12;
    actions[12] = action_13;
    actions[13] = action_14;
    actions[14] = action_15;
    actions[15] = action_16;
    actions[16] = action_17;
    actions[17] = action_18;
    actions[18] = action_19;
    actions[19] = action_20;
    actions[20] = action_21;
    actions[21] = action_22;
    actions[22] = action_23;
}

Semantic::~Semantic()
{
}

void Semantic::executeAction(int action, const Token *token) throw (SemanticError)
{
    code << this->actions[action-1](token);
}
