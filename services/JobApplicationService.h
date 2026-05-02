#pragma once

#include "../models/JobApplication.h"
#include "../repositories/JobApplicationRepository.h"
#include <vector>

class JobApplicationService {
public:

    std::vector<JobApplication> getAllApplications() {
        JobApplicationRepository repository;
        return repository.getAllApplications();
    }
};
