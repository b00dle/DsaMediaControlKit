#include "dsa_media_control_kit.h"
#include <QDebug>
#include <QDir>

DsaMediaControlKit::DsaMediaControlKit(QString const& name, QWidget *parent)
    : QWidget(parent)
    , control_name_(name)
    , list_view1_(0)
    , list_view2_(0)
    , category_view_(0)
    , sound_file_view_(0)
    , multi_track_player_(0)
    , multi_preset_controller_()
    , player_group_(0)
    , preset_group_(0)
    , add_button_(0)
    , create_preset_button_(0)
    , sound_file_importer_(0)
    , id_iterator_(0)
    , db_handler_(0)
{
    initDB();
    initWidgets();
    initLayout();
}

void DsaMediaControlKit::addButtonClicked(bool)
{
    multi_track_player_->addTrack(id_iterator_);
    ++id_iterator_;
}

void DsaMediaControlKit::createPresetButtonClicked(bool)
{
    qDebug() << "create Preset Button clicked";
    multi_preset_controller_->addCreator();

}

void DsaMediaControlKit::initWidgets()
{
    QList<DB::SoundFileRecord*> temp;
    list_view2_ = new UI::SoundFileListView(temp,this);

    temp.append(db_handler_->getSoundFileTableModel()->getSoundFileByRow(0));
    temp.append(db_handler_->getSoundFileTableModel()->getSoundFileByRow(1));
    temp.append(db_handler_->getSoundFileTableModel()->getSoundFileByRow(2));
    temp.append(db_handler_->getSoundFileTableModel()->getSoundFileByRow(3));
    temp.append(db_handler_->getSoundFileTableModel()->getSoundFileByRow(4));

    list_view1_ = new UI::SoundFileListView(temp, this);


    add_button_ = new QPushButton("Add Track", this);
    create_preset_button_ = new QPushButton("Create Preset", this);
    multi_track_player_ = new UI::MultiTrackMediaPlayer(this);
    multi_preset_controller_ = new UI::MultiPresetController(this);

    player_group_ = new QGroupBox(this);
    player_group_->setTitle(control_name_);
    player_group_->setLayout(multi_track_player_->layout());

    preset_group_ = new QGroupBox(this);
    preset_group_->setTitle("Presets:");
    preset_group_->setLayout(multi_preset_controller_->layout());

    sound_file_importer_ = new UI::SoundFileImporter(this);

    category_view_ = new QTreeView(this);
    category_view_->setModel(db_handler_->getCategoryTreeModel());

    sound_file_view_ = new QTableView(this);
    sound_file_view_->setModel(db_handler_->getSoundFileTableModel());

    connect(add_button_, SIGNAL(clicked(bool)),
            this, SLOT(addButtonClicked(bool)));
    connect(create_preset_button_, SIGNAL(clicked(bool)),
            this, SLOT(createPresetButtonClicked(bool)));
    connect(sound_file_importer_, SIGNAL(folderImported(QList<DB::SoundFile> const&)),
            db_handler_, SLOT(insertSoundFilesAndCategories(QList<DB::SoundFile> const&)));
}

void DsaMediaControlKit::initLayout()
{
    QHBoxLayout* layout = new QHBoxLayout;

    QHBoxLayout* list_view_layout = new QHBoxLayout;
    list_view_layout->addWidget(list_view1_);
    list_view_layout->addWidget(list_view2_);

    QVBoxLayout* l_layout = new QVBoxLayout;
    l_layout->addWidget(category_view_, 2);
    l_layout->addWidget(sound_file_view_, 2);
    l_layout->addLayout(list_view_layout, 1);

    QVBoxLayout* r_layout = new QVBoxLayout;
    r_layout->addWidget(sound_file_importer_, -1);
    r_layout->addWidget(add_button_, -1);
    r_layout->addWidget(create_preset_button_, -1);
    r_layout->addWidget(player_group_, 1);
    r_layout->addWidget(preset_group_, 1);

    layout->addLayout(l_layout, 1);
    layout->addLayout(r_layout, 1);

    setLayout(layout);
}

void DsaMediaControlKit::initDB()
{
    QString db_path = QDir::currentPath() + "/../../db/dsamediacontrolkit.db";
    DB::Api* db_api = new DB::Api(db_path, this);
    db_handler_ = new DB::Handler(db_api, this);
}
