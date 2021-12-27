#include "audioEffects.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
int main() {
    audioEffects x;
    plt::plot({1,3,2,x.returnFour()});
    plt::show();
}
