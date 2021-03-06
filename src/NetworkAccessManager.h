#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QStringList>

class NetworkAccessManager : public QNetworkAccessManager {

  Q_OBJECT

  struct NetworkResponse {
    int statusCode;
    QList<QNetworkReply::RawHeaderPair> headers;
    NetworkResponse() : statusCode(0) { }
  };

  public:
    NetworkAccessManager(QObject *parent = 0);
    void addHeader(QString key, QString value);
    void resetHeaders();
    void setUserName(const QString &userName);
    void setPassword(const QString &password);
    int statusFor(QUrl url);
    const QList<QNetworkReply::RawHeaderPair> &headersFor(QUrl url);
    void setUrlBlacklist(QStringList urlBlacklist);

  protected:
    QNetworkReply* createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &req, QIODevice * outgoingData);
    QString m_userName;
    QString m_password;
    QList<QUrl> m_urlBlacklist;


  private:
    QHash<QString, QString> m_headers;
    QHash<QUrl, NetworkResponse> m_responses;
    bool isBlacklisted(QUrl url);
    QHash<QUrl, QUrl> m_redirectMappings;

  private slots:
    void provideAuthentication(QNetworkReply *reply, QAuthenticator *authenticator);
    void finished(QNetworkReply *);

  signals:
    void requestCreated(QByteArray &url, QNetworkReply *reply);
};
