#pragma once

#include "../models/JobApplication.h"
#include <vector>
#include <optional>

class JobApplicationRepository {
private:
    std::vector<JobApplication> applications;
    int nextId = 1;

public:

    std::vector<JobApplication> getAllApplications() {
        return applications;
    }

    JobApplication addApplication(JobApplication app) {
        app.id = nextId;
        nextId++;

        applications.push_back(app);
        return app;
    }

    std::optional<JobApplication> getApplicationById(int id) {
        for (const auto &a : applications) {
            if (a.id == id) return a;
        }
        return std::nullopt;
    }
};