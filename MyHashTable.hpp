#ifndef MY_HASH_TABLE_HPP
#define MY_HASH_TABLE_HPP


/**
 * TODO: Complete this class!
 */


/// Your welcome /// Thank you~
#include <forward_list>
#include <functional>
#include <memory>
#include <string>


//	More includes ... ?
#include <stdexcept>
#include <iostream>

///	Begin our class namespace
namespace CPSC131::MyHashTable
{
	//
	template<class VTYPE>
	class MyHashTable
	{
		//
		public:
			
			//
			static constexpr size_t DEFAULT_CAPACITY = 1024;
			static constexpr size_t ULLONG_WRAP_AT = 4294967295;
			
			/**
			 * Constructor
			 * 
			 * Probably easiest to do the following:
			 * 
			 *   1. Call on setCapacity() to set the table's capacity
			 */
			MyHashTable(size_t capacity = MyHashTable::DEFAULT_CAPACITY)
			{
				// Create table's capacity
				setCapacity(capacity);
			}
			
			/**
			 * Copy constructor
			 */
			MyHashTable(const MyHashTable& other)
			{
				// Copy all the variables
				this->capacity_ = other.capacity_;
				this->size_ = other.size_;
				this->n_collisions_ = other.n_collisions_;
			}
			
			/**
			 * Destructor
			 * 
			 * Deallocate the table (array of std::forward_list 's), and set the table to nullptr
			 * Don't double-deallocate if the table is already a null pointer
			 */
			~MyHashTable()
			{
				// Check if table isn't nullptr
				if (table_ != nullptr) {
					// Deallocate the table
					delete[] table_;
					// Set the table to nullptr
					table_ = nullptr;
				}
				// Reset all variables to 0
				this->capacity_ = 0;
				this->size_ = 0;
				this->n_collisions_ = 0;
			}
			
			/**
			 * Should return the capacity_ of this hash table
			 * Meaning, the total number of rows in this hash table
			 * Doesn't discern between used/unused/collided rows
			 */
			size_t capacity()
			{
				return capacity_;
			}
			
			/**
			 * Should return the number of items currently in the hash table
			 */
			size_t size()
			{
				return size_;
			}
			
			/**
			 * Return true if the table is empty, false otherwise
			 */
			bool empty()
			{
				// Check for if table is empty
				if (size_ == 0) {
					return true; // Table is empty
				}
				else {
					return false; // Table is not empty
				}
			}
			
			/**
			 * Should return the number of collisions currently present in the hash table
			 */
			size_t n_collisions()
			{
				return n_collisions_;
			}
			
			/**
			 * Set the capacity for this table.
			 * Changes the total number of hash table rows available.
			 * 
			 * Existing entries should survive the change,
			 * 	so you probably want to do the following:
			 * 
			 *  1. Keep the existing table array pointer in a temporary pointer
			 *  
			 *  2. Re-initialize 'this' to contain a new empty table of the right capacity
			 *  
			 *  3. The temporary pointer should now contain the OLD data (old table),
			 *     while 'this' contains the brand new table of the new size.
			 * 
			 *  4. Iterate through all key/value pairs in the old data (temp pointer).
			 * 
			 *  5. For each key/value pair in the old data, call this->add() to insert
			 *     properly into the new table.
			 *  
			 *  6. Deallocate the old table by calling `delete []` on the temporary pointer.
			 * 
			 * Don't forget to check whether the current table is a nullptr before you
			 *  decide to do iterations!
			 */
			void setCapacity(size_t c)
			{
				// Existing table array pointer in a temporary pointer
				std::forward_list<std::pair<std::string, VTYPE>> *temp = table_;
				// New empty table of capacity
				size_t store_capacity = capacity_;
				// Creates new table
				table_ = new std::forward_list<std::pair<std::string, VTYPE>>[c];
				// Set the old capacity to new capacity
				this->capacity_ = c;
				// Reset size of table and number of collisions to 0.
				this->size_ = 0;
				this->n_collisions_ = 0;
				// Iterate through all key/value pairs in the store(old) capacity
				for ( size_t i = 0; i < store_capacity; i++ ) {
					// For each key/value pair in the old data
					for (auto itr = temp[i].begin(); itr != temp[i].end(); itr++) {
						// Dereference the iterator
						auto pair = *itr;
						// Call this->add to insert a new table
						this->add(pair.first, pair.second);
					}
				}
				// Deallocate the old table
				delete [] temp;
			}
			
			///	Your welcome /// Thank you~
			unsigned long long int hash(std::string key) const
			{
				return this->midSquareHash(key);
			}
			
			/**
			 * Implement the "modified mid square" hash function,
			 * as described in the instructions.
			 */
			unsigned long long int midSquareHash(std::string key) const
			{
				// Start with sum of 1
				unsigned long long int sum = 1;
				// Iterate over each character of the key
				for (size_t i = 0; i < key.size(); i++) {
					// Cast the character to unsigned long long int
					char value = key[i];
					// Multiply the sum by the value of current character
					sum = sum * value;
					// Keep the sum under control by applying a modulo against MyHashTable::ULLONG_WRAP_AT
					sum = sum % MyHashTable::ULLONG_WRAP_AT;	
				}
				// Square the sum
				sum = sum * sum;
				// Keep middle digit of the sum to get hash code
				std::string middle_digit = std::to_string(sum);
				// Create substring to be half of the original length
				std::string substr_middle = middle_digit.substr( middle_digit.size() / 4 , middle_digit.size() / 2 );
				// Convert string back to unsigned long long int by using stoull
				unsigned long long int convert_back = std::stoull(substr_middle);
				// Apply a modulo against the current capacity of the table
				return convert_back % capacity_; 
			}
			
			/**
			 * Implement your own custom hash functions to compete on the Gradescope Leaderboard!
			 * Four stubs are provided to make experimentation a little easier.
			 * Only the best hash function will count towards the leaderboard.
			 */
			unsigned long long int myCustomHashFunction1(std::string key) const
			{
				return this->midSquareHash(key);
			}
			unsigned long long int myCustomHashFunction2(std::string key) const
			{
				// Start with sum of 1
				unsigned long long int sum = 1;
				unsigned long long int value;
				// Iterate over each character of the key
				for (size_t i = 0; i < key.size(); i++) {
					/* Cast the character to unsigned long long int
					 Wrap the result of mid square by 777 (Follow example in INSTRUCTION.md)
					*/
					value = 777 *(unsigned long long int)key[i];
					// Multiply the sum by triple value of current character
					sum = sum * value * value * value;
					// Keep the sum under control by applying a modulo against MyHashTable::ULLONG_WRAP_AT
					sum = sum % MyHashTable::ULLONG_WRAP_AT;	
				}
				// Cube the sum
				sum = sum * sum * sum;
				// Keep middle digit of the sum to get hash code
				std::string middle_digit = std::to_string(sum);
				// Create substring to be half of the original length
				std::string substr_middle = middle_digit.substr( middle_digit.size() / 64 , middle_digit.size() / 2 );
				// Convert string back to unsigned long long int by using stoull
				unsigned long long int convert_back = std::stoull(substr_middle);
				// Apply a modulo against the current capacity of the table
				return convert_back % capacity_; 
			}
			unsigned long long int myCustomHashFunction3(std::string key) const
			{
				return 0; 
			}
			unsigned long long int myCustomHashFunction4(std::string key) const
			{
				return 0;
			}
			
			/**
			 * Return true if a key exists in the table, or false otherwise.
			 */
			bool exists(std::string key) const
			{
				// Create variable that could store key
				unsigned long long int store = hash(key);
				// Iterate through the table
				for (auto itr = table_[store].begin(); itr != table_[store].end(); itr ++) {
					// Dereference the iterator
					auto check_exists = *itr;
					// Check if key exists in the table
					if (check_exists.first == key) {
						return true; // Key exists
					}
				}
				return false; // Key does not exist
			}
			
			/**
			 * Add a key/value pair to this table.
			 * If the key already exists, throw a runtime_error.
			 */
			void add(std::string key, VTYPE value)
			{
				// Call exists function to check if key already exist then throw a runtime_error
				if (exists(key)) {
					throw std::runtime_error("Key already exists.");
				}
				// Code reference from slide #37
				// Create variable that could store key
				unsigned long long int store_value = hash(key);
				// Increase the number of collisions if table is not empty
				if (!table_[store_value].empty()) {
					n_collisions_++;
				}
				// Create pair for key and value
				std::pair<std::string, VTYPE> pair(key,value);
				// Add key/value pair to the table
				table_[store_value].push_front(pair);
				// Adjust the size
				size_++;
			}
			
			/**
			 * Should return a reference to the VTYPE value associated to the provided key.
			 * If the key/value pair isn't in the table, a runtime_error should be thrown.
			 */
			VTYPE& get(std::string key) const
			{
				// Call exists function to check if key isn't in the table then throw a runtime_error
				if (!exists(key)) {
					throw std::runtime_error("Key/Value pair is not in the table.");
				}
				// Create variable that could store key
				unsigned long long int value = midSquareHash(key);
				// Iterate through the table
				for (auto itr = table_[value].begin(); itr != table_[value].end(); itr++) {
					// Dereference the iterator
					auto pair = *itr;
					// Check for pair is in the key
					if (pair.first == key ) {
						// Return a reference to the VTYPE value associated to the provided key
						return (*itr).second;
					}
				}
			}
			
			
			/**
			 * Remove a key/value pair that corresponds to` the provided key.
			 * If no such key exists, throw a runtime_error.
			 */
			void remove(std::string key)
			{
				// Call exists function to check when no key exists, then throw a runtime_error
				if (!exists(key)) {
					throw std::runtime_error("Key does not exists.");
				}
				/*
				unsigned long long int store = hash(key);
				store = store % this->capacity_;
				table_[store].erase_after();
				*/
				
				// Create variable that could store key
				unsigned long long int value = hash(key);
				// Iterate through the table 
				// Use before_begin for element to be erase at the beginning of the list
				for (auto itr = table_[value].before_begin(); itr != table_[value].end(); itr++) {
					// Set a key to beginning of the table
					auto key_begin = table_[value].begin();
					// Check if first element is in the key
					// Once the peak-ahead iterator see's the element to be delete, then call erase_after()
					if ((*key_begin).first == key) {
						table_[value].erase_after(itr);
					// Else add more key
					} else {
						key_begin++;
					}
				}
				// Adjust the size
				size_ --;
			}
			
			/**
			 * Remove all entries in this table
			 * Iterate over each table row and call clear on the row's list
			 */
			void clear()
			{
				// Iterate over each table row
				for ( size_t i = 0; i < capacity_; i++ ) {
					// Call clear on the row's list
					table_[i].clear();
				}
				// Adjust the size
				size_ = 0;
			}
			
			/**
			 * Assignment Operator
			 */
			MyHashTable<VTYPE>& operator=(const MyHashTable<VTYPE>& other)
			{	
				return *this;
			}
			
		//
		private:
			
			/**
			 * Keeps track of the capacity of this hash table
			 * (total number of rows in the table, whether used or not)
			 * (does not care about collisions)
			 */
			size_t capacity_ = 0;
			
			/**
			 * Keeps track of the total number of items currently in
			 * the hash table
			 */
			size_t size_ = 0;
			
			/**
			 * Keeps track of the number of collisions currently present in the table
			 */
			size_t n_collisions_ = 0;
			
			/**
			 * The actual hash table.
			 * We'll make this a fixed-sized array,
			 *   but dynamically allocated so we can resize whenever we need.
			 * 
			 * Try to imagine each table row is actually a complete forward_list.
			 * In a perfect situation where a table has no collisions, each list
			 *   will simply contain one item.
			 * 
			 * One "item" in this case refers to an std::pair<std::string, VTYPE>,
			 *   where the first part of the pair is the key and the second
			 *   is the value (of type VTYPE).
			 */
			std::forward_list<std::pair<std::string, VTYPE>> * table_ = nullptr;
			
	};
}













#endif
