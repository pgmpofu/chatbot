#include "chatbot.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	Chatbot bot("Chatty");
	for (;;) {  // loop forever
		cout << "You> ";
		string input;
		getline(cin, input);  // reads entire line of input

		bot.tell(input);
		string reply = bot.get_reply();
		cout << bot.get_name() << "> " << reply << "\n\n";
		
	} // for
} // main
