#pragma once

#include <mutex>
#include <deque>
#include <cstddef>

namespace pr {

// File bornée de T*, thread safe mais non bloquante : pop rend nullptr si la file est vide,
// push rend false si elle est pleine. Le producteur alloue l'objet, le consommateur qui le
// retire le libère, la file libère à sa destruction ce que personne n'a retiré. Pas de nullptr dedans.
// À compléter (TD5) : condition variable, attente bloquante, setBlocking.
template <typename T>
class Queue {
    std::deque<T*> queue_;
    size_t capacity_;
    std::mutex m;
    condition_variable notfull;
    condition_variable notempty;
public:
    explicit Queue(size_t capacity) : capacity_(capacity) {}

    bool push(T* value) {
        std::unique_lock lock(m);
        //if (queue_.size() == capacity_) {
        //    return false;
        //}
        while(queue_.size()==capacity){
		    notFull.wait(lock);//la condition variable 1
	    }
        queue_.push_back(value);
        notempty.notify_one();
        return true;
    }

    T* pop() {
        std::unique_lock lock(m);
        while (queue.empty()){
	    	notempty.wait(lock);
	    }
        //if (queue_.empty()) {
        //    return nullptr; //je bloque aulieu de retourner un truc null ?
        //}
        T* value = queue_.front();
        queue_.pop_front();
        notfull.notify_one();
        return value;
    }

    ~Queue() {
        for (T* p : queue_) delete p;
    }
};

} // namespace pr
