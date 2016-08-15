#include <QtCore/QCoreApplication>
#include "testMacros.hpp"
#include "catch.hpp"
#include "Subreddit.hpp"


TEST_CASE("Construction from subreddit name", "[Subreddit]")
{
    SETUP_Q_CORE_APP
    Subreddit newsSub(QString("news"));

    SECTION("Get correct sub name")
    {
        REQUIRE(newsSub.getName() == "news");
    }

    SECTION("Get frontpage titles")
    {
        QStringList titles = newsSub.getFrontpageTitles();
        REQUIRE(titles.count() == 25);
        Q_FOREACH(QString title, titles) {
            CHECK_FALSE(title.isEmpty());
        }
    }

    SECTION("Get frontpage comment counts") {
        QVector<int> commentCounts = newsSub.getFrontpageCommentCounts();
        REQUIRE(commentCounts.count() == 25);
        Q_FOREACH(int count, commentCounts) {
            CHECK(count >= 0);
        }
    }

    SECTION("Get frontpage scores") {
        QVector<int> scores = newsSub.getFrontpageScores();
        REQUIRE(scores.count() == 25);
        Q_FOREACH(int score, scores) {
            CHECK(score >= 0);
        }
    }

    SECTION("Get frontpage domains") {
        QList<QUrl> domains = newsSub.getFrontpageDomains();
        REQUIRE(domains.count() == 25);
        Q_FOREACH(QUrl domain, domains) {
            CHECK_FALSE(domain.isEmpty());
        }
    }
}
