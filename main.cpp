#include <iostream>
#include <fstream>
#include <vector>
#include "extrafile.h"
//using namespace std;

int main() {

    std::ifstream fileOutput;
    std::vector<Header> fileHeaders;

    for (int i = 0; i < 2; i++) {
        if (i == 0) {
            fileOutput.open("input/car.tga",std::ios_base::binary);
        }
        else if (i == 1) {
            fileOutput.open("input/pattern1.tga,", std::ios_base::binary);
        }
        Header currentFileHead;

        fileOutput.read(&currentFileHead.idLength, sizeof(currentFileHead.idLength));
        std::cout << "ID Length: " << (int)currentFileHead.idLength << std::endl;

        fileOutput.read(&currentFileHead.colorMapType, sizeof(currentFileHead.colorMapType));
        std::cout << "Color Map Type: " << (int)currentFileHead.colorMapType << std::endl;

        fileOutput.read(&currentFileHead.dataTypeCode, sizeof(currentFileHead.dataTypeCode));
        std::cout << "Data Type Code: " << (int)currentFileHead.dataTypeCode << std::endl;

        fileOutput.read((char*) &currentFileHead.colorMapOrigin, sizeof(currentFileHead.colorMapOrigin));
        std::cout << "Color Map Origin: " << currentFileHead.colorMapOrigin << std::endl;

        fileOutput.read((char*) &currentFileHead.colorMapLength, sizeof(currentFileHead.colorMapLength));
        std::cout << "Color Map Length: " << currentFileHead.colorMapLength << std::endl;

        fileOutput.read(&currentFileHead.colorMapDepth, sizeof(currentFileHead.colorMapDepth));
        std::cout << "Color Map Depth: " << (int)currentFileHead.colorMapDepth << std::endl;

        fileOutput.read((char*) &currentFileHead.xOrigin, sizeof(currentFileHead.xOrigin));
        std::cout << "X Origin: " << currentFileHead.xOrigin << std::endl;

        fileOutput.read((char*) &currentFileHead.yOrigin, sizeof(currentFileHead.yOrigin));
        std::cout << "Y Origin: " << currentFileHead.yOrigin << std::endl;

        fileOutput.read((char*) &currentFileHead.width, sizeof(currentFileHead.width));
        std::cout << "Width: " << currentFileHead.width << std::endl;

        fileOutput.read((char*) &currentFileHead.height, sizeof(currentFileHead.height));
        std::cout << "Height: " << currentFileHead.height << std::endl;

        fileOutput.read(&currentFileHead.bitsPerPixel, sizeof(currentFileHead.bitsPerPixel));
        std::cout << "Bits Per Pixel: " << (int)currentFileHead.bitsPerPixel << std::endl;

        fileOutput.read(&currentFileHead.imageDescriptor, sizeof(currentFileHead.imageDescriptor));
        std::cout << "Image Descriptor: " << (int)currentFileHead.imageDescriptor << std::endl;
        std::cout << std::endl;

        int runtime = (currentFileHead.width * currentFileHead.height);

        for (int j = 0; j < runtime; j++) {
            Pixel newPixel;
            fileOutput.read((char*) &newPixel.blue, sizeof(newPixel.blue));
            fileOutput.read((char*) &newPixel.green, sizeof(newPixel.green));
            fileOutput.read((char*) &newPixel.red, sizeof(newPixel.red));
            currentFileHead.pixelVector.push_back(newPixel);
        }

        fileHeaders.push_back(currentFileHead);
        std::cout << "HEADERS ADDED: " << fileHeaders.size() << std::endl;
        fileOutput.close();
    }

    std::ofstream test;
    test.open("output/example1test.tga", std::ios_base::binary);
    if (test.is_open()) {
        test.write(&fileHeaders[0].idLength, sizeof(fileHeaders[0].idLength));
        test.write(&fileHeaders[0].colorMapType, sizeof(fileHeaders[0].colorMapType));
        test.write(&fileHeaders[0].dataTypeCode, sizeof(fileHeaders[0].dataTypeCode));
        test.write((char*) &fileHeaders[0].colorMapOrigin, sizeof(fileHeaders[0].colorMapOrigin));
        test.write((char*) &fileHeaders[0].colorMapLength, sizeof(fileHeaders[0].colorMapLength));
        test.write(&fileHeaders[0].colorMapDepth, sizeof(fileHeaders[0].colorMapDepth));
        test.write((char*) &fileHeaders[0].xOrigin, sizeof(fileHeaders[0].xOrigin));
        test.write((char*) &fileHeaders[0].yOrigin, sizeof(fileHeaders[0].yOrigin));
        test.write((char*) &fileHeaders[0].width, sizeof(fileHeaders[0].width));
        test.write((char*) &fileHeaders[0].height, sizeof(fileHeaders[0].height));
        test.write(&fileHeaders[0].bitsPerPixel, sizeof(fileHeaders[0].bitsPerPixel));
        test.write(&fileHeaders[0].imageDescriptor, sizeof(fileHeaders[0].imageDescriptor));

        int temp = (fileHeaders[0].width * fileHeaders[0].height);
        for (int i = 0; i < temp; i++) {
            /*
            float multiplyTestBlue = (((((fileHeaders[0].pixelVector[i].blue / 255.0f)) * ((fileHeaders[1].pixelVector[i].blue / 255.0f))) * 255.0f) + 0.5f);
            unsigned char blueTest = (unsigned char)multiplyTestBlue;
            float multiplyTestGreen = (((((fileHeaders[0].pixelVector[i].green / 255.0f)) * ((fileHeaders[1].pixelVector[i].green / 255.0f))) * 255.0f) + 0.5f);
            unsigned char greenTest = (unsigned char)multiplyTestGreen;
            float multiplyTestRed = (((((fileHeaders[0].pixelVector[i].red / 255.0f)) * ((fileHeaders[1].pixelVector[i].red / 255.0f))) * 255.0f) + 0.5f);
            unsigned char redTest = (unsigned char)multiplyTestRed;

            test.write((char*) &blueTest, sizeof(blueTest));
            test.write((char*) &greenTest, sizeof(greenTest));
            test.write((char*) &redTest, sizeof(redTest));

            if (i == 0 || i == 1) {
                std::cout << "Test Values: " << std::endl;
                std::cout << "Blue: " << multiplyTestBlue << " " << (int)blueTest << std::endl;
                std::cout << "Green: " << multiplyTestGreen << " " << (int)greenTest << std::endl;
                std::cout << "Red: " << multiplyTestRed << " " << (int)redTest << std::endl;

                std::cout << "Pixel Values Blue: " << (int)fileHeaders[0].pixelVector[0].blue << " " << (int)fileHeaders[1].pixelVector[1].blue << std::endl;
                std::cout << ((((fileHeaders[0].pixelVector[0].green / 255.0f)) * ((fileHeaders[1].pixelVector[0].green / 255.0f))) * 255.0f) << std::endl;
                std::cout << "Pixel Values Green: " << (int)fileHeaders[0].pixelVector[0].green << " " << (int)fileHeaders[1].pixelVector[1].green << std::endl;
                std::cout << "Pixel Values Red: " << (int)fileHeaders[0].pixelVector[0].red << " " << (int)fileHeaders[1].pixelVector[1].red << std::endl;
            }
            */


            test.write((char*) &fileHeaders[0].pixelVector[i].blue, sizeof(fileHeaders[0].pixelVector[i].blue));
            test.write((char*) &fileHeaders[0].pixelVector[i].green, sizeof(fileHeaders[0].pixelVector[i].green));
            test.write((char*) &fileHeaders[0].pixelVector[i].red, sizeof(fileHeaders[0].pixelVector[i].red));
        }

        test.close();
    }
    else {
        std::cout << "WRONG" << std::endl;
    }

    return 0;
}