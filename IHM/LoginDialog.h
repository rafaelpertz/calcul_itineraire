#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>

#include <string>

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
	void getResult( std::string& host, std::string& base,
        std::string& username, std::string& password );

// Slot function
public slots:
    void login();

private:
    QLineEdit *hostEditLine;
    QLineEdit *baseEditLine;
    QLineEdit *userEditLine;
    QLineEdit *pwdEditLine;

    QString hostname;
    QString basename;
    QString username;
    QString password;
};
#endif
