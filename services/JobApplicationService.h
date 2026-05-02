#pragma once

#include "../models/JobApplication.h"
#include <vector>

class JobApplicationService {
public:

    std::vector<JobApplication> getAllApplications() {
        JobApplication a1(1, "Google", "SWE1", "Pending");
        JobApplication a2(2, "Amazon", "SWE2", "Hired");

        std::vector<JobApplication> applications;
        applications.push_back(a1);
        applications.push_back(a2);

        return applications;
    }
};
