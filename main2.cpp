#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <climits>

int task(bool *isRunning,const int sleepInMs,const int workInMs){
   int i,c=0;
   time_t startTime = time(NULL);
   while (*isRunning){
       time_t endTime=startTime;
       while (difftime(endTime,startTime)*1000<workInMs){
           for (i=0;i<1000;++i)
               c = (c + c * c) % 256;
           endTime = time(NULL);
       }
       startTime = time(NULL);
       std::this_thread::sleep_for(std::chrono::milliseconds(sleepInMs));
   }
   return c;
}

int main(int argC,char **argV){
    if (argC!=3){
         std::cerr<<"Wrong argument count\n";
         return 1;
    }
    bool isRunning=true;
    const int CPU_COUNT = std::thread::hardware_concurrency();
    std::vector<std::thread> taskThreads;
    const int SLEEP_IN_MS= std::stoi(argV[1])*1000;
    const int WORK_IN_MS = std::stoi(argV[2])*1000;
    
    if (WORK_IN_MS <= SLEEP_IN_MS){
        std::cerr<<"Work period must be longer than sleep one\n";
        return 1;
    }
        
    for (int i=0;i<CPU_COUNT;++i)
        taskThreads.push_back(std::thread(task,&isRunning,SLEEP_IN_MS,WORK_IN_MS));
    for (int i=0;i<CPU_COUNT;++i)
        taskThreads[i].detach();
    while (true){
        std::string inputString;    
        std::cin>>inputString;
        if (inputString=="q"){
            isRunning = false;
            break;
        }
    }        
}
