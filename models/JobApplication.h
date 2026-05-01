#pragma once

#include <string>
#include <json/json.h>

class JobApplication {
public:
    int id;
    std::string company;
    std::string position;
    std::string status;

    Json::Value toJson() {
        Json::Value json;
        json["id"] = id;
        json["company"] = company;
        json["position"] = position;
        json["status"] = status;

        return json;
    }

    JobApplication(int id, std::string company, std::string position, std::string status) {
        this->id = id;
        this->company = company;
        this->position = position;
        this->status = status;
    }
};
