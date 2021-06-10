#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <ctime>
#include <vector>
#include <optional>
#include<mutex>


#define DEBUG 0
#define WARNING 1
#define ERROR 2
#define INFO 3





class OneLog {
private:
	std::string  message;
	std::optional<int>add;
	double additional;
	std::string  prefix;
	std::pair< std::string, int> status;
	std::thread::id threadID;


public:


	OneLog(const OneLog& A);
	OneLog();
	~OneLog();
	std::string getTime();
	void setPrefix(std::string prefix);
	std::string getPrefix();
	void setMessage(std::string message);
    std::string  getMessage();
	void setStatus(int status);
	int getStatus();

	OneLog& operator<<(double a);

	OneLog& operator<<(std::string msg);

	OneLog& operator<<(int add);

    std::string getLog(std::string _perfix);

};










enum class LogType {
	console, file
};



class WrapperLog {

private:
	std::optional<OneLog> container;
	std::string path;
	std::string prefix;
	static std::mutex mutex;
	void saveAll();
	void saveToConsole();
	void saveToFile();
public:
	WrapperLog    (const WrapperLog& a);
	WrapperLog    (std::string path = "", std::string perfix = "");
   ~WrapperLog    ();
	OneLog& operator<<(std::string msg) noexcept(false);
	OneLog& operator()(int status)      noexcept(false);
	LogType logType;
};




WrapperLog getLogger();


WrapperLog getLogger(std::string path);


WrapperLog getLogger(std::string path, std::string perfix);