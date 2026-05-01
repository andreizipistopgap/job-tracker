#include "ApplicationsController.h"
#include "../models/JobApplication.h"
#include <vector>

void ApplicationsController::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    JobApplication a1(1, "Google", "SWE1", "Pending");
    JobApplication a2(2, "Amazon", "SWE2", "Hired");

    std::vector<JobApplication> applications;
    applications.push_back(a1);
    applications.push_back(a2);

    Json::Value jsonApplications;

    for (auto &a : applications) {
        jsonApplications.append(a.toJson());
    }

    auto resp = HttpResponse::newHttpJsonResponse(jsonApplications);
    callback(resp);
}
