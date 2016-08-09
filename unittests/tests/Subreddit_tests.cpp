#include <gtest/gtest.h>
#include <QUrl>
#include "Subreddit.hpp"

TEST(SubredditConstruction, NameAsParam_getValidJson)
{
    Subreddit news(QString("news"));
    ASSERT_TRUE(news.getJson().isObject());
}