#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <variant>


enum class JsonType { 
	NUMBER,
	STRING,
	NULL_TYPE,
	OBJECT,
	ARRAY,
	BOOLEAN
};

class JsonNode {
public:
	using JsonObject = std::map<std::string, JsonNode>;
	using JsonArray = std::vector<JsonNode>;

private:
	std::variant<
		std::monostate,
		std::string,
		int,
		double,
		bool,
		JsonObject,
		JsonArray
	> value;
		
	std::vector<std::string> tokenizer(const std::string&);
	

public:
	JsonNode object(const std::string& token);
	JsonNode() : value(std::monostate()) {}
	JsonNode(std::monostate) : value(std::monostate()) {}
	JsonNode(const std::string& str): value(str) {}
	JsonNode(int num) : value(num) {}
	JsonNode(double num) : value(num) {}
	JsonNode(bool state) : value(state) {}
	JsonNode(const JsonObject& jobj) : value(jobj) {}
	JsonNode(const JsonArray& jarr) : value(jarr) {}

	bool isNull() const
	{
		return std::holds_alternative<std::monostate>(value);
	}
	bool isString() const
	{
		return std::holds_alternative<std::string>(value);
	}
	bool isInt() const
	{
		return std::holds_alternative<int>(value);
	}
	bool isDouble() const
	{
		return std::holds_alternative<double>(value);
	}
	bool isBool() const
	{
		return std::holds_alternative<bool>(value);
	}
	bool isObj() const
	{
		return std::holds_alternative<JsonObject>(value);
	}
	bool isArr() const
	{
		return std::holds_alternative<JsonArray>(value);
	}

	std::string& toString();
	const std::string& toString() const;
	int& toInt();
	const int& toInt() const;
	double& toDouble();
	const double& toDouble() const;
	bool& toBool();
	const bool& toBool() const;
	JsonObject& toObj();
	const JsonObject& toObj() const;
	JsonArray& toArr();
	const JsonArray& toArr() const;

	std::string serialize() const;
};
