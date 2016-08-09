#include <gtest/gtest.h>
#include <QtCore/QCoreApplication>
#include "Subreddit.hpp"
#include "testMacros.hpp"

TEST(SubredditConstruction, NameAsParam_getValidJson)
{
    SETUP_Q_CORE_APP
    Subreddit news(QString("news"));
    ASSERT_TRUE(news.getJson().isObject());
}