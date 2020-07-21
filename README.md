# A Simple Chatbot 

This chatbot has the following functionality:
1. An in-memory data store from which responses are retrieved.
2. A matching algorthim that takes the input, breaks it into separate words and returns responses with the highest match count.
3. If multiple answers are the same level of matching, the chatbot will select a response at random from the list of acceptable responses.
4. It is possible to print all the answers retrieved using the writeToFile method.
5. If no answer is found a default is returned.
