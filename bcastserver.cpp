
#include "bcastserver.h"
#include <QWebSocketServer>
#include <QWebSocket>
#include <QDebug>

namespace yshurik {

BcastServer::BcastServer(quint16 port
						 ,bool debug
						 ,QObject * parent)
	:QObject(parent)
	,m_serv(new QWebSocketServer("wsbcast"
								,QWebSocketServer::NonSecureMode
								,this)
	)
	,m_debug(debug)
{
	if (m_serv->listen(QHostAddress::Any, port)) {
		if (m_debug)
			qDebug() << "wsbcast listening on port" << port;
		connect(m_serv, &QWebSocketServer::newConnection
				,this, &BcastServer::onNewConnection);
		connect(m_serv, &QWebSocketServer::closed
				,this, &BcastServer::closed);
	}
}

BcastServer::~BcastServer() {
	m_serv->close();
	qDeleteAll(m_socks.begin(), m_socks.end());
}

void BcastServer::onNewConnection() {
	auto sock = m_serv->nextPendingConnection();
	connect(sock, &QWebSocket::textMessageReceived
			,this, &BcastServer::onTxtMsg);
	connect(sock, &QWebSocket::binaryMessageReceived
			,this, &BcastServer::onBinaryMsg);
	connect(sock, &QWebSocket::disconnected
			,this, &BcastServer::onDisconnected);
	m_socks << sock;
	if (m_debug) qDebug() << "Connected:" << qHash(sock);
}

void BcastServer::onTxtMsg(QString text) {
	auto from = qobject_cast<QWebSocket *>(sender());
	if (m_debug) qDebug() << "Txt recv:" << qHash(from) << text;
	for(auto sock : m_socks) {
		if (!sock) continue;
		if (sock==from) continue;
		sock->sendTextMessage(text);
	}
}

void BcastServer::onBinaryMsg(QByteArray bytes) {
	auto from = qobject_cast<QWebSocket *>(sender());
	if (m_debug) qDebug() << "Bin recv:" << qHash(from) << bytes;
	for(auto sock : m_socks) {
		if (!sock) continue;
		if (sock==from) continue;
		sock->sendBinaryMessage(bytes);
	}
}

void BcastServer::onDisconnected() {
	QWebSocket * sock = qobject_cast<QWebSocket *>(sender());
	if (m_debug) qDebug() << "Disconnected:" << qHash(sock);
	if (sock) {
		m_socks.removeAll(sock);
		sock->deleteLater();
	}
}

} // namespace
