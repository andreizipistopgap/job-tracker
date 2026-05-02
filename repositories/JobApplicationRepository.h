#pragma once

#include "../models/JobApplication.h"
#include <vector>

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
};