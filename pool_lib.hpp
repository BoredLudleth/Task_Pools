#ifndef POOL_LIB_HPP
#define POOL_LIB_HPP

#include <unordered_map>
#include <vector>
#include <deque>
#include <iterator>

template <typename KeyT = int>
class many_pools {
    private:
        size_t size;
        size_t num_of_con_set;

        std::unordered_map<KeyT, std::vector<KeyT>> data;
        std::unordered_map<KeyT, int> connectivity_sets;
        std::unordered_map<int, std::pair<float, int>> volume_and_size_of_set;
        
    public:
        many_pools (size_t sz) : size (sz), num_of_con_set (1) {};

        int& pool_set (KeyT key) {
            return connectivity_sets[key];
        }

        float& set_volume (int set_num) {
            return volume_and_size_of_set[set_num].first;
        }

        int& set_size (int set_num) {
            return volume_and_size_of_set[set_num].second;
        }

        void add_water (int index, float volume) {
            if (pool_set (index) == 0) {
                connectivity_sets[index] = num_of_con_set;
                ++num_of_con_set;
                volume_and_size_of_set[pool_set(index)].second = 1;
            }

            volume_and_size_of_set[pool_set(index)].first += volume;
        }

        void create_pool_set (KeyT first_key) {
            int cur_size = 0;
            int new_comp_num = num_of_con_set;
            ++num_of_con_set;

            std::deque <KeyT> set_of_children;
            set_of_children.push_front(first_key);

            KeyT cur_key = 0;

            while (set_of_children.size () != 0) {
                cur_key = set_of_children.back ();
                set_of_children.pop_back ();

                if (connectivity_sets[cur_key] != new_comp_num) {
                    ++cur_size;
                    connectivity_sets[cur_key] = new_comp_num;
                }

                for (auto it = data[cur_key].begin(); it != data[cur_key].end(); ++it) {
                    if (connectivity_sets[*it] != new_comp_num) {
                        set_of_children.push_front(*it);
                    }
                }
            }

            volume_and_size_of_set[new_comp_num].second = cur_size;
        }

        void connect (int a, int b) {
            data[a].push_back(b);
            data[b].push_back(a);

            if (connectivity_sets[a] == 0) {
                int new_comp_num = num_of_con_set;
                ++num_of_con_set;

                connectivity_sets[a] = new_comp_num;
            }

            if (connectivity_sets[a] != connectivity_sets[b]) {
                float new_volume = volume_and_size_of_set[connectivity_sets[a]].first + volume_and_size_of_set[connectivity_sets[b]].first;

                create_pool_set(a);

                volume_and_size_of_set[pool_set(a)].first = new_volume;
            }
        }
        
        void disconnect (int a, int b) {
            for (auto it = data[a].begin(); it != data[a].end(); ++it) {
                if (*it == b) {
                    data[a].erase(it);
                    break;
                }
            }

            for (auto it = data[b].begin(); it != data[b].end(); ++it) {
                if (*it == a) {
                    data[b].erase(it);
                    break;
                }
            }

            float prev_volume = volume_and_size_of_set[pool_set(a)].first;
            create_pool_set(a);

            if (connectivity_sets[a] != connectivity_sets[b]) {
                float new_volume_a = static_cast<float>(volume_and_size_of_set[pool_set(a)].second) 
                                     / static_cast<float>(volume_and_size_of_set[pool_set(b)].second) 
                                     * volume_and_size_of_set[pool_set(b)].first;
                float new_volume_b = volume_and_size_of_set[pool_set(b)].first - new_volume_a;

                volume_and_size_of_set[pool_set(b)].second = volume_and_size_of_set[pool_set(b)].second 
                                                                                 - volume_and_size_of_set[pool_set(a)].second;

                volume_and_size_of_set[pool_set(a)].first = new_volume_a;
                volume_and_size_of_set[pool_set(b)].first = new_volume_b;
            } else {
                volume_and_size_of_set[pool_set(a)].first = prev_volume;
            }
        };

        float water_in (KeyT a) {
            std::cout << a << "-"<< volume_and_size_of_set[pool_set(a)].first/volume_and_size_of_set[pool_set(a)].second 
                      << " " << pool_set(a) << std::endl;

            return volume_and_size_of_set[pool_set(a)].first
                   / static_cast<float>(volume_and_size_of_set[pool_set(a)].second);
        }

        void show_volume_and_size_of_set (KeyT key) {
            std::cout << key << ": water_volume = " << volume_and_size_of_set[key].first << "; water_elements_ = " << volume_and_size_of_set[key].second << std::endl;
        }    
};

#endif
