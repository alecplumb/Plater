#include <iostream>
#include <fcntl.h>
#if defined(_WIN32) || defined(_WIN64)
#include "wingetopt.h"
#else
#include <getopt.h>
#endif
#define _USE_MATH_DEFINES
#include <math.h>
#include "stl/StlFactory.h"
#include "Request.h"
#include "util.h"
#include "log.h"

using namespace std;
using namespace Plater;

void help()
{
    cerr << "Plater v1.VORON" << endl;
    cerr << "Usage: plater [options] plater.conf" << endl;
    cerr << "(Use - to read from stdin)" << endl;
    cerr << endl;
    cerr << "-h: Display this help" << endl;
    cerr << "-v: Verbose mode" << endl;
    cerr << "-W width: Setting the plate width (default: 150mm)" << endl;
    cerr << "-H height: Setting the plate height (default: 150mm)" << endl;
    cerr << "-D diameter: Set the plate diameter, in mm. If set, this will put the plate in circular mode" << endl;
    cerr << "-j precision: Sets the precision (in mm, default: 0.5)" << endl;
    cerr << "-s spacing: Change the spacing between parts (in mm, default: 1.5)" << endl;
    cerr << "-d delta: Sets the interval of place grid (in mm, default: 1.5)" << endl;
    cerr << "-r rotation: Sets the interval of rotation (in °, default: 90)" << endl;
    cerr << "-S: Trying multiple sort possibilities" << endl;
    cerr << "-R random: Sets the number of random (shuffled parts) iterations (only with -S)" << endl;
    cerr << "-o pattern: output file pattern (default: plate_%03d)" << endl;
    cerr << "-p: will output ppm of the plates" << endl;
    cerr << "-t threads: sets the number of threads (default 1)" << endl;
    cerr << "-c: enables the output of plates.csv containing plates infos" << endl;
    cerr << "-X: adds an exclusion region to the plates, in the format \"x1,y1:x2,y2\"" << endl;
    cerr << "-b <filename>: Use a 24-bit Windows BMP as an exclusion region." << endl;
    cerr << "               The image will be stretched to cover the plate." << endl;
    cerr << "               White pixels will be excluded from the plate." << endl;
    cerr << "-B <filename>: Same as '-b' except non-white pixels are excluded." << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int index;
    Request request;

    while ((index = getopt(argc, argv, "hvs:d:r:pj:d:o:W:H:R:D:t:ScX:b:B:")) != -1) {
        switch (index) {
            case 'h':
                help();
                break;
            case 'v':
                increaseVerboseLevel();
                break;
            case 's':
                request.spacing = atof(optarg)*1000;
                break;
            case 'd':
                request.delta = atof(optarg)*1000;
                break;
            case 'r':
                request.deltaR = DEG2RAD(atof(optarg));
                break;
            case 'p':
                request.mode = REQUEST_PPM;
                break;
            case 'j':
                request.precision = atof(optarg)*1000;
                break;
            case 'o':
                request.pattern = string(optarg);
                break;
            case 'W':
                request.plateWidth = atof(optarg)*1000;
                break;
            case 'H':
                request.plateHeight = atof(optarg)*1000;
                break;
            case 'S':
                request.sortMode = REQUEST_MULTIPLE_SORTS;
                break;
            case 'R':
                request.randomIterations = atoi(optarg);
                break;
            case 'D':
                request.plateMode = PLATE_MODE_CIRCLE;
                request.plateDiameter = atof(optarg)*1000;
                break;
            case 't':
                request.nbThreads = atoi(optarg);
                break;
            case 'c':
                request.platesInfo = true;
                break;
            case 'X':
                request.addExclusionRect(optarg);
                break;
            case 'b':
                request.excludeBitmap(optarg, false);
                break;
            case 'B':
                request.excludeBitmap(optarg, true);
                break;
        }
    }

    if (optind != argc) {
        string filename = string(argv[optind]);
        if (filename == "-") {
            request.readFromStdin();
        } else {
            request.readFromFile(filename);
        }
    } else {
        help();
    }
    request.process();

    return EXIT_SUCCESS;
}
