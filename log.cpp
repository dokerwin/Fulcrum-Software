#include "log.h"
#include <thread>





ConsoleLog & getLogger()
{
	ConsoleLog a;
	return a;
}






FileLog& getLogger(std::string file, std::string perfix)
{

	FileLog file_log(file, perfix);

	return file_log;
}



FileLog& getLogger(std::string file)
{

	FileLog file_log(file);

	return file_log;
}






FileLog::FileLog(std::string file)
{

	
	path = file;
	perfix = "";



}

FileLog::FileLog(std::string file, std::string perfix)
{
	
	this->path = file;
	
		//getTime() << "My message " + perfix << this->message <<" "<< std::this_thread::get_id() <<"\n";
	

}

FileLog& FileLog::operator<<(std::string msg)
{
	return *this;
}

FileLog& FileLog::operator<<(int)
{
	return *this;
}

FileLog& FileLog::operator()(int)
{
	return *this;
}

void FileLog::operator()(std::string)
{


}

void FileLog::LogToFile()
{
	std::ofstream MyFile(path, std::ios::out | std::ios::app);
	MyFile << onelog.getMessage();

}


void ConsoleLog::LogToConsole()
{
	//std::cout << a.getMessage();

}


ConsoleLog& ConsoleLog::operator<<(std::string msg)
{
	
	//onelog.setMessage(onelog.getMessage() + msg);


	return *this;


}








ConsoleLog& ConsoleLog::operator<<(int preprocessor)
{
	//onelog.setMessage(onelog.getMessage() + ":"+ std::to_string(preprocessor));
	return *this;
}

ConsoleLog& ConsoleLog::operator()(int preprocessor)
{/*
	if (preprocessor == 0) {
		onelog.setStatus("Debug");
	}
	if (preprocessor == 1) {
		onelog.setStatus("Warning");
	}
	if (preprocessor == 2) {
		onelog.setStatus("Error");
	}
	if (preprocessor == 3) {
		onelog.setStatus("Info");
	}*/

	return *this;
}
void ConsoleLog::operator()(std::string)
{
}
ConsoleLog::ConsoleLog()
{
}







OneLog::OneLog()
{
}

OneLog::~OneLog()
{
}

void OneLog::setThreadID(int id)
{
	this->id = id;

}

size_t OneLog::getThreadID()
{
	return 1;

}

std::string OneLog::getTime()
{
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);

	return std::to_string(1900 + ltm.tm_year) + " " + std::to_string(1 + ltm.tm_mon) + " " + std::to_string(ltm.tm_mday) +
		" " + std::to_string(ltm.tm_hour) + ":" + std::to_string(ltm.tm_min + 1) + ":" + std::to_string(ltm.tm_sec + 1);

}

void OneLog::setPrefix(std::string strView)
{
	this->prefix = prefix;
}

std::string OneLog::getPrefix()
{
	return this->prefix;
}

void OneLog::setMessage(std::string message)
{
	this->message = message;
}

std::string OneLog::getMessage()
{
	return this->message;
}

void OneLog::setStatus(std::string status)
{
	this->status = status;
}

std::string OneLog::getStatus(){
return this->status;
}


