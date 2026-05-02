#pragma once

#include "../models/JobApplication.h"
#include "../repositories/JobApplicationRepository.h"
#include <vector>

class JobApplicationService {
private:
    JobApplicationRepository repository;

public:

    std::vector<JobApplication> getAllApplications() {
        return repository.getAllApplications();
    }

    JobApplication addApplication(JobApplication app) {
        return repository.addApplication(app);
    }
};
