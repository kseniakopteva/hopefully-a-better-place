#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <thread>
#include <vector>
#include <chrono>
#include <ctype.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include "commands.cpp"

using namespace std;

void type_text(const string& text)
{
	// loop through each character in the text
	for (size_t i = 0; i < text.size(); ++i)
	{
		// output one character
		// flush to make sure the output is not delayed
		cout << text[i] << flush;

		// sleep 60 milliseconds
		this_thread::sleep_for(chrono::milliseconds(50));
	}
}

void word_wrap(char* buffer, const char* string, int line_width) {
    
 /*
   This function takes a string and an output buffer and a desired width. It then copies
   the string to the buffer, inserting a new line character when a certain line
   length is reached.  If the end of the line is in the middle of a word, it will
   backtrack along the string until white space is found.
 */

    int i = 0;
    int k, counter;

    while (i < strlen(string))
    {
        // copy string until the end of the line is reached
        for (counter = 1; counter <= line_width; counter++)
        {
            // check if end of string reached
            if (i == strlen(string))
            {
                buffer[i] = 0;
                //return buffer;
                type_text(buffer);
                return;
            }
            buffer[i] = string[i];
            // check for newlines embedded in the original input
            // and reset the index
            if (buffer[i] == '\n')
            {
                counter = 1;
            }
            i++;
        }
        // check for whitespace
        if (isspace(string[i]))
        {
            buffer[i] = '\n';
            i++;
        }
        else
        {
            // check for nearest whitespace back in string
            for (k = i; k > 0; k--)
            {
                if (isspace(string[k]))
                {
                    buffer[k] = '\n';
                    // set string index back to character after this one
                    i = k + 1;
                    break;
                }
            }
        }
    }
    buffer[i] = 0;

    //return buffer;
    type_text(buffer);
}

void print(const char* message) {
    char result[300];
    word_wrap(result, message, 80);
}

void startingMsg() {
    //char result[250];
    //const char* message = "You wake up in a small dark room. The walls are made out of wood and the sunlight pierces through the loose boards. You see tables with instruments, it looks like a shed. There is a door with a note on it.";

    //word_wrap(result, message, 80);
    print("You wake up in a small dark room. The walls are made out of wood and the sunlight pierces through the loose boards. You see tables with instruments, it looks like a shed. There is a door with a note on it.\n");
};


int main() {

    string action;
    string destination;
	string playerInput;
	startingMsg();

	bool exitStatus = false;
	while (true)
	{

		vector<string> result;      

        getline(cin, playerInput, '\n');
        if (playerInput.empty()) {
            continue;
        }


        int wordCount = 1;
        for (int i = 0; playerInput[i] != '\0'; i++)
        {
            if (playerInput[i] == ' ')
                wordCount++;
        }

        /*
        cout << "You said \"" << playerInput << "\"" << endl;
        cout << "There are " << wordCount << " words!" << endl;
        */

        if (wordCount >= 2) {
            boost::split(result, playerInput, boost::is_any_of(" "));
            action = result[0];
		    destination = result[1];
        }
        else {
            action = playerInput;
        }

		
		if (action == "quit") {
            break;
		}
		else if (action == "look") {
			//executeLook( ... );
			cout << "You have no eyes!" << endl;
		}
		else if (action == "go") {
			cout << "You can't see where to go! Because you have no eyes!" << endl;
        }
		else {
			cout << "What?.." << endl;
		}

	}




	return 0;
}