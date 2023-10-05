#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;
 
int number;
int count = 1;
int iteration = 0;

void printOddNumbers(){
    while(count<number){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{return (count % 2 == 1); });
        if(count % 2 == 1){
            cout<<"Thread a : "<< count << endl;
            count++;
            cv.notify_one();
        }
        else{
            ++iteration;
            cout<<iteration<<endl;
        }
    }
}

void printEvenNumbers(){
    while(count<number){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{return (count % 2 == 0); });
        if(count % 2 == 0){
            cout<<"Thread b : "<< count << endl;
            count++;
            cv.notify_one();
        }
        else{
            ++iteration;
            cout<<iteration<<endl;
        }     
    }
} 

int main(){
    cout<<"Enter the number : "<<endl;
    cin>>number;

    thread thread_a(printOddNumbers);
    thread thread_b(printEvenNumbers);
    
    thread_a.join();
    thread_b.join();
 

    return 0;
}
