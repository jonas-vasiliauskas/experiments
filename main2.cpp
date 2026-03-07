#include <vector>
#include <thread>

void task(){
   
}

int main(){
    const int CPU_COUNT = std::thread::hardware_concurrency();
    std::vector<std::thread> taskThreads;
    for (int i=0;i<CPU_COUNT;++i)
        taskThreads.push_back(std::thread(task));
    for (int i=0;i<CPU_COUNT;++i)
        taskThreads[i].detach();        
}
