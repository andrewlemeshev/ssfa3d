#include <iostream>
#include "funnel.h"

int main(int argc, char* argv[]) {
    const int test1Count = 10;
    funnel_in_t* in = new funnel_in_t[test1Count];
    vec_t* out = new vec_t[test1Count];
    
    // pay attention to the point (the last one), leftRight function depends on it
    in[0] = {segment_t(vec_t( 4.0f, 14.0f, 5.0f), vec_t( 4.0f, 14.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t( 4.0f,14.0f, 5.0f)};
    in[1] = {segment_t(vec_t( 2.0f, 11.0f, 5.0f), vec_t( 7.0f, 12.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t( 4.0f,14.0f, 5.0f)};
    in[2] = {segment_t(vec_t( 2.0f,  6.0f, 5.0f), vec_t( 7.0f, 12.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t( 4.0f, 9.0f, 5.0f)};
    in[3] = {segment_t(vec_t( 2.0f,  6.0f, 5.0f), vec_t( 7.0f,  6.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t( 6.0f, 8.0f, 5.0f)};
    in[4] = {segment_t(vec_t( 7.0f,  1.0f, 5.0f), vec_t( 7.0f,  6.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t( 6.0f, 5.0f, 5.0f)};
    in[5] = {segment_t(vec_t( 7.0f,  1.0f, 5.0f), vec_t(13.0f,  8.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t( 8.0f, 5.0f, 5.0f)};
    in[6] = {segment_t(vec_t(13.0f,  8.0f, 5.0f), vec_t(14.0f,  3.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t(12.0f, 4.0f, 5.0f)};
    in[7] = {segment_t(vec_t(14.0f,  3.0f, 5.0f), vec_t(19.0f, 10.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t(15.0f, 7.0f, 5.0f)};
    in[8] = {segment_t(vec_t(19.0f, 10.0f, 5.0f), vec_t(19.0f,  3.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t(18.0f, 5.0f, 5.0f)};
    in[9] = {segment_t(vec_t(22.0f,  7.0f, 5.0f), vec_t(22.0f,  7.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t(22.0f, 7.0f, 5.0f)};

    int outCount = funnelAlgorithm(in, test1Count, out, test1Count);
    
    assert(outCount == 3); // I expect three points path

    for (int i = 0; i < outCount; i++) {
        std::cout << "Path step " << i << ": x " << out[i].x << " y " << out[i].y << " z " << out[i].z << "\n";
    }

    delete [] in;
    delete [] out;

    // in opposite direction
    const int test2Count = 10;
    in = new funnel_in_t[test2Count];
    out = new vec_t[test2Count];

    in[0] = {segment_t(vec_t(22.0f,  7.0f, 5.0f), vec_t(22.0f,  7.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t(22.0f, 7.0f, 5.0f)};
    in[1] = {segment_t(vec_t(19.0f, 10.0f, 5.0f), vec_t(19.0f,  3.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t(22.0f, 7.0f, 5.0f)};
    in[2] = {segment_t(vec_t(14.0f,  3.0f, 5.0f), vec_t(19.0f, 10.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t(18.0f, 5.0f, 5.0f)};
    in[3] = {segment_t(vec_t(13.0f,  8.0f, 5.0f), vec_t(14.0f,  3.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t(15.0f, 7.0f, 5.0f)};
    in[4] = {segment_t(vec_t( 7.0f,  1.0f, 5.0f), vec_t(13.0f,  8.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t(12.0f, 4.0f, 5.0f)};
    in[5] = {segment_t(vec_t( 7.0f,  1.0f, 5.0f), vec_t( 7.0f,  6.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t( 8.0f, 5.0f, 5.0f)};
    in[6] = {segment_t(vec_t( 2.0f,  6.0f, 5.0f), vec_t( 7.0f,  6.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t( 6.0f, 5.0f, 5.0f)};
    in[7] = {segment_t(vec_t( 2.0f,  6.0f, 5.0f), vec_t( 7.0f, 12.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t( 6.0f, 8.0f, 5.0f)};
    in[8] = {segment_t(vec_t( 2.0f, 11.0f, 5.0f), vec_t( 7.0f, 12.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t( 4.0f, 9.0f, 5.0f)};
    in[9] = {segment_t(vec_t( 4.0f, 14.0f, 5.0f), vec_t( 4.0f, 14.0f, 5.0f)), vec_t(0.0f, 0.0f, 1.0f), vec_t( 4.0f,14.0f, 5.0f)};

    outCount = funnelAlgorithm(in, test2Count, out, test2Count);
    
    assert(outCount == 3);

    for (int i = 0; i < outCount; i++) {
        std::cout << "Path step " << i << ": x " << out[i].x << " y " << out[i].y << " z " << out[i].z << "\n";
    }

    delete [] in;
    delete [] out;

    return 0;
}
