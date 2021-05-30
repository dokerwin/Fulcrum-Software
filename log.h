#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <ctime>
#define DEBUG 0
#define WARNING 1
#define ERROR 2
#define INFO 3






class OneLog {
public:


	OneLog();
	~OneLog();

	void setThreadID(int id);
	size_t getThreadID();
	
	std::string getTime();

	void setPrefix(std::string strView);
	std::string getPrefix();
	void setMessage(std::string message);
	std::string getMessage();
	void setStatus(std::string status);
	std::string getStatus();

protected:
	 std::string message;
	 std::string prefix;
	 std::string status;
	 int id;
	
	//....date, prefix, status, sufix
};



class BaseLog {


private:

public:


	virtual BaseLog& operator<<(std::string msg) =0;
	virtual BaseLog& operator<<(int)=0;
	virtual BaseLog& operator()(int)=0;
	virtual void operator()(std::string)=0;


};



class ConsoleLog: public BaseLog {

private:
  OneLog onelog;
public:
	ConsoleLog();
	ConsoleLog& operator<<(std::string msg) override;
    ConsoleLog& operator<<(int) override;
	ConsoleLog& operator()(int) override;
	void operator()(std::string)override;
	void LogToConsole();
};




class FileLog: public BaseLog{

private :
	OneLog onelog;
	std::string path;
	std::string perfix;
	FileLog();

public:
	FileLog(std::string);
	FileLog(std::string, std::string);


    FileLog& operator<<(std::string msg) override;
	FileLog& operator<<(int) override;
	FileLog& operator()(int) override;
	void operator()(std::string)override;

	void LogToFile();
};





ConsoleLog& getLogger();

FileLog& getLogger(std::string);

FileLog& getLogger(std::string, std::string );


