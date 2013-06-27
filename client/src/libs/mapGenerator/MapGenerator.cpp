/*
 *  Copyright (C) 2013 Jan Havran (sonicpp).
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
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Da Vinci Wars.    If not, see <http://www.gnu.org/licenses/>.
 */
     
#include <libnoise/noise.h>
#include <map>
#include <stdexcept>
#include <FreeImagePlus.h>
#include <cstdio> // func "remove"

#include "noiseutils.h"
#include "MapGenerator.h"
#include "Terrain.h"

void MapGenerator::generateMap(std::string type, std::string location, int seed)
{
    fipImage mImage;
    Terrain *terrain;

    try {
        if (type == "Grass") 
            terrain = new GrassTerrain(seed);
        else if (type == "Desert")
            terrain = new DesertTerrain(seed);
        else if (type == "Winter")
            terrain = new WinterTerrain(seed);
        else if (type == "Coast")
            terrain = new CoastTerrain(seed);
        else if (type == "Islands")
            terrain = new IslandsTerrain(seed);
        else if (type == "Peninsula")
            terrain = new PeninsulaTerrain(seed);
        else
            throw std::invalid_argument("Unknown type of map");
    
        terrain->generate();
        terrain->render();

        utils::Image colorMap = terrain->getColorMap();
        utils::Image heightMap = terrain->getHeightMap();

        utils::WriterBMP writerColor, writerHeight;
    
        //TODO save as *.[bmp | jpg] directly
        writerColor.SetSourceImage (colorMap);
        writerColor.SetDestFilename (location + "map.bmp");
        writerColor.WriteDestFile ();

        writerHeight.SetSourceImage(heightMap);
        writerHeight.SetDestFilename(location + "map2.bmp");
        writerHeight.WriteDestFile();
    }
    catch (ExceptionInvalidParam& e) {
        throw std::invalid_argument("Noise: invalid param");
    }
    catch (ExceptionNoModule& e) {
        throw std::runtime_error("Noise: no module");
    }
    catch (ExceptionOutOfMemory& e) {
        throw std::runtime_error("Noise: out of memory");
    }
    catch (ExceptionUnknown& e) {
        throw std::runtime_error("Noise: unkown error");
    }
    catch (Exception& e) {
        throw std::runtime_error("Noise: general error");
    }

    mImage.load((location + "map2.bmp").c_str());
    mImage.convertToGrayscale();
    mImage.save((location + "terrain.png").c_str());
    
    mImage.load((location + "map.bmp").c_str());
    mImage.save((location + "terrain_texture.jpg").c_str());
    remove((location + "map.bmp").c_str());
    remove((location + "map2.bmp").c_str());

    delete terrain;
}

