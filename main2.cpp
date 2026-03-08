#include <iostream>
#include <string>
#include <vector>
#include <thread>

void task(bool *isRunning){
   int i,c=0;
   while (*isRunning)
   for (i=0;i<1000;++i)
       c = (c + c * c) % 256;
}

int main(){
    bool isRunning=true;
    const int CPU_COUNT = std::thread::hardware_concurrency();
    std::vector<std::thread> taskThreads;
    for (int i=0;i<CPU_COUNT;++i)
        taskThreads.push_back(std::thread(task,&isRunning));
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
