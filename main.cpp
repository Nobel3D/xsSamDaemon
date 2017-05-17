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
        daemon->serverWrite("(" + QString::number(daemon->pw->getHit()) + "/" + QString::number(daemon->pw->getMaxHit()) +  ") Enter your password -> ");
        buffer = daemon->serverRead();
    } while(!daemon->login(buffer, SAM_PORT));
    xsConsole() << "Logged and connected to 127.0.0.1\n";

    daemon->start();

    while(buffer.compare("quit",Qt::CaseInsensitive) != 0)
    {
        buffer = daemon->serverRead();
        xsConsole() << "> " << buffer << endl;
        daemon->samWrite(buffer);
    }
    //TODO: REPEAT FOR NEXT CONNECTION
    daemon->server->Disconnect();
    daemon->sam->Close();
    //TODO: CLOSE ALL
    return 0;
}
