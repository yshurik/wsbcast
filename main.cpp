#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>

#include "bcastserver.h"
using namespace yshurik;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QCommandLineParser opts;
	opts.setApplicationDescription(
		"wsbcast: Web Socket broadcast server, from one client to all other.");
	opts.addHelpOption();

	QCommandLineOption dbg_opt(
		QStringList() << "d" << "debug"
		,a.tr("Debug output [default: off].")
	);
	opts.addOption(dbg_opt);

	QCommandLineOption port_opt(
		QStringList() << "p" << "port"
		,a.tr("Port for wsbcast [default: 8086].")
		,a.tr("port"), QLatin1Literal("8086")
	);
	opts.addOption(port_opt);

	opts.process(a);
	bool debug = opts.isSet(dbg_opt);
	if (debug) { qDebug() << "Debug is on"; }
	int port = opts.value(port_opt).toInt();

	auto server = new BcastServer(port, debug);
	a.connect(server, &BcastServer::closed, &a, &QCoreApplication::quit);

	return a.exec();
}
