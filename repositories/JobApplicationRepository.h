#pragma once

#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>
#include "../models/JobApplication.h"
#include <vector>
#include <optional>

class JobApplicationRepository {
private:
    // std::vector<JobApplication> applications;
    int nextId = 1;

public:

    std::vector<JobApplication> getAllApplications() {
        auto client = drogon::app().getDbClient();
        auto result = client->execSqlSync(
            "SELECT id, company, position, status FROM applications"
        );
        std::vector<JobApplication> applications;

        for (const auto& row : result) {
            int id = row["id"].as<int>();
            std::string company = row["company"].as<std::string>();
            std::string position = row["position"].as<std::string>();
            std::string status = row["status"].as<std::string>();

            JobApplication app(id, company, position, status);
            applications.push_back(app);
        }
        return applications;
    }

    JobApplication addApplication(JobApplication app) {
        auto client = drogon::app().getDbClient();
        auto result = client->execSqlSync(
            "INSERT INTO applications (company, position, status) "
            "VALUES (?, ?, ?)",
            app.company,
            app.position,
            app.status
        );

        auto idResult = client->execSqlSync("SELECT last_insert_rowid()");
        int id = idResult[0][0].as<int>();
        app.id = id;

        return app;
    }

    std::optional<JobApplication> getApplicationById(int id) {
        auto client = drogon::app().getDbClient();
        auto result = client->execSqlSync(
            "SELECT id, company, position, status "
            "FROM applications "
            "WHERE id = ?",
            id
        );

        if (result.empty()) {
            return std::nullopt;
        }

        const auto& row = result[0];
        int dbId = row["id"].as<int>();
        std::string company = row["company"].as<std::string>();
        std::string position = row["position"].as<std::string>();
        std::string status = row["status"].as<std::string>();

        JobApplication app(dbId, company, position, status);
        return app;
    }

    std::optional<JobApplication> deleteApplicationById(int id) {
        auto client = drogon::app().getDbClient();
        auto app = getApplicationById(id);

        if (!app) {
            return std::nullopt;
        }

        auto result = client->execSqlSync(
            "DELETE FROM applications "
            "WHERE id = ?",
            id
        );

        return app;
    }

    std::optional<JobApplication> updateApplicationById(int id, JobApplication app) {
        auto client = drogon::app().getDbClient();

        auto res = getApplicationById(id);

        if (!res) {
            return std::nullopt;
        }

        auto result = client->execSqlSync(
            "UPDATE applications "
            "SET company = ?, position = ?, status = ? "
            "WHERE id = ?",
            app.company,
            app.position,
            app.status,
            id
        );

        return getApplicationById(id);
    }
};