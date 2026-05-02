#include "ApplicationsController.h"
#include "../models/JobApplication.h"
#include "../services/JobApplicationService.h"
#include <vector>

void ApplicationsController::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{   
    static JobApplicationService service;
    if (req->method() == Get) {
        std::vector<JobApplication> applications = service.getAllApplications();
        Json::Value jsonApplications(Json::arrayValue);

        for (auto &a : applications) {
            jsonApplications.append(a.toJson());
        }

        auto resp = HttpResponse::newHttpJsonResponse(jsonApplications);
        callback(resp);
    }

    if (req->method() == Post) {
        auto json = req->getJsonObject();

        std::string company = (*json)["company"].asString();
        std::string position = (*json)["position"].asString();

        JobApplication app(company, position);

        JobApplication created = service.addApplication(app);

        auto resp = HttpResponse::newHttpJsonResponse(created.toJson());
        callback(resp);
    }
}
