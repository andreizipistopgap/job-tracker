#include "HelloController.h"

void HelloController::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    Json::Value json;
    json["message"] = "Hello";
    
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
