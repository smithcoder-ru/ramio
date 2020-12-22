#include <QApplication>
#include <QTest>
#include "SuperItemTest.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QScopedPointer sit(new SuperItemTest());
	QTest::qExec(sit.data(), argc, argv);
	return 0;
}
