#pragma once

#include "../models/JobApplication.h"
#include <vector>

class JobApplicationRepository {
public:

    std::vector<JobApplication> getAllApplications() {
        JobApplication a1(1, "Microsoft", "SWE1", "Pending");
        JobApplication a2(2, "Amazon", "SWE2", "Hired");

        std::vector<JobApplication> applications;
        applications.push_back(a1);
        applications.push_back(a2);

        return applications;
    }
};