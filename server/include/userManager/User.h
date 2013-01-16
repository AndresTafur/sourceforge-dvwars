#ifndef _USER_
#define _USER_

#include <string>

/**
 * Represents a User (nonplayer) in the system (Note: this is a VO).
 */
class User
{
public:

        User();

        virtual inline std::string getName() { return mName; }

        virtual inline void setName(std::string val) { mName = val; }


        virtual inline std::string getPassword() { return mPsswd; }

        virtual inline void setPassword(std::string val) { mPsswd = val; }


        virtual inline void setEmail(std::string val) { mEmail = val; }

        virtual inline std::string getEmail() { return mEmail; }


        virtual inline void setSide(std::string val) { mSide = val; }

        virtual inline std::string getSide() { return mSide; }




        virtual ~User();

protected:

  std::string mName;
  std::string mPsswd;
  std::string mEmail;
  std::string mSide;
};

#endif // USER_H
