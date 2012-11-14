
#include "SetUrlBlacklist.h"
#include "WebPageManager.h"
#include "WebPage.h"
#include "NetworkAccessManager.h"

SetUrlBlacklist::SetUrlBlacklist(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

void SetUrlBlacklist::start() {
  NetworkAccessManager* networkAccessManager = qobject_cast<NetworkAccessManager*>(page()->networkAccessManager());
  networkAccessManager->setUrlBlacklist(arguments());
  emit finished(new Response(true));
}

