#ifndef DSA_MEDIA_CONTROL_KIT_H
#define DSA_MEDIA_CONTROL_KIT_H

#include <QWidget>

#include <QMap>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>

#include "ui/audio_widget.h"
#include "ui/multi_track_media_player.h"

class DsaMediaControlKit : public QWidget
{
    Q_OBJECT
public:
    explicit DsaMediaControlKit(QString const& name, QWidget *parent = 0);

signals:

public slots:

private slots:
    void addButtonClicked(bool);

private:
    void initWidgets();
    void initLayout();

    QString control_name_;
    UI::MultiTrackMediaPlayer* multi_track_player_;
    QGroupBox* player_group_;
    QPushButton* add_button_;
    int id_iterator_;
};

#endif // DSAMEDIACONTROLKIT_H
