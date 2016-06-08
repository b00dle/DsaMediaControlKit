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

#include "preset/multi_preset_controller.h"
#include "misc/drop_group_box.h"
#include "sound_file/sound_file_importer.h"
#include "sound_file/sound_file_list_view.h"
#include "db/handler.h"
#include "category/tree_view.h"

class DsaMediaControlKit : public QWidget
{
    Q_OBJECT
public:
    explicit DsaMediaControlKit(QWidget *parent = 0);

    QMenu* getMenu();
    QString const& getStatusMessage() const;
    QProgressBar* getProgressBar() const;

signals:
    void statusMessageUpdated(QString const&);

public slots:

private slots:
    void createPresetButtonClicked(bool);
    void onProgressChanged(int);
    void onReceivedDrop(QObject*, const QMimeData*);
    void onSelectedCategoryChanged(DB::CategoryRecord* rec);

private:
    void initWidgets();
    void initLayout();
    void initActions();
    void initMenu();
    void initDB();

    // STATUS
    QString status_message_;
    QProgressBar* progress_bar_;

    // MENU & ACTIONS
    QMap<QString, QAction*> actions_;
    QMenu* main_menu_;

    // WIDGETS
    SoundFile::SoundFileListView* sound_file_view_;
    Category::TreeView* category_view_;
    Preset::MultiPresetController* multi_preset_controller_;
    Misc::DropGroupBox* preset_group_;
    QPushButton* create_preset_button_;
    SoundFile::SoundFileImporter* sound_file_importer_;

    // DB handler
    DB::Handler* db_handler_;
};

#endif // DSAMEDIACONTROLKIT_H
