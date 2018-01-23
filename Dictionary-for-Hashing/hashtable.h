/**
 *  Basic hash table implementation
 *   Aaron S. Crandall - 2017 <acrandal@gmail.com>
 *
 */

#ifndef __HASH_H
#define __HASH_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;
/*
	private:
		void rehash();
		int hash_function(KEYTYPE key);
		
	public:
		bool insert(KEYTYPE key, VALTYPE val);
		bool contains(KEYTYPE key);
		int remove(KEYTYPE key);
		VALTYPE & find(KEYTYPE key);
		int size();            // Elements currently in table
		bool empty();          // Is the hash empty?
		float load_factor();   // Return current load factor
		void clear();          // Empty out the table
		int bucket_count();    // Total number of buckets in table
*/

template <typename KEYTYPE, typename VALTYPE>
class Hashtable
{
	private:
		/**
		 *  Rehash the table into a larger table when the load factor is too large
		 */
		vector<list<Word>> lists;
		int tableSize;
		int numOfElements;

		void rehash() 
		{
			vector<list<Word>> oldlists=lists;
			int prime=nextPrime(2*lists.size());
			lists.resize(prime);
			for(auto & thisList : lists)
			{
				thisList.clear();
			}
			numOfElements=0;
			tableSize=prime;
			for(auto & thisList : oldlists)
			for( auto & x : thisList)
			insert(x.myword, x);
		}

		bool isPrime(int n)
		{
			for(int i=2; i<=n/2;i++)
			{
				if (n%i==0)
				return false;
			}
			return true;
		}

		int nextPrime(int oldPrime)
		{
			int nextPrime=oldPrime;
			bool found=false;
			while(!found)
			{
				nextPrime++;
				if(isPrime(nextPrime))
				{
					found=true;
				}
			}
			return nextPrime;
		}

		/**
		 *  Function that takes the key (a string or int) and returns the hash key
		 *   This function needs to be implemented for several types it could be used with!
		 */
		int hash_function(int key) {
			return key%tableSize;
		}

		int hash_function(string key) {
			unsigned int hashval=0;
			for(char ch : key)
			{
				hashval=37*hashval+ch;
			}
			return hashval % tableSize;

		}

		 
	public:
		/**
		 *  Basic constructor
		 */
		Hashtable( int startingSize = 101 )
		{
			numOfElements = 0;
			tableSize = startingSize;
			lists.resize(101);
		}

		/**
		 *  Add an element to the hash table
		 */
		bool insert(KEYTYPE key, VALTYPE val) {
			 int index = hash_function(key);
			 bool IsInList=false;
			 // if item is not in the list
			 // hash the key to determine which bucket the key would be stored in.
			if( !lists[index].empty())
			{
				for(auto item : lists[index])// item takes on each successive element of list on that index
			 							//at list[index] an object is stored and item is an object here
			 {

				 if(item.myword == key ) //if the same word/key is found then replace the definition
				 {
					 item.definition=val.definition;
					 return true;
				 }
				
			 }
			}				
				 lists[index].push_back(val);
				 numOfElements++;
				 if(load_factor()>1.0)
				 {
					 rehash();
				 }
				 return true;
				 
			 
			 //if item is in the list
		}

		/**
		 *  Return whether a given key is present in the hash table
		 */
		bool contains(KEYTYPE key) {
			int index=hash_function(key);
			if(!lists.empty())
			{
			 for(auto item : lists[index])// item takes on each successive element of list on that index
			 							//at list[index] an object is stored and item is an object here
			 {

				 if(item.myword == key ) //if the same word/key is found then replace the definition
				 {
					 return true;
				 }
				
			 }
			}

			return false;
			 
		}


		/**
		 *  Completely remove key from hash table
		 *   Returns number of elements removed
		 */
		int remove(KEYTYPE key) {
			// Doesn't actually remove anything yet
			int index=hash_function(key);
			for(unsigned int i = 0; i < key.length(); i++)
			key[i] = toupper(key[i]);

			if(!empty())
			{
			 for(auto item : lists[index])// item takes on each successive element of list on that index
			 							//at list[index] an object is stored and item is an object here
			 {

				 if(item.myword == key ) //if the same word/key is found then replace the definition
				 {
					 lists[index].remove(item);
					 numOfElements--;
					 return 1;
				 }
				
			 }
			 return 0;
			}
			cout<<"List is Empty\n";
		}
		/**
		 *  Searches the hash and returns a pointer
		 *   Pointer to Word if found, or nullptr if nothing matches
		 */
		VALTYPE *find(KEYTYPE key) {
			int index=hash_function(key);
			if(!empty())
			{
			 for(auto &item : lists[index])// item takes on each successive element of list on that index
			 							//at list[index] an object is stored and item is an object here
			 {

				 if(item.myword == key ) //if the same word/key is found then replace the definition
				 {
					 return &item;
				 }
				
			 }
			 
			}
			return nullptr;
			
		}

		/**
		 *  Return current number of elements in hash table
		 */
		int size() {
			
			return numOfElements;
		}

		/**
		 *  Return true if hash table is empty, false otherwise
		 */
		bool empty() {
			if (numOfElements==0)
			return true;
			return(false);
		}

		/**
		 *  Calculates the current load factor for the hash
		 */
		float load_factor() {
			//return _hash.load_factor();
			return (float)numOfElements/(float)tableSize;
		}

		/**
		 *  Returns current number of buckets (elements in vector)
		 */
		int bucket_count() {
			return tableSize;
		}

		/**
		 *  Deletes all elements in the hash
		 */
		void clear() {
			// Does nothing yet
			for(auto & thisList : lists)
			{
				thisList.clear();
			}
			numOfElements=0;
		}


		void load(string filename)
		{
		ifstream myfile;
		//filename='"'+filename+'"';
		string line,temp;
		string tempWord, tempDef;
		int found, curly,square;
		myfile.open(filename.c_str()); // this in_stream (fstream) the "filename" to open.
		if (!myfile.is_open())
		{
			cout << "Could not open file to read.""\n"; // if the open file fails.
			return;
		}
		else
		{
			getline(myfile, line);
			getline(myfile, line);
			while(!myfile.eof()) 
			{
				
				getline(myfile, line);
				curly=line.find('}'); //find first quote : word
				square=line.find(']'); //find first quote : word
				
				if (curly>8  || square>8)
				{
				found=line.find('\"'); //find first quote : word
				temp=line.substr(found+1,line.length());
				found=temp.find('\"');//find second quote : word
				temp=temp.substr(found+1,line.length());

				found=temp.find('\"'); //find first quote : myWord
				temp=temp.substr(found+1,line.length());
				found=temp.find('\"'); //find seond quote : word
				tempWord=temp.substr(0,found);
				temp=temp.substr(found+1,line.length());
				
				found=temp.find('\"'); //find first quote : definition
				temp=temp.substr(found+1,temp.length()); 
				found=temp.find('\"'); //find second quote : definition
				temp=temp.substr(found+1,temp.length()); 
				
				found=temp.find('\"'); //find first quote : myDef
				temp=temp.substr(found+1,temp.length());
				found=temp.find('\"'); //find seond quote : myDef
				tempDef=temp.substr(0,found);
				
				Word myWord(tempWord, tempDef);
				insert(tempWord,myWord);
				}}
		
		
		}
		myfile.close();

	}
	void unload(string filename)
	{
	ifstream myfile2;
	//filename='"'+filename+'"';
	string line,temp;
	string tempWord, tempDef;
	int found;
	myfile2.open(filename.c_str()); // this in_stream (fstream) the "filename" to open.
	if (!myfile2.is_open())
	{
		cout << "Could not open file to read.""\n"; // if the open file fails.
		return;
	}
	else
	{
		getline(myfile2, line);
		getline(myfile2, line);
		while(!myfile2.eof()) 
		{
			
			getline(myfile2, line);
			found=line.find('\"'); //find first quote : word
			temp=line.substr(found+1,line.length());
			found=temp.find('\"');//find second quote : word
			temp=temp.substr(found+1,line.length());

			found=temp.find('\"'); //find first quote : myWord
			temp=temp.substr(found+1,line.length());
			found=temp.find('\"'); //find seond quote : word
			tempWord=temp.substr(0,found);
			temp=temp.substr(found+1,line.length());
			
			found=temp.find('\"'); //find first quote : definition
			temp=temp.substr(found+1,temp.length()); 
			found=temp.find('\"'); //find second quote : definition
			temp=temp.substr(found+1,temp.length()); 
			
			found=temp.find('\"'); //find first quote : myDef
			temp=temp.substr(found+1,temp.length());
			found=temp.find('\"'); //find seond quote : myDef
			tempDef=temp.substr(0,found);
			
			Word myWord(tempWord, tempDef);
			remove(tempWord);
			
		}
	
	}
	myfile2.close();
}
		void print(int num )
		{
			if(num==0)
			{
			
				int i=0;
				int j=0;
				if(!lists.empty())
				{
					for (int i=0; i< tableSize ; i++)
					{
						
						for (auto item: lists[i])
							{
							cout<<item.myword<<endl;
							j++;
							}
						
					}
				}
			}
			else
			{
				int i=0;
				int j=0;
				if(!lists.empty())
				{
					for (int i=0; i< tableSize ; i++)
					{
						
						for (auto item: lists[i])
							{
							if (j>=num)
							return;
							cout<<item.myword<<endl;
							j++;
							}
						
					}
				}
			}
			
	
		}
		void define(string word)
		{
			for(unsigned int i = 0; i < word.length(); i++)
			  word[i] = toupper(word[i]);
			  int hash_key=hash_function(word);
			if(!lists.empty())
			{

					
					for (auto item: lists[hash_key])
						{
						if(item.myword==word)
						{
							cout<<item.definition<<endl;
						break;
					}
						
				}
					
				
			}
		}
		void randomPrint()
		{
			int key,index;
			while(true)
			{
			
			 key = (rand ()% lists.size())+1;
			index=hash_function(key);
			if(!lists[index].empty())
			{
			 for(auto &item : lists[index])// item takes on each successive element of list on that index
			 							//at list[index] an object is stored and item is an object here
			 {
				cout<< "Random word generated is: "<<item.myword<<endl;
				return;
				 
				
			 }
			}
			
		}
	}

};


#endif
