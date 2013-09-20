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
	size_t size;
	std::string full_name;
	unsigned char *data;
	fipMemoryIO *mem;
	FREE_IMAGE_FORMAT fif;
	FIBITMAP * check;

        writerColor.SetSourceImage (colorMap);
	writerColor.Write();
	size = writerColor.GetSizeInBytes();
	data = writerColor.GetMem();
	mem = new fipMemoryIO(data, size);
	if (!mem->isValid())
		throw std::runtime_error("MapGenerator: Bad image content");
	fif = mem->getFileType();
	check = mem->load(fif, PNG_DEFAULT);
	delete mem;
	full_name = location + "terrain_texture.png";
	if (!FreeImage_Save(FIF_PNG, check, full_name.c_str(), PNG_DEFAULT)) {
            throw std::logic_error("An error occurred while saving" \
                " image '" + full_name + "'");
        }

        writerHeight.SetSourceImage(heightMap);
	writerHeight.Write();
	size = writerHeight.GetSizeInBytes();
	data = writerHeight.GetMem();
	mem = new fipMemoryIO(data, size);
	if (!mem->isValid())
		throw std::runtime_error("MapGenerator: Bad image content");
	fif = mem->getFileType();
	check = mem->load(fif, PNG_DEFAULT);
	delete mem;
	full_name = location + "terrain.png";
	if (!FreeImage_Save(FIF_PNG, check, full_name.c_str(), PNG_DEFAULT)) {
            throw std::logic_error("An error occurred while saving" \
                " image '" + full_name + "'");
    }
		
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

    delete terrain;
}

