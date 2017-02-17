#ifndef NENCRYPTIONKIT_H
#define NENCRYPTIONKIT_H

/**
  * 加解密组件库
  *	作者: daodaoliang
  * 时间: 2016年8月05日
  * 版本: 1.0.1.0
  * 邮箱: daodaoliang@yeah.net
  */

#include "nencryptionkit_global.h"
#include <QCryptographicHash>
#include <QChar>
#include <QObject>
#include <vector>
#include <QByteArray>
#include <string>

using namespace std;

/**
 * @brief The NEncryptionKit class
 * 数据的加解密、签名、校验等组件
 */
class NENCRYPTIONKITSHARED_EXPORT NEncryptionKit : public QObject
{
    Q_OBJECT
public:
    explicit NEncryptionKit(QObject *parent = 0);

public:

    /**
     * @brief getMD5Hash 获取字符串的MD5散列值
     * @param param_data 待转换的数据
     * @return 转换后的散列值
     */
    QString getMD5Hash(const QString &param_data);

    /**
     * @brief getSHAHash 获取字符串的SHA散列值
     * @param param_data 待转换的数据
     * @return 转换后的散列值
     */
    QString getSHAHash(const QString &param_data);

    /**
     * @brief getByKaiser 获取采用凯撒机密的字符串
     * @param param_data 待加密的数据
     * @param param_key 加密秘钥
     * @return 是否加密成功
     */
    bool getByKaiser(QString &param_data,qint8 param_key);

    /**
     * @brief createRSAKey 产生RSA密钥
     * @param paramPubKeyFile 公钥文件存储地址
     * @param paramPriKeyFile 私钥文件存储地址
     * @return
     */
    bool createRSAKey(QString paramPubKeyFile, QString paramPriKeyFile);

    /**
     * @brief getEncryptByRSA 用RSA公钥进行加密
     * @param paramDataSource 需要被加密的数据
     * @param paramDataDest 加密后的数据
     * @param paramPubKey 公钥文件路径
     * @return
     */
    bool getEncryptByRSA(QString paramDataSource, QByteArray &paramDataDest, QString paramPubKeyPath);

    /**
     * @brief decryptionByRSA 用RSA私钥进行解密
     * @param paramDataSource 需要进行解密的数据
     * @param paramDataDest 解密后的数据
     * @param paramPriKeyPath 私钥文件路劲
     * @return
     */
    bool decryptionByRSA(QByteArray paramDataSource, QString &paramDataDest, QString paramPriKeyPath);

    /**
     * @brief getEncryByAES 用AES进行加密
     * @param paramSource 待加密字符串
     * @param paramDest 加密后的字符串
     * @return 是否解密成功
     */
    bool getEncryByAES(QString paramSource, string &paramDest);

    /**
     * @brief decryptByAES 用AES进行解密
     * @param paramSource 待解密字符串
     * @param paramDest 解密后的字符串
     * @return 是否解密成功
     */
    bool decryptByAES(string paramSource, QString &paramDest);

    /**
     * @brief setPassword 设置加密的密钥
     * @param param_password 密钥
     */
    void setPassword(QString param_password);

    /**
     * @brief setSalt 设置加密盐
     * @param param_salt
     */
    void setSalt(QString param_salt);

private:

    /**
     * @brief mPassword 密码
     */
    QString mPassword;
};

#endif // NENCRYPTIONKIT_H

