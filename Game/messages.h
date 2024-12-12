#include <string>
#include <deque>
#include <SFML/Graphics.hpp>
#include <iostream>

class Message {
    private:
    int colour;
    std::string content;

    public:
    Message(int, std::string); 
    std::string getContent();
    int getColour();
    void setContent(std::string);
    void setColour(int);
};

class MessageLog {
    private:
    const int maxLength = 4;
    std::deque<Message> messages;
    std::deque<Message> legacyMessages;
    int previousMessage = 0;

    public:
    MessageLog();
    void addMessage(Message);
    std::deque<Message> getMessages();
    std::deque<Message> getOldMessage();
};