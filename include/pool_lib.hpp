#ifndef POOL_LIB_HPP
#define POOL_LIB_HPP

#include <unordered_map>
#include <list>
#include <deque>
#include <iterator>

template <typename KeyT = int, typename SetT = int>
class many_pools {
    private:
        size_t size;
        SetT num_of_set;

        std::unordered_map<KeyT, std::list<KeyT>> data;
        std::unordered_map<KeyT, SetT> connectivity_sets;
        std::unordered_map<SetT, std::pair<float, int>> volume_and_size_of_set;

        SetT& pool_set (KeyT& key) {
            return connectivity_sets[key];
        }

        float& set_volume (SetT& set_num) {
            return volume_and_size_of_set[set_num].first;
        }

        int& set_size (SetT& set_num) {
            return volume_and_size_of_set[set_num].second;
        }

        int& pool_set_size (KeyT& index) {
            return set_size (pool_set (index));
        }

        float& pool_set_volume (KeyT& index) {
            return set_volume (pool_set (index));
        }
        
        bool is_null_set (KeyT& index) {
            return pool_set (index) == 0;
        }

        bool is_in_diff_set (KeyT& a, KeyT& b) {
            return pool_set (a) != pool_set (b);
        }

        bool erase_edge_ab (KeyT& a, KeyT& b) {
            for (auto it = data[a].begin(); it != data[a].end(); ++it) {
                if (*it == b) {
                    data[a].erase(it);
                    return true;
                }
            }

            return false;
        }

    public:
        many_pools (size_t sz) : size (sz), num_of_set (0) {};

        void add_water (int index, float volume) {
            if (is_null_set (index)) {
                ++num_of_set;
                pool_set (index) = num_of_set;
                pool_set_size (index) = 1;
            }

            pool_set_volume (index) += volume;
        }

        void create_pool_set (KeyT first_key) {
            SetT prev_pool_set_a = pool_set (first_key);

            int cur_size = 0;
            ++num_of_set;
            SetT new_comp_num = num_of_set;

            std::deque <KeyT> set_of_children;
            set_of_children.push_front(first_key);

            KeyT cur_key = 0;

            while (set_of_children.size () != 0) {
                cur_key = set_of_children.back ();
                set_of_children.pop_back ();

                if (pool_set (cur_key) != new_comp_num) {
                    ++cur_size;
                    pool_set (cur_key) = new_comp_num;
                }

                for (auto it = data[cur_key].begin(); it != data[cur_key].end(); ++it) {
                    if (pool_set (*it) != new_comp_num) {
                        set_of_children.push_front(*it);
                    }
                }
            }

            set_size(new_comp_num) = cur_size;
        }

        void connect (KeyT a, KeyT b) {
            data[a].push_back(b);
            data[b].push_back(a);

            if (is_null_set (a)) {
                ++num_of_set;
                SetT new_comp_num = num_of_set;

                pool_set (a) = new_comp_num;
            }

            if (is_in_diff_set (a, b)) {
                float new_volume = pool_set_volume (a) + pool_set_volume (b);

                create_pool_set(a);

                pool_set_volume (a) = new_volume;
            }
        }
        
        void disconnect (KeyT a, KeyT b) {
            if (a == b) {
                return;
            }

            bool was_way = false;

            if (!erase_edge_ab (a, b)) {
                return;
            }

            erase_edge_ab (b, a);
            
            float prev_volume = pool_set_volume (a);

            create_pool_set(a);

            if (is_in_diff_set (a, b)) {
                float new_volume_a = static_cast<float>(pool_set_size (a)) / static_cast<float>(pool_set_size (b)) * pool_set_volume (b);
                float new_volume_b = pool_set_volume (b) - new_volume_a;

                pool_set_size (b) = pool_set_size (b) - pool_set_size (a);

                pool_set_volume (a) = new_volume_a;
                pool_set_volume (b) = new_volume_b;
            } else {
                pool_set_volume (a) = prev_volume;
            }
        };

        float water_in (KeyT a) {
            // std::cout << a << "-"<< pool_set_volume (a) / pool_set_size (a) << std::endl;

            return volume_and_size_of_set[pool_set(a)].first
                   / static_cast<float>(volume_and_size_of_set[pool_set(a)].second);
        }

        // отладочная функция
        void show_volume_and_size_of_set (int key) {
            std::cout << key << ": water_volume = " << set_volume (key) << "; water_elements_ = " << set_size (key) << std::endl;
        }
};

#endif
