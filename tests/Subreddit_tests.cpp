#include <QtCore/QCoreApplication>
#include "testMacros.hpp"
#include "Subreddit.hpp"

/*

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
        ASSERT_FALSE(title.isEmpty());
    }
}

TEST_F(NewsSubredditTest, getAll25FrontPageCommentCounts) {
    QVector<int> commentCounts = newsSub->getFrontpageCommentCounts();
    EXPECT_EQ(25, commentCounts.count());
    Q_FOREACH(int count, commentCounts) {
        ASSERT_LE(0, count);
    }
}

TEST_F(NewsSubredditTest, getAll25FrontPageScores) {
    QVector<int> scores = newsSub->getFrontpageScores();
    EXPECT_EQ(25, scores.count());
    Q_FOREACH(int score, scores) {
        ASSERT_LE(0, score);
    }
}

TEST_F(NewsSubredditTest, getAll25FrontPageDomains) {
    QList<QUrl> domains = newsSub->getFrontpageDomains();
    EXPECT_EQ(25, domains.count());
    Q_FOREACH(QUrl domain, domains) {
        ASSERT_FALSE(domain.isEmpty());
    }
}

*/
