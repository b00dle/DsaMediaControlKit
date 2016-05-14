#include "dsa_media_control_kit.h"

#include <QDebug>
#include <QDir>

DsaMediaControlKit::DsaMediaControlKit(QWidget *parent)
    : QWidget(parent)
    , multi_track_player_(0)
    , db_handler_(0)
    , player_group_(0)
    , add_button_(0)
    , sound_file_importer_(0)
    , id_iterator_(0)
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

void DsaMediaControlKit::initWidgets()
{
    add_button_ = new QPushButton("Add Track", this);
    multi_track_player_ = new UI::MultiTrackMediaPlayer(this);
    player_group_ = new QGroupBox(this);
    player_group_->setLayout(multi_track_player_->layout());
    sound_file_importer_ = new UI::SoundFileImporter(this);

    connect(add_button_, SIGNAL(clicked(bool)),
            this, SLOT(addButtonClicked(bool)));
    connect(sound_file_importer_, SIGNAL(folderImported(QList<DB::SoundFile> const&)),
            db_handler_, SLOT(insertSoundFiles(QList<DB::SoundFile> const&)));
}

void DsaMediaControlKit::initLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(sound_file_importer_, -1);
    layout->addWidget(add_button_, -1);
    layout->addWidget(player_group_, 10000);

    setLayout(layout);
}

void DsaMediaControlKit::initDB()
{
    QString db_path = QDir::currentPath() + "/../../db/dsamediacontrolkit.db";
    DB::Api* db_api = new DB::Api(db_path, this);
    db_handler_ = new DB::Handler(db_api, this);
}
