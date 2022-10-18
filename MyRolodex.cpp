

//
#include "MyRolodex.hpp"
#include "MyHashTable.hpp"
#include "Address.hpp"


/**
 * TODO: Finish the implementation for this class
 */


//	More includes?


//
namespace CPSC131::MyRolodex
{
	/// Your welcome /// Thank you~
	MyRolodex::MyRolodex() {}
	
	/**
	 * Return true if a person exists in the Rolodex
	 */
	bool MyRolodex::exists(std::string name) const
	{
		// Call exists() from MyHashTable to go through and check for a person is in Rolodex
		return table_.exists(name);
	}
	
	/**
	 * Allow the user to add an address using its parts.
	 * This should probably just call on the other overload
	 */
	void MyRolodex::add(std::string name, std::string line1, std::string line2, std::string city, std::string state, int zip, std::string country)
	{
		// Create an adress for user to enter
		// Call on the other overload
		Address user_address;
		user_address.line1 = line1;
		user_address.line2 = line2;
		user_address.city = city;
		user_address.state = state;
		user_address.zip = zip;
		user_address.country = country;
		table_.add (name, user_address);
	}
	
	/**
	 * Add an entry into the Rolodex
	 * The person's name is the key, and their Address is the value.
	 * The Address comes in the form of the Address struct, defined in another source file.
	 */
	void MyRolodex::add(std::string name, Address address)
	{
		// Call add() from MyHashTable to add an entry into the Rolodex
		table_.add(name, address);	
	}
	
	/**
	 * Return an address structure associated with a person
	 */
	Address MyRolodex::get(std::string name) const
	{
		// Get an address structure of a person
		return table_.get(name);
	}
	
	/**
	 * Remove a person from the Rolodex
	 */
	void MyRolodex::remove(std::string name)
	{
		// Call remove() from MyHashTable to remove a person from the Rolodex
		table_.remove(name);
	}
	
	/**
	 * Clear the Rolodex of all information.
	 * (Hint: The table also has this method)
	 */
	void MyRolodex::clear()
	{
		// Call clear() from MyHashTable to clear all the Rolodex's information
		table_.clear();	
	}
	
	/**
	 * Return true if the Rolodex is empty, false otherwise
	 */
	bool MyRolodex::empty()
	{	
		// Call empty() from MyHashTable to see if the Rolodex is empty
		return table_.empty();
	}
	
	/**
	 * Return the number of entries in this Rolodex
	 */
	size_t MyRolodex::size()
	{
		// Call size() from MyHashTable to return the size
		return table_.size();
	}
}
