/**
 * @file hash.h
 * @brief header file for the class hash_table
 * @version 0.1
 * @date 2022-07-27
 * @copyright Copyright (c) 2022
 */

#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
template <typename Key, typename Value>
class hash_table {
public: // constructors and destructor

	// default constructor
	hash_table();

	// copy constructor
	hash_table(const hash_table<Key, Value>&);

	// move constructor
	hash_table(hash_table<Key, Value>&&); 

	// parametrized constructors
	hash_table(size_t);
	hash_table(const std::initializer_list<std::pair<Key, Value>>&);
	
	// destructor
	~hash_table();

public: // overloaded operators

	// copy operator assignment
	hash_table<Key, Value>& operator=(const hash_table<Key, Value>&); 

	// move operator assignment
	hash_table<Key, Value>& operator=(hash_table<Key, Value>&&);

	// operator plus
	hash_table<Key, Value> operator+(const hash_table<Key, Value>&);

	// operator plus equal
	const hash_table<Key, Value> operator+=(const hash_table<Key, Value>& ht);

	// subscript operator by const
	const Value& operator[](const Key&) const;

	// subscript operator without const
	Value& operator[](const Key&);

	// operator is equal to
	friend bool operator==(const hash_table<Key, Value>& t1, const hash_table<Key, Value>& t2) {
		if (t1.m_table.size() != t2.m_table.size()) {
			return false;
		}
		for (int i = 0; i < t1.m_table.size(); ++i) {
			if (t1.m_table[i] != t2.m_table[i]) {
				return false;
			}
		}
		return true;
	}
	
	// operator not equal to
	friend bool operator!=(const hash_table<Key, Value>& t1, const hash_table<Key, Value>& t2) {
		return !(t1 == t2);
	}

	// operator less
	friend bool operator<(const hash_table<Key, Value>& t1, const hash_table<Key, Value>& t2) {
		if (t1.m_table.size() >= t2.m_table.size()) {
			return false;
		}
		for (int i = 0; i < t1.m_table.size(); ++i) {
			if (t1.m_table[i] >= t2.m_table[i]) {
				return false;
			}
		}
		return true;
	}

	// operator less than or equal to
	friend bool operator<=(const hash_table<Key, Value>& t1, const hash_table<Key, Value>& t2) {
		return (t1 < t2) || (t1 == t2);
	}

	// operator greater
	friend bool operator>(const hash_table<Key, Value>& t1, const hash_table<Key, Value>& t2) {
		if (t1.m_table.size() <= t2.m_table.size()) {
			return false;
		}
		for (int i = 0; i < t1.m_table.size(); ++i) {
			if (t1.m_table[i] <= t2.m_table[i]) {
				return false;
			}
		}
		return true;
	}

	// operator greater than or equal to 
	friend bool operator>=(const hash_table<Key, Value>& t1, const hash_table<Key, Value>& t2) {
		return (t1 > t2) || (t1 == t2);
	}

	// operator stream out(cout)
	friend std::ostream& operator<<(std::ostream& os, const hash_table<Key, Value>& table) {
		for (const auto& list : table.m_table) {
			for (const auto& pair : list) {
				os << "Key : " << pair.first << " Value : " << pair.second << std::endl;
			}
		}
		return os;
	}

public: // main functionnality

	bool empty() const; // checks whether the container is empty

	bool contains(const Key&) const; // checks if the container contains element with specific key

	size_t size() const; // returns the number of elements

	void clear(); // clears the contents

	void insert(const std::pair<Key, Value>&); // inserts elements or nodes

	void emplace(const std::pair<Key, Value>&); // constructs element in-place

	void erase(const Key&); // erases elements

	void swap(hash_table<Key, Value>&); // swaps the contents

	std::pair<Key, Value> extract(const Key&); //  extracts nodes from the container

	void merge(const hash_table<Key, Value>&); // splices nodes from another container

	size_t count(const Key&); // returns the number of elements matching specific key

	Value* find(const Key&); // finds element with specific key

	size_t hash_function(const Key&); // returns function used to hash the keys

	double load_factor() const; // returns average number of elements per bucket

	void rehash(size_t); // reserves at least the specified number of buckets and regenerates the hash table

private:
	std::vector<std::list<std::pair<Key, Value>>> m_table;
};
#include "impl.hpp"
#endif
