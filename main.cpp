#include "Image.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char** argv) {
    Image the_map("the_map.png");
    Image the_skin("the_skin.png");

    // initialise input files
    int numFiles = 6;
    std::string skinName = "armoured";
    std::string fileName = "source.player_runSE";

    std::vector<Image> fileList;
    for (int i = 1;i <= numFiles;i++) {
        std::string currFile = "input/" + fileName + std::to_string(i) + ".png";
        Image file(currFile.c_str());
        fileList.push_back(file);
    }

    // create map
    // map: key is a colour, value is another colour
    std::unordered_map<std::string,int*> colourLookup;
    for (int i = 0;i < the_map.h*the_map.w*the_map.channels;i = i+4) {
        // alpha is not zero, that is, the pixel actually exists
        if (the_map.data[i+3] != 0) {
            std::string key = std::to_string(the_map.data[i]) + "," + std::to_string(the_map.data[i+1]) + "," + std::to_string(the_map.data[i+2]) + "," + std::to_string(the_map.data[i+3]);
            int* value = new int(4);
            value[0] = the_skin.data[i];
            value[1] = the_skin.data[i+1];
            value[2] = the_skin.data[i+2];
            value[3] = the_skin.data[i+3];
            colourLookup[key] = value;
        }
    }

    // process files
    for (int i = 0;i < numFiles;i++) {
        for (int j = 0;j < fileList[i].h*fileList[i].w*fileList[i].channels;j = j+4) {

            if (fileList[i].data[j+3] != 0) {
                std::string key = std::to_string(fileList[i].data[j]) + "," + std::to_string(fileList[i].data[j+1]) + "," + std::to_string(fileList[i].data[j+2]) + "," + std::to_string(fileList[i].data[j+3]);
                fileList[i].data[j] = colourLookup[key][0]; // red value
                fileList[i].data[j+1] = colourLookup[key][1]; // green value
                fileList[i].data[j+2] = colourLookup[key][2]; // blue value
                fileList[i].data[j+3] = colourLookup[key][3]; // alpha value
            }

        }
        std::string outFile = "output/" + skinName + "_" + fileName + std::to_string(i+1) + ".png";
        fileList[i].write(outFile.c_str());
    }

    return 0;
}