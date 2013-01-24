/*
 *  Copyright (C) 2011-2013 Jorge A. Tafur Q. (jatafurq).
 *
 *  This file is part of Da Vinci Wars project.
 *
 *  Da Vinci Wars is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Da Vinci Wars is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Da Vinci Wars.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "MainApplication.h"


#include <SceneSequencer.h>
#include <LoginStage/view/LoginView.h>
#include <LobbyStage/view/LobbyView.h>


int main(int argc, char **argv)
{
    MainApplication app;

    LoginView *mLogin = new LoginView();
    LobbyView *mLobby = new LobbyView();
    SceneSequencer *seq = new SceneSequencer();

    try
    {
        seq->addScene(mLogin);
        seq->addScene(mLobby);
        seq->setSceneSequence("seq.xml");

        app.setSequencer(seq);
        app.startApplication();

        fprintf(stderr,"All components released, expecting libboost exit");
    }
    catch( Ogre::Exception& e )
    {
            std::cerr << "An exception has occured: " << e.getFullDescription();
    }
    return 0;
}
