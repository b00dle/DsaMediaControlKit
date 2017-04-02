#include "chat_message_model.h"

namespace Web {
namespace App {

ChatMessageModel::ChatMessageModel(QObject *parent)
    : QAbstractTableModel(parent)
    , messages_()
{}

ChatMessageModel::~ChatMessageModel()
{
    ChatMessage* msg = 0;
    while(messages_.size() != 0) {
        msg = messages_.back();
        messages_.pop_back();
        delete msg;
        msg = 0;
    }
}

int ChatMessageModel::rowCount(const QModelIndex&) const
{
    return messages_.size();
}

int ChatMessageModel::columnCount(const QModelIndex&) const
{
    return ChatMessage::getAttributeNames().size();
}

QVariant ChatMessageModel::data(const QModelIndex& index, int) const
{
    if(!indexIsValid(index))
        return QVariant();

    return (*messages_[index.row()])[index.column()];
}

QVariant ChatMessageModel::headerData(int section, Qt::Orientation orientation, int) const
{
    QVariant res;
    if(orientation == Qt::Horizontal) {
        if(section < columnCount() && section >= 0)
            res = QVariant(ChatMessage::getAttributeNames()[section]);
    }
    else {
        if(section < rowCount() && section >= 0)
            res = QVariant(section);
    }
    return res;
}

void ChatMessageModel::addMessage(const ChatMessage message)
{
    messages_.append(new ChatMessage(message));
    emit dataChanged(index(rowCount()-2, 0), index(rowCount()-1, columnCount()));
    emit layoutAboutToBeChanged();
    emit layoutChanged();
    emit messageAdded(message);
}

bool ChatMessageModel::indexIsValid(const QModelIndex &idx) const
{
    return idx.isValid() && idx.column() < columnCount() && idx.row() < rowCount();
}

} // namespace App
} // namespace Web
