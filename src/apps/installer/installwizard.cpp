#include <QtWidgets>
#include <QPrinter>
#include <QPrintDialog>

#include <utils/systemid.h>
#include <utils/emailvalidator.h>
#include <widgets/filechooser.h>

#include "installer/installer_version.h"
#include "installer_global.h"
#include "installwizard.h"

Q_LOGGING_CATEGORY(installerLog, "athletic.loader")

using namespace Utils;
using namespace Widgets;

InstallWizard::InstallWizard(QWidget *parent)
    : QWizard(parent)
{
    setPage(Page_Intro, new IntroPage);
    setPage(Page_Evaluate, new EvaluatePage);
    setPage(Page_Register, new RegisterPage);
    setPage(Page_Details, new DetailsPage);
    setPage(Page_Conclusion, new ConclusionPage);

    setStartId(Page_Intro);
    setWizardStyle(QWizard::ModernStyle);

    setOption(HaveCustomButton1, true);
    setButtonText(CustomButton1, tr("Settings"));


    setPixmap(QWizard::LogoPixmap, QPixmap( QLatin1String(":/images/logo.png") ));

    setWindowTitle(tr("Athletic.Cloud installer"));

    connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(currentIdChanged(int)));
}

void InstallWizard::customButtonClicked(int which) {}

void InstallWizard::currentIdChanged(int id)
{
//    if ( id == Page_Conclusion ) {
        SystemId sysId;
        qCDebug(installerLog) << "System(name): " << sysId.getMachineName();
        qCDebug(installerLog) << "System(cpu): "<< sysId.getCpuHash();
        qCDebug(installerLog) << "System(volume): "<< sysId.getVolumeHash();
        qCDebug(installerLog) << "System(mac): "<< sysId.getMacHash();

        /*
         * evaluate.name
         * evaluate.email
         * register.name
         * register.key
         *
         * details.company
         * details.email
         * details.postal
        */


//        QString evalName = field("evaluate.name");
//        QString evalName = field("evaluate.name");
//    }
}


IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr( "Introduction" ));
    setPixmap(QWizard::WatermarkPixmap, QPixmap( QLatin1String(":/images/watermark.png") ));

    topLabel = new QLabel(tr("This wizard will help you install your copy of "
                             "<i>%1</i><br/> or start "
                             "evaluating the product.").arg( QLatin1String(Core::Constants::PRODUCT_NAME_C) ));
    topLabel->setWordWrap(true);

    registerRadioButton = new QRadioButton(tr( "&Register your copy" ));
    evaluateRadioButton = new QRadioButton(tr( "&Evaluate the product for 30 days" ));
    registerRadioButton->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addWidget(registerRadioButton);
    layout->addWidget(evaluateRadioButton);
    setLayout(layout);
}

int IntroPage::nextId() const
{
    if (evaluateRadioButton->isChecked()) {
        return InstallWizard::Page_Evaluate;
    } else {
        return InstallWizard::Page_Register;
    }
}

EvaluatePage::EvaluatePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Evaluate <i>%1</i>").arg( QLatin1String(Core::Constants::PRODUCT_NAME_C) ));
    setSubTitle(tr("Please fill both fields. Make sure to provide a valid "
                   "email address (e.g., email@example.com)."));

    nameLabel = new QLabel(tr("N&ame:"));
    nameLineEdit = new QLineEdit;

    nameLabel->setBuddy(nameLineEdit);

    emailLabel = new QLabel(tr("&Email address:"));
    emailLineEdit = new QLineEdit;
    emailLineEdit->setValidator(new EmailValidator(this));
    emailLabel->setBuddy(emailLineEdit);

    registerField( QLatin1String("evaluate.name*"), nameLineEdit);
    registerField( QLatin1String("evaluate.email*") , emailLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(emailLabel, 1, 0);
    layout->addWidget(emailLineEdit, 1, 1);
    setLayout(layout);
}

int EvaluatePage::nextId() const
{
    return InstallWizard::Page_Conclusion;
}

RegisterPage::RegisterPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Register Your Copy of <i>Super Product One</i>&trade;"));
    setSubTitle(tr("If you have a product key, please fill in "
                   "the appropriate field."));

    nameLabel = new QLabel(tr("N&ame:"));
    nameLineEdit = new QLineEdit;
    nameLabel->setBuddy(nameLineEdit);

    keyLabel = new QLabel(tr("&Product key:"));
    keyLineEdit = new FileChooser(this);
    keyLabel->setBuddy(keyLineEdit);

    registerField( QLatin1String("register.name*"), nameLineEdit);
    registerField( QLatin1String("register.key"), keyLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(keyLabel, 1, 0);
    layout->addWidget(keyLineEdit, 1, 1);
    setLayout(layout);
}

int RegisterPage::nextId() const
{
    if (keyLineEdit->file().isEmpty()) {
        return InstallWizard::Page_Details;
    } else {
        return InstallWizard::Page_Conclusion;
    }
}

DetailsPage::DetailsPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Fill In Your Details"));
    setSubTitle(tr("Please fill all three fields. Make sure to provide a valid "
                   "email address (e.g., tanaka.aya@example.co.jp)."));

    companyLabel = new QLabel(tr("&Licensee name:"));
    companyLineEdit = new QLineEdit;
    companyLabel->setBuddy(companyLineEdit);

    emailLabel = new QLabel(tr("&Email address:"));
    emailLineEdit = new QLineEdit;
    emailLineEdit->setValidator(new EmailValidator(this));
    emailLabel->setBuddy(emailLineEdit);

    registerField( QLatin1String("details.company*"), companyLineEdit);
    registerField( QLatin1String("details.email*"), emailLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(companyLabel, 0, 0);
    layout->addWidget(companyLineEdit, 0, 1);
    layout->addWidget(emailLabel, 1, 0);
    layout->addWidget(emailLineEdit, 1, 1);
    setLayout(layout);
}

int DetailsPage::nextId() const
{
    return InstallWizard::Page_Conclusion;
}

ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Complete Your Registration"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap( QLatin1String(":/images/watermark.png") ));

    bottomLabel = new QLabel;
    bottomLabel->setWordWrap(true);

    agreeCheckBox = new QCheckBox(tr("I agree to the terms of the license"));

    registerField(QLatin1String("conclusion.agree*"), agreeCheckBox);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(bottomLabel);
    layout->addWidget(agreeCheckBox);
    setLayout(layout);
}

int ConclusionPage::nextId() const
{
    return -1;
}

void ConclusionPage::initializePage()
{
    QString licenseText;

    if (wizard()->hasVisitedPage(InstallWizard::Page_Evaluate)) {
        licenseText = tr("<u>Evaluation License Agreement:</u> "
                         "You can use this software for 30 days and make one "
                         "backup, but you are not allowed to distribute it.");
    } else if (wizard()->hasVisitedPage(InstallWizard::Page_Details)) {
        licenseText = tr("<u>First-Time License Agreement:</u> "
                         "You can use this software subject to the license "
                         "you will receive by email.");
    } else {
        licenseText = tr("<u>License Agreement:</u> "
                         "This software is licensed under the terms of your "
                         "current license.");
    }
    bottomLabel->setText(licenseText);
}

void ConclusionPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);

    if (visible) {
        wizard()->setButtonText(QWizard::CustomButton1, tr("&Print"));
        wizard()->setOption(QWizard::HaveCustomButton1, true);
        connect(wizard(), &QWizard::customButtonClicked,
                this, &ConclusionPage::printButtonClicked);
    } else {
        wizard()->setOption(QWizard::HaveCustomButton1, false);
        disconnect(wizard(), &QWizard::customButtonClicked,
                   this, &ConclusionPage::printButtonClicked);
    }
}

void ConclusionPage::printButtonClicked()
{
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted)
        QMessageBox::warning(this, tr("Print License"),
                             tr("As an environmentally friendly measure, the "
                                "license text will not actually be printed."));
#endif
}
