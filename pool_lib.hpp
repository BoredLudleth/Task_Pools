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
        size_t num_of_con_component = 1;

        std::unordered_map<KeyT, std::vector<KeyT>> data;
        std::unordered_map<KeyT, int> connectivity_components;
        std::unordered_map<int, std::pair<float, int>> volume_and_size_of_con_comp;
    public:
        many_pools (size_t sz) : size (sz) {
            num_of_con_component = 0;
        };

        void add_water_in_pool (int index, float volume) {
            if (connectivity_components[index] == 0) {
                connectivity_components[index] = num_of_con_component;
                ++num_of_con_component;
                volume_and_size_of_con_comp[connectivity_components[index]].second = 1;
            }

            volume_and_size_of_con_comp[connectivity_components[index]].first += volume;
        };

        void refill_component (KeyT first_key) {
            int cur_size = 0;
            int new_comp_num = num_of_con_component;
            num_of_con_component++;

            std::deque <KeyT> component;
            component.push_front(first_key);

            KeyT cur_key = 0;

            while (component.size () != 0) {
                cur_key = component.back ();
                component.pop_back ();
                cur_size++;
                connectivity_components[cur_key] = new_comp_num;

                for (auto it = data[cur_key].begin(); it != data[cur_key].end(); ++it) {
                    if (connectivity_components[*it] != new_comp_num) {
                        component.push_front(*it);
                    }
                }
            }

            volume_and_size_of_con_comp[new_comp_num].second = cur_size;
        }

        void connect_pools (int a, int b) {
            data[a].push_back(b);
            data[b].push_back(a);

            if (connectivity_components[a] != connectivity_components[b]) {
                float new_volume = volume_and_size_of_con_comp[connectivity_components[a]].first + volume_and_size_of_con_comp[connectivity_components[b]].first;
                refill_component(a);
                volume_and_size_of_con_comp[connectivity_components[a]].first = new_volume;
            }
        };
        
        void destroy_pools_connection (int a, int b) {
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
            

            refill_component(a);
            if (connectivity_components[a] != connectivity_components[b]) {
                float new_volume_a = static_cast< float >(volume_and_size_of_con_comp[connectivity_components[a]].second) / static_cast< float >(volume_and_size_of_con_comp[connectivity_components[b]].second) * volume_and_size_of_con_comp[connectivity_components[b]].first;
                float new_volume_b = volume_and_size_of_con_comp[connectivity_components[b]].first - new_volume_a;
                volume_and_size_of_con_comp[connectivity_components[b]].second = volume_and_size_of_con_comp[connectivity_components[b]].second - volume_and_size_of_con_comp[connectivity_components[a]].second;
                volume_and_size_of_con_comp[connectivity_components[a]].first = new_volume_a;
                volume_and_size_of_con_comp[connectivity_components[b]].first = new_volume_b;
            }

            // удалить в data a из листа b и b из листа a
        };

        float water_volume_in_pool (int a) {
            std::cout << volume_and_size_of_con_comp[connectivity_components[a]].first/volume_and_size_of_con_comp[connectivity_components[a]].second << std::endl;
            return volume_and_size_of_con_comp[connectivity_components[a]].first/volume_and_size_of_con_comp[connectivity_components[a]].second;
        };
        
        ~many_pools () {};

    
};

#endif