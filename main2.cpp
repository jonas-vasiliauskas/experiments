#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

int task(bool *isRunning,const int sleepInMs,const int workInMs,int count){
   int i,c=0;
   time_t startTime = time(NULL);
   while (*isRunning && (count > 0 || count != -1)){
       --count;
       time_t endTime=startTime;
       while (difftime(endTime,startTime)*1000<workInMs){
           for (i=0;i<1000;++i)
               c = (c + c * c) % 256;
           endTime = time(NULL);
       }
       startTime = time(NULL);
       std::this_thread::sleep_for(std::chrono::milliseconds(sleepInMs));
   }
   std::cout<<"Finished thread\n";
   return c;
}

void killerTask(bool *isRunning){
    while (!(*isRunning)){
        std::string inputOption;
        std::cin>>inputOption;
        if (inputOption=="q")
            *isRunning=false;
    }
}

int main(int argC,char **argV){
    if (argC!=4){
         std::cerr<<"Wrong argument count\n";
         return 1;
    }
    bool isRunning=true;
    const int CPU_COUNT = std::thread::hardware_concurrency();
    std::vector<std::thread> taskThreads;
    const int SLEEP_IN_MS= std::stoi(argV[1])*1000;
    const int WORK_IN_MS = std::stoi(argV[2])*1000;
    const int REPETITION_COUNT = std::stoi(argV[3]);
    
    if (WORK_IN_MS <= SLEEP_IN_MS){
        std::cerr<<"Work period must be longer than sleep one\n";
        return 1;
    }
        
    for (int i=0;i<CPU_COUNT;++i)
        taskThreads.push_back(std::thread(task,&isRunning,SLEEP_IN_MS,WORK_IN_MS,REPETITION_COUNT));
    std::thread killerThread(killerTask,&isRunning);
    for (int i=0;i<CPU_COUNT;++i)
        taskThreads[i].join();
    killerThread.join();        
}
