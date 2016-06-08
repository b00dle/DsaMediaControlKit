#include "dsa_media_control_kit.h"

#include <QDebug>
#include <QDir>
#include <QKeySequence>

#include "db/core/api.h"

DsaMediaControlKit::DsaMediaControlKit(QWidget *parent)
    : QWidget(parent)
    , progress_bar_(0)
    , actions_()
    , main_menu_(0)
    , sound_file_view_(0)
    , category_view_(0)
    , multi_preset_controller_()
    , preset_group_(0)
    , create_preset_button_(0)
    , sound_file_importer_(0)
    , db_handler_(0)
{
    initDB();
    initWidgets();
    initLayout();
    initActions();
    initMenu();
}

QMenu *DsaMediaControlKit::getMenu()
{
    return main_menu_;
}

const QString &DsaMediaControlKit::getStatusMessage() const
{
    return status_message_;
}

QProgressBar *DsaMediaControlKit::getProgressBar() const
{
    return progress_bar_;
}

void DsaMediaControlKit::createPresetButtonClicked(bool)
{
    qDebug() << "create Preset Button clicked";
    multi_preset_controller_->addCreator();
}

void DsaMediaControlKit::onProgressChanged(int value)
{
    if(value != 100) {
        if(progress_bar_->isHidden()) {
            progress_bar_->show();
        }
    }
    else {
        progress_bar_->hide();
    }
    progress_bar_->setValue(value);
}

void DsaMediaControlKit::onReceivedDrop(QObject* source, const QMimeData* data)
{
    qDebug() << "received DROP";
    qDebug() << " > from" << source;
    qDebug() << " > text" << data->text();
}

void DsaMediaControlKit::onSelectedCategoryChanged(DB::CategoryRecord *rec)
{
    int id = -1;
    if(rec != 0)
        id = rec->id;

    sound_file_view_->setSoundFiles(db_handler_->getSoundFileRecordsByCategoryId(id));
}

void DsaMediaControlKit::initWidgets()
{
    sound_file_view_ = new SoundFile::SoundFileListView(QList<DB::SoundFileRecord*>(), this);

    progress_bar_ = new QProgressBar;
    progress_bar_->setMaximum(100);
    progress_bar_->setMinimum(0);
    progress_bar_->setValue(100);
    progress_bar_->hide();

    create_preset_button_ = new QPushButton("Create Preset", this);
    multi_preset_controller_ = new Preset::MultiPresetController(this);

    preset_group_ = new Misc::DropGroupBox("Presets:", this);
    preset_group_->setLayout(multi_preset_controller_->layout());

    sound_file_importer_ = new SoundFile::SoundFileImporter(this);

    category_view_ = new Category::TreeView(this);
    category_view_->setCategoryTreeModel(db_handler_->getCategoryTreeModel());

    connect(preset_group_, SIGNAL(receivedDrop(QObject*, const QMimeData*)),
            this, SLOT(onReceivedDrop(QObject*, const QMimeData*)));
    connect(create_preset_button_, SIGNAL(clicked(bool)),
            this, SLOT(createPresetButtonClicked(bool)));
    connect(sound_file_importer_, SIGNAL(folderImported(QList<DB::SoundFile> const&)),
            db_handler_, SLOT(insertSoundFilesAndCategories(QList<DB::SoundFile> const&)));
    connect(db_handler_, SIGNAL(progressChanged(int)),
            this, SLOT(onProgressChanged(int)));
    connect(category_view_, SIGNAL(categorySelected(DB::CategoryRecord*)),
            this, SLOT(onSelectedCategoryChanged(DB::CategoryRecord*)));
}

void DsaMediaControlKit::initLayout()
{
    QHBoxLayout* layout = new QHBoxLayout;

    QHBoxLayout* list_view_layout = new QHBoxLayout;
    list_view_layout->addWidget(sound_file_view_);

    QVBoxLayout* l_layout = new QVBoxLayout;
    l_layout->addWidget(category_view_, 1);
    l_layout->addLayout(list_view_layout, 1);

    QVBoxLayout* r_layout = new QVBoxLayout;
    r_layout->addWidget(create_preset_button_, -1);
    r_layout->addWidget(preset_group_, 1);

    layout->addLayout(l_layout, 1);
    layout->addLayout(r_layout, 1);

    setLayout(layout);
}

void DsaMediaControlKit::initActions()
{
    actions_["Add Sound Folder..."] = new QAction(tr("Add Sound Folder..."), this);
    actions_["Add Sound Folder..."]->setToolTip(tr("Imports a SoundFile folder into the database."));
    actions_["Add Sound Folder..."]->setShortcut(QKeySequence(tr("Ctrl+O")));

    connect(actions_["Add Sound Folder..."] , SIGNAL(triggered(bool)),
            sound_file_importer_, SLOT(startBrowserFolder(bool)));
}

void DsaMediaControlKit::initMenu()
{
    main_menu_ = new QMenu(tr("DsaMediaControlKit"));

    QMenu* add_menu = main_menu_->addMenu(tr("File"));
    add_menu->addAction(actions_["Add Sound Folder..."]);

    main_menu_->addMenu(add_menu);
}

void DsaMediaControlKit::initDB()
{
    QString db_path = QDir::currentPath() + "/../../db/dsamediacontrolkit.db";
    DB::Core::Api* db_api = new DB::Core::Api(db_path, this);
    db_handler_ = new DB::Handler(db_api, this);
}
