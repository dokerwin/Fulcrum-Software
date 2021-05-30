#include <thread>
#include "log.h"

using namespace std;

/*
Example of console output:
23.02.2020 18:06:06; INFO; (1020): Starting the app
23.02.2020 18:06:06; DEBUG; (2561): Running a thread

Example of log.txt output:
23.02.2020 18:06:06; INFO; (2561): Running a thread
23.02.2020 18:06:06; DEBUG; f2(3444): Running a thread
23.02.2020 18:06:06; WARNING; f2(3444): Time spent in the thread: 10.0 seconds

Example of log2.txt:
23.02.2020 18:06:06; INFO; f3(3444): Running a thread
23.02.2020 18:06:06; ERROR; f3(3444): My int is 123;
*/



//
//class Log {
//
//
//public :
//    Log(){}
//    int a;
//    string message;
//
//};
//
//
//class A {
//public:
//    A();
//   static Log a;
//  
//    
//  
//    
//    void set_message(std::string mes) 
//    {
//        std::cout << "Log to: " << mes<< std::endl;
//    }
//
//
//
//
//    A &operator << (std::string msg) 
//    {
//   
//      a.message += msg;
//      return *this;
//    }
//
//    A &operator () (std::string aa)
//    {
//        
//      a.message += aa;
//        return *this;
//    }
//
//    A & operator () (int aa) 
//    {
//        
//        a.message += std::to_string(aa);
//        return *this;
//
//    }
//
//   
//};
//
//
//Log a;
//
//
//
//A::A(){
//
//}
//class B:public A {
// 
//private:
//    //Log a;
//
//public:
//
//    B() {  std::cout << "Construktor B"<< std::endl; };
//  
//   
//};
//
//class C :public A {
//
//public:
//    C(){ std::cout << "Construktor C with parametres"<< std::endl; };
// 
//
//};
//
//B &get() {
//
//    B b;
//    return b;
//}
//C &get(std::string) {
//
//    C c;
//    return c;
//}
//
//
//
//C& get(std::string, std::string) {
//
//    C c;
//    return c;
//}

class ConsoleLog {

};

class FileLog {

};
#include < vector >
enum class LogType {
    console, file
};
class WrapperLog {
public:
    OneLog& operator()(int status) {
        saveAll();
        container.push_back( OneLog( status ) );
        return container.back();
    }
    void saveAll() {
        if (logType == LogType::console)
            saveToConsole();
        else if(logType == LogType::file)
            saveToFile();

        container.clear();
    }
    ~WrapperLog() {
        saveAll();
    }
private:
    void saveToConsole();
    void saveToFile();

    LogType logType;
    std::optional< OneLog > container;//std::optional
};
void f1() {
  


   auto consoleLogger = getLogger(); // Log to console
   
   // Console output: 23.02.2020 18:06:06; DEBUG; (2561): Running a thread
  consoleLogger(DEBUG) << "Running a thread";
 
    auto fileLogger = getLogger("log.txt"); // Log to file with name log.txt
    //// File output: 23.02.2020 18:06:06; INFO; (2561): Running a thread
    fileLogger << "Running a thread"; // Default log level INFO
}

void f2() {
    auto logger = getLogger("log.txt", "f2"); // Log to file with name log.txt. Each message has f2 prefix
    // File output: 23.02.2020 18:06:06; DEBUG; f2(3444): Running a thread
    logger(DEBUG) << "Running a thread";


    double timeSpent = 10.0;
    // File output: 23.02.2020 18:06:06; WARNING; f2(3444): Time spent in the thread: 10.0 seconds
    logger(WARNING) << "Time spent in the thread: " << timeSpent << " seconds";
}



void f3() {
    auto logger = getLogger("log2.txt", "f3");  // Log to file with name log2.txt. Each message has f3 prefix
    // File output: 23.02.2020 18:06:06; INFO; f3(3444): Running a thread
    logger << "Running a thread"; // Default log level INFO



    int i = 123;
    // File output: 23.02.2020 18:06:06; ERROR; f3(3444): My int is 123;
    logger(ERROR) << "My int is " << i;
}










int main() {

    //auto logger = getLogger(); // Log to console
    //// Console output: 23.02.2020 18:06:06; INFO; (1020): Starting the app
    //logger << "Starting the app"; // Default log level INFO



   // auto masakra = get();



    //cout << getTimeInString();





    // current date/time based on current system


    try
    {




    std::thread t1(f1);
    std::thread t2(f2);
    std::thread t3(f3);




    t1.join();
    t2.join();
    t3.join();




    }
    catch (...) {
       
        throw;




    }



    std::cout << "sd";

    return 0;
}
