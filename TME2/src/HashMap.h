#pragma once

#include <vector>
#include <forward_list>
#include <utility>
#include <cstddef>

template<typename K, typename V>
class HashMap {
public:
    // Entry stores a const key and a mutable value
    struct Entry {
        const K cle_;
        V value_;
        Entry(K cle, V value):cle_(cle), value_(value){}
    };

    using Bucket = std::forward_list<Entry>;
    using Table  = std::vector<Bucket>;
    using WordCount = std::pair<std::string, int>;
    using Buckets = std::vector<Bucket>;

    // Construct with a number of buckets (must be >= 1)
    HashMap(std::size_t nbuckets = 1024) : buckets(nbuckets){}

    // Return pointer to value associated with key, or nullptr if not found.
    // Only iterate the appropriate bucket.
    V* get(const K& key){
        size_t h = std::hash<K>()(key);
        Bucket &b = buckets[h%buckets.size()];
        for(Entry & e : b){
            if(e.cle_ == key){
                return & e.value_;
            }
        }
        return nullptr;
    }

    // Insert or update (key,value).
    // Returns true if an existing entry was updated, false if a new entry was inserted.
    bool put(const K& key, const V& value){
        size_t h = std::hash<K>()(key);
        Bucket &b = buckets[h%buckets.size()];
            //on a la clé
            for (auto &noeud : b) {
                if(noeud.cle_ == key ){
                    noeud.value_ = value;//mise a jour
                    return true;
                }
            }
            b.push_front(Entry(key,value));
            count_++;
            return false;
        }

    // Current number of stored entries
    std::size_t size() const{
        return buckets_.size();//c'est un vecteur donc on a le droit de size
    }

    // Convert table contents to a vector of key/value pairs.
    std::vector<std::pair<K,V>> toKeyValuePairs() const{
        std::vector<std::pair<K,V>> resultat;
        for(auto & element : buckets){
            for(auto & noeud : element){
                resultat.emplace_back(noeud.cle_,noeud.value_);
            }
        }
        return resultat;
    }

    // Optional: number of buckets
    // std::size_t bucket_count() const;

private:
    Table buckets_;
    Buckets buckets;
    std::size_t count_ = 0;
};
