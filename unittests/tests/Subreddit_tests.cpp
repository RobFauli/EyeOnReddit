#include <gtest/gtest.h>
#include <QtCore/QCoreApplication>
#include "Subreddit.hpp"
#include "testMacros.hpp"

TEST(SubredditConstruction, NameAsParam_getCorrectName)
{
    SETUP_Q_CORE_APP
    Subreddit news(QString("news"));
    ASSERT_STREQ("news", news.getName().toStdString().c_str());
}

TEST(SubredditConstruction, NameAsParam_getValidJson)
{
    SETUP_Q_CORE_APP
    Subreddit news(QString("news"));
    ASSERT_TRUE(news.getJson().isObject());
}

class NewsSubredditTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
        SETUP_Q_CORE_APP
        newsSub = std::make_unique<Subreddit>(QString("news"));
    }

    std::unique_ptr<Subreddit> newsSub;
};

TEST_F(NewsSubredditTest, getAll25FrontpageTitles) {
    QStringList titles = newsSub->getFrontpageTitles();
    EXPECT_EQ(25, titles.count());
    Q_FOREACH(QString title, titles) {
        ASSERT_LT(0, title.size());
    }
}