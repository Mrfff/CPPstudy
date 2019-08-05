#include <iostream>
#include"warcraftworld.h"
#include"warcraft.h"
#include"gameconfig.cc"
#include"warrior.h"
using namespace warcraft;

void WarrcraftWorld::init()
{
    GameConfig *config=GameConfig::getInstance();
    
    _redHeadquarters=new RedHeadquarters(config->headquartersInitialElements);


    Dragon::setHp(config->warriorInitalAttack(DRAGON_TYPE));
    Dragon setForce(config->warriorInitalAttack(DRAGON_TYPE));
    
    Ninja setHp(config->warriorInitalAttack(NINJA_TYPE));
    Ninja setForce(config->warriorInitalAttack(NINJA_TYPE));
    
    Iceman setHp(config->warriorInitalAttack(ICEMAN_TYPE));
    Iceman setForce(config->warriorInitalAttack(ICEMAN_TYPE));
    
    Lion setHp(config->warriorInitalAttack(LION_TYPE));
    Lion setForce(config->warriorInitalAttack(LION_TYPE));
    
    Wolf setHp(config->warriorInitalAttack(WOLF_TYPE));
    Wolf setForce(config->warriorInitalAttack(WOLF_TYPE));
}

