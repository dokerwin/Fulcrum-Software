#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <ctime>
#include < vector >
#include <optional>
#include<mutex>


#define DEBUG 0
#define WARNING 1
#define ERROR 2
#define INFO 3

std::mutex mutex;



class OneLog {
public:


	OneLog(const OneLog& A) {
		message = A.message;
		add = A.add;
		additional = A.additional;
		prefix = A.prefix;
		status = A.status;
		threadID = A.threadID;
	}


	OneLog() {
		this->status.first = "INFO", this->status.second = 4;
		threadID = std::this_thread::get_id();

	}
	~OneLog() {

	}

	std::string getTime()
	{
		time_t now = time(0);
		tm ltm;

		localtime_s(&ltm, &now);
		return std::to_string(1900 + ltm.tm_year) + "." + std::to_string(1 + ltm.tm_mon) + "." + std::to_string(ltm.tm_mday) +
			"." + std::to_string(ltm.tm_hour) + ":" + std::to_string(ltm.tm_min + 1) + ":" + std::to_string(ltm.tm_sec + 1)+";";

	}

	void setPrefix(std::string prefix) {
		this->prefix = prefix;
	}
	std::string getPrefix() {
		return this->prefix;
	}


	void setMessage(std::string message) {

		this->message = message;
	}
	std::string  getMessage() {
		return this->message;
	}
	void setStatus(int status) {


		if (status == DEBUG)
			this->status.first = "Debug", this->status.second = 1;
		if (status == WARNING)
			this->status.first = "Warning", this->status.second = 2;
		if (status == ERROR)
			this->status.first = "Error", this->status.second = 3;
		if (status == INFO)
			this->status.first = "INFO", this->status.second = 4;			\


	}
	int getStatus() {


		return status.second;
	}

	OneLog& operator<<(double a) {

		std::ostringstream streamObj;
		streamObj << std::fixed;
		streamObj.precision(1);
		streamObj << a;
		std::string strObj3 = streamObj.str();
		this->message += strObj3;
		return *this;
	}

	OneLog& operator<<(std::string msg) {


		this->message += msg;
		return *this;
	}

	OneLog& operator<<(int add) {

		this->add.emplace(add);
		this->message += std::to_string(add) + " ";
		return *this;
	}



	std::string getLog(std::string _perfix) {

		std::ostringstream ss;
		ss << std::this_thread::get_id();
		std::string  idstr = ss.str();


		if (prefix!="") {
			return getTime() + ":" + status.first + ":" + _perfix + ":" + idstr + ":" + message + ";\n";

		}

		else
		{
			return getTime() + ":" + status.first + ":" + idstr + ":" + message + ";\n";
		}

	}



protected:
	std::string  message;
	std::optional<int>add;
	double additional;
	std::string  prefix;
	std::pair< std::string, int> status;
	std::thread::id threadID;

	//....date, prefix, status, sufix
};










enum class LogType {
	console, file
};



class WrapperLog {

public:

	WrapperLog(WrapperLog& a) {
		logType = a.logType;
		path = a.path;
		prefix = a.prefix;
		container = a.container;
	}

	WrapperLog(std::string path="",std::string perfix = "") {


		if (!container.has_value()) {
			container = OneLog();
		}
		this->prefix = perfix;
		this->path = path;
		


	}

	OneLog& operator<<(std::string msg) {

		container.emplace(OneLog());

		container.value().setMessage(msg);

		if (container.value().getMessage() != "") {

			saveAll();
			container.emplace(OneLog());

		}

		return container.value();
	}


	OneLog& operator()(int status) {
	
		if (container.value().getMessage() != "") {
			saveAll();
		}
		container.emplace(OneLog());
		container.value().setStatus(status);
		return container.value();
	}
	void saveAll() {
		if (logType == LogType::console)
			saveToConsole();
		else if (logType == LogType::file)
			saveToFile();
	}
	~WrapperLog() {
		
		if (container.value().getMessage() != "")
		{
			container.value().setPrefix(prefix);
			saveAll();
		}
	}

	bool operator_scop;
	LogType logType;
	std::optional<OneLog> container;
	std::string path;
	std::string prefix;

private:
	static std::mutex mutex;

	void saveToConsole() {
		mutex.lock();
		std::cout << container.value().getLog(prefix);
		mutex.unlock();
	}
	void saveToFile() {
		mutex.lock();
		std::ofstream MyFile(path, std::ios::out | std::ios::app);
		MyFile << container.value().getLog(prefix);
		mutex.unlock();
	}
};



std::mutex WrapperLog::mutex;

WrapperLog getLogger() {

	WrapperLog w;
	w.logType = LogType::console;
	return w;
}


WrapperLog getLogger(std::string path) {

	WrapperLog w(path);
	w.logType = LogType::file;
	return w;


}


WrapperLog getLogger(std::string path, std::string perfix) {

	WrapperLog w(path,perfix);
	w.logType = LogType::file;
	return w;
}