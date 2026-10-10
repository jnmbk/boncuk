#include <QtTest>
#include <QSignalSpy>
#include "seslisozluk.h"

class TestSesliSozluk : public QObject {
    Q_OBJECT
private slots:
    void testSearch();
};

void TestSesliSozluk::testSearch() {
    SesliSozluk sozluk(nullptr);
    QSignalSpy spy(&sozluk, SIGNAL(found(QString,QList<QList<QVariant>>)));
    
    sozluk.search("test");
    
    QVERIFY(spy.wait(10000)); // wait up to 10 seconds
    QCOMPARE(spy.count(), 1);
    
    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).toString(), QString("test"));
    
    auto results = qvariant_cast<QList<QList<QVariant>>>(arguments.at(1));
    QVERIFY(!results.isEmpty());
}

QTEST_MAIN(TestSesliSozluk)
#include "test_seslisozluk.moc"

