/* cppsrc/main.cpp */
#include <napi.h>
#include "exporter/exporter.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  
  return Exporter::Init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)