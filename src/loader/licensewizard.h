#ifndef LICENSEWIZARD_H
#define LICENSEWIZARD_H

#include <QWizard>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QLineEdit;
class QRadioButton;
QT_END_NAMESPACE

namespace Widgets {
class FileChooser;
}

class LicenseWizard : public QWizard
{
    Q_OBJECT

public:
    enum { Page_Intro,
           Page_Evaluate,
           Page_Register,
           Page_Details,
           Page_Conclusion };

    LicenseWizard(QWidget *parent = 0);

private slots:
    void showHelp();
    void currentIdChanged(int id);
};

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

    int nextId() const Q_DECL_OVERRIDE;

private:
    QLabel *topLabel;
    QRadioButton *registerRadioButton;
    QRadioButton *evaluateRadioButton;
};

class EvaluatePage : public QWizardPage
{
    Q_OBJECT

public:
    EvaluatePage(QWidget *parent = 0);

    int nextId() const Q_DECL_OVERRIDE;

private:
    QLabel *nameLabel;
    QLabel *emailLabel;
    QLineEdit *nameLineEdit;
    QLineEdit *emailLineEdit;
};

class RegisterPage : public QWizardPage
{
    Q_OBJECT

public:
    RegisterPage(QWidget *parent = 0);

    int nextId() const Q_DECL_OVERRIDE;

private:
    QLabel *nameLabel;
    QLabel *keyLabel;
    QLineEdit *nameLineEdit;
    Widgets::FileChooser *keyLineEdit;
};

class DetailsPage : public QWizardPage
{
    Q_OBJECT

public:
    DetailsPage(QWidget *parent = 0);

    int nextId() const Q_DECL_OVERRIDE;

private:
    QLabel *companyLabel;
    QLabel *emailLabel;
    QLineEdit *companyLineEdit;
    QLineEdit *emailLineEdit;
};

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

    void initializePage() Q_DECL_OVERRIDE;
    int nextId() const Q_DECL_OVERRIDE;
    void setVisible(bool visible) Q_DECL_OVERRIDE;

private slots:
    void printButtonClicked();

private:
    QLabel *bottomLabel;
    QCheckBox *agreeCheckBox;
};

#endif
