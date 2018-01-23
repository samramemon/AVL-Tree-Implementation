/*
 *  dictionary.h -- A hash-based dictionary for searching definitions
 *   Copyright 2017 - Aaron S. Crandall <acrandal@gmail.com>
 */

#ifndef __DICT_H
#define __DICT_H

#include "hashtable.h"
#include "word.h"
#include <string>
#include <iostream>
#include <fstream>


class Dictionary
{

	private:
		Hashtable<string, Word> _dict;  // Primary dictionary store

	
	

	public:
		Dictionary()	// Default constructor
		 { }

	/**
	 *  Run the main dictionary user interface
	 */
	
	void run_ui() 
	{
		// print out header
		cout << "+------------------------------------------+" << endl;
		cout << "|-- Welcome to the best dictionary evar! --|" << endl;
		cout << "+------------------------------------------+" << endl;

		string line;
		cout << " Enter command (^D or EOF quits): ";

		// read in user input until eof
		while (getline(cin, line)) 
		{
			cout << endl << " --debug-- Entered command: " << line << endl;
			string space=" ";
			char quote='\"';
			string command;
			string temp;
			string word, def;
			int found1, found2;
			found1 = line.find(space);
			cout<<found1<<endl;
			if(found1>0)
			command = line.substr(0,found1);
			else 
			command=line;
			if (command == "help")
			{
				cout<<" call help"<<endl;
			}
			else if(command =="remove")
			{
				found1=line.find(space);
	
				if(found1>0) //if there is quotes around word
				{
	
					temp=line.substr(found1+1, line.length());
					_dict.remove(temp);
				}
				else  //if there is not quote around word
				{
				cout<<"the word was not found"<<endl;
				}
			}
			else if(command == "add")
			{
				found1++;
				if(line.at(found1)!=quote) //if there is not quote around word
				{
					temp=line.substr(found1,line.length());//copy word without first quote
					found1=temp.find(space);
					word=temp.substr(0,found1);
				//	cout<<"word is "<<word<<endl;	
	
				}
				else if(line.at(found1)==quote) //if there is quotes around word
				{
				temp=line.substr(found1+1,line.length());//copy word without first quote
			//	cout<<"the first temp is "<<temp<<endl;
				found1=temp.find(space);
				word=temp.substr(0,found1-1);
			//	cout<<"word is "<<word<<endl;
				}
				found1=temp.find(space);
				found1++;
				if(temp.at(found1)==quote) 
				{
					temp=temp.substr(found1+1,temp.length()); // copy def without quotes
					found2=temp.find(quote);
			//		cout<<"the second temp is "<<temp<<endl;
					def=temp.substr(0, found2);
			//		cout<<"def is "<<def<<endl;
				}
				else if(temp.at(found1)!=quote) //if there is not quote around word
				{
					temp=temp.substr(found1,temp.length());//copy word without first quote
					def=temp;
			//		cout<<"def is "<<def<<endl;
				}
			
	
			for(unsigned int i = 0; i < word.length(); i++)
			  word[i] = toupper(word[i]);
			
			cout<<word<<endl;
			Word newWord(word,def);
			_dict.insert(word,newWord);
		}
		else if(command =="define")
		{
			found1=line.find(space);
			
			if(found1>0) //if there is quotes around word
			{
			
							temp=line.substr(found1+1, line.length());
							_dict.define(temp);
						}
						else  //if there is not quote around word
						{
						cout<<"the word was not found"<<endl;
						}
		}
		else if(command == "print")
		{
			int num;
			found1=line.find(space);

			if(found1>0) //if there is quotes around word
			{
			temp=line.substr(found1+1, line.length());
			num=stoi(temp);
			cout<<"num is "<<num<<endl;
			_dict.print(num);
			}
			else  //if there is not quote around word
			{
				_dict.print(0);
			}
			
			
		}
		else if(command == "quit")
		{
			exit(0);
		}
		else if(command == "size")
		{
			cout<<"size is"<< _dict.size()<<endl;
		}
		else if(command =="random")
		{
			
			_dict.randomPrint();
		}
		else if(command =="load")
		{
			found1=line.find(space);

			if(found1>0) //if there is quotes around word
			{

				temp=line.substr(found1+1, line.length());
				_dict.load(temp);
			}
			else  //if there is not quote around word
			{
			cout<<"the filename was not found"<<endl;
			}
		}
		else if(command =="unload")
		{
			found1=line.find(space);

			if(found1>0) //if there is quotes around word
			{

				temp=line.substr(found1+1, line.length());
				_dict.unload(temp);
			}
			else  //if there is not quote around word
			{
			cout<<"the filename was not found"<<endl;
			}
		}

			cout << "Enter command: ";
	}
	}

};



#endif
