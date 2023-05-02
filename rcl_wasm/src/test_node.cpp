// #include <cstdio>

// int main(int argc, char ** argv)
// {
//   (void) argc;
//   (void) argv;

//   printf("hello world rcl_wasm package\n");
//   return 0;
// }


#include <emscripten/bind.h>

using namespace emscripten;

float lerp(float a, float b, float t)
{
    return (1 - t) * a + t * b;
}

EMSCRIPTEN_BINDINGS(my_module)
{
    function("lerp", &lerp);
}