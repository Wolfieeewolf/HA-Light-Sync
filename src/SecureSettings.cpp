#include "SecureSettings.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QCryptographicHash>
#include <QDataStream>
#include <QRandomGenerator>

QString SecureSettings::getConfigPath()
{
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    return QDir(configDir).filePath("homeassistant_config.ini");
}

void SecureSettings::ensureConfigDirectory()
{
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(configDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
}

QByteArray SecureSettings::generateKey()
{
    QByteArray key;
    const int keyLength = 32; // 256 bits
    key.resize(keyLength);
    
    for(int i = 0; i < keyLength; ++i) {
        key[i] = static_cast<char>(QRandomGenerator::global()->bounded(256));
    }
    
    return key;
}

QByteArray SecureSettings::getStoredKey()
{
    QString keyPath = QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation))
                         .filePath(".key");
    QFile keyFile(keyPath);
    
    if (!keyFile.exists()) {
        QByteArray newKey = generateKey();
        storeKey(newKey);
        return newKey;
    }
    
    if (keyFile.open(QIODevice::ReadOnly)) {
        QByteArray storedKey = keyFile.readAll();
        keyFile.close();
        return storedKey;
    }
    
    return QByteArray();
}

void SecureSettings::storeKey(const QByteArray &key)
{
    QString keyPath = QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation))
                         .filePath(".key");
    QFile keyFile(keyPath);
    
    if (keyFile.open(QIODevice::WriteOnly)) {
        keyFile.write(key);
        keyFile.close();
    }
}

QString SecureSettings::encryptData(const QString &data)
{
    if (data.isEmpty()) return QString();
    
    QByteArray key = getStoredKey();
    QByteArray dataBytes = data.toUtf8();
    QByteArray encrypted;
    
    // Simple XOR encryption
    for(int i = 0; i < dataBytes.size(); ++i) {
        encrypted.append(dataBytes[i] ^ key[i % key.size()]);
    }
    
    return QString::fromLatin1(encrypted.toBase64());
}

QString SecureSettings::decryptData(const QString &encryptedData)
{
    if (encryptedData.isEmpty()) return QString();
    
    QByteArray key = getStoredKey();
    QByteArray encrypted = QByteArray::fromBase64(encryptedData.toLatin1());
    QByteArray decrypted;
    
    // Simple XOR decryption
    for(int i = 0; i < encrypted.size(); ++i) {
        decrypted.append(encrypted[i] ^ key[i % key.size()]);
    }
    
    return QString::fromUtf8(decrypted);
}