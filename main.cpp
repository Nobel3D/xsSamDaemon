#include <xsSamServer/xsmanagerdaemon.h>
#include <xslib/xslib.h>


xsManagerDaemon* daemon;
QString buffer;


int main(int argc, char **argv)
{
    if(argc != 2)
        xsConsole() << "Wrong parameters!" << endl;

    daemon = new xsManagerDaemon();
    daemon->createConfiguration(argv[1]);
    xsConsole() << "Starting Serious Sam Manager Server Daemon on port " + QString::number(MANAGER_PORT) << endl;
    daemon->startServer("new.crt", "new.key");
    do {
        daemon->server->Write(QString("(" + QString::number(daemon->pw->getMaxHit()) + "/" + QString::number(daemon->pw->getHit()) +  ") Enter your password -> ").toUtf8());
        buffer = daemon->format((daemon->server->Read()));
    } while(daemon->login(buffer, SAM_PORT) != OK);
    xsConsole() << "Logged and connected to 127.0.0.1\n";

    while(buffer.compare("quit",Qt::CaseInsensitive) != 0)
    {
        buffer = daemon->format(daemon->server->Read());
        daemon->sam->WriteStream(buffer);
    }
    daemon->server->Disconnect();
    daemon->sam->Close();
    //TODO: CLOSE ALL
    return 0;
}
