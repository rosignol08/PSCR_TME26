#pragma once
#include "Queue.h"
#include <vector>
#include <thread>
namespace pr {

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};

void poolworker(Queue<Job>&queue){
	while(true){
		Job * j = queue.pop();
		if(!j) break;
		j->run();
		delete j;
	}
}

class Pool {
	public :
		bool started;
		Queue<Job> queue;
		std::vector<std::thread> workers;
		Pool(int taille_queue) : queue(taille_queue), started(false){}
		void start(int nbthread) {
			started = true;
			for(int i = 0; i < nbthread ; ++i){
				workers.push_back(std::thread (poolworker, std::ref(queue)));
			}
		}
		//ajoute tache dans la queue
		void submit(Job* job){
			queue.push(job);
		}
		void stop(){
			for(auto &t : workers){
				submit(nullptr);
			}
			for(auto &t : workers){
				t.join();
			}
			workers.clear();
			started = false;
		}
	~Pool(){
		if(started){stop();}
	}
};

// Job concret : exemple

/**
class SleepJob : public Job {
	int calcul (int v) {
		std::cout << "Computing for arg =" << v << std::endl;
		// traiter un gros calcul
		this_thread::sleep_for(1s);
		int ret = v % 255;
		std::cout << "Obtained for arg =" << arg <<  " result " << ret << std::endl;
		return ret;
	}
	int arg;
	int * ret;
public :
	SleepJob(int arg, int * ret) : arg(arg), ret(ret) {}
	void run () {
		* ret = calcul(arg);
	}
	~SleepJob(){}
};
**/

}
