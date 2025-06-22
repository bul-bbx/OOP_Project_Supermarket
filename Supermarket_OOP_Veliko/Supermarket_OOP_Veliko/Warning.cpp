#include "Warning.h"
using namespace std;

Warning::Warning()
{
    id = -1;
    senderId = -1;
    receiverId = -1;
    severity = 0;
}

Warning::Warning(Warning& const other)
{
    id = other.id;
    senderId = other.senderId;
    receiverId = other.receiverId;
    description = other.description;
    severity = other.severity;
}

Warning::Warning(int _id, int _senderId, int _receiverId, MyString _description, int _severity)
{
    id = _id;
    senderId = _senderId;
    receiverId = _receiverId;
    description = _description;
    severity = _severity;
}

int Warning::getSenderId()
{
    return senderId;
}

int Warning::getReceiverId()
{
    return receiverId;
}

MyString Warning::getDescription()
{
    return description;
}

int Warning::getId()
{
    return id;
}

int Warning::getSeverity()
{
    return severity;
}

void Warning::printWarning()
{
    cout << "Warning id: " << id << endl;
    cout << "Warning sender Id: " << senderId << endl;
    cout << "Warning receiver Id: " << receiverId << endl;
    cout << "Warning description: " << description.data << endl;
    cout << "Warning severity: " << severity << endl;
}
