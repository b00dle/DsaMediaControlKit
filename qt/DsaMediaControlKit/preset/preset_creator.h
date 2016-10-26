#ifndef PRESETCREATOR_H
#define PRESETCREATOR_H

#include <QWidget>

#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>

namespace Preset {

class PresetCreator : public QWidget
{
    Q_OBJECT
public:
    explicit PresetCreator(QWidget *parent = 0);
    ~PresetCreator();

    QString const getText();

signals:
    void closed();
    void created(QString const&);

public slots:
    //void onDoneClicked(bool);
    void onClosedClicked(bool);
    void onCreateClicked(bool);

private:
    void initWidgets();
    void initLayout();

    QLineEdit* edit_;
    QPushButton* close_button_;
    QPushButton* create_button_;
    QGroupBox* box_;
};

}// namespace Preset

#endif // PRESETCREATOR_H
