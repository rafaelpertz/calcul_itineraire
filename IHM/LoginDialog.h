#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QMessageBox>
using namespace std;

class LoginDialog : public QDialog {
    Q_OBJECT
    public:
        LoginDialog(QWidget* parent = nullptr);

        ~LoginDialog(){};

        // Getter 
        void getResult(string& host, string& database, string& username, string& password);

    public slots:
        void slotLogin();


    private:
       // QDialog (visual) attributes
       QLabel* hostLabel;
       QLabel* databaseLabel;
       QLabel* usernameLabel;
       QLabel* passwordLabel;
       QLineEdit* hostLineEdit;
       QLineEdit* usernameLineEdit;
       QLineEdit* databaseLineEdit;
       QLineEdit* passwordLineEdit;
       QPushButton* loginButton;
       QPushButton* cancelButton;

       // LoginDialog attributes
       QString host;
       QString database;
       QString username;
       QString password;
};



#endif
