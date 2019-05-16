#include <napi.h>
#include "../handlers/handler.h"

class Exporter : public Napi::ObjectWrap<Exporter> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports); //Init function for setting the export key to JS
  Exporter(const Napi::CallbackInfo& info); 

 private:
  static Napi::FunctionReference constructor; //reference to store the class definition that needs to be exported to JS
  Napi::Value RegisterProtocol(const Napi::CallbackInfo& info); //wrapped registerProtocol function 
  Handler *handler_; //internal instance of actualclass used to perform actual operations.
};