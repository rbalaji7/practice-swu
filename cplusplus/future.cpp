#include<future>
#include<iostream>


int factorial(std::future<int>& f){
	int res = 1;

	int n = f.get();

	for(int i = n;i>1;i--){
		res*=i;
	}
	std::cout << " res : " <<res <<std::endl;
	return res;
}

int main(){
	int x;
	std::promise<int> p;
	std::future<int> f = p.get_future();

	std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));
	//do something
	std::cout<<"waiting ";
	p.set_value(4);
	
	x = fu.get();
	std::cout <<"in main : "<<x<<std::endl;

	return 0;

}
