#ifndef RECEIVERFORM_H
#define RECEIVERFORM_H

#include <QDialog>

class DataProvider;
namespace Ui {
class ReceiverForm;
}

class ReceiverForm : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiverForm(DataProvider & p_data, QWidget *parent = 0);
    ~ReceiverForm();
signals:
    void receiverHeightChanged();

public slots:
    void accept();
    void update();
    void commit();

private:
    DataProvider & data;
    Ui::ReceiverForm *ui;
};

#endif // RECEIVERFORM_H
