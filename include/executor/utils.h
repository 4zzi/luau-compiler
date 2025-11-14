#pragma once

#include <Windows.h>
#include <string>

#include "nlohmann/json.hpp"
using nlohmann::json;

#include "executor/process.h"

HMODULE GetModule();

std::string Compile(const std::string& source);
std::string GenerateGUID();
void CheckRequiredKeys(const json& data, const std::vector<std::string>& keys);