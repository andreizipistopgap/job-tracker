#include "ApplicationsController.h"
#include "../models/JobApplication.h"
#include "../services/JobApplicationService.h"
#include <vector>

void ApplicationsController::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{   
    JobApplicationService service;
    std::vector<JobApplication> applications = service.getAllApplications();
    Json::Value jsonApplications;
    
    for (auto &a : applications) {
        jsonApplications.append(a.toJson());
    }

    auto resp = HttpResponse::newHttpJsonResponse(jsonApplications);
    callback(resp);
}
