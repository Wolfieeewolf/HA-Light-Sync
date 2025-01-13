#ifndef SECURESETTINGS_H
#define SECURESETTINGS_H

#include <QString>
#include <QByteArray>

class SecureSettings {
public:
    static QString encryptData(const QString &data);
    static QString decryptData(const QString &encryptedData);
    static QString getConfigPath();
    static void ensureConfigDirectory();

private:
    static QByteArray generateKey();
    static QByteArray getStoredKey();
    static void storeKey(const QByteArray &key);
};

#endif // SECURESETTINGS_H