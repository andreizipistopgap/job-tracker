#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ApplicationsController : public drogon::HttpController<ApplicationsController>
{
  public:
    void getAll(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

    void getById(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int id);

    void create(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

    METHOD_LIST_BEGIN
    // list path definitions here;
    // PATH_ADD("/path", "filter1", "filter2", HttpMethod1, HttpMethod2...);
    ADD_METHOD_TO(ApplicationsController::getAll, "/applications", Get);
    ADD_METHOD_TO(ApplicationsController::create, "/applications", Post);
    ADD_METHOD_TO(ApplicationsController::getById, "/applications/{1}", Get);
    METHOD_LIST_END
};
