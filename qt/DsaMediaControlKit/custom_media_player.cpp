#include "custom_media_player.h"
#include <random>

CustomMediaPlayer::CustomMediaPlayer(QObject* parent)
    : QMediaPlayer(parent)
    , current_content_index_(0)
    , delay_flag_(false)
    , delay_(0)
    , delay_timer_(0)
{
    delay_timer_ = new QTimer(this);
    connect(delay_timer_, SIGNAL(timeout()),
            this, SLOT(delayIsOver()));
    qDebug()<< "Playlist:" << getCustomPlaylist();
}

void CustomMediaPlayer::play()
{

    Playlist::Playlist* playlist = getCustomPlaylist();
    if(playlist){
        Playlist::Settings* settings = playlist->settings();

        // if delay interval is turned on
        if (settings->order == Playlist::PlayOrder::ORDERED){
            qDebug() << "Check loop";
            if (settings->loop_flag){
                qDebug() << "loop";
                playlist->setPlaybackMode(QMediaPlaylist::Loop);
            }else if (!settings->loop_flag){
                qDebug() << "no loop";
                playlist->setPlaybackMode(QMediaPlaylist::Sequential);
            }
        } else if (settings->order == Playlist::PlayOrder::SHUFFLE){

            playlist->setPlaybackMode(QMediaPlaylist::Random);

        } else if (settings->order == Playlist::PlayOrder::WEIGTHED){

            // TO DO implement weighted
            QMediaPlayer::pause();
        }

        qDebug() << "Check Interval";
        if (settings->interval_flag){
            qDebug() << "Interval turned on";
            int min = settings->min_delay_interval;
            int max = settings->max_delay_interval;

            std::random_device rd;     // only used once to initialise (seed) engine
            std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
            std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

            delay_ = uni(rng);
            qDebug() << "delay"<<delay_;
            delay_flag_ = true;
            //delay_ = min + (rand() % (int)(max - min + 1))

            //playlist->setPlaybackMode(QM);
            QMediaPlayer::play();
            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        } else {
            delay_flag_ = false;
            qDebug() << "Interval turned off";
            QMediaPlayer::play();

        }
    }

    /*if (playlist()->settings()->interval_flag){

        } else if (playlist()->settings()->)
    }
    */
}

void CustomMediaPlayer::setPlaylist(Playlist::Playlist *playlist)
{
    qDebug() << "setting playlist in custom player";
    connect(playlist, SIGNAL(currentIndexChanged(int)),
            this, SLOT(currentMediaIndexChanged(int)) );
    QMediaPlayer::setPlaylist(playlist);
}

void CustomMediaPlayer::delayIsOver()
{
    qDebug() << "delay is over";
    delay_timer_->stop();
    play();
}

void CustomMediaPlayer::currentMediaIndexChanged(int position)
{
    qDebug()<< "song changed";
    current_content_index_ = position;
    if (delay_flag_){
        delay_timer_->start(delay_*1000);
        qDebug() << "started delay " << delay_;
    }
}


Playlist::Playlist *CustomMediaPlayer::getCustomPlaylist() const
{

    Playlist::Playlist* pl = qobject_cast<Playlist::Playlist*>( playlist() );
    if(pl){
        return pl;
    } else {
        return nullptr;
    }
}

