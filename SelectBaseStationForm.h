#ifndef SELECTBASESTATIONFORM_H
#define SELECTBASESTATIONFORM_H

#include <QDialog>
#include <memory>

namespace Ui {
class SelectBaseStationForm;
}
class DataProvider;
class QStringListModel;

class SelectBaseStationForm : public QDialog
{
    Q_OBJECT

public:
    explicit SelectBaseStationForm(const DataProvider & p_data,
                                   QWidget *parent = 0);
    ~SelectBaseStationForm();
    std::string getSelectedBaseStation();

signals:
    void baseStationSelected();

public slots:
    void accept();
    void update();
    void commit();

private:
    const DataProvider & data;
    std::string selectedBaseStation;
    Ui::SelectBaseStationForm *ui;
    QStringListModel * model;
};

#endif // SELECTBASESTATIONFORM_H
