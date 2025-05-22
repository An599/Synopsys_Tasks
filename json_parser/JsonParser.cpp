#include "JsonParser.h"
#include <vector>
#include <string>
#include <sstream>

bool separatist(char x) {
	return (x == '{' || x == '}' || x == '[' || x == ']' || x == ':' || x == ',');
} //vor haskananq tvyal simvoly separator e te voch

std::vector<std::string> JsonNode::tokenizer(const std::string& str) //nermucvac jsony tokenneri bajanelu hamar grvac function
{
	std::vector<std::string> instance; //ir mej pahvum en tokennery 
	int i = 0;
	while (i < str.size())
	{
		if (isspace(str[i])) //datarky bac enq toxnum
			i++;
		else if (separatist(str[i]))
		{
			instance.emplace_back(1,str[i]); //qani vor separatory char e sarqum enq string, vorpes token avelacnum mer vectorin
			i++;
		}
		else if (str[i] == '"')
		{
			std::string temp; // sra mej havaqelu enq amboxj stringy
			temp.push_back(str[i]);
			i++;
			while (str[i] != '"') {
				temp.push_back(str[i]);
				i++;
			} // kardum enq amboxj stringy minchev " pakvely u avelacnum mer instancein
			temp.push_back(str[i]); //pakvox chakerty push enq anum
			instance.push_back(temp);
			i++;
		}
		else {
			std::string temp;
			while (!separatist(str[i]) && str[i] != '"' && !isspace(str[i]))
			{
				temp.push_back(str[i]);
				i++;
			} //ete voch str voch separator voch space =>valuei inch vor mas, gnum enq aynqan minchev drancic mekin handipenq yndacqum exac masy avelacnum enq mer vectorin
			instance.push_back(temp);
		}
	}
	return instance;
}
bool isInt(const std::string& token) {
	std::istringstream input_str_stream(token); //bufferacnum e mer tokeny parunakutyuny karanq input anenq ayl tex
	int integer;
	char c;
	if (!(input_str_stream >> integer)) return false; // bufferi mejiny grum e integerei mej (parse e anum) ete chkaroxacav iragorcel uremn bufferum tiv chi grvac 
	return !(input_str_stream >> c); //ete karoxanum e charum simvol grel=> buffern amboxjutyamb int cher vael simvolner kayin
}
bool isDouble(const std::string& token) {
		std::istringstream input_str_stream(token);
		double d;
		char c;
		if (!(input_str_stream >> d)) return false;
		return !(input_str_stream >> c);
}
void helper_str_to_type(const std::vector<std::string>& token, JsonNode& node, int& index) { //tokenneri hajordakanutyuny veracum e Jsoni
	if (token[index] == "null")
	{
		node = std::monostate(); //datark obj i hamar
		index++;
		std::cout << "null" << std::endl;
	}
	else if (token[index] == "true" || token[index] == "false") //bool tipi jsoni veracumy
	{
		node = token[index] == "true" ? true : false;
		index++;
		std::cout << "bool" << std::endl;
	}
	else if (token[index].front() == '"' && token[index].back() == '"' && 
		token[index].size() >= 2) //stri hamar
	{
		node = token[index].substr(1, token[index].size() - 2);
		index++;
		std::cout << "str" << std::endl;
	}
	else if (isInt(token[index]))
	{
		std::istringstream input_str_stream(token[index]);
		int integer;
		input_str_stream >> integer;
		node = integer;
		index++;
		std::cout << "int" << std::endl;
	}
	else if (isDouble(token[index]))
	{
		std::istringstream input_str_stream(token[index]);
		double d;
		input_str_stream >> d;
		node = d;
		index++;
		std::cout << "double" << std::endl;
	}
	else if (token[index] == "[") //for jsonArray parseing from str to json
	{
		std::cout << "jsonArray" << std::endl;
		JsonNode::JsonArray temp_node = JsonNode::JsonArray();
		index++;
		while (token[index] != "]")
		{
			JsonNode temp2;
			helper_str_to_type(token, temp2, index); // recursive kanch henc ir functionin qani vor arrayy ir mej eli hasarak tvyalner e parunakum (e.g. tiv, bool)
			temp_node.push_back(temp2);
			if (token[index] == ",")
				index++;
		}
		index++;
		node = temp_node;
	}
	else if (token[index] == "{")
	{
		std::cout << "json Obj" << std::endl;
		JsonNode::JsonObject temp_jobj = JsonNode::JsonObject();
		index++;
		while (token[index] != "}")
		{
			std::string key = token[index];
			index += 2;
			helper_str_to_type(token, temp_jobj[key], index);
			if (token[index] == ",")
				index++;
		}
		index++; // pakoc pakagci avelacman hamar
		node = temp_jobj;
	}
}

JsonNode JsonNode::object(const std::string& json) {
	std::vector<std::string> token = tokenizer(json);
	//for (int i = 0; i < token.size(); i++)
	//	std::cout << token[i] << std::endl;
	/*JsonNode node;*/
	int index = 0;
	helper_str_to_type(token, *this, index);
	return *this;
} //wrapper function - helper functioni kanch - vor miayn json stringov karoxananq karucel object 

std::string& JsonNode::toString() {
	if (isString())
		return std::get<std::string>(value);
	throw std::runtime_error("Json Node is not string");
} // apahov dzev jsonn nodeic string kardalu hamar

const std::string& JsonNode::toString() const{
	if (isString())
		return std::get<std::string>(value);
	throw std::runtime_error("Json Node is not string");
} //verevi functiony arden const stringneri hamar, vor ayd casey yevs handle arvi

int& JsonNode::toInt() {
	if (isInt())
		return std::get<int>(value);
	throw std::runtime_error("Json Node is not integer");
}//nuyn verevi 2 functionnery arvum en bolor tiperi hamar jsonic tvyal tipi valuen kardum  e

const int& JsonNode::toInt() const {
	if (isInt())
		return std::get<int>(value);
	throw std::runtime_error("Json Node is not integer");
}

double& JsonNode::toDouble() {
	if (isDouble())
		return std::get<double>(value);
	throw std::runtime_error("Json Node is not double");
}

const double& JsonNode::toDouble() const {
	if (isDouble())
		return std::get<double>(value);
	throw std::runtime_error("Json Node is not double");
}

bool& JsonNode::toBool() {
	if (isBool())
		return std::get<bool>(value);
	throw std::runtime_error("Json Node is not bool");
}

const bool& JsonNode::toBool() const {
	if (isBool())
		return std::get<bool>(value);
	throw std::runtime_error("Json Node is not bool");
}
JsonNode::JsonObject& JsonNode::toObj() {
	if (isObj())
		return std::get<JsonNode::JsonObject>(value);
	throw std::runtime_error("Json Node is not json object");
}

const JsonNode::JsonObject& JsonNode::toObj() const {
	if (isObj())
		return std::get<JsonNode::JsonObject>(value);
	throw std::runtime_error("Json Node is not json object");
}
JsonNode::JsonArray& JsonNode::toArr() {
	if (isArr())
		return std::get<JsonNode::JsonArray>(value);
	throw std::runtime_error("Json Node is not json array");
}

const JsonNode::JsonArray& JsonNode::toArr() const {
	if (isArr())
		return std::get<JsonNode::JsonArray>(value);
	throw std::runtime_error("Json Node is not json array");
}

void helper_serialize_conv(const JsonNode& node, std::string& str) { //jsonic sarqum enq string vor stringi tesqov ir mej infon pahenq
	if (node.isNull())
	{
		str += "null";
	}
	else if (node.isBool())
	{
		str += node.toBool() ? "true" : "false";
	}
	else if (node.isInt())
	{
		str += std::to_string(node.toInt());
	}
	else if (node.isDouble())
	{
		str += std::to_string(node.toDouble());
	}
	else if (node.isString()) 
	{
		str += node.toString();
	}
	else if (node.isArr())
	{
		str.push_back('[');
		for (const JsonNode& temp : node.toArr())
		{
			helper_serialize_conv(temp, str);
			str.push_back(',');
		}
		if (str.back() == ',')
			str.back() = ']';
		else
			str.push_back(']');
	}
	else if (node.isObj())
	{
		str.push_back('{');
		for (const std::pair<const std::string, JsonNode>& temp : node.toObj())
		{
			helper_serialize_conv(temp.first, str);
			str.push_back(':');
			helper_serialize_conv(temp.second, str);
			str.push_back(',');
		}
		if (str.back() == ',')
			str.back() = '}';
		else
			str.push_back('}');
	}
}

std::string JsonNode::serialize() const 
{
	std::string sequence;
	helper_serialize_conv(*this, sequence);
	return sequence;
} // recursive functioni wrapper vor helperin nersum tanq anhrajesht parametrery
