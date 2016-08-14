#include "Submonitor.hpp"

//SubMonitor::SubMonitor(QObject *parent) : QObject(parent)
//{
//
//}

SubMonitor::SubMonitor(std::shared_ptr<Subreddit> &sub, QObject *parent)
    : QObject(parent), m_sub(sub)
{

}
