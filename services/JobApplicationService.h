#pragma once

#include "../models/JobApplication.h"
#include "../repositories/JobApplicationRepository.h"
#include <vector>
#include <optional>

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

    std::optional<JobApplication> getApplicationById(int id) {
        return repository.getApplicationById(id);
    }

    std::optional<JobApplication> deleteApplicationById(int id) {
        return repository.deleteApplicationById(id);
    }

    std::optional<JobApplication> updateApplicationById(int id, JobApplication app) {
        return repository.updateApplicationById(id, app);
    }
};
