#include "Exporter.h"

Napi::FunctionReference Exporter::constructor;

Napi::Object Exporter::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Exporter", {
    InstanceMethod("registerProtocol", &Exporter::RegisterProtocol),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Exporter", func);
  return exports;
}

Exporter::Exporter(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Exporter>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->handler_ = new Handler();
}

Napi::Value Exporter::RegisterProtocol(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  if (length != 1 || !info[0].IsString()) {
    Napi::TypeError::New(env, "Protocol parameter expected").ThrowAsJavaScriptException();
  }

  Napi::String protocol = info[0].As<Napi::String>();
  bool res = this->handler_->registerProtocol(protocol);
  return Napi::Boolean::New(env, res);
}

