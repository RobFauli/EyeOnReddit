#include <QtCore/QCoreApplication>
#include "testMacros.hpp"
#include "catch.hpp"
#include "Subreddit.hpp"


TEST_CASE("Construction from subreddit name", "[Subreddit]")
{
    SETUP_Q_CORE_APP
    Subreddit newsSub(QString("news"));

    SECTION("Get frontpage titles")
    {
        QStringList titles = newsSub.getFrontpageTitles();
        REQUIRE(titles.count() == 25);
        Q_FOREACH(QString title, titles) {
            REQUIRE_FALSE(title.isEmpty());
        }
    }

    SECTION("Get frontpage comment counts") {
        QVector<int> commentCounts = newsSub.getFrontpageCommentCounts();
        REQUIRE(commentCounts.count() == 25);
        Q_FOREACH(int count, commentCounts) {
            REQUIRE(count >= 0);
        }
    }

    SECTION("Get frontpage scores") {
        QVector<int> scores = newsSub.getFrontpageScores();
        REQUIRE(scores.count() == 25);
        Q_FOREACH(int score, scores) {
            REQUIRE(score >= 0);
        }
    }

    SECTION("Get frontpage domains") {
        QList<QUrl> domains = newsSub.getFrontpageDomains();
        REQUIRE(domains.count() == 25);
        Q_FOREACH(QUrl domain, domains) {
            REQUIRE_FALSE(domain.isEmpty());
        }
    }
}
