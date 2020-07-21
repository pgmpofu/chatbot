/*
* @author Patience Mpofu
* @date 20 July 20202
*/
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <map>
#include <fstream>

using namespace std;

class Chatbot
{
    map<string, int> keywordCount;
    map<string, string> inputResponseMap;
    vector<string> responses;
    string name;
    string question;
    int maxCount;

public:
    Chatbot(string bot_name)
    {
        name = bot_name;
    }

public:
    string get_name()
    {
        return name;
    }

public:
    vector<string> createResponses()
    {
        vector<string> responses;
        responses.insert(responses.end(), "Unfortunately, we do not accept credit card payments for regular tuition or fees.");
        responses.insert(responses.end(), "Your direct deposit summary is as follows: Bank Name - RBC, Account Number - 8636262");
        responses.insert(responses.end(), "Your have 1 listed bank account(s).");
        responses.insert(responses.end(), "Your refund will be paid out in 7 business days.");
        responses.insert(responses.end(), "Contact the finance office to make a payment");
        responses.insert(responses.end(), "Your next payment is due at the start of the fall term in September");
        responses.insert(responses.end(), "You can run reports in GoSFU");
        responses.insert(responses.end(), "Your financial award is currently being processed");
        responses.insert(responses.end(), "Hi, how can I help you today");
        responses.insert(responses.end(), "Nice talking to you. Goodbye! Have a good day");
        responses.insert(responses.end(), "Unfortunately, I cannot help you. Please contact the finance office on 111-222-3333");
        return responses;
    }

public:
    vector<string> getKeywords(string input)
    {
        vector<string> words;
        string word = "";

        for (int i = 0; i < input.length() - 1; i++)
        {
            if (input[i] != ' ' || input[i] == '\0')
            {
                word += input[i];
            }
            else
            {
                if (word != " ")
                {
                    word + input[i];
                }
                words.insert(words.end(), word);
                word = "";
            }
        }

        return words;
    }

    void tell(string input)
    {
        question = input;
        responses = createResponses();
        vector<string> keywords = getKeywords(input);
        //Count how many keywords can be associated with a response
        for (vector<string>::iterator keywordIt = keywords.begin(); keywordIt != keywords.end(); keywordIt++)
        {
            for (vector<string>::iterator responseIt = responses.begin(); responseIt != responses.end(); responseIt++)
            {
                if (responseIt->find(*keywordIt) != string::npos)
                {
                    keywordCount[*responseIt]++;
                }
            }
        }
    }

    string get_reply()
    {
        vector<string> matches;
        maxCount = INT_MIN;
        //Print all responses with the same key count
        for (map<string, int>::iterator highestCountIt = keywordCount.begin(); highestCountIt != keywordCount.end(); highestCountIt++)
        {
            if (highestCountIt->second > maxCount)
            {
                maxCount = highestCountIt->second;
            }
        }

        if (keywordCount.size() <= 0)
        {
            matches.insert(matches.end(), responses.at(responses.size() - 1));
            inputResponseMap[question] = responses.at(responses.size() - 1);
            writeToFile(inputResponseMap);
            return responses.at(responses.size() - 1);
        }
        else
        {

            for (map<string, int>::iterator it = keywordCount.begin(); it != keywordCount.end(); it++)
            {
                if (it->second == maxCount)
                {
                    matches.insert(matches.end(), it->first);
                    inputResponseMap[question + to_string(rand())] = it->first;
                }
            }

            int index = rand() % matches.size();
            writeToFile(inputResponseMap);
            return matches.at(index);
        }

        return "";
    }

    void writeToFile(map<string, string> inputResponseMap)
    {
        ofstream conversation;
        conversation.open("conversation.txt");
        for (map<string, string>::iterator it = inputResponseMap.begin(); it != inputResponseMap.end(); it++)
        {
            conversation << "Input: " << it->first << endl;
            conversation << "Answer: " << it->second << endl;
        }
        conversation.close();
    }
};
