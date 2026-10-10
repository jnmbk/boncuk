#include <QtTest>
#include <QSignalSpy>
#include "sqlitedatabase.h"

class TestSqliteDatabase : public QObject {
    Q_OBJECT
private slots:
    void testAddAndSearch();
};

void TestSqliteDatabase::testAddAndSearch() {
    QCoreApplication::setOrganizationName("boncuk");
    QCoreApplication::setApplicationName("boncuk");
    QSettings settings;
    settings.setValue("add/enabled", true);
    settings.setValue("fatdb", -1);

    SqliteDatabase db(nullptr, "");
    
    QSignalSpy spy(&db, SIGNAL(found(QString,QList<QList<QVariant>>)));
    
    QList<QList<QVariant>> results;
    QList<QVariant> r1; r1 << 1 << "test_en";
    QList<QVariant> r2; r2 << 0 << "test_tr";
    QList<QVariant> r3; r3 << 2 << "test_de";
    results << r1 << r2 << r3;
    
    db.add("testword", results); db.add("testword", results);
    
    db.search("testword");
    
    QCOMPARE(spy.count(), 1);
    QList<QVariant> args = spy.takeFirst();
    QCOMPARE(args.at(0).toString(), QString("testword"));
    
    auto res = qvariant_cast<QList<QList<QVariant>>>(args.at(1));
    QVERIFY(!res.isEmpty());
}

QTEST_MAIN(TestSqliteDatabase)
#include "test_sqlite.moc"
