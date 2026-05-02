#include "ApplicationsController.h"
#include "../models/JobApplication.h"
#include "../services/JobApplicationService.h"
#include <vector>
static JobApplicationService service;

void ApplicationsController::getAll(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
    std::vector<JobApplication> applications = service.getAllApplications();
    Json::Value jsonApplications(Json::arrayValue);

    for (auto &a : applications) {
        jsonApplications.append(a.toJson());
    }

    auto resp = HttpResponse::newHttpJsonResponse(jsonApplications);
    callback(resp);
}

void ApplicationsController::getById(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int id) {
    std::optional<JobApplication> result = service.getApplicationById(id);
    
    if (result.has_value()) {
        auto resp = HttpResponse::newHttpJsonResponse(result.value().toJson());
        callback(resp);
    } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k404NotFound);
        resp->setBody("Application not found");
        callback(resp);
    }
}

void ApplicationsController::create(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback) {
    auto json = req->getJsonObject();
    if (json == nullptr) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Invalid json body");
        callback(resp);
        return;
    }

    if (!json->isMember("company") || !json->isMember("position")) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Missing required fields");
        callback(resp);
        return;
    }

    std::string company = (*json)["company"].asString();
    std::string position = (*json)["position"].asString();

    if (company.size() == 0 || position.size() == 0) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Missing required fields");
        callback(resp);
        return;
    }

    JobApplication app(company, position);

    JobApplication created = service.addApplication(app);

    auto resp = HttpResponse::newHttpJsonResponse(created.toJson());
    resp->setStatusCode(k201Created);
    callback(resp);
}

void ApplicationsController::deleteById(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int id) {
    std::optional<JobApplication> result = service.deleteApplicationById(id);

    if (result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.value().toJson());
        callback(resp);
    } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k404NotFound);
        resp->setBody("Application not found");
        callback(resp);
    }
}

void ApplicationsController::updateById(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int id) {
    auto json = req->getJsonObject();
    if (json == nullptr) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Invalid json body");
        callback(resp);
        return;
    }

    if (!json->isMember("company") || !json->isMember("position")) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Missing required fields");
        callback(resp);
        return;
    }

    std::string company = (*json)["company"].asString();
    std::string position = (*json)["position"].asString();

    if (company.size() == 0 || position.size() == 0) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Missing required fields");
        callback(resp);
        return;
    }

    JobApplication app(company, position);

    std::optional<JobApplication> result = service.updateApplicationById(id, app);
    if (result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.value().toJson());
        callback(resp);
    } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k404NotFound);
        resp->setBody("Application not found");
        callback(resp);
    }
}