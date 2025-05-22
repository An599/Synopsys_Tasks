#include "JsonParser.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
           std::vector<std::string> valid_cases = {
            R"({"key": "value"})"
            R"([1, 2, 3, 4, 5])",
            R"({"user": {"id": 1, "name": "John"}})",
            R"([{"id":1}, {"id":2}, {"id":3}])",
            R"({"a": null, "b": true, "c": false})",
            R"({})",
            R"([])",
            R"({"int": 123, "float": -123.456, "exp": 1.2e10})",
            R"({"a":[{"b":[{"c":null}]}]})",
            R"({"quote": "He said \"hello\"."})"
        };

        for (const auto& json_str : valid_cases)
        {/*
                json::from_string(json_str); */
                JsonNode node;
                node.object(json_str);
                std::cout << node.serialize() << std::endl;
        }
   
}
