#include "nencryptionkit.h"
#include <QDebug>
#include <memory>
#include <QFile>
#include "botan.h"

using namespace Botan;

NEncryptionKit::NEncryptionKit(QObject *parent):QObject(parent)
{
    //设置默认密码
    mPassword = getSHAHash("iamdaodaoliang(nami_salt)");
}

QString NEncryptionKit::getMD5Hash(const QString &param_data)
{
    return QString(QCryptographicHash::hash(param_data.toLocal8Bit(),QCryptographicHash::Md5).toHex());
}

QString NEncryptionKit::getSHAHash(const QString &param_data)
{
    return QString(QCryptographicHash::hash(param_data.toLocal8Bit(),QCryptographicHash::Sha3_512).toHex());
}

bool NEncryptionKit::getByKaiser(QString &param_data, qint8 param_key)
{
    if(param_data.isEmpty()){
        return false;
    }
    for(int temp_index = 0; temp_index != param_data.size();++temp_index){
        char tempChar = param_data.at(temp_index).toLatin1();
        int tempValue = 0;
        if(tempChar >= 0x30 && tempChar <= 0x39){
            tempValue = (tempChar - '0' + param_key);
            tempChar = (tempValue >= 0) ? (tempValue % 10 + '0') : (tempValue % 10 + 0x3a);
        } else if (tempChar >= 0x41 && tempChar <= 0x5a) {
            tempValue = (tempChar - 'A' + param_key);
            tempChar = (tempValue >= 0) ? (tempValue % 26 + 'A') : (tempValue % 26 + 0x5b);
        } else if (tempChar >= 0x61 && tempChar <= 0x7a) {
            tempValue = (tempChar - 'a' + param_key);
            tempChar = (tempValue >= 0) ? (tempValue % 26 + 'a') : (tempValue % 26 + 0x7b);
        }
        param_data[temp_index] = QChar(tempChar);
    }
    return true;
}

bool NEncryptionKit::createRSAKey(QString paramPubKeyFile, QString paramPriKeyFile)
{
    try{
        Botan::AutoSeeded_RNG rng;
        Botan::RSA_PrivateKey privateKey(rng, 1024);
        QString temp_pri(Botan::X509::PEM_encode(privateKey).c_str());
        QString temp_pub(Botan::PKCS8::PEM_encode(privateKey).c_str());

        if(QFile::exists(paramPriKeyFile)){
            QFile::remove(paramPriKeyFile);
        }
        QFile innerFile(paramPriKeyFile);
        if(innerFile.open(QFile::ReadWrite)){
            innerFile.write(temp_pub.toLocal8Bit());
            innerFile.flush();
        }
        innerFile.close();

        if(QFile::exists(paramPubKeyFile)){
            QFile::remove(paramPubKeyFile);
        }
        QFile innerFile_1(paramPubKeyFile);
        if(innerFile_1.open(QFile::ReadWrite)){
            innerFile_1.write(temp_pri.toLocal8Bit());
            innerFile_1.flush();
        }
        innerFile_1.close();
        return true;
    } catch(Exception &e){
        qDebug()<<e.what();
        return false;
    }
}

bool NEncryptionKit::getEncryptByRSA(QString paramDataSource, QByteArray &paramDataDest, QString paramPubKeyPath)
{
    try{
        AutoSeeded_RNG rng;
        X509_PublicKey* temp_pub = X509::load_key(paramPubKeyPath.toStdString());
        PK_Encryptor_EME enc(*temp_pub, "EME1(SHA-256)");
        SecureVector<byte> en = enc.encrypt(paramDataSource.toStdString().c_str(), paramDataSource.toStdString().size(), rng);
        QByteArray temp;
        for (uint i = 0; i < en.size(); i++)
        {
            temp[i] = en[i];
        }
        paramDataDest = temp;
        return true;
    } catch(Exception &e){
        qDebug()<<e.what();
        return false;
    }
}

bool NEncryptionKit::decryptionByRSA(QByteArray paramDataSource, QString &paramDataDest, QString paramPriKeyPath)
{
    try{
        AutoSeeded_RNG rng;
        PKCS8_PrivateKey* temp_pri = PKCS8::load_key(paramPriKeyPath.toStdString(),rng);
        PK_Decryptor_EME dec(*temp_pri, "EME1(SHA-256)");
        SecureVector<byte> temp_mem;
        temp_mem.resize(paramDataSource.size());
        for(uint i = 0; i< paramDataSource.size(); ++i){
            temp_mem[i] = paramDataSource[i];
        }
        SecureVector<byte> re = dec.decrypt(temp_mem,temp_mem.size());
        QByteArray temp;
        for (uint i = 0; i < re.size(); i++)
        {
            temp[i] = re[i];
        }
        paramDataDest = QString(temp);
        return true;
    } catch(Exception &e){
        qDebug()<<e.what();
        return false;
    }
}

bool NEncryptionKit::getEncryByAES(QString paramSource, string &paramDest)
{
    try
    {
        HashFunction* hash = get_hash("MD5");
        SymmetricKey key = hash->process(mPassword.toStdString());
        SecureVector<byte> raw_iv = hash->process('0'+ mPassword.toStdString());
        InitializationVector iv(raw_iv, 16);
        Pipe pipe(get_cipher("AES-128/CBC/PKCS7", key, iv, ENCRYPTION));
        pipe.process_msg(paramSource.toStdString());
        string output=pipe.read_all_as_string();
        paramDest = output;
        return true;
    }
    catch(Exception &e)
    {
        qDebug()<<e.what();
        return false;
    }
}

bool NEncryptionKit::decryptByAES(string paramSource, QString &paramDest)
{
    try
    {
        HashFunction* hash = get_hash("MD5");
        SymmetricKey key = hash->process(mPassword.toStdString());
        SecureVector<byte> raw_iv = hash->process('0'+ mPassword.toStdString());
        InitializationVector iv(raw_iv, 16);
        Pipe pipe(get_cipher("AES-128/CBC/PKCS7", key, iv, DECRYPTION));
        pipe.process_msg(paramSource);
        string output=pipe.read_all_as_string();
        paramDest = QString::fromStdString(output);
        return true;
    }
    catch(Exception &e)
    {
        qDebug()<<e.what();
        return false;
    }
}

void NEncryptionKit::setPassword(QString param_password)
{
    mPassword = param_password;
}

void NEncryptionKit::setSalt(QString param_salt)
{
    // TODO 设置加密盐
}
