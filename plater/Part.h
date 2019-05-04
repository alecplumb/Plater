#ifndef _PLATER_PART_H
#define _PLATER_PART_H

#include <iostream>
#include "stl/StlFactory.h"


namespace Plater
{
    class Part
    {
        public:
            Part();
            virtual ~Part();

            void load(std::string filename, float precision, float deltaR, float spacing, string orientation);
            void placeholder(int width_, int height_, float precision_);
            std::string getFilename();

            Model model;

            Bitmap *getBmp(int index) const;
            float getSurface() const;
            float getDensity(int index) const;

            float precision;
            float deltaR;

            float width;
            float height;

            int bmps;
            Bitmap **bmp;
        
        protected:
            std::string filename;
    };
}

#endif
