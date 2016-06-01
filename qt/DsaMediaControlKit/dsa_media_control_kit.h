#ifndef DSA_MEDIA_CONTROL_KIT_H
#define DSA_MEDIA_CONTROL_KIT_H

#include <QWidget>

#include <QMap>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QTreeView>
#include <QTableView>

#include "ui/audio_widget.h"
#include "ui/multi_track_media_player.h"
#include "ui/multi_preset_controller.h"
#include "ui/sound_file_importer.h"
#include "db/api.h"
#include "db/handler.h"

class DsaMediaControlKit : public QWidget
{
    Q_OBJECT
public:
    explicit DsaMediaControlKit(QString const& name, QWidget *parent = 0);

signals:

public slots:

private slots:
    void addButtonClicked(bool);
    void createPresetButtonClicked(bool);

private:
    void initWidgets();
    void initLayout();
    void initDB();

    QString control_name_;
    // WIDGETS
    QTreeView* category_view_;
    QTableView* sound_file_view_;
    UI::MultiTrackMediaPlayer* multi_track_player_;
    UI::MultiPresetController* multi_preset_controller_;
    QGroupBox* player_group_;
    QGroupBox* preset_group_;
    QPushButton* add_button_;
    QPushButton* create_preset_button_;
    UI::SoundFileImporter* sound_file_importer_;
    int id_iterator_;

    // DB handler
    DB::Handler* db_handler_;
};

#endif // DSAMEDIACONTROLKIT_H
