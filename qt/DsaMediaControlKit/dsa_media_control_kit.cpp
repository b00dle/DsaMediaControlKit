#include "dsa_media_control_kit.h"

#include <QDebug>
#include <QDir>
#include <QKeySequence>

#include "db/core/api.h"
#include "resources/resources.h"
#include "misc/json_mime_data_parser.h"

DsaMediaControlKit::DsaMediaControlKit(QWidget *parent)
    : QWidget(parent)
    , progress_bar_(0)
    , actions_()
    , main_menu_(0)
    , sound_file_view_(0)
    , category_view_(0)
    , preset_view_(0)
    , sound_file_importer_(0)
    , center_h_splitter_(0)
    , left_v_splitter_(0)
    , left_box_(0)
    , right_box_(0)
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

void DsaMediaControlKit::onSelectedCategoryChanged(DB::CategoryRecord *rec)
{
    int id = -1;
    if(rec != 0)
        id = rec->id;

    sound_file_view_->setSoundFiles(db_handler_->getSoundFileRecordsByCategoryId(id));
}

void DsaMediaControlKit::onDeleteDatabase()
{
    db_handler_->deleteAll();
    category_view_->selectRoot();
}

void DsaMediaControlKit::initWidgets()
{
    sound_file_view_ = new SoundFile::MasterView(
        db_handler_->getSoundFileTableModel()->getSoundFiles(),
        this
    );

    progress_bar_ = new QProgressBar;
    progress_bar_->setMaximum(100);
    progress_bar_->setMinimum(0);
    progress_bar_->setValue(100);
    progress_bar_->hide();

    preset_view_ = new TwoD::GraphicsView(this);

    sound_file_importer_ = new SoundFile::ResourceImporter(this);

    category_view_ = new Category::TreeView(this);
    category_view_->setCategoryTreeModel(db_handler_->getCategoryTreeModel());

    left_box_ = new QGroupBox(this);
    right_box_ = new QGroupBox(this);

    left_v_splitter_ = new QSplitter(Qt::Vertical, this);
    left_v_splitter_->addWidget(category_view_);
    left_v_splitter_->addWidget(sound_file_view_);
    left_v_splitter_->setStretchFactor(0, 2);
    left_v_splitter_->setStretchFactor(1, 8);

    center_h_splitter_ = new QSplitter(Qt::Horizontal);
    center_h_splitter_->addWidget(left_box_);
    center_h_splitter_->addWidget(right_box_);
    center_h_splitter_->setStretchFactor(0, 0);
    center_h_splitter_->setStretchFactor(1, 10);

    connect(sound_file_importer_, SIGNAL(folderImported(QList<DB::SoundFile> const&)),
            db_handler_, SLOT(insertSoundFilesAndCategories(QList<DB::SoundFile> const&)));
    connect(sound_file_importer_, SIGNAL(folderImported()),
            category_view_, SLOT(selectRoot()));
    connect(db_handler_, SIGNAL(progressChanged(int)),
            this, SLOT(onProgressChanged(int)));
    connect(category_view_, SIGNAL(categorySelected(DB::CategoryRecord*)),
            this, SLOT(onSelectedCategoryChanged(DB::CategoryRecord*)));
    connect(sound_file_view_, SIGNAL(deleteSoundFileRequested(int)),
            db_handler_->getSoundFileTableModel(), SLOT(deleteSoundFile(int)));
    connect(db_handler_->getSoundFileTableModel(), SIGNAL(aboutToBeDeleted(DB::SoundFileRecord*)),
            sound_file_view_, SLOT(onSoundFileAboutToBeDeleted(DB::SoundFileRecord*)));
}

void DsaMediaControlKit::initLayout()
{
    QHBoxLayout* layout = new QHBoxLayout;

    // left layout
    QVBoxLayout* l_layout = new QVBoxLayout;
    l_layout->addWidget(left_v_splitter_);
    left_box_->setLayout(l_layout);

    // right layout
    QVBoxLayout* r_layout = new QVBoxLayout;
    r_layout->addWidget(preset_view_);
    right_box_->setLayout(r_layout);

    layout->addWidget(center_h_splitter_);

    setLayout(layout);
}

void DsaMediaControlKit::initActions()
{
    actions_["Add Sound Folder..."] = new QAction(tr("Add Sound Folder..."), this);
    actions_["Add Sound Folder..."]->setToolTip(tr("Imports a SoundFile folder into the database."));
    actions_["Add Sound Folder..."]->setShortcut(QKeySequence(tr("Ctrl+O")));

    actions_["Delete Database Contents..."] = new QAction(tr("Delete Database Contents..."), this);
    actions_["Delete Database Contents..."]->setToolTip(tr("Deletes all contents from application database."));

    connect(actions_["Add Sound Folder..."] , SIGNAL(triggered(bool)),
            sound_file_importer_, SLOT(startBrowserFolder(bool)));
    connect(actions_["Delete Database Contents..."], SIGNAL(triggered()),
            this, SLOT(onDeleteDatabase()));
}

void DsaMediaControlKit::initMenu()
{
    main_menu_ = new QMenu(tr("DsaMediaControlKit"));

    QMenu* add_menu = main_menu_->addMenu(tr("File"));
    add_menu->addAction(actions_["Add Sound Folder..."]);
    add_menu->addSeparator();
    add_menu->addAction(actions_["Delete Database Contents..."]);

    main_menu_->addMenu(add_menu);
}

void DsaMediaControlKit::initDB()
{
    DB::Core::Api* db_api = new DB::Core::Api(Resources::DATABASE_PATH, this);
    db_handler_ = new DB::Handler(db_api, this);
}
