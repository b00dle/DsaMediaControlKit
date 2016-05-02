#include "dsa_media_control_kit.h"

#include <QDebug>

DsaMediaControlKit::DsaMediaControlKit(QWidget *parent)
    : QWidget(parent)
    , multi_track_player_(0)
    , db_api_(0)
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
    QString db_path = "C:\\Users\\Basti-Laptop\\Documents\\Qt\\DsaMediaControlKit\\db\\dsamediacontrolkit.db";
    db_api_ = new DB::Api(db_path, this);

    QSqlTableModel* model = db_api_->getCategoryTable();

    for(int r = 0; r < model->rowCount(); ++r) {
        QString data_str = "";
        for(int c = 0; c < model->columnCount(); ++c) {
            if(c != 0)
                data_str += " | ";
            data_str += model->data(model->index(r, c)).toString();
        }
        qDebug() << data_str;
    }
}
