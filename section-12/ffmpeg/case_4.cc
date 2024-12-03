/**
 * cpp invoke ffmpeg
 */
#include <iostream>

extern "C" {
#include <libavcodec/avcodec.h>
}

using namespace std;

int main()
{
    cout << "test ffmpeg" << endl;
    string cfg = avcodec_configuration();
    cout << cfg << endl;
    string license = avcodec_license();
    cout << license << endl;
    return EXIT_SUCCESS;
}
