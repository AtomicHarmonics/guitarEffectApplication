#include <benchmark/benchmark.h>
#include "audioEffects.h"
static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state)
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_tremoloEffect(benchmark::State& state) {
  audioEffects a;
  float inputBuffer[512] = {};
  float outputBuffer[512] = {};
  for(int x = 0; x < 512; x++)
  {
    inputBuffer[x] = (float)x/512.0;
  }
  for (auto _ : state)
    a.tremoloEffect(inputBuffer, outputBuffer, 512, 4, 48000);
}
BENCHMARK(BM_tremoloEffect);

static void BM_tremoloEffect_2(benchmark::State& state) {
  audioEffects a;
  float inputBuffer[512] = {};
  float outputBuffer[512] = {};
  for(int x = 0; x < 512; x++)
  {
    inputBuffer[x] = (float)x/512.0;
  }
  for (auto _ : state)
    a.tremoloEffect_2(inputBuffer, outputBuffer, 512, 6, 100);
}
BENCHMARK(BM_tremoloEffect_2);

static void BM_distortEffect(benchmark::State& state) {
  audioEffects a;
  float inputBuffer[512] = {};
  float outputBuffer[512] = {};
  for(int x = 0; x < 512; x++)
  {
    inputBuffer[x] = (float)x/512.0;
  }
  for (auto _ : state)
    a.distortEffect(inputBuffer, outputBuffer, 512, 0.1);
}
BENCHMARK(BM_distortEffect);

static void BM_overdriveEffect(benchmark::State& state) {
  audioEffects a;
  float inputBuffer[512] = {};
  float outputBuffer[512] = {};
  for(int x = 0; x < 512; x++)
  {
    inputBuffer[x] = (float)x/512.0;
  }
  for (auto _ : state)
    a.overdriveEffect(inputBuffer, outputBuffer, 512, 3);
}
BENCHMARK(BM_overdriveEffect);

static void BM_reverbEffect(benchmark::State& state) {
  audioEffects a;
  float inputBuffer[512] = {};
  float outputBuffer[512] = {};
  for(int x = 0; x < 512; x++)
  {
    inputBuffer[x] = (float)x/512.0;
  }
  for (auto _ : state)
    a.reverbEffect(inputBuffer, outputBuffer, 512, 44100, (1.0f/3.0f), 0.5f, 0.0f, 0.25f, 1.0f, 0.0f);
//    a.overdriveEffect(inputBuffer, outputBuffer, 512, 3);
}
BENCHMARK(BM_reverbEffect);


BENCHMARK_MAIN();
