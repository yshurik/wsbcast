#ifndef BcastServer_H
#define BcastServer_H

#include <QList>
#include <QObject>
#include <QByteArray>

class QWebSocket;
class QWebSocketServer;

namespace yshurik {

class BcastServer : public QObject {
	Q_OBJECT
	QWebSocketServer * m_serv;
	QList<QWebSocket *> m_socks;
	bool m_debug;
public:
	explicit BcastServer(quint16 port
						 ,bool debug =false
						 ,QObject * p =nullptr);
	~BcastServer();

signals:
	void closed();

private slots:
	void onNewConnection();
	void onTxtMsg(QString message);
	void onBinaryMsg(QByteArray message);
	void onDisconnected();
};

} // namespace
#endif // BcastServer_H
