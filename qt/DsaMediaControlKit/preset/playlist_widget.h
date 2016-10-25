#ifndef PRESET_PLAYLIST_WIDGET_H
#define PRESET_PLAYLIST_WIDGET_H

#include <QWidget>

#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>

#include "playlist_old.h"
#include "playlist_settings_widget.h"
#include "sound_file/list_view.h"


namespace Preset {

class PlaylistWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlaylistWidget(QString name = "playlist", QWidget *parent = 0, int id = -1);
    explicit PlaylistWidget(PlaylistOld* playlist, QWidget *parent = 0, int id = -1);
    explicit PlaylistWidget(QList<DB::SoundFileRecord* > const& sound_files, QWidget *parent = 0, int id = -1);
    ~PlaylistWidget();

signals:
    void closed(int);

public slots:
    void onClosedClicked(bool);

private slots:
    void onSettingsButtonClicked(bool);


private:
    void initWidgets();
    void initLayout();


    int id_;
    PlaylistOld* playlist_;
    PlaylistSettingsWidget* playlist_settings_widget_;
    QPushButton* close_button_;
    QPushButton* settings_button_;
    QLineEdit* label_;
    SoundFile::ListView* list_view_;
    QGroupBox* box_;

};

} // namespace Preset

#endif // PRESET_PLAYLIST_WIDGET_H
