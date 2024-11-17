#pragma once
#include "crt/allocation/allocation.h"
#include "pair.h"

constexpr float MAX_TABLE_LOAD = 0.75f;

template<typename K, typename V>
class c_hash_table {
private:
	using hash_pair = pair_t<K, V>;

	int size{ 5 };
	int elements_count{ 0 };

	struct node_t {
		hash_pair value{};
		node_t* next{ nullptr };

		node_t() {}
		node_t(hash_pair&& val) : value(std::forward<hash_pair>(val)) {}
		node_t(hash_pair val) : value(val) {}
	};

	struct linked_list_t {
		node_t* head{ nullptr };

		void add(hash_pair value) {
			node_t* p = (node_t*)allocation::malloc(sizeof(node_t));
			*p = node_t(value);

			if (head == nullptr) {
				head = p;
				return;
			}

			auto current = head;
			while (current->next)
				current = current->next;

			current->next = p;
		}

		node_t* find(const K& key) {
			node_t* p = head;
			while (p) {
				if (p->value.first == key)
					return p;

				p = p->next;
			}

			return nullptr;
		}

		void print_all_nodes() {
			node_t* temp = head;
			while (temp) {
				
				temp = temp->next;
			}
		}

		void remove_head() {
			node_t* temp = head;
			head = head->next;
			allocation::free(temp, sizeof(node_t));
		}

		void remove_end() {
			node_t* temp = head;
			node_t* next{};
			while (temp->next) {
				if (temp->next->next == nullptr) {
					next = temp->next;
					temp->next = temp->next->next;
					allocation::free(next, sizeof(node_t));
					break;
				}
				else
					temp = temp->next;
			}
		}

		void remove_node(const K& key) {
			node_t* temp{};
			if (head->value.first == key) {
				remove_head();
			}
			else {
				node_t* p = head;
				while (p->next) {
					if (p->next->value.first == key) {
						temp = p->next;
						p->next = p->next->next;
						allocation::free(temp);
						break;
					}
					else
						p = p->next;
				}
			}
		}

		void remove_all() {
			node_t* temp = head;
			node_t* next{};

			while (temp) {
				next = temp->next;
				allocation::free(temp);
				temp = next;
			}
			head = nullptr;
		}

		void copy_from(linked_list_t& list) {
			auto p = list.head;
			while (p) {
				add(p->value);
				p = p->next;
			}
		}
	};

	using iter = linked_list_t*;
	using const_iter = const linked_list_t*;

	linked_list_t* arr{};
public:
	c_hash_table() {
		arr = (linked_list_t*)allocation::malloc(sizeof(linked_list_t) * size);
	}

	~c_hash_table() {
		for (int i = 0; i < size; ++i)
			arr[i].remove_all();

		allocation::free(arr);
	}

	iter begin() {
		return &arr[0];
	}

	iter end() {
		return &arr[size];
	}

	void print_all() {
		for (int i = 0; i < size; ++i) {
		//	printf("%d st iter of hash map \n", i);
			arr[i].print_all_nodes();
		}
	}

	constexpr int abs(int number) {
		if (number < 0)
			return -number;

		return number;
	}

	int get_hash_for_key(const K& key) {
		std::hash<K> hash_func{};
		int result = hash_func(key);
		return abs(result);
	}

	int get_index(const K& key, int amt) {
		return get_hash_for_key(key) % amt;
	}

	bool contains(int index, const K& key) {
		return arr[index].find(key) != nullptr;
	}

	void add(const K& key, V value) {
		int index = get_index(key, size);
		if (contains(index, key))
			return;

		// too much elements
		// do rehash
		float load_amount = static_cast<float>(elements_count) / static_cast<float>(size);
		if (load_amount >= MAX_TABLE_LOAD) {
			// prepare new array with rehashed elements
			// use old data from current array 

			linked_list_t* new_array = (linked_list_t*)allocation::malloc(sizeof(linked_list_t) * size * 2);
			for (int i = 0; i < size; ++i) {
				auto array_node = arr[i];
				auto p = array_node.head;
				while (p) {
					int new_index = get_index(p->value.first, size * 2);
					new_array[new_index].add(p->value);

					p = p->next;
				}
			}

			// clear current array 
			for (int i = 0; i < size; ++i)
				arr[i].remove_all();

			allocation::free(arr);
			arr = nullptr;

			// extend array size for next rehash
			size *= 2;

			// copy data from prepared array 
			arr = new_array;
		}
		else {
			arr[index].add(pair_t{ key, value });
			++elements_count;
		}
	}

	linked_list_t& get_bucket(const K& key) {
		int index = get_index(key, size);
		return arr[index];
	}

	V& get(const K& key) {
		auto& bucket = get_bucket(key);
		auto node = bucket.find(key);
		if (node)
			return node->value.second;

		// just a placeholder
		V temp = {};
		return temp;
	}

	void remove(const K& key) {
		auto& bucket = get_bucket(key);
		bucket.remove_node(key);
	}

	void remove_head(const K& key) {
		auto& bucket = get_bucket(key);
		bucket.remove_head();
	}

	void remove_last(const K& key) {
		auto& bucket = get_bucket(key);
		bucket.remove_end();
	}

	V& operator[](const K& key) {
		add(key, 0);
		return get(key);
	}
};
