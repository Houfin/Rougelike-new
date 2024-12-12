#include "./messages.h"

Message::Message(int colour, std::string content) : colour(colour), content(content) {
}

void Message::setColour(int new_colour) {
    colour = new_colour;
}

void Message::setContent(std::string new_content) {
    content = new_content;
}

int Message::getColour() {
    return colour;
}

std::string Message::getContent() {
    return content;
}

MessageLog::MessageLog() {}

void MessageLog::addMessage(Message message) {
    messages.push_back(message);
    legacyMessages.push_front(message);
    if (messages.size() > maxLength) {
        messages.pop_front();
    }
}

std::deque<Message> MessageLog::getMessages() {
    previousMessage = 0;
    return messages;
}

std::deque<Message> MessageLog::getOldMessage() {
    previousMessage += 1;

    if (legacyMessages.size() <= 4) return messages;
    if (legacyMessages.size() < 4 + previousMessage) previousMessage -= 1;

    std::cout << previousMessage << std::endl;


    int endIndex = std::min(previousMessage + 4, (int) legacyMessages.size());

    std::deque<Message> selectionOfOldMessages;
    for (int i = previousMessage; i < endIndex; ++i) {
        selectionOfOldMessages.push_front(legacyMessages.at(i));
    }

    return selectionOfOldMessages;
}