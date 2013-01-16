#include "Player.h"

Player::Player(std::string name)
{
    mName = name;
    mGold = 500;
}


Player::Player(User &usr)
{
    this->mName = usr.getName();
    mGold = 500;
}


    void Player::addSquad(Squad *obj)
    {
       mSquads.insert( std::make_pair<unsigned int, Squad*>(obj->getID(), obj));
    }


    void Player::setGold(unsigned long gold)
    {
      char buff[500];

                mGold = gold;
                sprintf(buff,"410|%li",gold);
                this->Send(buff);
    }


    Squad* Player::findSquad(unsigned int squadId)
    {
      std::map<unsigned int, Squad*>::iterator iter;

            iter = mSquads.find(squadId);

            if(  iter != mSquads.end())
                return (iter->second);

            return NULL;
    }


Player::~Player()
{
    //dtor
}
