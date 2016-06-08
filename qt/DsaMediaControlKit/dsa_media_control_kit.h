#ifndef DSA_MEDIA_CONTROL_KIT_H
#define DSA_MEDIA_CONTROL_KIT_H

#include <QWidget>

#include <QMap>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QTreeView>
#include <QTableView>
#include <QAction>
#include <QMenu>
#include <QProgressBar>

#include "ui/audio_widget.h"
#include "ui/multi_track_media_player.h"
#include "ui/multi_preset_controller.h"
#include "ui/sound_file_importer.h"
#include "ui/sound_file_list_view.h"
#include "ui/drop_group_box.h"
#include "db/api.h"
#include "db/handler.h"

class DsaMediaControlKit : public QWidget
{
    Q_OBJECT
public:
    explicit DsaMediaControlKit(QString const& name, QWidget *parent = 0);

    QMenu* getMenu();
    QString const& getStatusMessage() const;
    QProgressBar* getProgressBar() const;

signals:
    void statusMessageUpdated(QString const&);

public slots:

private slots:
    void onAddWidgetAction(bool);
    void createPresetButtonClicked(bool);
    void onProgressChanged(int);
    void onReceivedDrop(const QMimeData*);

private:
    void initWidgets();
    void initLayout();
    void initActions();
    void initMenu();
    void initDB();

    QString control_name_;

    // STATUS
    QString status_message_;
    QProgressBar* progress_bar_;

    // MENU & ACTIONS
    QMap<QString, QAction*> actions_;
    QMenu* main_menu_;

    // WIDGETS
    UI::SoundFileListView* list_view1_;
    UI::SoundFileListView* list_view2_;
    QTreeView* category_view_;
    QTableView* sound_file_view_;
    UI::MultiTrackMediaPlayer* multi_track_player_;
    UI::MultiPresetController* multi_preset_controller_;
    QGroupBox* player_group_;
    UI::DropGroupBox* preset_group_;
    QPushButton* add_button_;
    QPushButton* create_preset_button_;
    UI::SoundFileImporter* sound_file_importer_;
    int id_iterator_;

    // DB handler
    DB::Handler* db_handler_;
};

#endif // DSAMEDIACONTROLKIT_H
