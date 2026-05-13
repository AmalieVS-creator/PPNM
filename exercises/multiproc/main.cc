#include<thread>
#include<functional>
#include<string>
#include<iostream>

struct data { int start,end; double sum; };

void harm(data& p){
	int start=p.start,end=p.end;
	std::cout<<"harm: summing from "<<start<<" to "<<end<<" ...\n";
	double sum=0;
	for (int i=start; i<end; i++) sum+=1.0/i;
	std::cout<<"harm: sum from "<<start<<" to "<<end<<"="<<sum<<"\n";
	p.sum=sum;
	}

int main(int argc, char** argv){
	int nterms=(int)1e7, nthreads=1;
	for(int i=0;i<argc;i++){
		std::string arg=argv[i];
		if(arg=="-nterms" && i+1<argc) nterms=(int)std::stod(argv[++i]);
		if(arg=="-nthreads" && i+1<argc) nthreads=std::stoi(argv[++i]);
	}

	std::vector<std::thread> threads;
	threads.reserve(nthreads);
	std::vector<data> parameters(nthreads);
	for(int i=0; i<nthreads; i++){
		parameters[i].start=1+(nterms/nthreads)*i;
		parameters[i].end  =1+(nterms/nthreads)*(i+1);
		threads.emplace_back(harm,std::ref(parameters[i]));
		}

	for(std::thread& thread : threads) thread.join();
	double sum=0;
	for(auto p : parameters) sum+=p.sum;

	std::cout <<"main: harmonic sum from "<<1<<" to " <<nterms << "=" << sum <<std::endl;

return 0;
}