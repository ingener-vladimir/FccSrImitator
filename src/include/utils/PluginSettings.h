#ifndef PLUGINSETTINGS_H
#define PLUGINSETTINGS_H
#include <QUuid>
#include <QTextStream>

struct PluginSettings
{
    QUuid plgUuid;
    QUuid devUuid;
    QString ipMng;
    uint16_t portMng;
    QString ipDev;
    uint16_t portDev;
    int64_t pid;
    bool load;
    QString text;
    bool debug;
    int32_t request_time;

    std::string serializeToJSON () const {
        QString node;
        QTextStream out(&node);

        // serialize plugin UUID
        out << "{";
        out << "\"PLG_UUID\":\"" << plgUuid.toString() << "\"";
        out << ",";
        out << "\"DEV_UUID\":\"" << devUuid.toString() << "\"";
        out << ",";
        out << "\"TEXT\":\"" << text << "\"";
        out << "}";

        return node.toStdString();
    }
};
#endif // PLUGINSETTINGS_H
