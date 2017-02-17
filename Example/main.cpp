#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include "nencryptionkit.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"******************************************测试用例开始*****************************************************";
    NEncryptionKit test_instance;
    qDebug()<<"----------------------------MD5测试开始----------------------------";
    QString test_case_001("I am daodaoliang");
    QString test_encry_str = test_instance.getMD5Hash(test_case_001);
    qDebug()<<"MD5前的字符串:" << test_case_001;
    qDebug()<<"MD5后的字符串:" << test_encry_str;
    qDebug()<<"----------------------------MD5测试结束----------------------------";

    qDebug()<<"----------------------------SHA测试开始----------------------------";
    QString test_case_002("I am nami");
    QString test_encry_str_002 = test_instance.getSHAHash(test_case_002);
    qDebug()<<"SHA前的字符串:" << test_case_002;
    qDebug()<<"SHA后的字符串:" << test_encry_str_002;
    qDebug()<<"----------------------------SHA测试结束----------------------------";

    qDebug()<<"----------------------------Kaiser测试开始-------------------------";
    QString test_case_003("I am wangxiaowei");
    qint8 test_case_key(7);
    QString test_encry_str_003 = test_case_003;
    bool ret = test_instance.getByKaiser(test_case_003, test_case_key);
    qDebug()<<"加密是否成功:"<<ret;
    qDebug()<<"Kaiser前的字符串:" << test_encry_str_003;
    qDebug()<<"Kaiser后的字符串:" << test_case_003;
    ret = test_instance.getByKaiser(test_case_003, -test_case_key);
    qDebug()<<"解密是否成功:"<<ret;
    qDebug()<<"解密后的字符串:" << test_case_003;
    qDebug()<<"----------------------------Kaiser测试结束-------------------------";

    qDebug()<<"----------------------------AES文件测试开始-------------------------";
    QString test_case_005("iamdaodaoliang");
    string test_case_006;
    QString test_case_007;
    test_instance.setPassword(QString("IamdaodaoliangSecret"));
    ret = test_instance.getEncryByAES(test_case_005,test_case_006);
    qDebug()<<"AES加密成功:"<<ret;
    qDebug()<<"加密前的数据:"<<test_case_005;
    qDebug()<<"加密后的数据:"<<QString::fromStdString(test_case_006);
    ret = test_instance.decryptByAES(test_case_006,test_case_007);
    qDebug()<<"AES解密成功:"<<ret;
    qDebug()<<"解密后的数据:"<<test_case_007;
    qDebug()<<"----------------------------AES文件测试结束-------------------------";

    qDebug()<<"----------------------------RSA文件测试开始-------------------------";
    QString test_case_pub = QCoreApplication::applicationDirPath() + "/daodaoliang_test.pub";
    QString test_case_pri = QCoreApplication::applicationDirPath() + "/daodaoliang_test.private";
    ret = test_instance.createRSAKey(test_case_pub, test_case_pri);
    qDebug()<<"是否产生密钥文件成功:"<<ret;
    QByteArray test_encrypt_str;
    QString test_decrypt_str;
    ret = test_instance.getEncryptByRSA("I am daodaoliang, my daughter is nami", test_encrypt_str, test_case_pub);
    qDebug()<<"RSA签名成功:"<<ret;
    qDebug()<<"RSA签名后的数据:"<<QString(test_encrypt_str);
    ret = test_instance.decryptionByRSA(test_encrypt_str,test_decrypt_str, test_case_pri);
    qDebug()<<"RSA解密成功:"<<ret;
    qDebug()<<"RSA解密后的数据:"<<test_decrypt_str;
    qDebug()<<"----------------------------RSA文件测试结束-------------------------";

    qDebug()<<"******************************************测试用例结束*****************************************************";
    return a.exec();
}
