#pragma once
#include <iostream>
#include <fstream>
#include <vector>

struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;

    Pixel();
};

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char  colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
    std::vector<Pixel> pixelVector;

    Header();
    ~Header();

    Header multiply(Header &header1, Header &header2) {};
};
